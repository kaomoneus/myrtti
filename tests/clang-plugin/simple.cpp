// RUN: %clang++ -fplugin=%lib/myrtti_clang.so -c %s

class [[myrtti]] A {};

void [[myrtti]] foo() {};