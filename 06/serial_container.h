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
            capacity_{ 0 },
            totalNum_{ 0 } {
    }

    // Копирующий конструктор.
    SerialContainer(const SerialContainer &container) : SerialContainer() {

        if (container.data_ == nullptr) {
            return;
        }

        data_ = new T[container.capacity_];
        std::copy(container.data_, container.data_ + capacity_, data_);

        capacity_ = container.capacity_;
        totalNum_ = container.totalNum_;
    }

    // Деструктор
    ~SerialContainer() {
        clear();
    }

    // очистить
    void clear() {
        delete [] data_;
        data_ = nullptr;
        capacity_ = 0;
        totalNum_ = 0;
    }

    // зарезервировать место под новое количество элементов.
    void reserve(const size_t t_newCapacity) {
        if (t_newCapacity <= capacity_) {
            return;
        }

        T* dataNew = new T[t_newCapacity];

        if (data_ == nullptr) {
            data_ = dataNew;
            capacity_ = t_newCapacity;
            return;
        }

        std::copy(data_, data_ + totalNum_, dataNew);

        delete [] data_;

        data_ = dataNew;
        capacity_ = t_newCapacity;
    }

    // вставить элемент в конец
    void push_back(T t_value) {
        progressionalResize();
        data_[totalNum_++] = t_value;
    }

    // извлечь элемент с конца
    T pop_back() {
        if (totalNum_ == 0 || !data_) {
            throw std::out_of_range("array is empty!");
        }
        T ret = data_[totalNum_ - 1];
        --totalNum_;
        return ret;
    }

    // вставить элемент в начало
    void push_front(T t_value) {
        progressionalResize();

        std::copy(data_ + 1, data_ + capacity_, data_);
        if (data_) {
            std::copy(data_, data_ + capacity_, data_ + 1);
        }
        data_[0] = t_value;
        ++totalNum_;
    }

    // извлечь элемент с начала
    T pop_front() {
        if (totalNum_ == 0 || !data_) {
            throw std::out_of_range("array is empty!");
        }
        T ret = data_[0];
        std::copy(data_ + 1, data_ + totalNum_, data_);
        --totalNum_;
        return ret;
    }

    // вставить элемент в указанную позицию
    void insert(const size_t t_pos, const T t_value) {
        if (t_pos == 0) {
            push_front(t_value);
            return;
        }
        if (t_pos > totalNum_) {
            throw std::out_of_range("out of array bounds!");
        }
        progressionalResize();
        if (t_pos == totalNum_) {
            push_back(t_value);
            return;
        }
        std::copy(data_ + t_pos, data_ + totalNum_, data_ + t_pos + 1);
        data_[t_pos] = t_value;
        ++totalNum_;
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

        std::copy(data_ + t_pos + 1, data_ + totalNum_, data_ + t_pos);
        --totalNum_;
    }

    // размер
    size_t size() const {
        return totalNum_;
    }

    Iterator begin() const {
        if (data_ == nullptr) {
            return Iterator(nullptr);
        }
        return Iterator(data_);
    }

    Iterator end() const {
        if (data_) {
            return Iterator(&data_[totalNum_]);
        }
        return Iterator(nullptr);
    }

    Iterator last() const {
        if (data_ == nullptr) {
            return Iterator(nullptr);
        }
        return Iterator(&data_[totalNum_ - 1]);
    }

    T operator[](size_t t_pos) {
        if (data_ == nullptr || t_pos >= totalNum_) {
            throw std::out_of_range("out of array bounds!");
        }
        return data_[t_pos];
    }

private:
    void progressionalResize() {
        if (totalNum_ == capacity_) {
            reserve((capacity_ == 0) ? 4 : static_cast<size_t>(capacity_ * 1.5));
        }
    }

private:
    T      *data_;
    size_t capacity_;
    size_t totalNum_;
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
