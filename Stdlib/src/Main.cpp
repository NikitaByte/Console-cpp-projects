#include <iostream>
#include "LinkedList.h"

int main() {
    LinkedList<int> list;
    list.pushBack(10);
    list.pushBack(20);
    list.pushBack(18);
    list.pushFront(5);

    std::cout << "Linked list: " << list.toString() << std::endl;
    std::cout << "Length: " << list.getLength() << std::endl;
    std::cout << "Front: " << list.getFront() << std::endl;
    std::cout << "Back: " << list.getBack() << std::endl;

    list.clear();

    std::cout << "List after clear: " << list.toString() << std::endl;
}