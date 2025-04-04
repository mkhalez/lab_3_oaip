#ifndef VALID_H
#define VALID_H

#include <QString>

class Valid {
   public:
    Valid();

   public:
    int NumberDigitAfterPoint(QString number);
    bool CheckInput(const QString& input);
};

#endif	// VALID_H
