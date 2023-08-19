#include <iostream>
#include "seqContainer.hpp"


int main() {

    Container<int> con;
    for (int i=0; i<7; i++) 
        con.push_back(i);
    con.print();

    con.insert(2, 5);
    con.print();

    con.erase(3);
    con.print();

    std::cout << con[2] << std::endl;

    std::cout << con.size() << std::endl;

    return 0;
}