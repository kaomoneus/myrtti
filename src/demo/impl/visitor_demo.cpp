#include <iostream>
#include <optional>
#include <string>

#include "myrtti.h"
#include "myrtti/visitor.h"

using namespace std;
using namespace myrtti;

struct Exception : virtual Object, RTTI<Exception>
{
    DEFINE_RTTI(Exception, Object);
    Exception(const std::string_view &m) : message(m) {}
    string message;
};

struct ExceptionErrorOne : Exception, RTTI<ExceptionErrorOne>
{
    DEFINE_RTTI(ExceptionErrorOne, Exception);
    ExceptionErrorOne() : Exception("Exception One Error") {}
};

struct ExceptionErrorTwo : Exception, RTTI<ExceptionErrorTwo>
{
    DEFINE_RTTI(ExceptionErrorTwo, Exception);
    ExceptionErrorTwo() : Exception("Exception Two Error") {}

};

struct ExceptionErrorThree : Exception, RTTI<ExceptionErrorThree>
{
    DEFINE_RTTI(ExceptionErrorThree, Exception);
    ExceptionErrorThree() : Exception("Exception Three Error") {}
};

int main() {

    std::cout << "Checking classic visitor...\n";

    VisitorConst visitor(
        [](const Exception& e) {
            cout << "TEST EXCEPTION: Exception, msg: " << e.message << "\n";
            return true;
        },
        [](const ExceptionErrorOne& e) {
            cout << "TEST EXCEPTION: ExceptionOne.\n";
            return true;
        },
        [](const ExceptionErrorTwo& e) {
            cout << "TEST EXCEPTION: ExceptionTwo.\n";
            return true;
        }
    );

    cout << "Running classic visitor:\n";

    visitor.visit(ExceptionErrorOne());
    visitor.visit(ExceptionErrorTwo());
    visitor.visit(ExceptionErrorThree());

    cout << "Checking and running info visitor:\n";

    VisitorStatic staticVisitor({
        {
            &Exception::info(), [] {
                std::cout << "STATIC: Exception\n";
                return true;
            }
        },
        {
            &ExceptionErrorOne::info(), [] {
                std::cout << "STATIC: ExceptionOne\n";
                return true;
            }
        },
        {
            &ExceptionErrorTwo::info(), [] {
                std::cout << "STATIC: ExceptionTwo\n";
                return true;
            }
        }
    });

    staticVisitor.visit(&ExceptionErrorOne::info());
    staticVisitor.visit(&ExceptionErrorTwo::info());
    staticVisitor.visit(&ExceptionErrorThree::info());

    return 0;
}