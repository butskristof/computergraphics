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

// implementations

    // intro
    #include "implementations/intro.cpp" // colorRectangle, blocks, quartercircle

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
