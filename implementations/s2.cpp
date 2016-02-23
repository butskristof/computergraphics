
Matrix scaleFigure(double scale) {
    Matrix s;
    s(1, 1) = scale;
    s(2, 2) = scale;
    s(3, 3) = scale;
    return s;
}

Matrix rotateX(double angle) {
    Matrix mx;
    angle *= (-1);
    mx(2, 2) = std::cos(angle);
    mx(2, 3) = std::sin(angle) * (-1);
    mx(3, 2) = std::sin(angle);
    mx(3, 3) = std::cos(angle);
}

Matrix rotateY(double angle) {
    Matrix my;
    angle *= (-1);
    my(1, 1) = std::cos(angle);
    my(1, 3) = std::sin(angle);
    my(3, 1) = std::sin(angle) * (-1);
    my(3, 3) = std::cos(angle);
    return my;
}

Matrix rotateZ(double angle) {
    Matrix mz;
    angle *= (-1);
    mz(1, 1) = std::cos(angle);
    mz(1, 2) = std::sin(angle) * (-1);
    mz(2, 1) = std::sin(angle);
    mz(2, 2) = std::cos(angle);
    return mz;
}

Matrix translate(Vector3D v) {
    Matrix t;
    t(4, 1) = v.x;
    t(4, 2) = v.y;
    t(4, 3) = v.z;
    return t;
}

Matrix eyePoint(Vector3D eye) {
    Matrix m;
    double phi, theta, r;
    r = std::sqrt( pow( eye.x, 2 ) + pow(eye.y, 2) + pow(eye.z, 2) );
    phi = std::acos( eye.z / r );
    theta = std::atan2( eye.y, eye.z );

    m(1, 1) = std::sin(theta) * (-1);
    m(1, 2) = (-1) * std::cos(theta) * std::cos(phi);
    m(1, 3) = std::cos(theta) * std::sin(phi);
    m(2, 1) = std::cos(theta);
    m(2, 2) = (-1) * std::sin(theta) * std::cos(phi);
    m(2, 3) = std::sin(theta) * std::sin(phi);
    m(3, 2) = std::sin(phi);
    m(3, 3) = std::cos(phi);
    m(4, 3) = (-1) * r;

    return m;
}

void applyEyeTransformation(Figures3D& f, Matrix e) {
    for (auto i: f.size()) {
        applyTransformation(f[i], e);
    }
}

void applyTransformation(Figure& f, Matrix const& m) {
    for (auto i: f.points.size()) {
        f.points.at(i) *= m;
    }
}
