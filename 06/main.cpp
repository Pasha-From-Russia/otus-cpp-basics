#include "linked_list_container.h"
#include "serial_container.h"
#include <list>
#include <iomanip>
#include <vector>

static constexpr int kPadding = 20;

#define TRY(t_caption, ...) \
    try { \
        std::cout \
            << std::left \
            << std::setw(kPadding) \
            << t_caption; \
        __VA_ARGS__; \
    } catch (const std::exception &e) { \
        std::cerr << e.what() << std::endl; \
    }

#define TRY1(...) \
    try { \
        __VA_ARGS__; \
    } catch (const std::exception &e) { \
        std::cerr << e.what() << std::endl; \
    }

void testLinkedListContainer() {

    std::cout << std::endl << __FUNCTION__ << std::endl << std::endl;
    LinkedListContainer<int> llc;
    for (int i = 0; i <= 9; i++) {
        llc.push_back(i);
    }

    TRY("dump",
        std::cout
            << std::left
            << llc
            << std::endl);

    TRY("size", \
        std::cout \
            << llc.size() \
            << std::endl); \

    TRY("erase 3,5,7",
        // для сохранения очерёдности согласно заданию
        llc.erase(3 - 1);
        llc.erase(5 - 2);
        llc.erase(7 - 3);
        std::cout
            << llc
            << std::endl);

    TRY("push_front(10)",
        llc.push_front(10);
        std::cout
            << llc
            << std::endl);

    TRY("insert_center(20)",
        llc.insert((llc.size() / 2), 20);
        std::cout
            << llc
            << std::endl);

    TRY("push_back(30)",
        llc.push_back(30);
        std::cout
            << llc
            << std::endl);

    TRY("value[2] = ",
        std::cout
            << llc[2]
            << std::endl);

    TRY1(std::cout
            << "pop_back = "
            << std::setw(9) << std::left << llc.pop_back()
            << llc
            << std::endl);

    TRY("insert(0, 99)",
        llc.insert(0, 99);
        std::cout
            << llc
            << std::endl);

    TRY("insert(size, 88)",
        llc.insert(llc.size(), 88);
        std::cout
            << llc
            << std::endl);

    TRY("test insert to wrong pos: ",
        llc.insert(123, 10));

    while(true) {
        try {
            std::cout
                << "pop_front = "
                << std::setw(9) << std::left << llc.pop_front()
                << llc
                << std::endl;
        } catch (...) {
            std::cout << "break!" << std::endl;
            break;
        }
    }

    TRY("test insert [0] = 12 for empty array: ",
        llc.clear();
        llc.insert(0, 12);
        std::cout
            << llc
            << std::endl);
    llc.clear();

    TRY("test push_back()->pop_front(): ",
        llc.push_back(0);
        llc.pop_front();
        std::cout << "ok" << std::endl);

    TRY("test copy constructor: ",
        auto a = llc;
        std::cout << "ok" << std::endl);
}


void testSerialContainer() {

    std::cout << std::endl << __FUNCTION__ << std::endl << std::endl;
    SerialContainer<int> sc;
    for (int i = 0; i <= 9; i++) {
        sc.push_back(i);
    }

    TRY("dump",
        std::cout
            << std::left
            << sc
            << std::endl);

    TRY("size",
        std::cout
            << sc.size()
            << std::endl);

    TRY("erase 3,5,7",
        // для сохранения очерёдности согласно заданию
        sc.erase(3 - 1);
        sc.erase(5 - 2);
        sc.erase(7 - 3);
        std::cout
            << sc
            << std::endl);

    TRY("push_front(10)",
        sc.push_front(10);
        std::cout
            << sc
            << std::endl);

    TRY("insert_center(20)",
        sc.insert((sc.size() / 2), 20);
        std::cout
            << sc
            << std::endl);

    TRY("push_back(30)",
        sc.push_back(30);
        std::cout
            << sc
            << std::endl);

    TRY("value[2] = ",
        std::cout
            << sc[2]
            << std::endl);

    TRY1(std::cout
            << "pop_back = "
            << std::setw(9) << std::left << sc.pop_back()
            << sc
            << std::endl);

    TRY("insert(0, 99)",
        sc.insert(0, 99);
        std::cout
            << sc
            << std::endl);

    TRY("insert(size, 88)",
        sc.insert(sc.size(), 88);
        std::cout
            << sc
            << std::endl);

    TRY("test insert to wrong pos: ",
        sc.insert(123, 10));

    while(true) {
        try {
            std::cout
                << "pop_front = "
                << std::setw(9) << std::left << sc.pop_front()
                << sc
                << std::endl;
        } catch (...) {
            std::cout << "break!" << std::endl;
            break;
        }
    }

    TRY("test insert [0] = 12 for empty array: ",
        sc.clear();
        sc.insert(0, 12);
        std::cout
            << sc
            << std::endl);
    sc.clear();

    TRY("test push_back()->pop_front(): ",
        sc.push_back(0);
        sc.pop_front();
        std::cout << "ok" << std::endl);

    TRY("test copy constructor: ",
        auto a = sc;
        std::cout << "ok" << std::endl);
}

int main() {
    testLinkedListContainer();
    testSerialContainer();
    return 0;
}

#undef TRY
#undef TRY1