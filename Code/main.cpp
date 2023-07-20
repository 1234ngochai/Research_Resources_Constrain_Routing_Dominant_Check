#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <array>
#include <algorithm> // for min and max functions
#include <random>
#include <set>
//#include "dominant_check.h"
//#include "dominant_check_2.h"
#include "dominant_check_3.h"
#include "tree_dominant_check.h"
#include <immintrin.h>

int main() {
  

    default_random_engine gen;
    std::vector<Node> nodes = createNodes(2000000, gen,87);
    
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    sorted_array_dominant_check1(nodes);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "ms" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() << "s" << std::endl;
    
    std::chrono::steady_clock::time_point begin1 = std::chrono::steady_clock::now();
    unsorted_array_dominant_check(nodes);
    std::chrono::steady_clock::time_point end1 = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end1 - begin1).count() << "ms" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::seconds> (end1 - begin1).count() << "s" << std::endl;
    
    std::chrono::steady_clock::time_point begin2 = std::chrono::steady_clock::now();
    dominant_check(nodes);
    std::chrono::steady_clock::time_point end2 = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end2 - begin2).count() << "ms" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::seconds> (end2 - begin2).count() << "s" << std::endl;

    return 0;

}