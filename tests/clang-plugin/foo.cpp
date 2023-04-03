// Just make sure whole LIT thing works as expected.

// RUN: (! %clang ) 2>&1 | FileCheck %s
// RUN: (! %clang ) 2>&1 | FileCheck %s --check-prefixes=CHECK2

// CHECK: no input files
// CHECK2-NOT: nope input files
