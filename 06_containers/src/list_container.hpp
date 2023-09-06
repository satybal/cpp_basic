#pragma once

namespace List {

    template <typename T>
    struct Node {
        Node() {}

        Node* next;
        Node* prev;
        T value;
    };

    template <typename T>
    class Container {
    public:
        friend class iterator;

        class iterator {
        public:
            friend class Container;

            iterator &operator++();
            iterator &operator--();
            bool operator!=(const iterator &rhs);
            T operator*(); 

        private:
            Node<T> *iter_node = nullptr;
        };

        Container() {}
        ~Container();

        Container(std::initializer_list<T> init);

        Container(const Container &other); // copy ctor
        Container &operator=(const Container &other); // copy assignment

        Container(Container &&other) noexcept; // move ctcr
        Container &operator=(Container &&rhs); // move assignment

        iterator begin();
        iterator end(); 

        void print() const;
        virtual void push_back(T value);
        virtual void erase(size_t idx);
        void insert(size_t idx, T value);

        T &operator[](size_t idx);
        T &operator[](size_t idx) const;

        size_t size() const;
        void clear();

    private:
        Node<T> *get_node(size_t idx) const;
        void check_index(bool expr) const;

        Node<T> *last;
        Node<T> *first;
        size_t m_size = 0;
        iterator iter;
    };
} // end of namespace List

#include "list_container.ipp"
