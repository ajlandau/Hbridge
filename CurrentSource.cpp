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

#include "CurrentSource.hpp"
#include <cmath>

CurrentSource::CurrentSource(int nodei, int nodej, double Idc, double R, double C)
{
    this->nodei = nodei;
    this->nodej = nodej;
    this->Idc = Idc;
    this->R = R;
    this->C = C;

    this->type = DCSOURCE;
}

CurrentSource::CurrentSource(int nodei, int nodej, double Idc, double Ia,
    double f, double phi, double R, double C)
{
    this->nodei = nodei;
    this->nodej = nodej;
    this->Idc = Idc;
    this->Ia = Ia;
    this->f = f;
    this->phi = phi;
    this->R = R;
    this->C = C;

    this->type = SINESOURCE;
}

void CurrentSource::Step(double t, double dt)
{
    double gr = 0.0;
    double gc = C / dt;

    if (R > 0.0)
    {
        gr = 1.0 / R;
    }

    AddJacobian(nodei, nodei, (gr + gc));
    AddJacobian(nodei, nodej, -(gr + gc));
    AddJacobian(nodej, nodei, -(gr + gc));
    AddJacobian(nodej, nodej, (gr + gc));

    current = 0.0;

    switch (type)
    {

    case DCSOURCE:
        current = Idc;
        break;

    case SINESOURCE:
        current = Idc + Ia * sin(2.0 * M_PI * f * t + phi);
        break;
    }

    AddBEquivalent(nodei, -current + gc * GetVoltage());
    AddBEquivalent(nodej, current - gc * GetVoltage());
}

void CurrentSource::DC()
{
    double gr = 0.0;

    if (R > 0.0)
    {
        gr = 1.0 / R;
    }

    AddJacobian(nodei, nodei, gr);
    AddJacobian(nodei, nodej, -gr);
    AddJacobian(nodej, nodei, -gr);
    AddJacobian(nodej, nodej, gr);

    AddBEquivalent(nodei, -Idc);
    AddBEquivalent(nodej, Idc);
}

double CurrentSource::GetVoltage()
{
    return GetStateDifference(nodej, nodei);
}

double CurrentSource::GetCurrent()
{
    return current;
}

double CurrentSource::GetPower()
{
    return GetVoltage() * GetCurrent();
}

void CurrentSource::SetIdc(double Idc)
{
    this->Idc = Idc;
}

void CurrentSource::SetIa(double Ia)
{
    this->Ia = Ia;
}

void CurrentSource::SetFrequency(double f)
{
    this->f = f;
}

void CurrentSource::SetPhi(double phi)
{
    this->phi = phi;
}
