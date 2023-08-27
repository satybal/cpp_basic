#include <stdexcept>
#include "vector_container.hpp"

namespace Vector {

    template <typename T>
    bool Container<T>::iterator::operator!=(const Container<T>::iterator &rhs) {
        return this->ptr != rhs.ptr;
    }

    template <typename T>
    typename Container<T>::iterator &Container<T>::iterator::operator++() {
        ptr++;
        return *this;
    }
    
    template <typename T>
    T &Container<T>::iterator::operator*() {
        return *ptr;
    }

    template <typename T>
    typename Container<T>::iterator Container<T>::begin() {
        iter.ptr = data;
        return iter;
    }

    template <typename T>
    typename Container<T>::iterator Container<T>::end() {
        iter.ptr = data + m_size;
        return iter;
    }

    template <typename T>
    Container<T>::Container(): data{nullptr}, m_size{0}, total_space{0} {}

    template <typename T>
    Container<T>::~Container() { delete[] data; }
    
    template <typename T>
    Container<T>::Container(Container<T> &&other) {
        data = other.data;
        other.data = nullptr;

        m_size = other.m_size;
        other.m_size = 0;

        total_space = other.total_space;
        other.total_space = 0;
    }

    template <typename T>
    Container<T> &Container<T>::operator=(const Container<T> &&rhs) {
        this->data = rhs.data;
        this->m_size = std::move(rhs.m_size);
        this->total_space = std::move(rhs.total_space);

        return *this;
    }

    template <typename T>
    T &Container<T>::operator[](size_t idx) {
        check_index(idx >= m_size); 

        auto pos = data + idx;
        return *pos;
    }

    template <typename T>
    const T &Container<T>::operator[](size_t idx) const {
        check_index(idx >= m_size); 
        
        auto pos = data + idx;
        return *pos;
    }

    template <typename T>
    void Container<T>::print() { // PRINT
        for (size_t i=0; i < m_size; i++) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

    template <typename T>
    void Container<T>::push_back(const T &value) { // PUSH BACK
        if (space_filled()) {
            T *new_data = new T[total_space];

            for (size_t i = 0; i < m_size; i++) {
                new_data[i] = data[i];
            }
        
            new_data[m_size] = value;

            delete []data;
            data = new_data;
        } else {
            data[m_size] = value;
        }

        m_size++;
    }

    template <typename T>
    void Container<T>::erase(size_t idx) { // ERASE
        check_index(idx >= m_size); 
        
        m_size--;

        for (size_t i = idx; i < m_size; i++) {
            data[i] = data[i+1];
        }
    }

    template <typename T>
    void Container<T>::insert(size_t idx, const T &value) { // INSERT
        check_index(idx > m_size); 
        
        if (m_size == 0) {
            this->push_back(value);
            return;
        }

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

    template <typename T>
    size_t Container<T>::size() const { return m_size; }

    template <typename T>
    void Container<T>::check_index(bool expr) const {
        if (expr) {
            throw std::invalid_argument("Out of range");
        }
    }

    template <typename T>
    bool Container<T>::space_filled() {
        if (total_space <= m_size) {
            total_space = int((m_size + 1) * 1.5);

            return true;
        } else return false;
    }
} // end of namespace Vector