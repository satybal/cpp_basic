#include <iostream>

template <typename T>
class Container {
public:
    Container() {}

    struct Iterator {
    public:
        friend class Container;
        Iterator(T *ptr): m_ptr(ptr) {}

    private:
        T *m_ptr;        
    };

    T *begin() {
        return pointer;
    }

    T *end() {
        return pointer + m_size;
    }

    T &operator[](size_t ind) {
        auto place = this->begin() + ind;
        return *place;
    }

    const T &operator[](size_t ind) const {
        auto place = this->begin() + ind;
        return *place;
    }

    void print() {
        std::cout << std::endl;
        for (size_t i=0; i < m_size; i++) {
            std::cout << pointer[i] << " ";
        }
        std::cout << std::endl;
    }

    void push_back(T &&value) {
        T *new_pointer = new T[(m_size + 1) * 2];

        for (size_t i = 0; i < m_size; i++) {
            new_pointer[i] = pointer[i];
        }

        new_pointer[m_size] = value;

        delete pointer;
        pointer = new_pointer;

        m_size++;
    }

    void push_back(T &value) {
        T *new_pointer = new T[(m_size + 1) * 2];

        for (size_t i = 0; i < m_size; i++) {
            new_pointer[i] = pointer[i];
        }

        new_pointer[m_size] = value;

        delete[] pointer;
        pointer = new_pointer;
        
        m_size++;
    }

    size_t size() { return m_size; }

private:
    size_t m_size = 0;
    //Iterator iter = new int[m_size];
    T *pointer = new T[m_size];
};