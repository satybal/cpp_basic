#include <iostream>

namespace Sequence {
    template <typename T>
    class Container {
    public:
        Container() {}

        ~Container() {
            delete[] data;
        }

        // copy constructor
        Container(const Container &other) : Container{} {
            m_size = other.m_size;
            total_space = other.total_space;
            data = new T[m_size];

            for (size_t i = 0; i < m_size; i++) {
                data[i] = other[i];
            }
        }

        // copy assignment operator
        Container &operator=(const Container &rhs) {
            Container temp = rhs;

            T * ptr = data;
            data = temp.data;
            temp.data = ptr;
            
            size_t size = m_size;
            m_size = temp.m_size;
            temp.m_size = size;

            size_t total = total_space;
            total_space = temp.total_space;
            temp.total_space = total;

            return *this;
        }

        // move constustor
        Container(Container &&other) {
            data = other.data;
            other.data = nullptr;

            m_size = other.m_size;
            other.m_size = 0;

            total_space = other.total_space;
            other.total_space = 0;
        }

        // move assignment operator
        Container &operator=(const Container &&rhs) {
            Container tmp{std::move(rhs)};
            return *this = tmp;
        }

        class iterator {
        public:      
            friend class Container;  

            bool operator<(const iterator &rhs) {
                return this->ptr < rhs.ptr;
            }

            iterator &operator++() {
                ptr++;
                return *this;
            }

            T &operator*() {
                return *ptr;
            }
        private:
            T *ptr;
        };

    
        iterator begin() {
            iter.ptr = data;
            return iter;
        }

        iterator end() {
            iter.ptr = data + m_size;
            return iter;
        }

        T &operator[](size_t ind) {
            auto pos = data + ind;
            return *pos;
        }

        const T &operator[](size_t ind) const {
            auto pos = data + ind;
            return *pos;
        }

        void print() { // PRINT
            for (size_t i=0; i < m_size; i++) {
                std::cout << data[i] << " ";
            }
            std::cout << std::endl;
        }

        bool space_filled() {
            if (total_space < m_size) {
                total_space = (m_size + 1) * 2;

                return true;
            } else return false;
        }

        void push_back(const T &value) { // PUSH BACK
            if (space_filled()) {
                T *new_data = new T[total_space];

                for (size_t i = 0; i < m_size; i++) {
                    new_data[i] = data[i];
                }
            
                new_data[m_size] = value;

                delete[] data;
                data = new_data;
            } else {
                data[m_size] = value;
            }

            m_size++;
        }

        void erase(size_t idx) { // ERASE
            m_size--;

            for (size_t i = idx; i < m_size; i++) {
                data[i] = data[i+1];
            }
        }

        void insert(size_t idx, const T &value) { // INSERT
            if (space_filled()) {
                T *new_data = new T[total_space];
                for (size_t i = m_size; i > idx; i--) {
                    new_data[i] = data[i-1];
                }

                new_data[idx] = value;

                for (size_t i = 0; i < idx - 1; i++) {
                    new_data[i] = data[i];
                }

                delete[] data;
                data = new_data;
            } else {
                for (size_t i = m_size; i > idx; i--) {
                    data[i] = data[i-1];
                }
                data[idx] = value;
            }

            m_size++;
        }

        size_t size() const { return m_size; }

    private:
        size_t m_size = 0;
        size_t total_space = 0; // total mem x2 to real used
        T *data = new T[m_size];
        iterator iter;
    };

    void test_container() {
        Container<int> con;
        
        for (size_t i = 0; i < 10; ++i) { con.push_back(i); }
        std::cout << "Printing sequence container" << std::endl;
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

        std::cout << "Adding 10 to the beginning" << std::endl;
        con.insert(0, 10);
        con.print();
        std::cout << std::endl;

        std::cout << "Adding 20 to the center" << std::endl;
        con.insert(con.size() / 2, 20);
        con.print();
        std::cout << std::endl;

        std::cout << "Adding 30 to the end" << std::endl;
        con.push_back(30);
        con.print();
        std::cout << std::endl;

        std::cout << "Printing with iterator" << std::endl;
        for (auto i = con.begin(); i < con.end(); ++i) 
            std::cout << *i << " ";
        std::cout << std::endl;
    }
} // end of namespace Sequence