#pragma once
#include<iostream>
using std::cout;

template<typename T>
struct Node {
	T data;
	Node* next;
	Node(const T& _data) : data(_data), next(nullptr) {}
};

template<typename T>
class List {
	Node<T>* start;

public:
    class Iterator {
        Node<T>* crr;
    public:
        Iterator(Node<T>* node) {
            crr = node;
        }
        bool operator != (const Iterator& other) const {
            return crr != other.crr;
        }
        void operator++ () {
            crr = crr->next;
        }
        T& operator* () {
            return crr->data;
        }
        T operator*() const {
            return crr->data;
        }
    };

    Iterator begin() const {
        return Iterator(start);
    }

    Iterator end() const {
        return Iterator(nullptr);
    }

	List() : start(nullptr) {}

	~List() {
		del(start);
	}

	void print() const {
		print(start);
	}

	void push_back(T x) {
		if (start == nullptr) {
			start = new Node<T>(x);
			return;
		}
		push_back(x, start);
	}
	
	void pop_back() {
		if (start == nullptr) {
			return;
		}
		if (start->next == nullptr) {
			delete[] start;
			start = nullptr;
			return;
		}
		pop_back(start);
	}

private:
	void print(const Node<T>* top) const {
		if (top == nullptr) {
			return;
		}
		cout << top->data << " ";
		print(top->next);
	}

	void push_back(int x, Node<T>*& top) {
		if (top->next == nullptr) {
			top->next = new Node<T>(x);
			return;
		}
		push_back(x, top->next);
	}
	
	void pop_back(Node<T>*& top) {
		if (top->next->next == nullptr) {
			delete[] top->next;
			top->next = nullptr;
			return;
		}
		pop_back(top->next);
	}
	
	void del(Node<T>*& top) {
		if (top == nullptr) {
			return;
		}
		cout << "Deleting " << top->data << '\n';    // For test purposes - do NOT leave
		                                             // such lines in official solutions
		Node<T>* temp = top->next;
		delete top;
		del(temp);
	}
};