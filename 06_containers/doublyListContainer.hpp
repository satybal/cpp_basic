namespace DoublyDirectedList {

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

        Container() {}

        class iterator {
        public:
            friend class Container;

            iterator &operator++() {
                _node = _node->next;
                return *this;
            }

            iterator &operator--() {
                _node = _node->prev;
                return *this;
            }

            bool operator!=(const iterator &rhs) {
                return this->_node != rhs._node;
            }

            T operator*() {
                return _node->value;
            }

        private:
            Node<T> *_node;
        };

        iterator begin() {
            iter._node = head;
            
            return iter;
        }

        iterator end() {
            iter._node = tail->next;
            return iter;
        }

        Node<T> *move_idx(size_t idx) const {
            Node<T> *_node = head;

            for (size_t i = 0; i < idx; ++i) {
                _node = _node->next;
            }

            return _node;
        }

        T &operator[](size_t idx) {
            Node<T> *value = move_idx(idx);
            return value->value;
        }

        void print() const { // PRINT
            Node<T> *curr = head;

            while (curr != nullptr) {
                std::cout << curr->value << " ";
                curr = curr->next;
            }

            std::cout << std::endl;
        }
        
        void push_back(T value) { //PUSH BACK
            Node<T> *new_node = new Node<T>{};

            new_node->value = value;
            new_node->next = nullptr;

            if (m_size == 0) {
                new_node->prev = nullptr;
                head = new_node;
            } else {
                new_node->prev = tail;
            }
                
            tail->next = new_node;
            tail = new_node;

            m_size++;
        }

        void erase(size_t idx) { //ERASE
            Node<T> *_cur = move_idx(idx);

            m_size--;

            if (_cur->next) {
                if (_cur->prev) {
                    _cur->prev->next = _cur->next;
                    _cur->next->prev = _cur->prev;
                } else {
                    _cur->next->prev = nullptr;
                    head = _cur->next;
                }
            } else {
                _cur->prev->next = nullptr;
            }
        }

        void insert(size_t idx, T value) { //INSERT
            Node<T> *_curr = move_idx(idx);
            Node<T> *new_node = new Node<T>{};

            new_node->next = _curr;
            new_node->value = value;

            if (idx == 0) {
                new_node->prev = nullptr;
                head = new_node;
            } else {
                _curr->prev->next = new_node;
                new_node->prev = _curr->prev;
            }

            m_size++;
        }

        size_t size() { return m_size; }

    private:
        Node<T> *tail;
        Node<T> *head;
        size_t m_size = 0;
        iterator iter;
    };
} // end of DoublyDirectedList
