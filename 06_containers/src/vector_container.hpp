#pragma once

#include <stdexcept>
#include <iostream>

namespace Vector {

    template <typename T>
    class Container {
    public:
        
        class iterator {
        public:      
            friend class Container;  

            bool operator!=(const iterator &rhs);
            iterator &operator++();
            T &operator*(); 

        private:
            T *ptr = nullptr;
        };

        Container();
        ~Container();

        explicit Container(std::initializer_list<T> init);

        Container(const Container &other); // copy constructor
        Container &operator=(const Container &rhs); // copy assignment

        Container(Container &&other) noexcept; // move constustor
        Container &operator=(Container &&rhs); // move assignment operator
    
        iterator begin();
        iterator end();

        T &operator[](size_t idx);
        T &operator[](size_t idx) const;

        void print(); 
        void push_back(const T &value);
        void erase(size_t idx);
        void insert(size_t idx, const T &value);

        size_t size() const;
        T *get_data() const;

    private:
        void check_index(bool expr) const;
        bool space_filled();

        T *data;
        size_t m_size;
        size_t total_space; // total mem x1.5 to real used
        iterator iter;
    };

} // end of namespace Vector

#include "vector_container.ipp"
