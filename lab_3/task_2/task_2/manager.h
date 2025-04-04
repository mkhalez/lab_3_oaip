#ifndef MANAGER_H
#define MANAGER_H

#include <QString>

class Manager {
   public:
    Manager();

    int FunctionAckerman(int m, int n, int i = 0);

    bool CheckInput(const QString& input);
};

#endif	// MANAGER_H
