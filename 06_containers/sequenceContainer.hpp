namespace Sequence {
    template <typename T>
    class Container {
    public:
        Container(): data{nullptr}, m_size{0}, total_space{0} {}

        ~Container() {
            delete[] data;
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
            this->data = rhs.data;
            this->m_size = std::move(rhs.m_size);
            this->total_space = std::move(rhs.total_space);

            return *this;
        }

        class iterator {
        public:      
            friend class Container;  

            bool operator!=(const iterator &rhs) {
                return this->ptr != rhs.ptr;
            }

            iterator &operator++() {
                ptr++;
                return *this;
            }

            T &operator*() {
                return *ptr;
            }
        private:
            T *ptr = nullptr;
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
            if (total_space <= m_size) {
                total_space = int((m_size + 1) * 1.5);

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

                delete []data;
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
        T *data;
        size_t m_size;
        size_t total_space; // total mem x2 to real used
        iterator iter;
    };

} // end of namespace Sequence
