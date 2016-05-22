#include "easy_image.hh"
#include "ini_configuration.hh"


#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include <utility> // std::swap

// general additions
    // pi: we want a good approximation for our calculations
    // this can be used throughout the whole project
    #define _USE_MATH_DEFINES
    #include <cmath>
    double pi = M_PI; // pi to 50 decimal places

    // rounding is important!
    inline int roundToInt(double d) {
        return d < 0 ? std::ceil(d-0.5): std::floor(d+0.5);
    }

    // session 2
    #include "vector/vector.hh"
    #include "implementations/Face.hh"
    #include "implementations/Figure.hh"

// implementations

    // intro
    #include "implementations/intro.cpp" // colorRectangle, blocks, quartercircle

    // session 1
    #include "implementations/Point2D.hh" // Point2D
    #include "implementations/Lines2D.hh" // Line2D
    #include "implementations/ZBuffer.hh"
    #include "implementations/s1.cpp" // draw2DLines

    #include "implementations/2dlsystems.cpp" // L-system shizzle

    // session 2
    #include "implementations/s2.cpp"

    // session 3
    #include "implementations/s3.cpp"

    // session 4
        // s4.cpp already included in s1.cpp

    // session 5 
    #include "implementations/s5.cpp"

// root function, more like root of all evil

img::EasyImage generate_image(const ini::Configuration &configuration)
{
    std::string type = configuration["General"]["type"].as_string_or_die(); // type must ALWAYS be set

    img::EasyImage image;

    if ( type == "IntroColorRectangle" ) {
        unsigned int width = configuration["ImageProperties"]["width"].as_int_or_die();
        unsigned int height = configuration["ImageProperties"]["height"].as_int_or_die();
        image = colorRectangle( width, height );
    } else if ( type == "IntroBlocks") {
        unsigned int width = configuration["ImageProperties"]["width"].as_int_or_die();
        unsigned int height = configuration["ImageProperties"]["height"].as_int_or_die();
        unsigned int nrXBlocks = configuration["BlockProperties"]["nrXBlocks"].as_int_or_die();
        unsigned int nrYBlocks = configuration["BlockProperties"]["nrYBlocks"].as_int_or_die();
        ini::DoubleTuple colorWhite = configuration["BlockProperties"]["colorWhite"].as_double_tuple_or_die();
        ini::DoubleTuple colorBlack = configuration["BlockProperties"]["colorBlack"].as_double_tuple_or_die();
        bool invertColors = configuration["BlockProperties"]["invertColors"].as_bool_or_default(false);
        if (invertColors) {
            std::swap(colorWhite, colorBlack);
        }

        image = introBlocks(width, height, nrXBlocks, nrYBlocks, colorWhite, colorBlack);
    } else if ( type == "IntroLines" ) {
        unsigned int width = configuration["ImageProperties"]["width"].as_int_or_die();
        unsigned int height = configuration["ImageProperties"]["height"].as_int_or_die();
        unsigned int nrLines = configuration["LineProperties"]["nrLines"].as_int_or_die();
        ini::DoubleTuple linecolor = configuration["LineProperties"]["lineColor"].as_double_tuple_or_die();
        img::Color linec = img::Color(linecolor);
        ini::DoubleTuple bgcolor = configuration["LineProperties"]["backgroundcolor"].as_double_tuple_or_die();
        img::Color bgc = img::Color(bgcolor);
        std::string figure = configuration["LineProperties"]["figure"].as_string_or_die();
        if ( figure == "QuarterCircle" ) {
            image = introQuarterCircle(width, height, nrLines, linec, bgc);
        } else if ( figure == "Eye" ) {
            image = introEye(width, height, nrLines, linec, bgc);
        } else if ( figure == "Diamond" ) {
            image = introDiamond(width, height, nrLines, linec, bgc);
        }
    } else if ( type == "2DLines" ) {
        unsigned int size = configuration["General"]["size"].as_int_or_die();
        Lines2D lines;
        lines.push_back( Line2D( 10, 1, 10, 10 ) );
        lines.push_back( Line2D( 2, 2, 20, 20 ) );
        image = draw2DLines(lines, size, img::Color(255, 255, 255));
    } else if ( type == "2DLSystem") {
        unsigned int size = configuration["General"]["size"].as_int_or_die();
        img::Color bgc = img::Color( configuration["General"]["backgroundcolor"].as_double_tuple_or_die() );
        img::Color linec = img::Color( configuration["2DLSystem"]["color"].as_double_tuple_or_die() );
        std::string inputloc = configuration["2DLSystem"]["inputfile"].as_string_or_die();
        LParser::LSystem2D lsystem = makeLSystem(inputloc);
        Lines2D lines = drawLSystem(lsystem, linec);
        image = draw2DLines(lines, size, bgc);
    } else if ( type == "Wireframe" or type == "ZBufferedWireframe" or type == "ZBuffering" ) {

        int zb = 0; // zbuffering: 0 -> wireframe, 1 -> zbuffered wireframe
        if ( type == "ZBufferedWireframe" ) {
            zb = 1;
        } else if ( type == "ZBuffering") {
            zb = 2;
        }

        unsigned int size = configuration["General"]["size"].as_int_or_die();
        ini::DoubleTuple eye = configuration["General"]["eye"].as_double_tuple_or_die();
        Matrix eyem = eyePoint( Vector3D::point(eye.at(0), eye.at(1), eye.at(2)) );
        img::Color bgc = img::Color( configuration["General"]["backgroundcolor"].as_double_tuple_or_die() );
        unsigned int nrFigures = configuration["General"]["nrFigures"].as_int_or_die();

        Figures3D figures;
        Lines2D lines;

        for (int it = 0; it < nrFigures; ++it) {
            std::string fig = "Figure" + std::to_string(it);
            Figure f;

            // transformations

            // scale
            Matrix scale = scaleFigure( configuration[fig]["scale"].as_double_or_die() );

            // rotations
            Matrix rotate;
            ini::DoubleTuple r;
            r.push_back( configuration[fig]["rotateX"].as_double_or_die() );
            r.push_back( configuration[fig]["rotateY"].as_double_or_die() );
            r.push_back( configuration[fig]["rotateZ"].as_double_or_die() );
            for (int i = 0; i < r.size(); ++i) {
                r.at(i) *= (pi / 180);
            }
            rotate = rotateX(r.at(0)) * rotateY(r.at(1)) * rotateZ(r.at(2));

            // translation
            ini::DoubleTuple center = configuration[fig]["center"].as_double_tuple_or_die();
            Matrix translation = translate( Vector3D::vector(center.at(0), center.at(1), center.at(2) ) );

            // final
            Matrix final = scale * rotate * translation;

            f.color = img::Color( configuration[fig]["color"].as_double_tuple_or_die() );


            std::string figtype = configuration[fig]["type"].as_string_or_die();
            if ( figtype == "LineDrawing" ) {
                unsigned int nrPoints = configuration[fig]["nrPoints"].as_int_or_die();
                for (int i = 0; i < nrPoints; ++i) {
                    ini::DoubleTuple p = configuration[fig]["point" + std::to_string(i)].as_double_tuple_or_die();
                    f.points.push_back( Vector3D::point( p.at(0), p.at(1), p.at(2) ) );
                }
                unsigned int nrLines = configuration[fig]["nrLines"].as_int_or_die();
                for (int i = 0; i < nrLines; ++i) {
                    ini::IntTuple l = configuration[fig]["line" + std::to_string(i)].as_int_tuple_or_die();
                    f.lines.push_back( l );
                }
            } else if ( figtype == "Cube" ) {
                createCube(f);
            } else if ( figtype == "Tetrahedron" ) {
                createTetrahedron(f);
            } else if ( figtype == "Octahedron" ) {
                createOctahedron(f);
            } else if ( figtype == "Icosahedron" ) {
                createIcosahedron(f);
            } else if ( figtype == "Dodecahedron" ) {
                createDodecahedron(f);
            } else if ( figtype == "Cone" ) {
                int n = configuration[fig]["n"].as_int_or_die();
                double h = configuration[fig]["height"].as_double_or_die();
                createCone(f, n, h);
            } else if ( figtype == "Cylinder" ) {
                int n = configuration[fig]["n"].as_int_or_die();
                double h = configuration[fig]["height"].as_double_or_die();
                createCylinder(f, n, h);
            } else if ( figtype == "Torus" ) {
                double r = configuration[fig]["r"].as_double_or_die();
                double R = configuration[fig]["R"].as_double_or_die();
                int n = configuration[fig]["n"].as_int_or_die();
                int m = configuration[fig]["m"].as_int_or_die();
                createTorus(f, r, R, n, m);
            } else if ( figtype == "Sphere" ) {
                int n = configuration[fig]["n"].as_int_or_die();
                createSphere(f, n);

                for (int i = 0; i < f.points.size(); i++) {
                    Vector3D* p = &(f.points[i]);
                    double d = std::sqrt( std::pow( p->x ,2) + std::pow( p->y ,2) + std::pow( p->z ,2)  );
                    p->x = p->x / d;
                    p->y = p->y / d;
                    p->z = p->z / d;
                }
            } else if ( figtype == "3DLSystem" ) {
                return img::EasyImage();
            }

            applyTransformation( f, final );
            figures.push_back(f);
        }
        applyEyeTransformation(figures, eyem);

        if ( zb == 2 ) {
            image = drawZBufferedImage(figures, size, bgc);
        } else {
            perspectiveProjection(figures, lines);
            image = draw2DLines(lines, size, bgc, ( zb > 0 ));
        }


    } else {
        image = img::EasyImage();
    }

    return image;
}

int main(int argc, char const* argv[])
{
        int retVal = 0;
        try
        {
                for(int i = 1; i < argc; ++i)
                {
                        ini::Configuration conf;
                        try
                        {
                                std::ifstream fin(argv[i]);
                                fin >> conf;
                                fin.close();
                        }
                        catch(ini::ParseException& ex)
                        {
                                std::cerr << "Error parsing file: " << argv[i] << ": " << ex.what() << std::endl;
                                retVal = 1;
                                continue;
                        }

                        img::EasyImage image = generate_image(conf);
                        if(image.get_height() > 0 && image.get_width() > 0)
                        {
                                std::string fileName(argv[i]);
                                std::string::size_type pos = fileName.rfind('.');
                                if(pos == std::string::npos)
                                {
                                        //filename does not contain a '.' --> append a '.bmp' suffix
                                        fileName += ".bmp";
                                }
                                else
                                {
                                        fileName = fileName.substr(0,pos) + ".bmp";
                                }
                                try
                                {
                                        std::ofstream f_out(fileName.c_str(),std::ios::trunc | std::ios::out | std::ios::binary);
                                        f_out << image;

                                }
                                catch(std::exception& ex)
                                {
                                        std::cerr << "Failed to write image to file: " << ex.what() << std::endl;
                                        retVal = 1;
                                }
                        }
                        else
                        {
                                std::cout << "Could not generate image for " << argv[i] << std::endl;
                        }
                }
        }
        catch(const std::bad_alloc &exception)
        {
    		//When you run out of memory this exception is thrown. When this happens the return value of the program MUST be '100'.
    		//Basically this return value tells our automated test scripts to run your engine on a pc with more memory.
    		//(Unless of course you are already consuming the maximum allowed amount of memory)
    		//If your engine does NOT adhere to this requirement you risk losing points because then our scripts will
		//mark the test as failed while in reality it just needed a bit more memory
                std::cerr << "Error: insufficient memory" << std::endl;
                retVal = 100;
        }
        return retVal;
}
