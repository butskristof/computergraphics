void createCube(Figure& f) {
    f.points.push_back( Vector3D::point( 1, -1, 1 ) );
    f.points.push_back( Vector3D::point( -1, 1, -1 ) );
    f.points.push_back( Vector3D::point( 1, 1, 1 ) );
    f.points.push_back( Vector3D::point( -1, -1, 1 ) );
    f.points.push_back( Vector3D::point( 1, 1, -1 ) );
    f.points.push_back( Vector3D::point( -1, -1, -1 ) );
    f.points.push_back( Vector3D::point( 1, -1, 1 ) );
    f.points.push_back( Vector3D::point( -1, 1, 1 ) );

    Face temp;
    temp.point_indexes.push_back( 0 );
    temp.point_indexes.push_back( 4 );
    temp.point_indexes.push_back( 2 );
    temp.point_indexes.push_back( 6 );
    f.faces.push_back( temp );
    temp.point_indexes.clear();
    temp.point_indexes.push_back( 4 );
    temp.point_indexes.push_back( 1 );
    temp.point_indexes.push_back( 7 );
    temp.point_indexes.push_back( 2 );
    f.faces.push_back( temp  );
    temp.point_indexes.clear();
    temp.point_indexes.push_back( 1 );
    temp.point_indexes.push_back( 5 );
    temp.point_indexes.push_back( 3 );
    temp.point_indexes.push_back( 7 );
    f.faces.push_back( temp  );
    temp.point_indexes.clear();
    temp.point_indexes.push_back( 5 );
    temp.point_indexes.push_back( 0 );
    temp.point_indexes.push_back( 6 );
    temp.point_indexes.push_back( 3 );
    f.faces.push_back( temp  );
    temp.point_indexes.clear();
    temp.point_indexes.push_back( 6 );
    temp.point_indexes.push_back( 2 );
    temp.point_indexes.push_back( 7 );
    temp.point_indexes.push_back( 3 );
    f.faces.push_back( temp  );
    temp.point_indexes.clear();
    temp.point_indexes.push_back( 0 );
    temp.point_indexes.push_back( 5 );
    temp.point_indexes.push_back( 1 );
    temp.point_indexes.push_back( 4 );
    f.faces.push_back( temp  );
    temp.point_indexes.clear();
}

