#include <iostream>
#include <memory>
#include <vector>

#include <myrtti.h>


using namespace std;
using namespace myrtti;

#if 0

struct Shape : RTTIRoot<Shape>
{
    RTTI_CLASS_NAME(Shape);
};

struct Square :
    Shape,
    RTTI<Square, Shape>
{
    RTTI_CLASS_NAME(Square);
};

struct Circle :
    Shape,
    RTTI<Circle, Shape>
{
    RTTI_CLASS_NAME(Circle);    
};

struct CircleSquare :
    Circle, Square,
    RTTI<CircleSquare, Circle, Square>
{
    RTTI_CLASS_NAME(CircleSquare);

    CircleSquare(int numCircles, int numSquares)
    : numCircles(numCircles), numSquares(numSquares) {}

    int numCircles;
    int numSquares;
};

struct CircleSquareFirstKid :
    CircleSquare,
    RTTI<CircleSquareFirstKid, CircleSquare>
{
    RTTI_CLASS_NAME(CircleSquare);
    
    CircleSquareFirstKid() : CircleSquare(1,1) {}
};

#else

struct Shape : virtual Object, RTTI<Shape>
{
    DEFINE_RTTI(Shape, Object);
};

struct Square : Shape, RTTI<Square>
{
    DEFINE_RTTI(Square, Shape);
};

struct Circle : Shape, RTTI<Circle>
{
    DEFINE_RTTI(Circle, Shape);
};

struct CircleSquare : Circle, Square, RTTI<CircleSquare>
{
    DEFINE_RTTI(CircleSquare, Circle, Square);

    CircleSquare(int numCircles, int numSquares)
    : numCircles(numCircles), numSquares(numSquares) {}

    int numCircles;
    int numSquares;
};

struct CircleSquareFirstKid : CircleSquare, RTTI<CircleSquareFirstKid>
{
    DEFINE_RTTI(CircleSquareFirstKid, CircleSquare);
    CircleSquareFirstKid() : CircleSquare(1,1) {}
};

#endif

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

        if (o->rtti == &CircleSquareFirstKid::info()) {
            auto *cc = o->cast<CircleSquareFirstKid>();
            cout << "Discovered " << cc->rtti->name << ": "
                 << cc->numCircles << ", " << cc->numSquares << "\n";
        }
    }

    cout << "CircleSquareFirstKid::info().name = " << CircleSquareFirstKid::info().name << "\n";
    cout << "Object::info().name = " << Object::info().name << "\n";

    return 0;
}
