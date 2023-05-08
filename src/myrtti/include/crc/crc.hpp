/**
 * Copyright 2019 Sam Robert Belliveau
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall
 * be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

// Github:
// https://gist.github.com/Sam-Belliveau/72ba4a8710324ce7a1ac1789d64ec831

#ifndef SAM_BELLIVEAUS_CRC_IMPLEMENTATION_HPP
#define SAM_BELLIVEAUS_CRC_IMPLEMENTATION_HPP 1

#include <type_traits> // get information about type
#include <iterator> // Iterator traits
#include <cstdint> // fixed width ints
#include <utility> // SFINAE

namespace crc
{
    // Underlying types for calculations
    using byte = std::uint8_t;
    using u8   = std::uint8_t;
    using u16  = std::uint16_t;
    using u32  = std::uint32_t;
    using u64  = std::uint64_t;
    using size = std::size_t;

    // Takes a function and precalculates all
    // of the possible 8-bit inputs for it
    template<class Generator>
    class MemTable
    {
    public:
        // type in which the MemTable takes inpus
        using input_type = const byte;

        // max value for MemTable
        static constexpr size max = 0x100;

        // get return type of generator
        using return_type = typename std::invoke_result_t<Generator, const byte>;

    private:
        // store PolyTable
        return_type table_[max];

    public:
        // generate PolyTable
        constexpr MemTable() noexcept : table_()
        {
            Generator gen;
            for(size i = 0; i < max; ++i)
            { table_[i] = gen(i); }
        }

        // access mem_array
        constexpr return_type operator()(input_type index) const noexcept
        { return table_[index]; }
    };

    // Takes return type and polynomial
    // and makes a crc PolyTable generator
    template<class ReturnType, ReturnType Polynomial>
    struct CRCTableGenerator
    {
        constexpr CRCTableGenerator() noexcept {}
        constexpr ReturnType operator()(const byte index) const noexcept
        {
            ReturnType out = index;

            for(size bit = 0; bit < 8; ++bit)
                out = (out >> 1) ^ ((out & 1) ? (Polynomial) : (0));

            return out;
        }
    };

    // CRCEngine that takes in a
    // polynomial generator as a template
    template<class MTable>
    class CRCBaseEngine
    {
    public:
        using size_type = size;
        using return_type = typename MTable::return_type;

    private: // Create Memorization Table
        static constexpr MTable PolyTable = MTable();
        static constexpr return_type InitState = 0;
        static constexpr return_type FinalXOR = 0;

    private:
        // Add Single Byte
        template<class T, std::enable_if_t<(sizeof(T) == 1), int> Size = 1>
        static constexpr inline return_type AddData(const return_type state, const T data)
        { return (state >> 8) ^ PolyTable(static_cast<byte>(state ^ data)); }

        // Add Integer
        template<
            class T, std::enable_if_t<
                (sizeof(T) > 1) && std::is_integral<T>::value,
            int> Size = sizeof(T)
        > static constexpr inline return_type AddData(return_type state, const T d)
        {
            T data = d;
            state = AddData(state, static_cast<byte>(data & static_cast<T>(0xff)));
            for(int i = 1; i < Size; ++i)
            {
                data >>= 8;
                state = AddData(state, static_cast<byte>(data & static_cast<T>(0xff)));
            }

            return state;
        }

        // Add Range Type
        template<class T, class BT = decltype(std::cbegin(T())), class ET = decltype(std::cend(T()))>
        static constexpr inline return_type AddData(const return_type state, const T& data)
        { return AddDataArray(state, std::cbegin(data), std::cend(data)); }

        // Add C String
        static constexpr inline return_type AddData(const return_type state, const char* str)
        {
            // Look for null pointer
            const char* end = str;
            for(; *end != '\0'; ++end) {}
            return AddDataArray(state, str, end);
        }

        // Add Multiple Data Types
        // This allows for the hash to recursively hash stuff
        template<class Iterator>
        static constexpr inline return_type AddDataArray(return_type state, Iterator begin, const Iterator end)
        {
            for(; begin < end; ++begin)
            { state = AddData(state, *begin); }
            return state;
        }

    private:
        // Finalize State
        static constexpr inline return_type Finalize(return_type state)
        { return FinalXOR ^ state; }

    public: // Static Hashing Methods
        // Compute hash on fundamental type
        template<class T>
        constexpr return_type operator()(const T& data) const noexcept
        { return Finalize(AddData(InitState, data)); }

        template<class ...Args>
        constexpr return_type operator()(Args&& ...args) const noexcept
        {
            return_type s = InitState;
            (
                [&] {
                    s = AddData(s, args);
                } (), ...
            );
            return Finalize(s);
        }

        // Compute Hash on generic types
        template<class Iterator> // (begin,  end)
        constexpr return_type array(const Iterator begin, const Iterator end) const noexcept
        { return Finalize(AddDataArray(InitState, begin, end)); }

        template<class Iterator> // (begin, size)
        constexpr return_type array(const Iterator data, const size_type size) const noexcept
        { return Finalize(AddDataArray(InitState, data, data + size)); }
    };

    // Initialize static MemTable outside of class
    template<class MTable>
    constexpr MTable CRCBaseEngine<MTable>::PolyTable;

    // Makes CRCBaseEngine with Generator instead of MemTable
    template<class Generator>
    using CRCBaseEngineMem = CRCBaseEngine<MemTable<Generator>>;

    // Makes CRCBaseEngine with ReturnType and Polynomial
    template<class ReturnType, ReturnType Polynomial>
    using CRCBase = CRCBaseEngineMem<CRCTableGenerator<ReturnType, Polynomial>>;

    // CRC Bases for each CRC Type
    template<u8 Polynomial>
    using CRC8Base = CRCBase<u8, Polynomial>;

    template<u16 Polynomial>
    using CRC16Base = CRCBase<u16, Polynomial>;

    template<u32 Polynomial>
    using CRC32Base = CRCBase<u32, Polynomial>;

    template<u64 Polynomial>
    using CRC64Base = CRCBase<u64, Polynomial>;

    // CRC Engines with Polynomials
    // The Polynomials from
    // https://en.wikipedia.org/wiki/Cyclic_redundancy_check
    using CRC8 = CRC8Base<0xE5>; // CRC-8-Bluetooth

    using CRC16 = CRC16Base<0x8408>; // CRC-16-CCITT

    using CRC32   = CRC32Base<0xEDB88320>; // CRC-32
    using CRC32C  = CRC32Base<0x82F63B78>; // CRC-32C (Castagnoli)
    using CRC32K  = CRC32Base<0xEB31D82E>; // CRC-32K (Koopman)
    using CRC32K2 = CRC32Base<0x992C1A4C>; // CRC-32K2 (Koopman)

    using CRC64 = CRC64Base<0xC96C5795D7870F42>; // CRC-64-ECMA
}

#endif // SAM_BELLIVEAUS_CRC_IMPLEMENTATION_HPP