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
#include <optional>
#include <string>

#include "myrtti.h"
#include "myrtti/visitor.h"

using namespace std;
using namespace myrtti;

with_rtti_vparents(struct, Exception, (myrtti::Object))
    Exception(const std::string_view &m) : message(m) {}
    string message;
with_rtti_end();

with_rtti(class, ExceptionErrorOne, Exception)
public:
    ExceptionErrorOne() : Exception("Exception One Error") {}
with_rtti_end();


with_rtti_parents(struct, ExceptionErrorTwo, (Exception))
    ExceptionErrorTwo() : Exception("Exception Two Error") {}
with_rtti_end();

with_rtti_vparents_parents(struct, ExceptionErrorThree, (myrtti::Object), (Exception))
    ExceptionErrorThree() : Exception("Exception Three Error") {}
with_rtti_end();

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
            class_id<Exception>(), [] {
                std::cout << "STATIC: Exception\n";
                return true;
            }
        },
        {
            class_id<ExceptionErrorOne>(), [] {
                std::cout << "STATIC: ExceptionOne\n";
                return true;
            }
        },
        {
            class_id<ExceptionErrorTwo>(), [] {
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