// Copyright 2023 Stepan Dyatkovskiy at Kaspersky Lab.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <iostream>
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
            auto *cc = o->cast<CircleSquareFirstKid*>();
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
