#include "../l_parser/l_parser.hh"

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
    return out;
}

LParser::LSystem2D makeLSystem(std::string inputloc) {
    LParser::LSystem2D ls;
    std::ifstream input("./input/1_2dlsystems/" + inputloc);
    input >> ls;
    input.close();

    return ls;
}

Lines2D drawLSystem( LParser::LSystem2D &ls, img::Color col) {
    Lines2D lines;

    double x = 0, y = 0, xprev = 0, yprev = 0;
    double initAngle = (ls.get_starting_angle() * (pi/180) );
    double angle = (ls.get_angle() * (pi/180));
    double currentAngle = initAngle;

    std::string initiator = ls.get_initiator();
    std::set<char> alphabet = ls.get_alphabet();

    std::string final = lSystemReplacement( ls.get_nr_iterations(), initiator, &ls );

    for ( char c: final) {
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
        }
    }

    return lines;
}
