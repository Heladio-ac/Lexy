#include "lexer.h"

#include "token.h"
#include "error.h"

#include <ctype.h>
#include <algorithm>
#include <initializer_list>

// Delimiting states
#ifndef STATES
    #define STATES
    //Accepting states
    #define RESERVED 101
    #define IDENTIFIER 102
    #define COMMENTARY 103
    #define INTEGER 104
    #define FLOAT 105
    #define FLOATSCI 106
    #define CHARACTER 107
    #define STRING 108
    #define MULTIPLICATION 109
    #define DIVISION 110
    #define ADDITION 111
    #define SUBSTRACTION 112
    #define MODULO 113
    #define OR 114
    #define AND 115
    #define NOT 116
    #define LESSTHAN 117
    #define LESSEQUALS 118
    #define GREATERTHAN 119
    #define GREATEREQUALS 120
    #define EQUALS 121
    #define NEQUALS 122
    #define ASSIGNMENT 123
    #define POINT 124
    #define COMMA 125
    #define COLON 126
    #define SEMICOLON 127
    #define PARENTHESISOPEN 128
    #define PARENTHESISCLOSE 129
    #define BRACKETSOPEN 130
    #define BRACKETSCLOSE 131
    #define SQUAREBOPEN 132
    #define SQUAREBCLOSE 133
    //Error states
    #define ERRORIDENTIFIER 501
    #define ERRORFLOAT 502
    #define ERRORFLOATSCI 503
    #define ERROROR 504
    #define ERRORAND 505
    #define ERRORUNKNOWN 599
#endif

// Symbols sets
#ifndef SYMBOLS
    #define SYMBOLS

    #define LOWERL 2
    #define UPPERL 3
    #define DIGITS 4
    #define BLANKS 14
    #define ELSE 30
#endif

static int transition[34][31] = {
    {2,   1,   1,   2,   7,   599, 16,  4,   17,  18,  19,  32,  13,  15,  0,   20,  22,  24,  25,  27,  31,  33,  125, 127, 128, 129, 130, 131, 132, 133, 599},
    {2,   1,   1,   2,   2,   3,   101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101},
    {2,   2,   2,   2,   2,   3,   102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102},
    {2,   2,   2,   2,   2,   501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501},
    {110, 110, 110, 110, 110, 110, 5,   110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110},
    {5,   5,   5,   5,   5,   5,   6,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5},
    {5,   5,   5,   5,   5,   5,   6,   103, 5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5},
    {104, 104, 104, 104, 7,   104, 104, 104, 104, 104, 104, 8,   104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104},
    {502, 502, 502, 502, 9,   502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502},
    {10,  10,  105, 105, 9,   105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105},
    {503, 503, 503, 503, 12,  503, 503, 503, 11,  11,  503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503},
    {503, 503, 503, 503, 12,  503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503},
    {106, 106, 106, 106, 12,  106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106},
    {14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  107, 14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14,  14},
    {504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 107, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504},
    {15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  108, 15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15,  15},
    {109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109},
    {111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111},
    {112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112},
    {113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113},
    {505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 21,  505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505},
    {114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114},
    {506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 23,  506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506},
    {115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115},
    {116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 30,  116, 116, 116, 116, 116, 116, 116, 116, 116, 116},
    {117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 26,  117, 117, 117, 117, 117, 117, 117, 117, 117, 117},
    {118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118},
    {119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 28,  119, 119, 119, 119, 119, 119, 119, 119, 119, 119},
    {120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120},
    {121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121},
    {122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122},
    {123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 29,  123, 123, 123, 123, 123, 123, 123, 123, 123, 123},
    {124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124},
    {126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126}
};

static std::string reservedWords[] = {
    "class",
    "begin",
    "end",
    "def",
    "as",
    "integer",
    "float",
    "char",
    "string",
    "boolean",
    "if",
    "else",
    "elseif",
    "endif",
    "for",
    "do",
    "endfor",
    "while",
    "endwhile",
    "function",
    "endfunction",
    "import",
    "null",
    "read",
    "write",
    "enter",
    "principal"
};

Lexer::Lexer(void) {
    state = 0;
    lexeme = "";
}

void Lexer::step(char symbol) {
    state = transition[state][hash(symbol)];
}

void Lexer::transduce(std::string text) {
    tokens.clear();
    errors.clear();
    for(int i = 0; i < text.length(); i++) {
        step(text[i]);
        if (isDelimiter()) {
            if (isFinal()) {
                lexeme += text[i];
            } else {
                i--;
            }
            if (isValid()) {
                if (state == RESERVED) {
                    state = IDENTIFIER;
                    for (std::string reserved: reservedWords) {
                        if (reserved == lexeme) {
                            state = RESERVED;
                            break;
                        }
                    }
                }
                tokens.push_back(Token(lexeme, state));
            } else {
                errors.push_back(Error(lexeme, state));
            }
            restart();
        } else if (state != 0){
            lexeme += text[i];
        }
    }
    restart();
}

int Lexer::hash(char symbol) {
    if (symbol == 'E') {
        return 0;
    } else if (symbol == 'e') {
        return 1;
    } else if (islower(symbol)) {
        return LOWERL;
    } else if (isupper(symbol)) {
        return UPPERL;
    } else if (isdigit(symbol)) {
        return DIGITS;
    } else if (symbol == '_') {
        return 5;
    } else if (symbol == '*') {
        return 6;
    } else if (symbol == '/') {
        return 7;
    } else if (symbol == '+') {
        return 8;
    } else if (symbol == '-') {
        return 9;
    } else if (symbol == '%') {
        return 10;
    } else if (symbol == '.') {
        return 11;
    } else if (symbol == '\'') {
        return 12;
    } else if (symbol == '\"') {
        return 13;
    } else if (symbol == ' ' || symbol == '\n' || symbol == '\t') {
        return BLANKS;
    } else if (symbol == '|') {
        return 15;
    } else if (symbol == '&') {
        return 16;
    } else if (symbol == '!') {
        return 17;
    } else if (symbol == '<') {
        return 18;
    } else if (symbol == '>') {
        return 19;
    } else if (symbol == '=') {
        return 20;
    } else if (symbol == ':') {
        return 21;
    } else if (symbol == ',') {
        return 22;
    } else if (symbol == ';') {
        return 23;
    } else if (symbol == '(') {
        return 24;
    } else if (symbol == ')') {
        return 25;
    } else if (symbol == '{') {
        return 26;
    } else if (symbol == '}') {
        return 27;
    } else if (symbol == '[') {
        return 28;
    } else if (symbol == ']') {
        return 29;
    } else {
        return ELSE;
    }
}

void Lexer::restart() {
    state = 0;
    lexeme = "";
}

bool Lexer::isValid() {
    return !(state >= 500);
}

bool Lexer::isDelimiter() {
    return state >= 100;
}

bool Lexer::isFinal() {
    switch (state) {
        case COMMENTARY: case CHARACTER: case STRING:
        case COMMA: case SEMICOLON:
        case PARENTHESISOPEN: case PARENTHESISCLOSE:
        case BRACKETSOPEN: case BRACKETSCLOSE:
        case SQUAREBOPEN: case SQUAREBCLOSE:
        case ERRORUNKNOWN:
            return true;
        default:
            return false;
    }
}

int Lexer::getstate() {
    return state;
}

