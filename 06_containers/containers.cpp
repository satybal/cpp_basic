#include <iostream>
#include "seqContainer.hpp"


int main() {

    Container<int> con;
    for (int i=0; i<7; i++) 
        con.push_back(i);
    con.print();


    Container con1 = con;
    con1.print();

    Container<int> con2;
    con2 = con;
    con2.print();

    con2.insert(0, 10);
    con2.print();

    Container<int> con3;
    con3 = static_cast<Container<int>&&>(con2);
    con3 = std::move(con2);
    con3.print();
    con2.print();
    // con.insert(2, 5);
    // con.print();

    // con.erase(3);
    // con.print();

    // std::cout << con[2] << std::endl;
    // con[2] = 4;
    // std::cout << con[2] << std::endl;
    // std::cout << con.size() << std::endl;

    return 0;
}