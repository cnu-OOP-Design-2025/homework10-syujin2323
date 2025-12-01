#include "MyVector.h"
#include <stdexcept>

template<typename T>
void MyVector<T>::push_back(const T& val) {
    
    if (cap == 0) {
        cap = 1;
        data = new T[cap];
    } else if (length == cap) {
        size_t newCap = cap * 2;
        if (newCap == 0) newCap = 1;

        T* newData = new T[newCap];
        for (size_t i = 0; i < length; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        cap = newCap;
    }

    data[length++] = val;
}

template<typename T>
void MyVector<T>::pop_back() {
    if (length > 0) {
        --length;
    }
}

template<typename T>
size_t MyVector<T>::size() const {
    return length;
}

template<typename T>
T& MyVector<T>::operator[](int i) {
    return data[i];
}

template<typename T>
bool MyVector<T>::operator==(const MyVector<T>& other) const {
    if (length != other.length) return false;
    for (size_t i = 0; i < length; ++i) {
        if (!(data[i] == other.data[i])) return false;
    }
    return true;
}

template<typename T>
bool MyVector<T>::operator!=(const MyVector<T>& other) const {
    return !(*this == other);
}

template<typename T>
bool MyVector<T>::operator<(const MyVector<T>& other) const {
    size_t n = (length < other.length) ? length : other.length;
    for (size_t i = 0; i < n; ++i) {
        if (data[i] < other.data[i]) return true;
        if (other.data[i] < data[i]) return false;
    }
    return length < other.length;
}

template<typename T>
bool MyVector<T>::operator>(const MyVector<T>& other) const {
    return other < *this;
}

template<typename T>
bool MyVector<T>::operator<=(const MyVector<T>& other) const {
    return !(*this > other);
}

template<typename T>
bool MyVector<T>::operator>=(const MyVector<T>& other) const {
    return !(*this < other);
}

template<typename T>
T& MyVector<T>::Iterator::operator*() {
    return *ptr;
}

template<typename T>
typename MyVector<T>::Iterator& MyVector<T>::Iterator::operator++() {
    ++ptr;
    return *this;
}

template<typename T>
typename MyVector<T>::Iterator& MyVector<T>::Iterator::operator--() {
    --ptr;
    return *this;
}

template<typename T>
typename MyVector<T>::Iterator MyVector<T>::Iterator::operator+(int n) const {
    return Iterator(ptr + n);
}

template<typename T>
typename MyVector<T>::Iterator MyVector<T>::Iterator::operator-(int n) const {
    return Iterator(ptr - n);
}

template<typename T>
bool MyVector<T>::Iterator::operator==(const Iterator& other) const {
    return ptr == other.ptr;
}

template<typename T>
bool MyVector<T>::Iterator::operator!=(const Iterator& other) const {
    return ptr != other.ptr;
}

template<typename T>
int MyVector<T>::Iterator::operator-(const Iterator& other) const {
    return static_cast<int>(ptr - other.ptr);
}

template<typename T>
typename MyVector<T>::Iterator MyVector<T>::begin() {
    return Iterator(data);
}

template<typename T>
typename MyVector<T>::Iterator MyVector<T>::end() {
    return Iterator(data + length);
}

template<typename T>
typename MyVector<T>::Iterator MyVector<T>::insert(Iterator pos, const T& value) {
    
    size_t index = static_cast<size_t>(pos - begin());
    if (index > length) index = length;

    if (cap == 0) {
        cap = 1;
        data = new T[cap];
    }
    if (length == cap) {
        size_t newCap = cap * 2;
        if (newCap == 0) newCap = 1;
        T* newData = new T[newCap];

        for (size_t i = 0; i < index; ++i) {
            newData[i] = data[i];
        }
        
        newData[index] = value;
        
        for (size_t i = index; i < length; ++i) {
            newData[i + 1] = data[i];
        }

        delete[] data;
        data = newData;
        cap = newCap;
        ++length;
    } else {
        
        for (size_t i = length; i > index; --i) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        ++length;
    }

    return Iterator(data + index);
}

template<typename T>
typename MyVector<T>::Iterator MyVector<T>::erase(Iterator pos) {
    size_t index = static_cast<size_t>(pos - begin());
    if (index >= length) {
        return end();
    }

    for (size_t i = index + 1; i < length; ++i) {
        data[i - 1] = data[i];
    }
    --length;

    return Iterator(data + index);
}

template<typename T>
void MyVector<T>::clear() {
    length = 0;
}

template<typename T>
T& MyVector<T>::at(size_t i) {
    if (i >= length) {
        throw std::out_of_range("MyVector::at");
    }
    return data[i];
}

template<typename T>
T& MyVector<T>::front() {
    return data[0];
}

template<typename T>
T& MyVector<T>::back() {
    return data[length - 1];
}

template<typename T>
size_t MyVector<T>::capacity() const {
    return cap;
}

template<typename T>
bool MyVector<T>::empty() const {
    return length == 0;
}

template class MyVector<int>;