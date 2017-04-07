
#include "Capacitor.hpp"

Capacitor::Capacitor(int nodei, int nodej, double C)
{
    this->nodei = nodei;
    this->nodej = nodej;
    this->C = C;
}

void Capacitor::Step(double t, double dt)
{
    double gc = C / dt;
    double ic = C / dt * GetStateDifference(nodei, nodej);

    AddJacobian(nodei, nodei, gc);
    AddJacobian(nodei, nodej, -gc);
    AddJacobian(nodej, nodei, -gc);
    AddJacobian(nodej, nodej, gc);

    AddBEquivalent(nodei, ic);
    AddBEquivalent(nodej, -ic);
}

void Capacitor::DC()
{
    double gc = 1.0e-9;
    AddJacobian(nodei, nodei, gc);
    AddJacobian(nodei, nodej, -gc);
    AddJacobian(nodej, nodei, -gc);
    AddJacobian(nodej, nodej, gc);
}

double Capacitor::GetVoltage()
{
    return GetStateDifference(nodei, nodej);
}

double Capacitor::GetCurrent()
{
    return C / GetTimeStep() * Capacitor::GetVoltage() - GetBEquivalent(nodei);
}

double Capacitor::GetPower()
{
    return Capacitor::GetVoltage() * Capacitor::GetCurrent();
}