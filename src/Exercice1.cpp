#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

struct Point {
    int x;
    int y;

    Point() {          
        x = 0;
        y = 0;
    }

    Point(int x1, int y1) {  
        x = x1;
        y = y1;
    }
};

template <typename T>
class ArrayDyn {
private:
    T* data;
    size_t taille;
    size_t capacite;

    void reallouer(size_t nouvelleCapacite) { 
        T* nouveau = new T[nouvelleCapacite];
        for (size_t i = 0; i < taille; ++i)
            nouveau[i] = data[i];
        delete[] data;
        data = nouveau;
        capacite = nouvelleCapacite;
    }

public:
    ArrayDyn() : data(NULL), taille(0), capacite(0) {}
    ArrayDyn(size_t cap) : data(new T[cap]), taille(0), capacite(cap) {}

    ArrayDyn(const ArrayDyn& other)
        : data(new T[other.capacite]), taille(other.taille), capacite(other.capacite) {
        for (size_t i = 0; i < taille; ++i)
            data[i] = other.data[i];
    }

    ArrayDyn& operator=(const ArrayDyn& other) {
        if (this != &other) {
            delete[] data;
            data = new T[other.capacite];
            taille = other.taille;
            capacite = other.capacite;
            for (size_t i = 0; i < taille; ++i)
                data[i] = other.data[i];
        }
        return *this;
    }

    ~ArrayDyn() { delete[] data; }

    void push_back(const T& val) {
        if (taille == capacite) {
            size_t newCap = (capacite == 0) ? 1 : capacite * 2;
            reallouer(newCap);
        }
        data[taille++] = val;
    }

    void pop_back() {
        if (taille == 0)
            throw out_of_range("Array vide");
        --taille;
    }

    T& operator[](size_t index) {
        if (index >= taille)
            throw out_of_range(" hors limites");
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= taille)
            throw out_of_range(" hors limites");
        return data[index];
    }

    size_t size() const { return taille; }

    class Iterator {
    private:
        T* ptr;
    public:
        Iterator(T* p) : ptr(p) {}
        T& operator*() { return *ptr; }
        Iterator& operator++() { ++ptr; return *this; }
        Iterator operator++(int) { Iterator tmp = *this; ++ptr; return tmp; }
        Iterator& operator--() { --ptr; return *this; }
        Iterator operator--(int) { Iterator tmp = *this; --ptr; return tmp; }
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
        bool operator==(const Iterator& other) const { return ptr == other.ptr; }
    };

    Iterator begin() { return Iterator(data); }
    Iterator end() { return Iterator(data + taille); }
};


int main() {
 
    ArrayDyn<int> arr;
    arr.push_back(10);
    arr.push_back(22);
    arr.push_back(36);

    cout << "les entiers: ";
    for (ArrayDyn<int>::Iterator it = arr.begin(); it != arr.end(); ++it)
        cout << *it << " ";
 
    ArrayDyn<string> mots;
    mots.push_back("validee");
    mots.push_back("test");

    cout << " Les mots: ";
    for (ArrayDyn<string>::Iterator it = mots.begin(); it != mots.end(); ++it)
        cout << *it << " ";
    cout << "\n";

    ArrayDyn<Point> points;
    points.push_back(Point(10, 22));
    points.push_back(Point(36, 49));

    cout << "Points: ";
    for (ArrayDyn<Point>::Iterator it = points.begin(); it != points.end(); ++it)
        cout << "(" << (*it).x << "," << (*it).y << ") ";
    cout << "\n";

    return 0;
}



