#include <stdexcept>
#include "list_container.hpp"

namespace List {

    template <typename T>
    Container<T>::~Container() {
        this->clear();
    }

    template <typename T>
    Container<T>::Container(std::initializer_list<T> init): Container<T>::Container{} {
        this->clear();
        for (auto i : init)
            this->push_back(i);
    }

    template <typename T>
    Container<T>::Container(const Container<T> &other): Container<T> {} {
        for (size_t i = 0; i < other.size(); ++i)
            this->push_back(other[i]);
    }

    template <typename T>
    Container<T> &Container<T>::operator=(const Container<T> &other) {
        this->clear();

        for (size_t i = 0; i < other.size(); ++i)
            this->push_back(other[i]);
       
       return *this;
    }

    template <typename T>
    Container<T>::Container(Container<T> &&other) {
        m_size = other.m_size;
        other.m_size = 0;

        first = other.first;
        last = other.last;

        other.first = other.last = nullptr;
    }

    template <typename T>
    Container<T> &Container<T>::operator=(Container<T> &&rhs) {
        Container<T> tmp = std::move(rhs);
        return *this = tmp;
    }

    template <typename T>
    typename Container<T>::iterator &Container<T>::iterator::operator++() {
        iter_node = iter_node->next;
        return *this;
    }

    template <typename T>
    typename Container<T>::iterator &Container<T>::iterator::operator--() {
        iter_node = iter_node->prev;
        return *this;
    }

    template <typename T>
    bool Container<T>::iterator::operator!=(const Container<T>::iterator &rhs) {
        return this->iter_node != rhs.iter_node;
    }

    template <typename T>
    T Container<T>::iterator::operator*() {
        return iter_node->value;
    }

    template <typename T>
    typename Container<T>::iterator Container<T>::begin() {
        iter.iter_node = first;          
        return iter;
    }

    template <typename T>
    typename Container<T>::iterator Container<T>::end() {
        iter.iter_node = last->next;
        return iter;
    }

    template <typename T>
    void Container<T>::clear() {
        while (m_size > 0) {
            this->erase(0);
        }
    }

    template <typename T>
    Node<T> *Container<T>::get_node(size_t idx) const {
        check_index(idx >= m_size);

        Node<T> *_node = first;

        for (size_t i = 0; i < idx; ++i) {
            _node = _node->next;
        }

        return _node;
    }

    template <typename T>
    T &Container<T>::operator[](size_t idx) {
        Node<T> *_node = get_node(idx);
        return _node->value;
    }

    template <typename T>
    T &Container<T>::operator[](size_t idx) const {
        Node<T> *_node = get_node(idx);
        return _node->value;
    }

    template <typename T>
    void Container<T>::print() const { // PRINT
        Node<T> *_node = first;

        while (_node != nullptr) {
            std::cout << _node->value << " ";
            _node = _node->next;
        }

        std::cout << std::endl;
    }
    
    template <typename T>
    void Container<T>::push_back(T value) { //PUSH BACK
        Node<T> *new_node = new Node<T>{};

        new_node->value = value;
        new_node->next = nullptr;

        if (m_size == 0) {
            new_node->prev = nullptr;
            first = last = new_node;
        } else {
            new_node->prev = last;
        }
            
        last->next = new_node;
        last = new_node;

        m_size++;
    }

    template <typename T>
    void Container<T>::erase(size_t idx) {
        check_index(idx >= m_size);

        Node<T> *_node = get_node(idx);

        m_size--;

        if (_node->next) {
            if (_node->prev) {
                _node->prev->next = _node->next;
                _node->next->prev = _node->prev;
            } else {
                _node->next->prev = nullptr;
                first = _node->next;
            }
        } else {
            _node->prev = nullptr;
        }
        delete _node;
    }

    template <typename T>
    void Container<T>::insert(size_t idx, T value) { //INSERT
        check_index(idx > m_size);

        if (idx == m_size) {
            this->push_back(value);
            return;
        }

        Node<T> *_node = get_node(idx);
        Node<T> *new_node = new Node<T>{};

        new_node->next = _node;
        new_node->value = value;

        if (idx == 0) {
            new_node->prev = nullptr;
            first = new_node;
        } else {
            _node->prev->next = new_node;
            new_node->prev = _node->prev;
        }

        m_size++;
    }

    template <typename T>
    void Container<T>::check_index(bool expr) const {
        if (expr) 
            throw std::invalid_argument("Out of range");
    }

    template <typename T>
    size_t Container<T>::size() const { return m_size; }

} // end of namespace List
