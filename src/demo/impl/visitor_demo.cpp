#include <iostream>
#include <optional>
#include <string>

#include "myrtti.h"
#include "myrtti/visitor.h"

using namespace std;
using namespace myrtti;

RTTI_STRUCT_ROOT_BEGIN(Exception)
    Exception(const std::string_view &m) : message(m) {}
    string message;
RTTI_STRUCT_END();

RTTI_STRUCT_BEGIN(ExceptionErrorOne, (Exception))
    ExceptionErrorOne() : Exception("Exception One Error") {}
RTTI_STRUCT_END();

RTTI_STRUCT_BEGIN(ExceptionErrorTwo, (Exception))
    ExceptionErrorTwo() : Exception("Exception Two Error") {}
RTTI_STRUCT_END();

RTTI_STRUCT_BEGIN(ExceptionErrorThree, (Exception))
    ExceptionErrorThree() : Exception("Exception Three Error") {}
RTTI_STRUCT_END();

int main() {

    std::cout << "Checking classic visitor...\n";

    Visitor visitor(
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
            Exception::class_id, [] {
                std::cout << "STATIC: Exception\n";
                return true;
            }
        },
        {
            ExceptionErrorOne::class_id, [] {
                std::cout << "STATIC: ExceptionOne\n";
                return true;
            }
        },
        {
            ExceptionErrorTwo::class_id, [] {
                std::cout << "STATIC: ExceptionTwo\n";
                return true;
            }
        }
    });

    staticVisitor.visit<ExceptionErrorOne>();
    staticVisitor.visit<ExceptionErrorTwo>();
    staticVisitor.visit<ExceptionErrorThree>();

    return 0;
}