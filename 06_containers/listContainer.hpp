#include <iostream>

//template <typename T>
struct Node {
    Node() {}

    Node* next;
    int value;
};

class Container {
public:
    Container() {}

    void print() {
        Node *curr = head;

        while (curr != nullptr) {
            std::cout << curr->value << " ";

            curr = curr->next;
        }

        std::cout << std::endl;
    }
    
    void push_back(int value) {
        Node *new_node = new Node{};

        new_node->value = value;
        new_node->next = nullptr;

        tail->next = new_node;
        tail = new_node;

        if (m_size == 0) 
            head = new_node;

        m_size++;
    }

private:
    Node *tail;
    Node *head;
    size_t m_size = 0;
};
