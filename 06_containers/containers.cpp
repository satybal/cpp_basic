#include <iostream>
//#include "seqContainer.hpp"
#include "listContainer.hpp"


int main() {
  //Sequence::test_container();
  Container con;
  con.push_back(5);
  con.push_back(15);
  con.push_back(25);
  con.print();

  return 0;
}