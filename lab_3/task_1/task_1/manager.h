#ifndef MANAGER_H
#define MANAGER_H

#include <QString>
#include "valid.h"

class Manager {
   public:
    Manager();


   public:
    QString TransformationToBin(int& integer, double& fractional_part_of_number,
                                bool stop_integer, bool stop_fractional,
                                QString result);
    int accuracy;

   public:
    void SetAccuracy(int accuracy);

   private:
    Valid check_;
};

#endif	// MANAGER_H
