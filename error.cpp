#include "error.h"

#ifndef ERROR_STATES
    #define ERROR_STATES

    #define ERRORIDENTIFIER 501
    #define ERRORFLOAT 502
    #define ERRORFLOATSCI 503
    #define ERRORCHAR 504
    #define ERROROR 505
    #define ERRORAND 506
    #define ERRORUNKNOWN 599
#endif

Error::Error(std::string l, int e) {
    lexeme = l;
    error = e;
}

std::string Error::getError() {
    switch (error) {
        case ERRORIDENTIFIER:
            return "Identifiers can not end with a _";
        case ERRORFLOAT:
            return "Malformed floating point constant, expected a digit after the point";
        case ERRORFLOATSCI:
            return "Malformed floating point constant, expected a digit or +/- sign after the exponent";
        case ERRORCHAR:
            return "Malformed character constant, expected a closing apostrophe";
        case ERROROR:
            return "Malformed OR operator, expected a second |";
        case ERRORAND:
            return "Malformed AND operator, expected a second &";
        case ERRORUNKNOWN: default:
            return "Unknown Error";
    }
}
