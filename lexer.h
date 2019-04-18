#ifndef LEXER_H
#define LEXER_H

#include "list"
#include <string>

class Token;
class Error;
class Lexer {
    public:
        int state;
        std::list<Token> tokens;
        std::list<Error> errors;
        std::string lexeme;

    public:
        Lexer();
        //Completely read file
        //Return true if succesful
        void transduce(std::string text);
        //Read a symbol
        void step(char symbol);
        int hash(char symbol);
        void restart();
        bool isValid();
        bool isDelimiter();
        bool isFinal();
        int getstate();
};

#endif // LEXER_H
