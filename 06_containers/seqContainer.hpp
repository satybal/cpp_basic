#include <iostream>

template <typename T>
class Container {
public:
    Container() {}

    // struct Iterator {
    // public:
    //     friend class Container;
    //     Iterator(int *ptr): m_ptr(ptr) {}

    // private:
    //     int *m_ptr;        
    // };

    // int *begin() {
    //     return address;
    // }

    // int *end() {
    //     return address + m_size;
    // }

    const T &operator[] (size_t ind) const {
        // int ptr = *address;
        // ptr += ind;
        // return *ptr;
        return *(pointer + ind);
    }

    T &operator[](size_t ind) {
        // int ptr = *address;
        // ptr += ind;
        // return ptr;
               // std::cout << "non const " << (address + ind) << " " << *(address + ind) << std::endl;

        return *(pointer + ind);
    }

    void print() {
        std::cout << std::endl;
        for (size_t i=0; i < m_size; i++) {
            std::cout << *(pointer + i) << " ";
        }
        std::cout << std::endl;
    }

    void push_back(T &&value) {
        T *new_pointer = alloc.allocate((m_size + 1) * 2);

        for (size_t i = 0; i < m_size; i++) {
            *(new_pointer + i) = *(pointer + i);
        }

        *(new_pointer + m_size) = value;

        delete pointer;
        pointer = new_pointer;
        m_size++;
    }

private:
    std::allocator<T> alloc;
    T *pointer = alloc.allocate(0);
    size_t m_size = 0;
};