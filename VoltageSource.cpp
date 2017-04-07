/*
MIT License

Copyright (c) 2017  Joe Hood

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#define _USE_MATH_DEFINES

#include "VoltageSource.hpp"
#include <cmath>

#include <iostream>

VoltageSource::VoltageSource(int nodei, int nodej, double Vdc, double R, double L)
{
    this->nodei = nodei;
    this->nodej = nodej;
    this->Vdc = Vdc;
    this->R = R;

    this->type = DCSOURCE;
}

VoltageSource::VoltageSource(int nodei, int nodej, double Vdc, double Va,
                             double f, double phi, double R, double L)
{
    this->nodei = nodei;
    this->nodej = nodej;
    this->Vdc = Vdc;
    this->Va = Va;
    this->f = f;
    this->phi = phi;
    this->R = R;

    this->type = SINESOURCE;
}

void VoltageSource::Init()
{
    this->nodep = GetNextNode();
}

void VoltageSource::Step(double t, double dt)
{
    AddJacobian(nodei, nodep, -1.0);
    AddJacobian(nodej, nodep, 1.0);
    AddJacobian(nodep, nodei, -1.0);
    AddJacobian(nodep, nodej, 1.0);
    AddJacobian(nodep, nodep, -(R + L / dt));

    double v = 0.0;

    switch (type)
    {

    case DCSOURCE:
        v = Vdc;
        break;

    case SINESOURCE:
        v = Vdc + Va * sin(2.0 * M_PI * f * t + phi);
        break;
    }

    AddBEquivalent(nodep, v - (R + L / dt)* GetState(nodep));
}

void VoltageSource::DC()
{
    AddJacobian(nodei, nodep, -1.0);
    AddJacobian(nodej, nodep, 1.0);
    AddJacobian(nodep, nodei, -1.0);
    AddJacobian(nodep, nodej, 1.0);
    AddJacobian(nodep, nodep, -R);

    AddBEquivalent(nodep, Vdc);   
}

void VoltageSource::SetVdc(double Vdc)
{
    this->Vdc = Vdc;
}

double VoltageSource::GetVoltage()
{
    return GetStateDifference(nodei, nodej);
}

double VoltageSource::GetCurrent()
{
    return -GetState(nodep);
}

double VoltageSource::GetPower()
{
    return VoltageSource::GetVoltage() * VoltageSource::GetCurrent();
}
