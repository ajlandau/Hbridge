#ifndef CAPACITOR_H
#define CAPACITOR_H

#include "Device.hpp"

class Capacitor : public Device
{
public:

    // constructor (should accept node indices and parameters):
    Capacitor(int nodei, int nodej, double C);

    // Device interface (must implement Step, but PostStep and DC are optional):
    void Step(double t, double dt);
    void DC();

    // viewable accessors:
    double GetVoltage();
    double GetCurrent();
    double GetPower();

private:

    // node indices:
    int nodei;
    int nodej;

    // parameters:
    double C;
};


#endif
