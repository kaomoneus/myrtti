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

struct Shape : RTTI<Shape, Object>
{
    RTTI_CLASS_NAME(Shape);
};

struct Square :
    RTTI<Square, Shape>
{
    RTTI_CLASS_NAME(Square);
};

struct Circle :
    RTTI<Circle, Shape>
{
    RTTI_CLASS_NAME(Circle);    
};

struct CircleSquare :
    RTTI<CircleSquare, Circle, Square>
{
    RTTI_CLASS_NAME(CircleSquare);

    CircleSquare(int numCircles, int numSquares)
    : numCircles(numCircles), numSquares(numSquares) {}

    int numCircles;
    int numSquares;
};

struct CircleSquareFirstKid :
    RTTI<CircleSquareFirstKid, CircleSquare>
{
    RTTI_CLASS_NAME(CircleSquare);
    
    CircleSquareFirstKid() : CircleSquare(1,1) {}
};

#endif

int main() {

    cout << "myrtti version: " << myrtti_info() << "\n";

    vector<shared_ptr<Object>> objs = {
        make_shared<Object>(),
        make_shared<Shape>(),
        make_shared<Circle>(),
        make_shared<Square>(),
        make_shared<CircleSquareFirstKid>()
    };

    for (auto &o : objs) {
        cout << "o->rtti->name = " << o->rtti->name << "\n";
    }

    cout << "Circle::info().name = " << Circle::info().name << "\n";
    cout << "Object::info().name = " << Object::info().name << "\n";

    return 0;
}
