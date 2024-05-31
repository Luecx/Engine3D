//
// Created by Luecx on 24.06.2021.
//

#ifndef ENGINE3D_SRC_MATH_PROJECTION_H_
#define ENGINE3D_SRC_MATH_PROJECTION_H_

#include "Matrix.h"
#include "Precision.h"

Matrix<4, 4> orthogonal(Precision left,
                        Precision right,
                        Precision top,
                        Precision bot,
                        Precision near,
                        Precision far);

Matrix<4, 4> perspective(Precision fov, Precision aspectRatio, Precision near, Precision far);

Matrix<4, 4> lookAt(Vector<3> const& eye, Vector<3> const& center, Vector<3> const& up);

#endif    // ENGINE3D_SRC_MATH_PROJECTION_H_
