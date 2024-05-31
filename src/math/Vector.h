//
// Created by Luecx on 31.05.2021.
//

#ifndef ENGINE3D_MATH_VECTOR_H_
#define ENGINE3D_MATH_VECTOR_H_

#include "Precision.h"

#include <cmath>
#include <cstring>
#include <iomanip>
#include <ostream>

template<int M>
class Vector {

    private:
    Precision values[M] {};

    public:
    Vector() {};
    Vector(Precision x, Precision y, Precision z) {
        static_assert(M >= 3);
        values[0] = x;
        values[1] = y;
        values[2] = z;
        if (M == 4) {
            values[3] = 1;
        }
    };
    Vector(Precision x, Precision y) {
        static_assert(M >= 2);
        values[0] = x;
        values[1] = y;
        if (M == 3) {
            values[2] = 1;
        }
    };
    Vector(Vector&& other) {
        std::memcpy(values, other.values, sizeof(Precision) * M);
    }
    Vector(const Vector& other) {
        std::memcpy(values, other.values, sizeof(Precision) * M);
    }

    void normalise() {
        Precision l = length();
        if (l == 0) {
            return;
        }
        (*this) *= 1.0 / l;
    }
    void clear() {
        std::memset(values, 0, M * sizeof(Precision));
    }
    Precision length() {
        return sqrt((*this) * (*this));
    }
    Precision operator*(const Vector<M>& other) {
        Precision sum = 0;
        for (int i = 0; i < M; i++) {
            sum += other[i] * (*this)(i);
        }
        return sum;
    }

    Vector<M> cross(const Vector<M>& other) const {
        static_assert(M == 3);
        Vector<M> res {};

        res[0] = (*this)[1] * other[2] - (*this)[2] * other[1];
        res[1] = -((*this)[0] * other[2] - (*this)[2] * other[0]);
        res[2] = (*this)[0] * other[1] - (*this)[1] * other[0];

        return res;
    }

    Vector<M> operator*(Precision other) const {
        Vector<M> vec {*this};
        vec *= other;
        return vec;
    }
    Vector<M>& operator*=(Precision other) {
        for (int i = 0; i < M; i++) {
            values[i] *= other;
        }
        return *this;
    }
    Vector<M> operator+(const Vector<M>& other) const {
        Vector<M> vec {*this};
        vec += other;
        return vec;
    }
    Vector<M>& operator+=(const Vector<M>& other) {
        for (int i = 0; i < M; i++) {
            values[i] += other[i];
        }
        return *this;
    }
    Vector<M> operator-(const Vector<M>& other) const {
        Vector<M> vec {*this};
        vec -= other;
        return vec;
    }
    Vector<M>& operator-=(const Vector<M>& other) {
        for (int i = 0; i < M; i++) {
            values[i] -= other[i];
        }
        return *this;
    }

    Vector<M>& operator=(const Vector<M>& other) {
        std::memcpy(values, other.values, sizeof(Precision) * M);
        return *this;
    }
    Vector<M>& operator=(Vector<M>&& other) {
        std::memcpy(values, other.values, sizeof(Precision) * M);
        return *this;
    }

    Precision& operator()(int index) {
        return values[index];
    }
    Precision& operator[](int index) {
        return values[index];
    }
    Precision operator()(int index) const {
        return values[index];
    }
    Precision operator[](int index) const {
        return values[index];
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector<M>& matrix) {
        os << std::fixed << std::setprecision(5);
        for (int i = 0; i < M; i++) {
            os << std::setw(10) << matrix.values[i] << ", ";
        }
        os << "\n";
        return os;
    }
};

#endif    // ENGINE3D_MATH_VECTOR_H_
