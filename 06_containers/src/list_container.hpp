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

        Container(Container &&other); // move ctcr
        Container &operator=(const Container &&rhs); // move assignment

        iterator begin();
        iterator end(); 

        void print() const;
        void push_back(T value);
        void erase(size_t idx);
        void insert(size_t idx, T value);

        T &operator[](size_t idx);
        size_t size();

    private:
        Node<T> *get_node(size_t idx);
        void check_index(bool expr) const;

        Node<T> *tail;
        Node<T> *head;
        size_t m_size = 0;
        iterator iter;
    };
} // end of namespace List

#include "list_container.cpp"
