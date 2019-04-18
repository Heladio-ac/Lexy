#include "token.h"

// Accepting states
#ifndef ACCEPTING_STATES
    #define ACCEPTING_STATES

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
#endif

Token::Token(std::string l, int g) {
    lexeme = l;
    grammeme = g;
}

std::string Token::getGrammeme() {
    switch (grammeme) {
        case RESERVED:
            return "Reserved word";
        case IDENTIFIER:
            return "Identifier";
        case COMMENTARY:
            return "Commentary";
        case INTEGER:
            return "Integer";
        case FLOAT:
            return "Real number";
        case FLOATSCI:
            return "Real number w/exponent";
        case CHARACTER:
            return "Character";
        case STRING:
            return "String";
        case MULTIPLICATION:
            return "Multiplication";
        case DIVISION:
            return "Division";
        case ADDITION:
            return "Addition";
        case SUBSTRACTION:
            return "Substraction";
        case MODULO:
            return "Modulo";
        case OR:
            return "Logical OR";
        case AND:
            return "Logical AND";
        case NOT:
            return "Logical NOT";
        case LESSTHAN:
            return "Less than";
        case LESSEQUALS:
            return "Less than or equals";
        case GREATERTHAN:
            return "Greater than";
        case GREATEREQUALS:
            return "Greater than or equals";
        case EQUALS:
            return "Equals";
        case NEQUALS:
            return "Is different";
        case ASSIGNMENT:
            return "Assign";
        case POINT:
            return "Point";
        case COMMA:
            return "Comma";
        case COLON:
            return "Colon";
        case SEMICOLON:
            return "Semi-colon";
        case PARENTHESISOPEN:
            return "Open Parenthesis";
        case PARENTHESISCLOSE:
            return "Close Parenthesis";
        case BRACKETSOPEN:
            return "Open Brackets";
        case BRACKETSCLOSE:
            return "Close Brackets";
        case SQUAREBOPEN:
            return "Open Square Brackets";
        case SQUAREBCLOSE:
            return "Close Square Brackets";
        default:
            return "ERROR";
    }
}
