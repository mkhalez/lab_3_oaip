#ifndef MANAGER_H
#define MANAGER_H

#include <QString>

class Manager {
   public:
    Manager();
    long Reverse(long number, long result = 0);
    bool Check(QString input);
};

#endif	// MANAGER_H
