#pragma once
const unsigned MIN_CAPACITY = 16;

template<typename T>
class ArrayQueue {
    T* arr;                 // buffer
    unsigned capacity;      // buffer size
    T* first;               // the element that was inserted first
    T* last;                // the element that was inserted last 

    // We use this often, why not have it in a function?
    T* buffer_end() const {
        return arr + capacity - 1;
    }

public:
    ArrayQueue() {
        capacity = MIN_CAPACITY;
        arr = new T[capacity];
        first = nullptr;
        last = nullptr;
    }

    // Trivial
    ~ArrayQueue() {
        delete[] arr;
    }
    bool empty() const {
        return first == nullptr;
    }
    T get_first() const {
        return *first;
    }

    // 'push' helper
    bool no_space() const {
        return last == first - 1  ||  (last == buffer_end() && first == arr);
    }

    // Prettier solution than the one we wrote in class
    void push(const T& x) {
        if (empty()) {                  // We had missed this very important case!
            first = last = arr;
        }
        else {
            if (no_space()) {           // No need of comments here, right?
                resize();               // The more 'functional', the better!
            }
            last++;
            if (last > buffer_end()) {
                last = arr;
            }
        }
        // Now we're sure last points to the buffers' first free position, there's only 1 thing left.
        *last = x;
    }

    void pop() {
        if (empty()) {                  // Case 1: No elements
            return;
        }
        if (first == last) {            // Case 2: 1 element
            first = last = nullptr;
            return;
        }
        first++;                        // Case 3: More elements
        if (first > buffer_end()) {
            first = arr;
        }
    }

private:
    // Rewritten with for-s - shorter and probably more understandable
    void resize() {
        T* temp = new T[2 * capacity];      // New buffer
        unsigned i = 0;                     // Its first free position
        T* crr;                             // 'Iterator' for the old buffer

        // We copy the two parts of the old buffer into the new, fixing the elements' order
        for (crr = first; crr <= buffer_end(); crr++) {
            temp[i] = *crr;
            i++;
        }
        for (crr = arr; crr < first; crr++) {
            temp[i] = *crr;
            i++;
        }
        
        delete[] arr;       // Everything is copied, let's free the old memory...
        
        arr = temp;         // ...and update all the variables
        capacity *= 2;      // capacity wasn't updated earlier because it was used - in buffer_end()
        first = arr;
        last = arr + i - 1;
    }
};
