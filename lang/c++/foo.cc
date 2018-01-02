/*
 * foo.cc
 * Copyright (C) 2017 dawnworld <thundon@qq.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <iostream>

int main() {
    std::cout << "hello world" << std::endl;
    int a = 10;
    const int & b = a;
    // *b = 20;
    int c = 12;
    b = c;
    return 0;
}


