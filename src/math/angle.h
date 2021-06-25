//
// Created by Luecx on 23.06.2021.
//

#ifndef ENGINE3D_SRC_TRANSFORMATION_ANGLE_H_
#define ENGINE3D_SRC_TRANSFORMATION_ANGLE_H_

#include "Matrix.h"
#include "Precision.h"
#include "Vector.h"

#include <cmath>
#include <iostream>

Precision toDegrees(Precision angle);

Precision toRadians(Precision angle);

Vector<3> matrixToDegrees(Matrix<4, 4>& m);

#endif    // ENGINE3D_SRC_TRANSFORMATION_ANGLE_H_
