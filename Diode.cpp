
#include "Diode.hpp"
#include <cmath>

Diode::Diode(int nodei, int nodej, double Is, double Vt, double n)
{
    this->nodei = nodei;
    this->nodej = nodej;
    this->Is = Is;
    this->Vt = Vt;
    this->n = n;
}

void Diode::Step(double t, double dt)
{  
    double Vd = GetIterationStateDifference(nodei, nodej);  // Vd(k-1)  (newton "X")

    double Id = Is * (exp(Vd / (n * Vt)) - 1);       // Id(k-1)  (newton "f(x)")

    double gd = Is / (n * Vt) * exp(Vd / (n * Vt));  // gd(k) (newton "f'(x)")

    AddJacobian(nodei, nodei, gd);
    AddJacobian(nodei, nodej, -gd);
    AddJacobian(nodej, nodei, -gd);
    AddJacobian(nodej, nodej, gd);

    AddBEquivalent(nodei, -(Id - gd * Vd));
    AddBEquivalent(nodej, (Id - gd * Vd));
}

void Diode::DC()
{
    Step(0, 0);
}

double Diode::GetVoltage()
{
    return GetStateDifference(nodei, nodej);
}

double Diode::GetCurrent()
{
    return Is * (exp(GetVoltage() / (n * Vt)) - 1);
}