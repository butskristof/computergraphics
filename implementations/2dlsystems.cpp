#include "../l_parser/l_parser.hh"
#include <stack>

std::string lSystemReplacement(int nrIter, std::string toRepl, LParser::LSystem* lsystem) {
    if ( nrIter == 0 ) {
        return toRepl;
    }

    std::string out = "";

    for (char c: toRepl) {
        if (c == '+' or c == '-' or c == '(' or c == ')' or c == '^' or c == '&' or c == '\\' or c == '/' or c == '|' ) {
            out += c;
        } else {
            out += lsystem->get_replacement(c);
        }
    }

    out = lSystemReplacement( nrIter - 1, out, lsystem);
    std::cout << out.length() << std::endl;
    return out;
}

LParser::LSystem2D makeLSystem(std::string inputloc) {
    LParser::LSystem2D ls;
    std::ifstream input("./input/1_2dlsystems/" + inputloc);
    input >> ls;
    input.close();

    return ls;
}

std::vector< std::pair< int, char > > splitString(std::string input) {
    std::vector< std::pair< int, char > > ret;

    char c = ' ';
    char prev = ' ';
    int ctr = 0;

    for (int i = 0; i < input.size(); ++i) {
        c = input.at(i);
        if ( c == prev ) {
            ++ctr;
        } else {
            // add to vector
        }
    }
}

Lines2D drawLSystem( LParser::LSystem2D &ls, img::Color col) {
    Lines2D lines;
    std::stack<ini::DoubleTuple> bracketstack;

    double x = 0, y = 0, xprev = 0, yprev = 0;
    double initAngle = (ls.get_starting_angle() * (pi/180) );
    double angle = (ls.get_angle() * (pi/180));
    double currentAngle = initAngle;

    std::string initiator = ls.get_initiator();
    std::set<char> alphabet = ls.get_alphabet();

    std::string final = lSystemReplacement( ls.get_nr_iterations(), initiator, &ls );

    // split up per char

    char c = ' ';
    char tracking = ' ';
    double xtrack, ytrack;
    int lengthctr = 0; // length counter for line

    for ( int i = 0; i < final.length(); ++i) {

            c = final.at(i);

            // TO REVISE!!

        if (alphabet.find(c) != alphabet.end() ) {

            xprev = x; yprev = y;
            x = x + std::cos( currentAngle );
            y = y + std::sin( currentAngle );
            if (ls.draw(c) ) {
                lines.push_back(Line2D(xprev, yprev, x, y, col));
            }
        } else if ( c == '+' ) {
            currentAngle = fmod((currentAngle + angle), (2*pi));
        } else if ( c == '-' ) {
            currentAngle = fmod((currentAngle - angle), (2*pi));
        } else if ( c == '(' ) {
            ini::DoubleTuple d;
            d.push_back(x);
            d.push_back(y);
            d.push_back(currentAngle);
            bracketstack.push( d );
        } else if ( c == ')' ) {
            ini::DoubleTuple d = bracketstack.top();
            bracketstack.pop();
            x = d.at(0);
            y = d.at(1);
            currentAngle = d.at(2);
        }
//        prev = c;
    }

    return lines;
}
