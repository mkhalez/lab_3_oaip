#include "manager.h"
#include <cmath>

Manager::Manager() {}

QString Manager::TransformationToBin(int& integer,
                                     double& fractional_part_of_number,
                                     bool stop_integer, bool stop_fractional,
                                     QString result) {


    if (stop_integer && stop_fractional) {
        return result;
    }


    if (!stop_integer) {
        result = QString::number(integer % 2) + result;
        integer /= 2;
    }


    if (!stop_fractional) {
        double after_multyplay = fractional_part_of_number * 2;
        int new_init = (int)after_multyplay;
        fractional_part_of_number = after_multyplay - new_init;
        result += QString::number(new_init);
    }


    if (integer == 0) {
        stop_integer = true;
    }

    double int_part;

    if (check_.NumberDigitAfterPoint(result) > accuracy ||
        std::modf(fractional_part_of_number, &int_part) == 0.0) {
        stop_fractional = true;
    }


    return TransformationToBin(integer, fractional_part_of_number, stop_integer,
                               stop_fractional, result);
}

void Manager::SetAccuracy(int accuracy) {
    this->accuracy = accuracy;
}
