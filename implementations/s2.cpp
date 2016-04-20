
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
    return mx;
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
    double phi, theta, r;
    r = std::sqrt( pow( eye.x, 2 ) + pow(eye.y, 2) + pow(eye.z, 2) );
    phi = std::acos( eye.z / r );
    theta = std::atan2( eye.y, eye.x );

    /*
    std::cout << "original eye: " << std::endl;
    std::cout << "(" << ( r * std::sin(phi)) * std::cos(theta) << ", " << r * std::sin(phi) * std::sin(theta) << ", " << r * std::cos(phi) << ")\n";
    std::cout << "r: " << r << ", phi: " << phi << ", theta: " << theta << std::endl;
    */

    Matrix m;
    m(1, 1) = std::sin(theta) * (-1);
    m(1, 2) = (-1) * std::cos(theta) * std::cos(phi);
    m(1, 3) = std::cos(theta) * std::sin(phi);
    m(2, 1) = std::cos(theta);
    m(2, 2) = (-1) * std::sin(theta) * std::cos(phi);
    m(2, 3) = std::sin(theta) * std::sin(phi);
    m(3, 2) = std::sin(phi);
    m(3, 3) = std::cos(phi);
    m(4, 3) = (-1) * r;

    /*
    Matrix v;
    v = rotateZ( (pi/2) + theta );
    v *= rotateX( phi );
    v *= translate( Vector3D::vector( 0, 0, (-1) * r) );
    */

    return m;
}

void applyTransformation(Figure& f, Matrix const& m) {
    for (int i = 0; i < f.points.size(); ++i) {
        f.points.at(i) *= m;
    }
}

void applyEyeTransformation(Figures3D& f, Matrix e) {
    for (int i = 0; i < f.size(); ++i) {
        applyTransformation(f.at(i), e);
    }
}

Point2D perspectivePointProjection(Vector3D point, double d) {
    double x = (d * point.x) / ( (-1) * point.z);
    double y = (d * point.y) / ( (-1) * point.z);

    return Point2D(x, y);

}

void perspectiveProjection( Figures3D& figures, Lines2D& lines) {

    for (int i = 0; i < figures.size(); ++i) {
        if ( figures.at(i).faces.size() != 0 ) {
            // for future
            for ( int j = 0; j < figures.at(i).faces.size(); ++j ) {
                for (int k = 0; k < figures.at(i).faces.at(j).point_indexes.size(); ++k) {
                    Point2D p1, p2;

                    if ( k == figures.at(i).faces.at(j).point_indexes.size() - 1 ) {
                        int pi1 = figures.at(i).faces.at(j).point_indexes.at(k);
                        int pi2 = figures.at(i).faces.at(j).point_indexes.at( 0 );

                        p1 = perspectivePointProjection( figures.at(i).points.at(pi1) , 1.0);
                        p2 = perspectivePointProjection( figures.at(i).points.at(pi2) , 1.0);

                    } else {
                        int pi1 = figures.at(i).faces.at(j).point_indexes.at(k);
                        int pi2 = figures.at(i).faces.at(j).point_indexes.at(k+1);

                        p1 = perspectivePointProjection( figures.at(i).points.at(pi1) , 1.0);
                        p2 = perspectivePointProjection( figures.at(i).points.at(pi2) , 1.0);
                    }

                lines.push_back( Line2D( p1, p2, figures.at(i).color ) );

                }
            }
        } else {
            for ( int j = 0; j < figures.at(i).lines.size(); ++j ) {
                Point2D p1, p2;

                p1 = perspectivePointProjection( figures.at(i).points.at( figures.at(i).lines.at(j).at(0) ) , 1.0 );
                p2 = perspectivePointProjection( figures.at(i).points.at( figures.at(i).lines.at(j).at(1) ) , 1.0 );

                double z1, z2;
                z1 = figures.at(i).points.at( figures.at(i).lines.at(j).at(0) ).z;
                z2 = figures.at(i).points.at( figures.at(i).lines.at(j).at(1) ).z;

                lines.push_back( Line2D( p1, z1, p2, z2, figures.at(i).color ) );

            }
        }
    }

}

