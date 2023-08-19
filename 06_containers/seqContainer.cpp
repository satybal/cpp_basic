#pragma once
#include "seqContainer.hpp"

    void Container<T>::push_back(T &&value) {
        T *new_pointer = new T[(m_size + 1) * 2];

        for (size_t i = 0; i < m_size; i++) {
            new_pointer[i] = pointer[i];
        }

        new_pointer[m_size] = value;

        delete pointer;
        pointer = new_pointer;

        m_size++;
    }


