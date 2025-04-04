#include "manager.h"

const int kDecimal = 10;

Manager::Manager() {}

long Manager::Reverse(long number, long result) {


    if (number == 0) {
        return result;
    }

    result *= kDecimal;
    long remainder = number % kDecimal;
    result += remainder;

    number = (number - remainder) / kDecimal;

    return Reverse(number, result);
}

bool Manager::Check(QString input) {

    if (input[0] == '0' || input[input.length() - 1] == '0') {

        return false;
    }

    bool ok;
    input.toLong(&ok);

    return ok;
}
