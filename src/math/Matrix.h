//
// Created by Luecx on 31.05.2021.
//

#ifndef ENGINE3D_MATH_MATRIX_H_
#define ENGINE3D_MATH_MATRIX_H_

#include "Precision.h"
#include "Vector.h"

#include <algorithm>
#include <cassert>
#include <cstring>
#include <iomanip>
#include <ostream>
template<int M, int N>
class Matrix {

    private:
    Precision values[M][N] {};

    public:
    void identity() {
        clear();
        for (int i = 0; i < std::min(M, N); i++) {
            values[i][i] = 1;
        }
    }
    void clear() {
        std::memset(values, 0, M * N * sizeof(Precision));
    }

    void translate3D(const Vector<3>& translation) {
        static_assert(M == N && M == 4);
        (*this)(0, 3) += (*this)(0, 0) * translation[0] + (*this)(0, 1) * translation[1]
                         + (*this)(0, 2) * translation[2];
        (*this)(1, 3) += (*this)(1, 0) * translation[0] + (*this)(1, 1) * translation[1]
                         + (*this)(1, 2) * translation[2];
        (*this)(2, 3) += (*this)(2, 0) * translation[0] + (*this)(2, 1) * translation[1]
                         + (*this)(2, 2) * translation[2];
        (*this)(3, 3) += (*this)(3, 0) * translation[0] + (*this)(3, 1) * translation[1]
                         + (*this)(3, 2) * translation[2];
    }
    void scale3D(const Vector<3>& scale) {
        static_assert(M == N && M == 4);
        (*this)(0, 0) = (*this)(0, 0) * scale(0);
        (*this)(1, 0) = (*this)(1, 0) * scale(0);
        (*this)(2, 0) = (*this)(2, 0) * scale(0);
        (*this)(3, 0) = (*this)(3, 0) * scale(0);
        (*this)(0, 1) = (*this)(0, 1) * scale(1);
        (*this)(1, 1) = (*this)(1, 1) * scale(1);
        (*this)(2, 1) = (*this)(2, 1) * scale(1);
        (*this)(3, 1) = (*this)(3, 1) * scale(1);
        (*this)(0, 2) = (*this)(0, 2) * scale(2);
        (*this)(1, 2) = (*this)(1, 2) * scale(2);
        (*this)(2, 2) = (*this)(2, 2) * scale(2);
        (*this)(3, 2) = (*this)(3, 2) * scale(2);
    }
    void rotate3D(Precision angle, const Vector<3>& axis) {
        static_assert(M == N && M == 4);
        Precision c         = (Precision) cos(angle);
        Precision s         = (Precision) sin(angle);
        Precision oneminusc = 1.0f - c;
        Precision xy        = axis[0] * axis[1];
        Precision yz        = axis[1] * axis[2];
        Precision xz        = axis[0] * axis[2];
        Precision xs        = axis[0] * s;
        Precision ys        = axis[1] * s;
        Precision zs        = axis[2] * s;

        Precision f00       = axis[0] * axis[0] * oneminusc + c;
        Precision f01       = xy * oneminusc + zs;
        Precision f02       = xz * oneminusc - ys;
        // n[3] not used
        Precision f10 = xy * oneminusc - zs;
        Precision f11 = axis[1] * axis[1] * oneminusc + c;
        Precision f12 = yz * oneminusc + xs;
        // n[7] not used
        Precision f20 = xz * oneminusc + ys;
        Precision f21 = yz * oneminusc - xs;
        Precision f22 = axis[2] * axis[2] * oneminusc + c;

        Precision t00 = (*this)(0, 0) * f00 + (*this)(0, 1) * f01 + (*this)(0, 2) * f02;
        Precision t01 = (*this)(1, 0) * f00 + (*this)(1, 1) * f01 + (*this)(1, 2) * f02;
        Precision t02 = (*this)(2, 0) * f00 + (*this)(2, 1) * f01 + (*this)(2, 2) * f02;
        Precision t03 = (*this)(3, 0) * f00 + (*this)(3, 1) * f01 + (*this)(3, 2) * f02;
        Precision t10 = (*this)(0, 0) * f10 + (*this)(0, 1) * f11 + (*this)(0, 2) * f12;
        Precision t11 = (*this)(1, 0) * f10 + (*this)(1, 1) * f11 + (*this)(1, 2) * f12;
        Precision t12 = (*this)(2, 0) * f10 + (*this)(2, 1) * f11 + (*this)(2, 2) * f12;
        Precision t13 = (*this)(3, 0) * f10 + (*this)(3, 1) * f11 + (*this)(3, 2) * f12;
        (*this)(0, 2) = (*this)(0, 0) * f20 + (*this)(0, 1) * f21 + (*this)(0, 2) * f22;
        (*this)(1, 2) = (*this)(1, 0) * f20 + (*this)(1, 1) * f21 + (*this)(1, 2) * f22;
        (*this)(2, 2) = (*this)(2, 0) * f20 + (*this)(2, 1) * f21 + (*this)(2, 2) * f22;
        (*this)(3, 2) = (*this)(3, 0) * f20 + (*this)(3, 1) * f21 + (*this)(3, 2) * f22;
        (*this)(0, 0) = t00;
        (*this)(1, 0) = t01;
        (*this)(2, 0) = t02;
        (*this)(3, 0) = t03;
        (*this)(0, 1) = t10;
        (*this)(1, 1) = t11;
        (*this)(2, 1) = t12;
        (*this)(3, 1) = t13;
    }

    template<int J>
    Matrix<M, J> operator*(const Matrix<N, J>& other) {
        Matrix<M, J> res {};
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < J; j++) {
                Precision h = 0;
                for (int r = 0; r < N; r++) {
                    h += other(r, j) * values[i][r];
                }
                res(i, j) = h;
            }
        }
        return res;
    }
    Matrix<M, N> operator*(Precision other) const {
        Matrix<M, N> vec {*this};
        vec *= other;
        return vec;
    }
    Matrix<M, N>& operator*=(Precision other) {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                values[i][j] *= other;
            }
        }
        return *this;
    }
    Matrix<M, N> operator+(const Matrix<M, N>& other) const {
        Matrix<M, N> vec {*this};
        vec += other;
        return vec;
    }
    Matrix<M, N>& operator+=(const Matrix<M, N>& other) {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                values[i][j] += other(i, j);
            }
        }
        return *this;
    }
    Matrix<M, N> operator-(const Matrix<M, N>& other) const {
        Matrix<M, N> vec {*this};
        vec -= other;
        return vec;
    }
    Matrix<M, N>& operator-=(const Matrix<M, N>& other) {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                values[i][j] -= other(i, j);
            }
        }
        return *this;
    }

    Matrix<M, N> invert() {
        static_assert(M == N);
        static_assert(M == 4);

        if constexpr (M == 4) {

            Matrix<M, M> inv {};

            inv[0] = (*this)[5] * (*this)[10] * (*this)[15] - (*this)[5] * (*this)[11] * (*this)[14]
                     - (*this)[9] * (*this)[6] * (*this)[15] + (*this)[9] * (*this)[7] * (*this)[14]
                     + (*this)[13] * (*this)[6] * (*this)[11]
                     - (*this)[13] * (*this)[7] * (*this)[10];

            inv[4] = -(*this)[4] * (*this)[10] * (*this)[15] + (*this)[4] * (*this)[11] * (*this)[14]
                     + (*this)[8] * (*this)[6] * (*this)[15] - (*this)[8] * (*this)[7] * (*this)[14]
                     - (*this)[12] * (*this)[6] * (*this)[11]
                     + (*this)[12] * (*this)[7] * (*this)[10];

            inv[8] = (*this)[4] * (*this)[9] * (*this)[15] - (*this)[4] * (*this)[11] * (*this)[13]
                     - (*this)[8] * (*this)[5] * (*this)[15] + (*this)[8] * (*this)[7] * (*this)[13]
                     + (*this)[12] * (*this)[5] * (*this)[11] - (*this)[12] * (*this)[7] * (*this)[9];

            inv[12] = -(*this)[4] * (*this)[9] * (*this)[14] + (*this)[4] * (*this)[10] * (*this)[13]
                      + (*this)[8] * (*this)[5] * (*this)[14] - (*this)[8] * (*this)[6] * (*this)[13]
                      - (*this)[12] * (*this)[5] * (*this)[10]
                      + (*this)[12] * (*this)[6] * (*this)[9];

            inv[1] = -(*this)[1] * (*this)[10] * (*this)[15] + (*this)[1] * (*this)[11] * (*this)[14]
                     + (*this)[9] * (*this)[2] * (*this)[15] - (*this)[9] * (*this)[3] * (*this)[14]
                     - (*this)[13] * (*this)[2] * (*this)[11]
                     + (*this)[13] * (*this)[3] * (*this)[10];

            inv[5] = (*this)[0] * (*this)[10] * (*this)[15] - (*this)[0] * (*this)[11] * (*this)[14]
                     - (*this)[8] * (*this)[2] * (*this)[15] + (*this)[8] * (*this)[3] * (*this)[14]
                     + (*this)[12] * (*this)[2] * (*this)[11]
                     - (*this)[12] * (*this)[3] * (*this)[10];

            inv[9] = -(*this)[0] * (*this)[9] * (*this)[15] + (*this)[0] * (*this)[11] * (*this)[13]
                     + (*this)[8] * (*this)[1] * (*this)[15] - (*this)[8] * (*this)[3] * (*this)[13]
                     - (*this)[12] * (*this)[1] * (*this)[11] + (*this)[12] * (*this)[3] * (*this)[9];

            inv[13] = (*this)[0] * (*this)[9] * (*this)[14] - (*this)[0] * (*this)[10] * (*this)[13]
                      - (*this)[8] * (*this)[1] * (*this)[14] + (*this)[8] * (*this)[2] * (*this)[13]
                      + (*this)[12] * (*this)[1] * (*this)[10]
                      - (*this)[12] * (*this)[2] * (*this)[9];

            inv[2] = (*this)[1] * (*this)[6] * (*this)[15] - (*this)[1] * (*this)[7] * (*this)[14]
                     - (*this)[5] * (*this)[2] * (*this)[15] + (*this)[5] * (*this)[3] * (*this)[14]
                     + (*this)[13] * (*this)[2] * (*this)[7] - (*this)[13] * (*this)[3] * (*this)[6];

            inv[6] = -(*this)[0] * (*this)[6] * (*this)[15] + (*this)[0] * (*this)[7] * (*this)[14]
                     + (*this)[4] * (*this)[2] * (*this)[15] - (*this)[4] * (*this)[3] * (*this)[14]
                     - (*this)[12] * (*this)[2] * (*this)[7] + (*this)[12] * (*this)[3] * (*this)[6];

            inv[10] = (*this)[0] * (*this)[5] * (*this)[15] - (*this)[0] * (*this)[7] * (*this)[13]
                      - (*this)[4] * (*this)[1] * (*this)[15] + (*this)[4] * (*this)[3] * (*this)[13]
                      + (*this)[12] * (*this)[1] * (*this)[7] - (*this)[12] * (*this)[3] * (*this)[5];

            inv[14] = -(*this)[0] * (*this)[5] * (*this)[14] + (*this)[0] * (*this)[6] * (*this)[13]
                      + (*this)[4] * (*this)[1] * (*this)[14] - (*this)[4] * (*this)[2] * (*this)[13]
                      - (*this)[12] * (*this)[1] * (*this)[6] + (*this)[12] * (*this)[2] * (*this)[5];

            inv[3] = -(*this)[1] * (*this)[6] * (*this)[11] + (*this)[1] * (*this)[7] * (*this)[10]
                     + (*this)[5] * (*this)[2] * (*this)[11] - (*this)[5] * (*this)[3] * (*this)[10]
                     - (*this)[9] * (*this)[2] * (*this)[7] + (*this)[9] * (*this)[3] * (*this)[6];

            inv[7] = (*this)[0] * (*this)[6] * (*this)[11] - (*this)[0] * (*this)[7] * (*this)[10]
                     - (*this)[4] * (*this)[2] * (*this)[11] + (*this)[4] * (*this)[3] * (*this)[10]
                     + (*this)[8] * (*this)[2] * (*this)[7] - (*this)[8] * (*this)[3] * (*this)[6];

            inv[11] = -(*this)[0] * (*this)[5] * (*this)[11] + (*this)[0] * (*this)[7] * (*this)[9]
                      + (*this)[4] * (*this)[1] * (*this)[11] - (*this)[4] * (*this)[3] * (*this)[9]
                      - (*this)[8] * (*this)[1] * (*this)[7] + (*this)[8] * (*this)[3] * (*this)[5];

            inv[15] = (*this)[0] * (*this)[5] * (*this)[10] - (*this)[0] * (*this)[6] * (*this)[9]
                      - (*this)[4] * (*this)[1] * (*this)[10] + (*this)[4] * (*this)[2] * (*this)[9]
                      + (*this)[8] * (*this)[1] * (*this)[6] - (*this)[8] * (*this)[2] * (*this)[5];

            Precision det = (*this)[0] * inv[0] + (*this)[1] * inv[4] + (*this)[2] * inv[8]
                            + (*this)[3] * inv[12];

            assert(det != 0);

            det = 1.0 / det;

            inv *= det;
            return inv;
        }
    }

    Vector<M> operator*(const Vector<N>& other) const {
        Vector<M> res {};

        for (int i = 0; i < M; i++) {
            Precision sum = 0;

            for (int j = 0; j < N; j++) {
                sum += values[i][j] * other[j];
            }

            res[i] = sum;
        }

        return res;
    }

    Precision& operator()(int m, int n) {
        return values[m][n];
    }
    Precision operator()(int m, int n) const {
        return values[m][n];
    }
    Precision& operator[](int index) {
        return values[index % M][index / N];
    }
    Precision operator()(int index) const {
        return values[index % M][index / N];
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix<M, N>& matrix) {
        os << std::fixed << std::setprecision(5);
        for (int i = 0; i < M; i++) {
            for (int n = 0; n < N; n++) {
                os << std::setw(10) << matrix.values[i][n] << ", ";
            }
            os << "\n";
        }
        return os;
    }
};

#endif    // ENGINE3D_MATH_MATRIX_H_
