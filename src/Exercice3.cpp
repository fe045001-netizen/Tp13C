#include <iostream>
#include <memory>
#include <stdexcept>
#include <iterator>
#include <vector>

using namespace std;

class StackOverflow : public runtime_error {
public:
    StackOverflow() : runtime_error(" capacite depassee") {}
};

class StackUnderflow : public runtime_error {
public:
    StackUnderflow() : runtime_error(" pile vide") {}
};

template <typename T>
class Stack {
private:
    size_t capacity;               
    size_t topIndex;               
    unique_ptr<T[]> data;          

public:

Stack(size_t cap = 10) : capacity(cap), topIndex(0) {
    data = unique_ptr<T[]>(new T[capacity]);
}

template <typename InputIt>
Stack(InputIt begin, InputIt end) {
    capacity = distance(begin, end);
    topIndex = 0;
    data = unique_ptr<T[]>(new T[capacity]);
    for (auto it = begin; it != end; ++it) {
        push(*it);
    }
}

    void push(const T& value) {
        if (topIndex >= capacity)
            throw StackOverflow();
        data[topIndex++] = value;
    }

    T pop() {
        if (topIndex == 0)
            throw StackUnderflow();
        return data[--topIndex];
    }

    T peek() const {
        if (topIndex == 0)
            throw StackUnderflow();
        return data[topIndex - 1];
    }

    bool empty() const {
        return topIndex == 0;
    }

    size_t size() const {
        return topIndex;
    }
};

int main() {
    try {
	 Stack<int> s1(4);

        for (int i = 1; i <= 4; ++i) {
            s1.push(i);
            cout << "Push: " << i << endl;
        }

        cout << "Sommet: " << s1.peek() << endl;

        while (!s1.empty()) {
            cout << "Pop: " << s1.pop() << endl;
        }

        vector<int> v = {1,2,3,4};
        Stack<int> s2(v.begin(), v.end());

        cout << "Pile initialisée depuis vector:" << endl;
        while (!s2.empty()) {
            cout << s2.pop() << " ";
        }
        cout << endl;

    } catch (const exception& e) {
        cerr << "Erreur: " << e.what() << endl;
    }

    return 0;
}

