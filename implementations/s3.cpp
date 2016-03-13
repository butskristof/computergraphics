void createCube(Figure& f) {
    f.points.push_back( Vector3D::point( 1, -1, -1  )  );
    f.points.push_back( Vector3D::point( -1, 1, -1  )  );
    f.points.push_back( Vector3D::point( 1, 1, 1 )  );
    f.points.push_back( Vector3D::point( -1, -1, 1  )  );
    f.points.push_back( Vector3D::point( 1, 1, -1  )  );
    f.points.push_back( Vector3D::point( -1, -1, -1  )  );
    f.points.push_back( Vector3D::point( 1, -1, 1  )  );
    f.points.push_back( Vector3D::point( -1, 1, 1  )  );

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

void createTetrahedron(Figure& f) {
    f.points.push_back( Vector3D::point( 1, -1, -1 ) );
    f.points.push_back( Vector3D::point( -1, 1, -1 ) );
    f.points.push_back( Vector3D::point( 1, 1, 1 ) );
    f.points.push_back( Vector3D::point( -1, -1, 1 ) );


    Face temp;
    temp.point_indexes.push_back( 0 );
    temp.point_indexes.push_back( 1 );
    temp.point_indexes.push_back( 2 );
    f.faces.push_back( temp );
    temp.point_indexes.clear();
    temp.point_indexes.push_back( 1 );
    temp.point_indexes.push_back( 3 );
    temp.point_indexes.push_back( 2 );
    f.faces.push_back( temp );
    temp.point_indexes.clear();
    temp.point_indexes.push_back( 0 );
    temp.point_indexes.push_back( 3 );
    temp.point_indexes.push_back( 1 );
    f.faces.push_back( temp );
    temp.point_indexes.clear();
    temp.point_indexes.push_back( 0 );
    temp.point_indexes.push_back( 2 );
    temp.point_indexes.push_back( 3 );
    f.faces.push_back( temp );
    temp.point_indexes.clear();
}

void createOctahedron(Figure& f) {
    f.points.push_back( Vector3D::point( 1, 0, 0 ) );
    f.points.push_back( Vector3D::point( 0, 1, 0 ) );
    f.points.push_back( Vector3D::point( -1, 0, 0 ) );
    f.points.push_back( Vector3D::point( 0, -1, 0 ) );
    f.points.push_back( Vector3D::point( 0, 0, -1 ) );
    f.points.push_back( Vector3D::point( 0, 0, 1 ) );

    Face temp;
    temp.point_indexes.push_back( 0 );
    temp.point_indexes.push_back( 1 );
    temp.point_indexes.push_back( 5 );
    f.faces.push_back( temp );
    temp.point_indexes.clear();
    temp.point_indexes.push_back( 1 );
    temp.point_indexes.push_back( 2 );
    temp.point_indexes.push_back( 5 );
    f.faces.push_back( temp );
    temp.point_indexes.clear();
    temp.point_indexes.push_back( 2 );
    temp.point_indexes.push_back( 3 );
    temp.point_indexes.push_back( 5 );
    f.faces.push_back( temp );
    temp.point_indexes.clear();
    temp.point_indexes.push_back( 3 );
    temp.point_indexes.push_back( 0 );
    temp.point_indexes.push_back( 5 );
    f.faces.push_back( temp );
    temp.point_indexes.clear();
    temp.point_indexes.push_back( 1 );
    temp.point_indexes.push_back( 0 );
    temp.point_indexes.push_back( 4 );
    f.faces.push_back( temp );
    temp.point_indexes.clear();
    temp.point_indexes.push_back( 2 );
    temp.point_indexes.push_back( 1 );
    temp.point_indexes.push_back( 4 );
    f.faces.push_back( temp );
    temp.point_indexes.clear();
    temp.point_indexes.push_back( 3 );
    temp.point_indexes.push_back( 2 );
    temp.point_indexes.push_back( 4 );
    f.faces.push_back( temp );
    temp.point_indexes.clear();
    temp.point_indexes.push_back( 0 );
    temp.point_indexes.push_back( 3 );
    temp.point_indexes.push_back( 4 );
    f.faces.push_back( temp );
    temp.point_indexes.clear();
}

void createIcosahedron(Figure& f) {
    f.points.push_back( Vector3D::point( 0, 0, ( std::sqrt(5) / 2 ) ) );

    for (int i = 2; i <= 6; i++) {
        f.points.push_back( Vector3D::point( std::cos( ( (i-2)*2*pi )/5 ), ( std::sin( ((i-2)*2*pi)/5 ) ), (0.5)  ) );
    }
    for (int i = 7; i <= 11; i++) {
        f.points.push_back( Vector3D::point( std::cos( (pi/5) + (((i-7)*2*pi)/5) ), std::sin( (pi/5) + (((i-7)*2*pi)/5) ), -0.5 ) );
    }

    f.points.push_back( Vector3D::point( 0, 0, (-1) * ( std::sqrt(5) / 2 ) ) );


    Face temp;
    temp.point_indexes.push_back( 0 );
    temp.point_indexes.push_back( 1 );
    temp.point_indexes.push_back( 2 );
    f.faces.push_back( temp );
    temp.point_indexes.clear();
    temp.point_indexes.push_back( 0 );
    temp.point_indexes.push_back( 2 );
    temp.point_indexes.push_back( 3 );
    f.faces.push_back( temp );
    temp.point_indexes.clear();
    temp.point_indexes.push_back( 0 );
    temp.point_indexes.push_back( 3 );
    temp.point_indexes.push_back( 4 );
    f.faces.push_back( temp );
    temp.point_indexes.clear();
    temp.point_indexes.push_back( 0 );
    temp.point_indexes.push_back( 4 );
    temp.point_indexes.push_back( 5 );
    f.faces.push_back( temp );
    temp.point_indexes.clear();
    temp.point_indexes.push_back( 0 );
    temp.point_indexes.push_back( 5 );
    temp.point_indexes.push_back( 1 );
    f.faces.push_back( temp );
    temp.point_indexes.clear();
    temp.point_indexes.push_back( 1 );
    temp.point_indexes.push_back( 6 );
    temp.point_indexes.push_back( 2 );
    f.faces.push_back( temp );
    temp.point_indexes.clear();
    temp.point_indexes.push_back( 2 );
    temp.point_indexes.push_back( 6 );
    temp.point_indexes.push_back( 7 );
    f.faces.push_back( temp );
    temp.point_indexes.clear();
    temp.point_indexes.push_back( 2 );
    temp.point_indexes.push_back( 7 );
    temp.point_indexes.push_back( 3 );
    f.faces.push_back( temp );
    temp.point_indexes.clear();
    temp.point_indexes.push_back( 3 );
    temp.point_indexes.push_back( 7 );
    temp.point_indexes.push_back( 8 );
    f.faces.push_back( temp );
    temp.point_indexes.clear();
    temp.point_indexes.push_back( 3 );
    temp.point_indexes.push_back( 8 );
    temp.point_indexes.push_back( 4 );
    f.faces.push_back( temp );
    temp.point_indexes.clear();
    temp.point_indexes.push_back( 4 );
    temp.point_indexes.push_back( 8 );
    temp.point_indexes.push_back( 9 );
    f.faces.push_back( temp );
    temp.point_indexes.clear();
    temp.point_indexes.push_back( 4 );
    temp.point_indexes.push_back( 9 );
    temp.point_indexes.push_back( 5 );
    f.faces.push_back( temp );
    temp.point_indexes.clear();
    temp.point_indexes.push_back( 5 );
    temp.point_indexes.push_back( 9 );
    temp.point_indexes.push_back( 10 );
    f.faces.push_back( temp );
    temp.point_indexes.clear();
    temp.point_indexes.push_back( 5 );
    temp.point_indexes.push_back( 10 );
    temp.point_indexes.push_back( 1 );
    f.faces.push_back( temp );
    temp.point_indexes.clear();
    temp.point_indexes.push_back( 1 );
    temp.point_indexes.push_back( 10 );
    temp.point_indexes.push_back( 6 );
    f.faces.push_back( temp );
    temp.point_indexes.clear();
    temp.point_indexes.push_back( 11 );
    temp.point_indexes.push_back( 7 );
    temp.point_indexes.push_back( 6 );
    f.faces.push_back( temp );
    temp.point_indexes.clear();
    temp.point_indexes.push_back( 11 );
    temp.point_indexes.push_back( 8 );
    temp.point_indexes.push_back( 7 );
    f.faces.push_back( temp );
    temp.point_indexes.clear();
    temp.point_indexes.push_back( 11 );
    temp.point_indexes.push_back( 9 );
    temp.point_indexes.push_back( 8 );
    f.faces.push_back( temp );
    temp.point_indexes.clear();
    temp.point_indexes.push_back( 11 );
    temp.point_indexes.push_back( 10 );
    temp.point_indexes.push_back( 9 );
    f.faces.push_back( temp );
    temp.point_indexes.clear();
    temp.point_indexes.push_back( 11 );
    temp.point_indexes.push_back( 6 );
    temp.point_indexes.push_back( 10 );
    f.faces.push_back( temp );
    temp.point_indexes.clear();
}

void createDodecahedron(Figure& f) {
    Figure g;
    createIcosahedron(g);

    for (auto it: g.faces) {
        Vector3D p = Vector3D::point(0,0,0);
        p.x = ( g.points.at( it.point_indexes.at(0)).x  +  g.points.at( it.point_indexes.at(1)).x  +  g.points.at( it.point_indexes.at(2)).x  ) / 3;
        p.y = ( g.points.at( it.point_indexes.at(0)).y  +  g.points.at( it.point_indexes.at(1)).y  +  g.points.at( it.point_indexes.at(2)).y  ) / 3;
        p.z = ( g.points.at( it.point_indexes.at(0)).z  +  g.points.at( it.point_indexes.at(1)).z  +  g.points.at( it.point_indexes.at(2)).z  ) / 3;
        f.points.push_back( p );
    }

    Face temp;
    temp.point_indexes.push_back( 0 );
    temp.point_indexes.push_back( 1 );
    temp.point_indexes.push_back( 2 );
    temp.point_indexes.push_back( 3 );
    temp.point_indexes.push_back( 4 );
    f.faces.push_back( temp );
    temp.point_indexes.clear();
    temp.point_indexes.push_back( 0 );
    temp.point_indexes.push_back( 5 );
    temp.point_indexes.push_back( 6 );
    temp.point_indexes.push_back( 7 );
    temp.point_indexes.push_back( 1 );
    f.faces.push_back( temp );
    temp.point_indexes.clear();
    temp.point_indexes.push_back( 1 );
    temp.point_indexes.push_back( 7 );
    temp.point_indexes.push_back( 8 );
    temp.point_indexes.push_back( 9 );
    temp.point_indexes.push_back( 2 );
    f.faces.push_back( temp );
    temp.point_indexes.clear();
    temp.point_indexes.push_back( 2 );
    temp.point_indexes.push_back( 9 );
    temp.point_indexes.push_back( 10 );
    temp.point_indexes.push_back( 11 );
    temp.point_indexes.push_back( 3 );
    f.faces.push_back( temp );
    temp.point_indexes.clear();
    temp.point_indexes.push_back( 3 );
    temp.point_indexes.push_back( 11 );
    temp.point_indexes.push_back( 12 );
    temp.point_indexes.push_back( 13 );
    temp.point_indexes.push_back( 4 );
    f.faces.push_back( temp );
    temp.point_indexes.clear();
    temp.point_indexes.push_back( 4 );
    temp.point_indexes.push_back( 13 );
    temp.point_indexes.push_back( 14 );
    temp.point_indexes.push_back( 5 );
    temp.point_indexes.push_back( 0 );
    f.faces.push_back( temp );
    temp.point_indexes.clear();
    temp.point_indexes.push_back( 19 );
    temp.point_indexes.push_back( 18 );
    temp.point_indexes.push_back( 17 );
    temp.point_indexes.push_back( 16 );
    temp.point_indexes.push_back( 15 );
    f.faces.push_back( temp );
    temp.point_indexes.clear();
    temp.point_indexes.push_back( 19 );
    temp.point_indexes.push_back( 14 );
    temp.point_indexes.push_back( 13 );
    temp.point_indexes.push_back( 12 );
    temp.point_indexes.push_back( 18 );
    f.faces.push_back( temp );
    temp.point_indexes.clear();
    temp.point_indexes.push_back( 18 );
    temp.point_indexes.push_back( 12 );
    temp.point_indexes.push_back( 11 );
    temp.point_indexes.push_back( 10 );
    temp.point_indexes.push_back( 17 );
    f.faces.push_back( temp );
    temp.point_indexes.clear();
    temp.point_indexes.push_back( 17 );
    temp.point_indexes.push_back( 10 );
    temp.point_indexes.push_back( 9 );
    temp.point_indexes.push_back( 8 );
    temp.point_indexes.push_back( 16 );
    f.faces.push_back( temp );
    temp.point_indexes.clear();
    temp.point_indexes.push_back( 16 );
    temp.point_indexes.push_back( 8 );
    temp.point_indexes.push_back( 7 );
    temp.point_indexes.push_back( 6 );
    temp.point_indexes.push_back( 15 );
    f.faces.push_back( temp );
    temp.point_indexes.clear();
    temp.point_indexes.push_back( 15 );
    temp.point_indexes.push_back( 6 );
    temp.point_indexes.push_back( 5 );
    temp.point_indexes.push_back( 14 );
    temp.point_indexes.push_back( 19 );
    f.faces.push_back( temp );
    temp.point_indexes.clear();
}

void createCylinder(Figure& f, int n, double h) {
    for (int i = 0; i < n; i++) {
        f.points.push_back( Vector3D::point( std::cos( ( 2 * i * pi ) / n ), std::sin( ( 2 * i * pi ) / n  ), 0) );
        f.points.push_back( Vector3D::point( std::cos( ( 2 * i * pi ) / n ), std::sin( ( 2 * i * pi ) / n  ), h) );
    }

    Face r, b;
    for (int i = 0; i < (2*n); i+=2) {
        Face t;
        t.point_indexes.push_back( i );
        t.point_indexes.push_back( (i+2)%(2*n) );
        t.point_indexes.push_back( (i+3)%(2*n) );
        t.point_indexes.push_back( i + 1 );
        f.faces.push_back(t);

        b.point_indexes.push_back(i);
        r.point_indexes.push_back(i+1);
    }
    f.faces.push_back(b);
    f.faces.push_back(r);
}

void createCone(Figure& f, int n, double h) {
    //points
    for (int i = 0; i < n; i++) {
        f.points.push_back( Vector3D::point( std::cos( ( 2 * i * pi ) / n ), std::sin( ( 2 * i * pi ) / n  ), 0) );
    }
    f.points.push_back( Vector3D::point(0,0,h) ); // top

    //faces
    Face b; // bottom
    for (int i = 0; i < n; i++) {
        Face t;
        t.point_indexes.push_back( i );
        t.point_indexes.push_back( (i+1)%n );
        t.point_indexes.push_back( n );
        f.faces.push_back(t);
        b.point_indexes.push_back(i);
    }
    f.faces.push_back(b);
}

void createSphere(Figure& fff, int n) {
    Figure g = fff;
    createIcosahedron(g);
    if (n == 0) {
        fff = g;
        return;
    }
    Figure ff = fff;

    for (int i = 0; i < n; i++) {
        for (auto it: g.faces) {
            Vector3D a = g.points.at( it.point_indexes.at(0) );
            Vector3D b = g.points.at( it.point_indexes.at(1) );
            Vector3D c = g.points.at( it.point_indexes.at(2) );
            Vector3D d;
            Vector3D e;
            Vector3D f;

            d = Vector3D::point( (a.x+b.x)/2, (a.y+b.y)/2, (a.z+b.z)/2  );
            e = Vector3D::point( (a.x+c.x)/2, (a.y+c.y)/2, (a.z+c.z)/2  );
            f = Vector3D::point( (b.x+c.x)/2, (b.y+c.y)/2, (b.z+c.z)/2  );

            
            ff.points.push_back(a); //size-6
            ff.points.push_back(b); //size-5
            ff.points.push_back(c); //size-4
            ff.points.push_back(d); //size-3
            ff.points.push_back(e); //size-2
            ff.points.push_back(f); //size-1
            
            int vsize = ff.points.size();

            Face ade;
            //ade.points.push_back(&(ff.points.at( ff.points.end() - 6 )));
            ade.point_indexes.push_back(vsize-6);
            ade.point_indexes.push_back(vsize-3);
            ade.point_indexes.push_back(vsize-2);
            ff.faces.push_back(ade);
            Face bfd;
            bfd.point_indexes.push_back(vsize-5);
            bfd.point_indexes.push_back(vsize-1);
            bfd.point_indexes.push_back(vsize-3);
            ff.faces.push_back(bfd);
            Face cef;
            cef.point_indexes.push_back(vsize-4);
            cef.point_indexes.push_back(vsize-2);
            cef.point_indexes.push_back(vsize-1);
            ff.faces.push_back(cef);
            Face dfe;
            dfe.point_indexes.push_back(vsize-3);
            dfe.point_indexes.push_back(vsize-1);
            dfe.point_indexes.push_back(vsize-2);
            ff.faces.push_back(dfe);

        }

        g = ff;
        if (i != (n-1)) {
            ff = fff;
        }
    }
    fff = ff;
    return;
}

void createTorus(Figure& f, double r, double R, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            double u = (2*i*pi) / n;
            double v = (2*j*pi) / m;
            Vector3D p = Vector3D::point(0,0,0);
            p.x = (R + ( r * std::cos(v) )) * std::cos(u);
            p.y = (R + ( r * std::cos(v) )) * std::sin(u);
            p.z = r * std::sin(v);

            f.points.push_back(p);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            Face t;
            t.point_indexes.push_back( (i*m) + j );
            t.point_indexes.push_back( ( ( (i+1)%n  ) * m ) + j );
            t.point_indexes.push_back( (( (i+1)%n )*m) + ((j+1)%m)  );
            t.point_indexes.push_back( (i*m) + ( (j+1)%m ) );

            f.faces.push_back(t);
        }
    }
}
