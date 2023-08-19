#include <iostream>

template <typename T>
class Container {
public:
    Container() {}

    // struct Iterator {
    // public:
    //     friend class Container;
    //     Iterator(T *ptr): m_ptr(ptr) {}

    // private:
    //     T *m_ptr;        
    // };

    T *begin() {
        return head;
    }

    T *end() {
        return (head + m_size + 1);
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
            std::cout << head[i] << " ";
        }
        std::cout << std::endl;
    }

    bool space_filled() {
        if (total_space < m_size) {
            total_space = (m_size + 1) * 2;

            return true;
        } else return false;
    }

    void push_back(const T &value) {
        if (space_filled()) {
            T *new_head = new T[total_space];

            for (size_t i = 0; i < m_size; i++) {
                new_head[i] = head[i];
            }
        
            new_head[m_size] = value;

            delete[] head;
            head = new_head;
        } else {
            head[m_size] = value;
        }

        m_size++;
    }

    size_t size() { return m_size; }

private:
    size_t m_size = 0;
    size_t total_space = 0; // total mem x2 to real used
    T *head = new T[m_size];
};