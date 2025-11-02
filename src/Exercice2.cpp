#include <iostream>
#include <initializer_list>
#include <stdexcept>
using namespace std;


template <typename T, size_t N, size_t M>
class Matrice {
private:
    T data[N][M];

public:

    Matrice() {
        for (size_t i = 0; i < N; ++i)
            for (size_t j = 0; j < M; ++j)
                data[i][j] = T{};
    }

  Matrice(initializer_list<initializer_list<T>> init) {
        size_t i = 0;
        for (auto row : init) {
            if (i >= N) break;
            size_t j = 0;
            for (auto val : row) {
                if (j >= M) break;
                data[i][j] = val;
                ++j;
            }
            ++i;
        } 
		for (; i < N; ++i)
            for (size_t j = 0; j < M; ++j)
                data[i][j] = T{};
    }
public:
    T get(size_t i, size_t j) const { return data[i][j]; }
    void set(size_t i, size_t j, T val) { data[i][j] = val; }

    Matrice operator+(const Matrice& other) const {
        Matrice result;
        for (size_t i = 0; i < N; ++i)
            for (size_t j = 0; j < M; ++j)
                result.data[i][j] = data[i][j] + other.data[i][j];
        return result;
    }

   template <size_t P>
Matrice<T, N, P> operator*(const Matrice<T, M, P>& other) const {
    Matrice<T, N, P> result;
    for (size_t i = 0; i < N; ++i)
        for (size_t j = 0; j < P; ++j) {
            result.set(i, j, T{}); 
            for (size_t k = 0; k < M; ++k)
                result.set(i, j, result.get(i,j) + data[i][k] * other.get(k,j));
        }
    return result;
}

    friend ostream& operator<<(ostream& os, const Matrice& mat) {
        for (size_t i = 0; i < N; ++i) {
            os << "[ ";
            for (size_t j = 0; j < M; ++j) {
                os << mat.data[i][j] << " ";
            }
            os << "]\n";
        }
        return os;
    }
};


int main() {
    Matrice<int, 2, 3> A{{11,20,33},{45,56,67}};
    Matrice<int, 2, 3> B{{67,56,45},{33,20,11}};
    cout << "A + B =\n" << A + B << endl;

    Matrice<int, 3, 2> C{{1,2},{3,4},{5,6}};
    Matrice<int, 2, 2> D{{1,0},{0,1}};
    cout << "C * D =\n" << C * D << endl;

    Matrice<double, 2, 2> E{{1.5, 2.3},{3.4, 4.2}};
    Matrice<double, 2, 2> F{{0.75, 1.56},{2.3, 3.4}};
    cout << "E + F =\n" << E + F << endl;

    return 0;
}

