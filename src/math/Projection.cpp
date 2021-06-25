//
// Created by Luecx on 24.06.2021.
//
#include "Projection.h"

#include <iostream>
Matrix<4, 4> orthogonal(Precision left, Precision right, Precision top, Precision bot, Precision near, Precision far) {

    Matrix<4,4> projectionMatrix{};

    projectionMatrix(0,0) =   2 / (right - left);
    projectionMatrix(1,1) =   2 / (top   - bot);
    projectionMatrix(2,2) = - 2 / (far   - near);
    projectionMatrix(3,3) =   1;
    projectionMatrix(0,3) = - (right + left)   / (right - left);
    projectionMatrix(1,3) = - (top   + bot )   / (top   - bot);
    projectionMatrix(2,3) = - (far   + near)   / (far   - near);

    return projectionMatrix;
}
Matrix<4, 4> perspective(Precision fov, Precision aspectRatio, Precision near, Precision far) {
    Matrix<4,4> projectionMatrix{};

    Precision yScale         = (float) ((1.0 / tan((fov / 2.0) * M_PI / 180.0)));
    Precision xScale         = yScale / aspectRatio;
    Precision frustumLength  = far - near;

    projectionMatrix(0,0) = xScale;
    projectionMatrix(1,1) = yScale;
    projectionMatrix(2,2) = -(far+near) / frustumLength;
    projectionMatrix(3,2) = -1;
    projectionMatrix(2,3) = - 2 * near * far / frustumLength;

    return projectionMatrix;
}
Matrix<4, 4> lookAt(const Vector<3>& eye, const Vector<3>& center, const Vector<3>& up) {
    Vector<3> f = (center - eye);
    f.normalise();
    Vector<3> u = up;
    u.normalise();
    Vector<3> s = f;
    s = s.cross(u);
    s.normalise();
    u      = s.cross(f);

    Matrix<4, 4> res {};
    res(0,0) = s[0];
    res(0,1) = s[1];
    res(0,2) = s[2];
    res(1,0) = u[0];
    res(1,1) = u[1];
    res(1,2) = u[2];
    res(2,0) = -f[0];
    res(2,1) = -f[1];
    res(2,2) = -f[2];
    res(0,3) = -(s * eye);
    res(1,3) = -(u * eye);
    res(2,3) =  (f * eye);
    res(3,3) =  1;
    return res;
}
