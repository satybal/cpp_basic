#include <iostream>

template <typename T>
class Container {
public:
    Container() {}

    ~Container() {
        delete[] data;
    }

    // copy constructor
    Container(const Container &other) : Container{} {
        m_size = other.m_size;
        total_space = other.total_space;
        data = new T[m_size];

        for (size_t i = 0; i < m_size; i++) {
            data[i] = other[i];
        }
    }

    // copy assignment operator
    Container &operator=(const Container &rhs) {
        Container temp = rhs;

		T * ptr = data;
		data = temp.data;
		temp.data = ptr;
		
		size_t size = m_size;
		m_size = temp.m_size;
		temp.m_size = size;

		size_t total = total_space;
		total_space = temp.total_space;
		temp.total_space = total;

		return *this;
    }

    //move constustor
    Container(Container &&other) {
        data = other.data;
        other.data = nullptr;

        m_size = other.m_size;
        other.m_size = 0;

        total_space = other.total_space;
        other.total_space = 0;
    }

    //move assignment operator
    Container &operator=(const Container &&rhs) {
		Container tmp{std::move(rhs)};
		return *this = tmp;
    }

    

    // T *begin() {
    //     return data;
    // }

    // T *end() {
    //     return (data + m_size);
    // }

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
        if (total_space < m_size) {
            total_space = (m_size + 1) * 2;

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

            delete[] data;
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
    size_t m_size = 0;
    size_t total_space = 0; // total mem x2 to real used
    T *data = new T[m_size];
};