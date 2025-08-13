#pragma once
#include <cstddef>     // size_t
#include <stdexcept>   // runtime_error
#include <sstream>     // ostringstream
#include <string>      // string

template<typename T>
struct Node {
	T data;
	Node* next;
	Node* prev;

	// Constructor
	Node(T value);
};

template<typename T>
class LinkedList {
public:
	LinkedList();
	~LinkedList();

	void pushFront(T value);
	void pushBack(T value);
	void popFront();
	void popBack();
	void clear();

	T getFront() const;
	T getBack() const;
	size_t getLength() const;

	bool isEmpty() const;

	std::string toString() const;
private:
	Node<T>* head;
	Node<T>* tail;
	size_t length;
};

template<typename T>
Node<T>::Node(T value)
	: data(value), prev(nullptr), next(nullptr) {
}

template<typename T>
LinkedList<T>::LinkedList()
	: head(nullptr), tail(nullptr), length(0) {
}

template<typename T>
LinkedList<T>::~LinkedList() {
	clear();
}

template<typename T>
void LinkedList<T>::pushFront(T value) {
	Node<T>* newNode = new Node<T>(value);
	if (head == nullptr) {
		head = tail = newNode;
	}
	else {
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	}
	length++;
}

template<typename T>
void LinkedList<T>::pushBack(T value) {
	Node<T>* newNode = new Node<T>(value);
	if (tail == nullptr) {
		head = tail = newNode;
	}
	else {
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
	}
	length++;
}

template<typename T>
void LinkedList<T>::popFront() {
	if (head == nullptr) return;

	Node<T>* temp = head;
	if (head == tail) {
		head = tail = nullptr;
	}
	else {
		head = head->next;
		head->prev = nullptr;
	}
	delete temp;
	length--;
}

template<typename T>
void LinkedList<T>::popBack() {
	if (tail == nullptr) return;

	Node<T>* temp = tail;
	if (head == tail) {
		head = tail = nullptr;
	}
	else {
		tail = tail->prev;
		tail->next = nullptr;
	}
	delete temp;
	length--;
}

template<typename T>
void LinkedList<T>::clear() {
	while (head != nullptr) {
		Node<T>* temp = head;
		head = head->next;
		delete temp;
	}
	head = tail = nullptr;
	length = 0;
}

template<typename T>
T LinkedList<T>::getFront() const {
	if (head == nullptr)
		throw std::runtime_error("List is empty");
	return head->data;
}

template<typename T>
T LinkedList<T>::getBack() const {
	if (tail == nullptr)
		throw std::runtime_error("List is empty");
	return tail->data;
}

template<typename T>
size_t LinkedList<T>::getLength() const {
	return length;
}

template<typename T>
bool LinkedList<T>::isEmpty() const {
	return head == nullptr;
}

template<typename T>
std::string LinkedList<T>::toString() const {
	std::ostringstream oss;
	Node<T>* current = head;

	oss << "[";
	while (current != nullptr) {
		oss << current->data;
		if (current->next != nullptr) oss << ", ";
		current = current->next;
	}
	oss << "]";
	return oss.str();
}