#include "manager.h"

const int kEstrictioNs = 5000;

Manager::Manager() {}


int Manager::FunctionAckerman(int m, int n, int i) {
    i++;


    if (i > kEstrictioNs) {
        return -1;
    }


    if (m == 0) {
        return n + 1;
    }


    if (m > 0 && n == 0) {
        return FunctionAckerman(m - 1, 1, i);
    }


    if (m > 0 && n > 0) {
        return FunctionAckerman(m - 1, FunctionAckerman(m, n - 1, i), i);
    }
    return -1;
}

bool Manager::CheckInput(const QString& input) {
    bool ok;
    int number = input.toInt(&ok);
    return ok && number >= 0;
}
