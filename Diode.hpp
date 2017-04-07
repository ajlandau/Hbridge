#include "Device.hpp"

class Diode : public Device
{

public:

    Diode(int nodei, int nodej, double Is = 5e-9, double Vt = 25.85e-3, double n = 1.0);
    
    void DC();
    void Step(double t, double dt);
    
    double GetVoltage();
    double GetCurrent();

private:

    int nodei;
    int nodej;

    double Is;
    double Vt;
    double n;

};
