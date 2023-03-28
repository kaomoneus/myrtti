#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>

#include <myrtti.h>


using namespace std;
using namespace myrtti;

struct Shape : RTTI<Shape>
{
    DEFINE_RTTI(Shape, Object);
};

struct Square : Shape, RTTI<Square>
{
    DEFINE_RTTI(Square, Shape /* more parents might be present*/);
};

struct Circle : Shape, RTTI<Circle>
{
    DEFINE_RTTI(Circle, Shape);
};

RTTI_STRUCT_BEGIN(CircleSquare, (Circle, Square))
    CircleSquare(int numCircles, int numSquares)
    : numCircles(numCircles), numSquares(numSquares) {}

    int numCircles;
    int numSquares;
RTTI_STRUCT_END()

RTTI_STRUCT_BEGIN(CircleSquareFirstKid, (CircleSquare))
    CircleSquareFirstKid() : CircleSquare(1,1) {}
RTTI_STRUCT_END()

int main() {

    cout << "myrtti version: " << myrtti_info() << "\n";

    vector<shared_ptr<Object>> objs = {
        make_shared<Object>(),
        make_shared<Shape>(),
        make_shared<Square>(),
        make_shared<Circle>(),
        make_shared<CircleSquareFirstKid>()
    };

    for (auto &o : objs) {
        cout << "o->rtti->name = " << o->rtti->name << "\n";
        cout << "    classId = " << o->rtti->getId() << "\n";

        if (o->rtti == CircleSquareFirstKid::info()) {
            auto *cc = o->cast<CircleSquareFirstKid>();
            cout << "Discovered " << cc->rtti->name << ": "
                 << cc->numCircles << ", " << cc->numSquares << "\n";
        }
    }

    cout << "CircleSquareFirstKid::info().name = " << CircleSquareFirstKid::info()->name << "\n";
    cout << "Object::info().name = " << Object::info()->name << "\n";

    cout << "isa<Square>(objs[1]): " << isa<Square>(objs[1].get()) << "\n";
    cout << "isa<Square>(objs[2]): " << isa<Square>(objs[2].get()) << "\n";

    return 0;
}
