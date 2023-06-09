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

ROOT(WideRoot)
ROOT(Wide2)
ROOT(Wide3)
ROOT(Wide4)
ROOT(Wide5)
ROOT(Wide6)
ROOT(Wide7)
ROOT(Wide8)
ROOT(Wide9)
ROOT(Wide10)
ROOT(Wide11)
ROOT(Wide12)
ROOT(Wide13)
ROOT(Wide14)
ROOT(Wide15)
ROOT(Wide16)
ROOT(Wide17)
ROOT(Wide18)
ROOT(Wide19)


INHERIT_ME_MULTI(
    (
        WideRoot,
        Wide2, Wide3, Wide4, Wide5, Wide6, Wide7, Wide8, Wide9,
        Wide10, Wide11, Wide12, Wide13, Wide14, Wide15, Wide16, Wide17,
        Wide18, Wide19
    ),
    WideFinal
);

ROOT(DeepRoot)
ROOT(DeepRoot2)
INHERIT_ME(DeepRoot, Deep2);
INHERIT_ME(Deep2, Deep3);
INHERIT_ME(Deep3, Deep4);
INHERIT_ME(Deep4, Deep5);
INHERIT_ME(Deep5, Deep6);
INHERIT_ME(Deep6, Deep7);
INHERIT_ME(Deep7, Deep8);
INHERIT_ME(Deep8, Deep9);
INHERIT_ME(Deep9, Deep10);
INHERIT_ME(Deep10, Deep11);
INHERIT_ME(Deep11, Deep12);
INHERIT_ME(Deep12, Deep13);
INHERIT_ME(Deep13, Deep14);
INHERIT_ME(Deep14, Deep15);
INHERIT_ME(Deep15, Deep16);
INHERIT_ME(Deep16, Deep17);
INHERIT_ME(Deep17, Deep18);
INHERIT_ME(Deep18, Deep19);
INHERIT_ME(Deep19, DeepFinal);
// INHERIT_ME_MULTI((Deep19, Wide2, Wide3, Wide4, Wide5, Wide6, Wide7), DeepFinal);
