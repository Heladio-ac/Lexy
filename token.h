#ifndef TOKEN_H
#define TOKEN_H

#include <string>

class Token {
    public:
        std::string lexeme;
        int grammeme;

    public:
        Token(std::string l, int g);
        std::string getGrammeme();
};

#endif // TOKEN_H
