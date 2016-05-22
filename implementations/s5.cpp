

void triangulate(Face const& face, std::vector<Face>& faces) { 
    for (int i = 1; i < (face.point_indexes.size() - 1); i++) {
        Face t;
        t.point_indexes.push_back(face.point_indexes.at(0));
        t.point_indexes.push_back(face.point_indexes.at(i));
        t.point_indexes.push_back(face.point_indexes.at(i+1));
        faces.push_back(t);
    }
}

void draw_zbuf_triag(ZBuffer& zb, img::EasyImage& img, Vector3D const& A, Vector3D const& B, Vector3D const& C, double d, double dx, double dy, img::Color color) {
    // projection

    Point2D ap, bp, cp; // projected corners
    ap.setX( ( ( d * A.x ) / ((-1) * A.z)  ) + dx );
    ap.setY( ( ( d * A.y ) / ((-1) * A.z)  ) + dy );
    bp.setX( ( ( d * B.x ) / ((-1) * B.z)  ) + dx );
    bp.setY( ( ( d * B.y ) / ((-1) * B.z)  ) + dy );
    cp.setX( ( ( d * C.x ) / ((-1) * C.z)  ) + dx );
    cp.setY( ( ( d * C.y ) / ((-1) * C.z)  ) + dy );

    // calculate pixels in triangle

    double ymin, ymax;
    ymin = std::min(ap.getY(), std::min(bp.getY(), cp.getY())); //round + 0.5?
    ymax = std::max(ap.getY(), std::max(bp.getY(), cp.getY()));

    Point2D p = ap;
    if (bp.getY() > p.getY()) {
        p = bp;
    }
    if (cp.getY() > p.getY()) {
        p = cp;
    }
    Point2D q = ap;
    if (bp.getY() < q.getY()) {
        q = bp;
    }
    if (cp.getY() < q.getY()) {
        q = cp;
    }


    for (int i = ymin; i < ymax; i++) {
    
        // calculate xl and xr

        if ( !((i - ymax)*(i - ymin) <= 0) or ymin == ymax  ) {
            continue;
        }

        double xi;

        double xlab = std::numeric_limits<double>::infinity();
        double xlac = std::numeric_limits<double>::infinity();
        double xlbc = std::numeric_limits<double>::infinity();
        double xrab = std::numeric_limits<double>::infinity() * (-1);
        double xrac = std::numeric_limits<double>::infinity() * (-1);
        double xrbc = std::numeric_limits<double>::infinity() * (-1);

        
        /*
        if ( (p == ap and q == bp) or ( (p == bp) and (q == ap) ) ) {
            std::cout << "ab" << std::endl;
            xlab = xi;
            xrab = xi;
        } else if ( ( p == bp and q == cp  ) or ( p == cp and q == bp )  ) {
            std::cout << "bc" << std::endl;
            xlbc = xi;
            xrbc = xi;
        } else if ( ( p == ap and q == cp ) or ( p == cp and q == ap ) ) {
            std::cout << "ac" << std::endl;
            xlac = xi;
            xrac = xi;
        }
        */

        if ( (i - ap.getY())*(i-bp.getY()) <= 0 and ap.getY() != bp.getY() ) {
            xi = ap.getX() + ( ( bp.getX()-ap.getX() )*( ( i - ap.getY() )/( bp.getY() - ap.getY() ) ) );
            xlab = xi;
            xrab = xi;
        }
        if ( (i - bp.getY())*(i-cp.getY()) <= 0 and bp.getY() != cp.getY() ) {
            xi = bp.getX() + ( ( cp.getX()-bp.getX() )*( ( i - bp.getY() )/( cp.getY() - bp.getY() ) ) );
            xlbc = xi;
            xrbc = xi;
        }
        if ( (i - ap.getY())*(i-cp.getY()) <= 0 and ap.getY() != cp.getY() ) {
            xi = ap.getX() + ( ( cp.getX()-ap.getX() )*( ( i - ap.getY() )/( cp.getY() - ap.getY() ) ) );
            xlac = xi;
            xrac = xi;
        }

        int xl, xr;
        xl = roundToInt(std::min(xlab, std::min(xlbc, xlac)) + 0.5);
        xr = roundToInt(std::max(xrab, std::max(xrbc, xrac)) - 0.5);

        double xg = ( ap.getX() + bp.getX() + cp.getX() ) / 3;
        double yg = ( ap.getY() + bp.getY() + cp.getY() ) / 3;
        double zg = (1/(3*A.z)) + (1/(3*B.z)) + (1/(3*C.z));

        for (int j = xl; j <= xr; j++) {
            // calculate 1/z values
            double dzdx, dzdy;
            Vector3D w = Vector3D::cross((B-A), (C-A));

            double k = (w.x * A.x) + (w.y * A.y) + (w.z * A.z);

            dzdx = w.x / ((-1) * d * k);
            dzdy = w.y / ((-1) * d * k);

            double z = (1.0001*zg) + ((j-xg)*dzdx) + ((i-yg)*dzdy);
            if ( z < zb.buffer[j][i] ) {
                zb.buffer[j][i] = z;
                img(j, i) = color;
            }
        }

    }

}

img::EasyImage drawZBufferedImage(const Figures3D& figures , const unsigned int size, const img::Color bgc = img::Color()) {
    // first project points, calculate arguments and create ZBuffer

    Lines2D l;

    // project points
    for ( int i = 0; i < figures.size(); ++i) {
        for ( auto j = 0; j < figures.at(i).faces.size(); ++j) {
            if ( figures.at(i).faces.at(j).point_indexes.size() != 0 ) {
                std::vector<Point2D> v;
                std::vector<double> zv; // original z values
                for ( int k = 0; k < figures.at(i).faces.at(j).point_indexes.size(); ++k) {
                    Point2D p = perspectivePointProjection( figures.at(i).points.at( figures.at(i).faces.at(j).point_indexes.at(k) ), 1.0 );
                    v.push_back(p);
                    zv.push_back( figures.at(i).points.at( figures.at(i).faces.at(j).point_indexes.at(k) ).z );
                }

                for ( int k = 0; k < v.size(); ++k ) {
                    if ( k == ( v.size() - 1 ) ) {
                        l.push_back( Line2D( v.at(k), zv.at(k), v.at(0), zv.at(0), figures.at(i).color ) );
                    } else {
                        l.push_back( Line2D( v.at(k), zv.at(k), v.at(k+1), zv.at(k+1), figures.at(i).color ) );
                    }
                }
            }
        }
    }


        // calculate argument values (size, offset, d, ...)

        // find xmin, xmax, ymin, ymax

        double xmin = INT_MAX, xmax = 0, ymin = INT_MAX, ymax = 0;
        for (auto it: l) {
            if (it.getp1()->getX() < xmin) {
                xmin = it.getp1()->getX();
            }
            if (it.getp1()->getY() < ymin ) {
                ymin = it.getp1()->getY();
            }
            if (it.getp1()->getX() > xmax) {
                xmax = it.getp1()->getX();
            }
            if (it.getp1()->getY() > ymax) {
                ymax = it.getp1()->getY();
            }

            if (it.getp2()->getX() < xmin) {
                xmin = it.getp2()->getX();
            }
            if (it.getp2()->getY() < ymin ) {
                ymin = it.getp2()->getY();
            }
            if (it.getp2()->getX() > xmax) {
                xmax = it.getp2()->getX();
            }
            if (it.getp2()->getY() > ymax) {
                ymax = it.getp2()->getY();
            }
        }

        double xrange = xmax - xmin;
        double yrange = ymax - ymin;
        double wi = size * (xrange/std::max(xrange,yrange));
        double hi = size * (yrange/std::max(xrange,yrange));
        img::EasyImage img = img::EasyImage(wi, hi, bgc);

        ZBuffer zb = ZBuffer(wi, hi);
        double d = 0.95 * (wi/xrange);

        double dcx = d * ( (xmin+xmax) / 2 );
        double dcy = d * ( (ymin+ymax) / 2 );
        double dx = (wi/2) - dcx;
        double dy = (hi/2) - dcy;


        for (auto it: figures) {
            for ( int i = 0; i < it.faces.size(); ++i ) {
                std::vector<Face> tf;
                triangulate(it.faces.at(i), tf);
                for ( auto it2: tf ) {
                    draw_zbuf_triag( zb, img, it.points.at(it2.point_indexes.at(0)), it.points.at(it2.point_indexes.at(1)), it.points.at(it2.point_indexes.at(2)), d, dx, dy, it.color );
                }
            }
        }

    return img;

}
