#include <iostream>
#include "tachyon_manifold.h"

int main() {
    //TachyonManifold tachyon{"Day_7_test.txt"};
    TachyonManifold tachyon{"Day_7_input.txt"};
    //tachyon.print();
    tachyon.run_process();
    return 0;
}