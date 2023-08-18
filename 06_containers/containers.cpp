#include <iostream>
#include "seqContainer.hpp"
#include <vector>

// void push_back(int value, std::allocator<int> my_alloc) {
//     my_alloc.
// }

int main() {

    Container <std::string> con;
    con.push_back("aaa");
    con.push_back("bbb");
    con.push_back("ccc");
    con.print();

    std::cout << sizeof(con) << std::endl;
    std::cout << con[1] << std::endl;
    // std::allocator<std::string> alloc;
    // std::string *p1 = alloc.allocate(2);
    // *p1 = "10";
    // auto p2 = p1 + 1;
    // *p2 = "20";
    // std::cout << p1 << std::endl;
    // std::cout << *p1 << std::endl;
    // std::cout << p2 << std::endl;
    // std::cout << *p2 << std::endl;
    return 0;
}