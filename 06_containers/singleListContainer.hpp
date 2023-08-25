namespace SinglyDirectedList {

    template <typename T>
    struct Node {
        Node() {}

        Node *next;
        T value;
    };

    template <typename T>
    class Container {
    public:
        friend class iterator;

        Container() {}

        ~Container() {
            while (m_size > 0) {
                this->erase(0);
            }
        }

        // move ctcr
        Container(Container &&other) {
            m_size = other.m_size;
            other.m_size = 0;

            head = other.head;
            other.head = nullptr;

            tail = other.tail;
            other.tail = nullptr;
        }

        // move assignment
        Container &operator=(const Container &&rhs) {
            this->head = std::move(rhs.head);
            this->tail = std::move(rhs.tail);
            this->m_size = std::move(rhs.m_size);

            return *this;
        }

        class iterator {
        public:
            friend class Container;

            iterator &operator++() {
                iter_node = iter_node->next;
                return *this;
            }

            bool operator!=(const iterator &rhs) {
                return this->iter_node != rhs.iter_node;
            }

            T operator*() {
                return iter_node->value;
            }

        private:
            Node<T> *iter_node;
        };

        iterator begin() {
            iter.iter_node = head;
            return iter;
        }

        iterator end() {
            iter.iter_node = tail->next;
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
            Node<T> *_node = move_idx(idx);
            return _node->value;
        }

        void print() const { // PRINT
            Node<T> *_node = head;

            while (_node != nullptr) {
                std::cout << _node->value << " ";
                _node = _node->next;
            }

            std::cout << std::endl;
        }
        
        void push_back(T value) { //PUSH BACK
            Node<T> *new_node = new Node<T>{};

            new_node->value = value;
            new_node->next = nullptr;

            if (m_size == 0) {
                head = tail = new_node;
            } else {
                tail->next = new_node;
                tail = new_node;
            }

            m_size++;
        }

        void erase(size_t idx) { //ERASE
            Node<T> *_node = move_idx(idx);

            m_size--;

            if (idx == 0) {
                if (_node->next) {
                    head = _node->next;
                }
            } else {
                Node<T> *_prev = move_idx(idx - 1);
                if (_node->next) {
                    _prev->next = _node->next;
                } else {
                    _prev->next = nullptr;
                    tail = _prev;
                }
            }
            delete _node;
        }

        void insert(size_t idx, T value) { //INSERT
            Node<T> *_node = move_idx(idx);

            Node<T> *new_node = new Node<T>{};
                new_node->next = _node;
                new_node->value = value;
            if (idx == 0) {
                head = new_node;
            } else {
                Node<T> *_prev = move_idx(idx - 1);
                _prev->next = new_node;
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
} // end of SinglyDirectedList
