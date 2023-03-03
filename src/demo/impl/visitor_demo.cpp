#include <iostream>
#include <string>

#include "myrtti.h"

using namespace std;
using namespace rtti;

struct Exception : virtual Object, RTTI<Exception>
{
    DEFINE_RTTI(Shape, Object);
    string message;
};

struct ExceptionErrorOne : Exception, RTTI<ExceptionErrorOne>
{
    DEFINE_RTTI(ExceptionErrorOne, Exception);
    ExceptionErrorOne() : Exception{"Exception One Error"} {}
};

struct ExceptionErrorTwo : Exception, RTTI<ExceptionErrorOne>
{
    DEFINE_RTTI(ExceptionErrorTwo, Exception);
    ExceptionErrorTwo() : Exception{"Exception Two Error"} {}

};

struct ExceptionErrorThree : Exception, RTTI<ExceptionErrorOne>
{
    DEFINE_RTTI(ExceptionErrorThree, Exception);
    ExceptionErrorTwo() : Exception{"Exception Three Error"} {}
};

int main() {
    Visitor<Object> visitor(
        [](const Exception& e) {
            cout << "Exception, msg: " << e.message << "\n";
        },
        [](const ExceptionErrorOne& e) {
            cout << "ExceptionOne direct catch.\n";
        },
        [](const ExceptionErrorTwo& e) {
            cout << "ExceptionTwo direct catch.\n";
        }
    );

    ExceptionErrorOne one;
    ExceptionErrorTwo two;
    ExceptionErrorThree three;

    cout << "Direct visitor:\n";

    visitor.visit(one);
    visitor.visit(two);
    visitor.visit(three);

    cout << "Class info visitor:\n";

    visitor.visit(ExceptionErrorOne::info());
    visitor.visit(ExceptionErrorTwo::info());
    visitor.visit(ExceptionErrorThree::info());

    return 0;
}