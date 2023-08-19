#include <iostream>
#include "seqContainer.hpp"
//#include <vector>


int main() {

    Container<int> con;
    // for (int i=0; i<10; i++) 
    //     con.push_back(i);

    con.push_back(10);
    con.push_back(20);
    con.push_back(30);
    con.push_back(40);

    std::cout << con.begin() << std::endl;
    std::cout << con.end() << std::endl;
    // std::cout << con[1] << std::endl;
    // size_t a = 1;
    // std::cout << con[a];

    // for (auto i = con.begin(); i < con.end(); i++) {
    //     std::cout << con[i] << std::endl;
    // }

    con.print();

    std::cout << con.size() << std::endl;
    //std::cout << con[1] << std::endl;
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