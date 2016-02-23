
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
