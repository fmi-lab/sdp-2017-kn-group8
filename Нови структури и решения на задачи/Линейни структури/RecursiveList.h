#pragma once
#include<iostream>
#include<vector>
using std::cout;
using std::vector;

template<typename T>
struct Node {
	T data;
	Node<T>* next;
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

    // A nice { 1, 2, 3 } - constructor
    List(const vector<T>& v) : start(nullptr) {
        for (unsigned i = 0; i < v.size(); i++)
            push_back(v[i]);
    }
    
    // Copy constructor and operator =, similar to DLList's 
    List(const List& other) : start(nullptr) {
        Node<T>* node_in_other = other.start;
        while (node_in_other != nullptr) {
            push_back(node_in_other->data);
            node_in_other = node_in_other->next;
        }
    }
    List& operator = (const List<T>& other) {
        if(this != &other) {
            del(start);
            start = nullptr;
            Node<T>* node_in_other = other.first;
            while (node_in_other != nullptr) {
                push_back(node_in_other->data);
                node_in_other = node_in_other->next;
            }
        }
        return *this;
    }

    void print() const {
		print(start);
	}

	void push_back(const T& x) {
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

    void remove(const T& x) {
        // ...
    }

    template <typename R>                   // R - Result type
    List<R> map(R (*f)(const T&)) const {
        List<R> result;
        for (Iterator it = begin(); it != end(); ++it) {
            result.push_back(f(*it));
        }
        return result;
    }
    
    void map_change(T(*f)(const T&)) {
        for (Iterator it = begin(); it != end(); ++it) {
            *it = f(*it);
        }
    }

    List<T> filter(bool(*pred)(const T&)) const {
        List<T> result;
        for (Iterator it = begin(); it != end(); ++it) {
            if (pred(*it)) {
                result.push_back(*it);
            }
        }
        return result;
    }

    // There is actually a better idea for this one, we'll discuss it later
    void filter_change(bool(*pred)(const T&)) {
        for (Iterator it = begin(); it != end(); ++it) {
            if (!pred(*it)) {
                remove(*it);
            }
        }
    }

    template <typename R>
    R reduce(void (*f)(R&, const T&), const R& init) const {
        R result = init;
        for (Iterator it = begin(); it != end(); ++it) {
            f(result, *it);
        }
        return result;
    }

private:
	void print(const Node<T>* top) const {
		if (top == nullptr) {
			return;
		}
		cout << top->data << " ";
		print(top->next);
	}

	void push_back(const T& x, Node<T>*& top) {
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