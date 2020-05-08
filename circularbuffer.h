#include <iterator>

template <typename T>
class CircularBuffer {
public:
    class iterator : public std::iterator<std::random_access_iterator_tag, T> {
    private:
        T* ptr;
    public:
        using difference_type = typename std::iterator<std::random_access_iterator_tag, T>::difference_type;
        iterator() : ptr(nullptr) {}
        explicit iterator(T* ptr) : ptr(ptr) {}
        iterator(const iterator &itr) : ptr(itr.ptr) {}
        iterator& operator+=(difference_type diff) {
            ptr += diff;
            return *this;
        }
        iterator& operator-=(difference_type diff) {
            ptr -= diff;
            return *this;
        }
        T& operator*() const { return *ptr; }
        T* operator->() const { return ptr; }
        T& operator[](difference_type diff) const { return ptr[diff]; }
        iterator& operator++() {
            ptr++;
            return *this;
        }
        iterator& operator--() {
            ptr--;
            return *this;
        }
        iterator operator++(T) {
            iterator tmp(*this);
            ++ptr;
            return tmp;
        }
        iterator operator--(T) {
            iterator tmp(*this);
            --ptr;
            return tmp;
        }
        difference_type operator-(const iterator& itr) const { return ptr - itr.ptr; }
        iterator operator+(difference_type diff) const { return iterator(ptr + diff); }
        iterator operator-(difference_type diff) const { return iterator(ptr - diff); }
        friend iterator operator+(difference_type diff, const iterator& itr) { return iterator(diff + itr.ptr); }
        friend iterator operator-(difference_type diff, const iterator& itr) { return iterator(diff - itr.ptr); }
        bool operator==(const iterator& itr) const { return ptr == itr.ptr; }
        bool operator!=(const iterator& itr) const { return ptr != itr.ptr; }
        bool operator>(const iterator& itr) const { return ptr > itr.ptr; }
        bool operator<(const iterator& itr) const { return ptr < itr.ptr; }
        bool operator>=(const iterator& itr) const { return ptr >= itr.ptr; }
        bool operator<=(const iterator& itr) const { return ptr <= itr.ptr; }
    };
private:
    size_t capacity = 0;
    T* array;
    iterator current;
public:
    CircularBuffer()= default;
    explicit CircularBuffer(int capacity) : capacity(capacity) {
        array = new T[capacity];
        current = iterator(array);
    }
    iterator begin() {
        return iterator(array);
    }
    iterator end() {
        return iterator(array+capacity);
    }
    size_t size() {
        return size;
    }
    T& operator[](int index) {
        return array[index % capacity];
    };
    void add(T value) {
        *current = value;
        current++;
        if (&*current == array + capacity)
            current = iterator(array);
    }
    T& last(){
        return *current;
    }
    void resize(size_t size) {
        if(size<capacity){
            throw std::exception();
        }
        T* new_array = new T[size];
        for(int i = 0; i < capacity; i++)
            new_array[i] = array[i];
        capacity = size;
        array = new_array;
        current = iterator(new_array);
    }
    T& front() {
        return *array;
    }
    T& back() {
        return *(array+capacity-1);
    }
    void set_front(T value){
        array[0] = value;
    }
    void set_back(T value){
        array[capacity-1] = value;
    }
};
