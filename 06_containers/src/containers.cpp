#include "vector_container.hpp"
#include "list_container.hpp"

template <class C>
void test_container(C &con) {    
    std::cout << std::endl;

    for (size_t i = 0; i < 10; ++i)
        con.push_back(i);
    std::cout << "Printing container" << std::endl;
    con.print();
    std::cout << std::endl;

    std::cout << "Container size: " << con.size() << std::endl;
    std::cout << std::endl;

    std::cout << "Erase 3,5,7 elements:" << std::endl;
    con.erase(6);
    con.erase(4);
    con.erase(2);
    con.print();
    std::cout << std::endl;

    std::cout << "Insert 10 to the beginning" << std::endl;
    con.insert(0, 10);
    con.print();
    std::cout << std::endl;

    std::cout << "Insert 20 to the center" << std::endl;
    con.insert(con.size() / 2, 20);
    con.print();
    std::cout << std::endl;

    std::cout << "Push 30 to the end" << std::endl;
    con.push_back(30);
    con.print();
    std::cout << std::endl;

    std::cout << "Printing with iterator" << std::endl;
    for (auto i = con.begin(); i != con.end(); ++i) 
      std::cout << *i << " ";
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
  }

int main() {

  std::cout << "LIST CONTAINER TEST" << std::endl;
  List::Container<int> con1;
  test_container(con1);

  std::cout << "VECTOR CONTAINER TEST" << std::endl;
  Vector::Container<int> con2;
  test_container(con2);

  return 0;
}