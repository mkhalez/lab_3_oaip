#include "valid.h"

Valid::Valid() {}

int Valid::NumberDigitAfterPoint(QString string) {
    int number = 0;
    bool after_point = false;

    for (int i = 0; i < string.length(); i++) {


        if (string[i] == '.') {
            after_point = true;
        }


        if (after_point) {
            number++;
        }
    }

    return number;
}

bool Valid::CheckInput(const QString& input) {
    bool ok;
    input.toDouble(&ok);
    return ok;
}
