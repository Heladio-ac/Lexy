#ifndef ERROR_H
#define ERROR_H

#include <string>

class Error {
    public:
        std::string lexeme;
        int error;

    public:
        Error(std::string l, int e);
        std::string getError();
};

#endif // ERROR_H
