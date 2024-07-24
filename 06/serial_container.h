#pragma once

#include <algorithm>
#include <iostream>
#include <cstring>
#include <stdexcept>

template <typename T>
class SerialContainer {
public:

    struct Iterator {
        Iterator() : ptr_{ nullptr } { }

        explicit Iterator(T *t_ptr) : ptr_{ t_ptr } { }

        T* operator++() {
            return ++ptr_;
        }

        T* operator--() {
            return --ptr_;
        }

        T get() {
            // проверять на null?
            return *ptr_;
        }

        bool operator==(const Iterator &compare) {
            return ptr_ == compare.ptr_;
        }

        bool operator!=(const Iterator &compare) {
            return !(ptr_ == compare.ptr_);
        }
    private:
        T *ptr_;
    };

    // Конструктор
    SerialContainer() :
            data_{ nullptr },
            capacity_{ 0 } {
    }

    // Копирующий конструктор.
    SerialContainer(const SerialContainer &container) : SerialContainer() {

        if (container.data_ == nullptr) {
            return;
        }

        data_ = new T[container.capacity_];
        std::copy(container.data_, container.data_ + capacity_, data_);

        capacity_ = container.capacity_;
    }

    // Деструктор
    ~SerialContainer() {
        clear();
    }

    // очистить
    void clear() {
        if (data_) {
            delete [] data_;
        }
        data_ = nullptr;
        capacity_ = 0;
    }

    // вставить элемент в конец
    void push_back(T t_value) {
        T *data_new = new T[capacity_ + 1];
        if (data_) {
            std::copy(data_, data_ + capacity_, data_new);
            delete [] data_;
        }
        data_new[capacity_] = t_value;
        data_ = data_new;
        ++capacity_;
    }

    // извлечь элемент с конца
    T pop_back() {
        if (capacity_ == 0 || !data_) {
            throw std::out_of_range("array is empty!");
        }
        T ret = data_[capacity_ - 1];
        --capacity_;
        T *data_new = new T[capacity_];
        std::copy(data_, data_ + capacity_, data_new);
        delete [] data_;
        data_ = data_new;
        return ret;
    }

    // вставить элемент в начало
    void push_front(T t_value) {
        T *data_new = new T[capacity_ + 1];
        data_new[0] = t_value;
        if (data_) {
            std::copy(data_, data_ + capacity_, data_new + 1);
            delete [] data_;
        }
        data_ = data_new;
        ++capacity_;
    }

    // извлечь элемент с начала
    T pop_front() {
        if (capacity_ == 0 || !data_) {
            throw std::out_of_range("array is empty!");
        }
        T ret = data_[0];
        --capacity_;
        T *data_new = new T[capacity_];
        std::copy(data_ + 1, data_ + capacity_ + 1, data_new);
        delete [] data_;
        data_ = data_new;
        return ret;
    }

    // вставить элемент в указанную позицию
    void insert(const size_t t_pos, const T t_value) {
        if (t_pos == 0) {
            push_front(t_value);
            return;
        }
        if (t_pos == capacity_) {
            push_back(t_value);
            return;
        }
        if (!data_) {
            throw std::out_of_range("failed to insert");
        }
        if (t_pos > capacity_) {
            throw std::out_of_range("out of array bounds!");
        }
        T *data_new = new T[capacity_ + 1];
        data_new[t_pos] = t_value;
        if (t_pos > 0) {
            std::copy(data_, data_ + t_pos, data_new);
        }
        std::copy(data_ + t_pos, data_ + capacity_, data_new + t_pos + 1);
        delete [] data_;
        data_ = data_new;
        ++capacity_;
    }

    // удалить элемент на позиции
    void erase(const size_t t_pos) {
        if (!data_) {
            return;
        }
        if (t_pos == 0) {
            pop_front();
            return;
        }
        if (t_pos >= capacity_) {
            throw std::out_of_range("out of array bounds!");
        }
        T *data_new = new T[capacity_ - 1];
        if (t_pos > 0) {
            std::copy(data_, data_ + t_pos, data_new);
        }
        if (t_pos != capacity_) {
            std::copy(data_ + t_pos + 1, data_ + capacity_, data_new + t_pos);
        }
        delete [] data_;
        data_ = data_new;
        --capacity_;
    }

    // размер
    size_t size() const {
        return capacity_;
    }

    Iterator begin() const {
        if (data_ == nullptr) {
            return Iterator(nullptr);
        }
        return Iterator(data_);
    }

    Iterator end() const {
        if (data_) {
            return Iterator(&data_[capacity_]);
        }
        return Iterator(nullptr);
    }

    Iterator last() const {
        if (data_ == nullptr) {
            return Iterator(nullptr);
        }
        return Iterator(&data_[capacity_ - 1]);
    }

    T operator[](size_t t_pos) {
        if (data_ == nullptr || t_pos >= capacity_) {
            throw std::out_of_range("out of array bounds!");
        }
        return data_[t_pos];
    }
private:
    T      *data_;
    size_t capacity_;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const SerialContainer<T>& sc) {
    for (auto item = sc.begin(); item != sc.end(); ++item) {
        os << item.get();
        if (item != sc.last()) {
            os << ", ";
        }
    }

    return os;
}
