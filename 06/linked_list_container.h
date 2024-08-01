#pragma once

#include <algorithm>
#include <iostream>
#include <stdexcept>

template <typename T>
struct LLNode {
    LLNode *next;
    LLNode *prev;
    T      data;

    LLNode() : next{ nullptr }, prev{ nullptr } {}
    explicit LLNode(const T t_value) : next{ nullptr }, prev{ nullptr }, data{ t_value } { }
};

template <typename T>
class LinkedListContainer {
public:

    struct Iterator {
        Iterator() : node_ptr_{ nullptr } { }

        explicit Iterator(LLNode<T> *t_ptr) : node_ptr_{ t_ptr } { }

        LLNode <T>* operator++() {
            node_ptr_ = node_ptr_->next;
            return node_ptr_;
        }

        LLNode <T>* operator--() {
            node_ptr_ = node_ptr_->prev;
            return node_ptr_;
        }

        T get() {
            // проверять на null?
            return node_ptr_->data;
        }

        bool operator==(const Iterator &compare) {
            return node_ptr_ == compare.node_ptr_;
        }

        bool operator!=(const Iterator &compare) {
            return !(node_ptr_ == compare.node_ptr_);
        }
    private:
        LLNode<T> *node_ptr_;
    };

    // Конструктор
    LinkedListContainer() :
            lastNode_{ nullptr },
            capacity_{ 0 } {
    }

    // Копирующий конструктор
    LinkedListContainer(const LinkedListContainer &container) : LinkedListContainer() {

        if (container.arrayEntry_.next == nullptr) {
            return;
        }

        LLNode<T>* currnode = container.arrayEntry_.next;
        while (currnode != nullptr) {
            push_back(currnode->data);
            currnode = currnode->next;
        }

        capacity_ = container.capacity_;
    }

    // Деструктор
    ~LinkedListContainer() {
        clear();
    }

    // очистить
    void clear() {
        if (!arrayEntry_.next) {
            return;
        }

        LLNode<T> *node = arrayEntry_.next;
        while (node) {
            LLNode<T> *next = node->next;
            delete node;
            node = next;
        }
        capacity_ = 0;
        arrayEntry_.next = nullptr;
        lastNode_ = nullptr;
    }

    // вставить элемент в конец
    void push_back(T t_value) {
        LLNode<T> *node = new LLNode<T>(t_value);
        if (!lastNode_) {
            if (!arrayEntry_.next) {
                arrayEntry_.next = node;
            }
            lastNode_ = node;
        } else {
            node->prev = lastNode_;
            lastNode_->next = node;
            lastNode_ = node;
        }
        ++capacity_;
    }

    // извлечь элемент с конца
    T pop_back() {
        if (!lastNode_) {
            throw std::out_of_range("array is empty!");
        }
        LLNode<T> *ln = lastNode_;
        T ret = ln->data;
        if (ln->prev) {
            ln->prev->next = nullptr;
            lastNode_ = ln->prev;
            delete ln;
            --capacity_;
        } else {
            // первый элемент
            arrayEntry_.next = nullptr;
            lastNode_ = nullptr;
            capacity_ = 0;
        }
        return ret;
    }

    // извлечь элемент с начала
    T pop_front() {
        if (!arrayEntry_.next) {
            throw std::out_of_range("array is empty!");
        }
        LLNode<T> *ln = arrayEntry_.next;
        T ret = ln->data;
        if (ln->next) {
            ln->next->prev = nullptr;
            arrayEntry_.next = ln->next;
            delete ln;
            --capacity_;
        } else {
            // первый элемент
            arrayEntry_.next = nullptr;
            lastNode_ = nullptr;
            delete ln;
            capacity_ = 0;
        }
        return ret;
    }

    // вставить элемент в начало
    void push_front(T t_value) {
        LLNode<T> *node = new LLNode<T>(t_value);
        if (!arrayEntry_.next) {
            arrayEntry_.next = node;
            lastNode_ = node;
        } else {
            node->next = arrayEntry_.next;
            arrayEntry_.next = node;
        }
        ++capacity_;
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
        if (t_pos > capacity_) {
            throw std::out_of_range("out of array bounds!");
        }
        size_t i = 0;
        LLNode<T> *node = arrayEntry_.next;
        while (i++ < t_pos && node) {
            node = node->next;
        }
        if (!node) {
            push_back(t_value);
            return;
        }
        LLNode<T> *newnode = new LLNode<T>(t_value);
        newnode->prev = node->prev;
        newnode->next = node;
        node->prev->next = newnode;
        if (node == lastNode_) {
            lastNode_ = node;
        }
        ++capacity_;
    }

    // удалить элемент на позиции
    void erase(const size_t t_pos) {
        if (!arrayEntry_.next) {
            return;
        }
        if (t_pos >= capacity_) {
            throw std::out_of_range("out of array bounds!");
        }
        size_t i = 0;
        LLNode<T> *node = arrayEntry_.next;
        while (i++ < t_pos && node) {
            node = node->next;
        }
        if (!node) {
            throw std::out_of_range("failed to erase");
        }
        node->prev->next = node->next;
        if (node->next) {
            node->next->prev = node->prev;
        }
        delete node;
        --capacity_;
    }

    // размер
    size_t size() const {
        return capacity_;
    }

    Iterator begin() const {
        return Iterator(arrayEntry_.next);
    }

    Iterator end() const {
        // даже если lastNode_ не nullptr, next у него должен быть nullptr
        return Iterator(nullptr);
    }

    Iterator last() const {
        if (!lastNode_) {
            return Iterator(nullptr);
        }
        return Iterator(lastNode_);
    }

    T operator[](size_t t_pos) {
        if (!arrayEntry_.next || t_pos > capacity_) {
            throw std::out_of_range("out of array bounds!");
        }
        size_t i = 0;
        LLNode<T> *node = arrayEntry_.next;
        while (i++ < t_pos) {
            node = node->next;
        }
        if (node == nullptr) {
            throw std::out_of_range("program error");
        }
        return node->data;
    }

private:
    LLNode<T>* newNode(T t_value) {
        return new LLNode<T>(t_value);
    }

public:

private:
    LLNode<T> arrayEntry_;
    LLNode<T> *lastNode_;
    size_t    capacity_;
};

template <typename T>
std::ostream& operator<<(std::ostream &os, const LinkedListContainer<T> &llc) {
    for (auto item = llc.begin(); item != llc.end(); ++item) {
        os << item.get();
        if (item != llc.last()) {
            os << ", ";
        }
    }
    return os;
}
