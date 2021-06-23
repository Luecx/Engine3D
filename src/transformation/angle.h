//
// Created by Luecx on 23.06.2021.
//

#ifndef ENGINE3D_SRC_TRANSFORMATION_ANGLE_H_
#define ENGINE3D_SRC_TRANSFORMATION_ANGLE_H_

#include <cmath>
#include <iostream>

inline Precision toDegrees(Precision angle) {
    return angle * 180 / M_PI;
}
inline Precision toRadians(Precision angle) {
    return angle / 180 * M_PI;
}

inline Vector<3> matrixToDegrees(Matrix<4, 4>& m) {

    double cN1 = 0;
    double aN1 = 0;
    double bN1 = 0;

    if (m(2, 0) != 1 && m(2, 0) != -1) {
        bN1 = -asin(m(2, 0));
        aN1 = atan2(m(2, 1) / cos(bN1), m(2, 2) / cos(bN1));
        cN1 = atan2(m(1, 0) / cos(bN1), m(0, 0) / cos(bN1));
    } else {

        if (m(2, 0) == -1) {
            bN1 = M_PI_2;
            aN1 = cN1 + atan2(m(0,1), m(0,2));
        } else {
            bN1 = -M_PI_2;
            aN1 = -cN1 + atan2(-m(0,1), -m(0,2));
        }
    }

    Vector<3> angle{(Precision) toDegrees(aN1), (Precision) toDegrees(bN1),
                               (Precision) toDegrees(cN1)};
    return angle;
}

#endif    // ENGINE3D_SRC_TRANSFORMATION_ANGLE_H_
