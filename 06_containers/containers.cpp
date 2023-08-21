#include <iostream>
//#include "seqContainer.hpp"
#include "listContainer.hpp"


int main() {
  //Sequence::test_container();
  Container<int> con;
  con.push_back(5);
  con.push_back(15);
  con.push_back(25);
  con.push_back(35);
  con.print();

  // con.erase(0);
  // con.print();

  // con.erase(1);
  // con.print();

  // con.erase(1);
  // con.print();

  // con.insert(0, 10);
  // con.insert(0, 11);
  // con.insert(1, 13);
  // con.print();

  // std::cout << con.size() << std::endl;
  // std::cout << con[1] << std::endl;

  return 0;
}