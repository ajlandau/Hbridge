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

#include "Inductor.hpp"

Inductor::Inductor(int nodei, int nodej, double L)
{
    this->nodei = nodei;
    this->nodej = nodej;
    this->L = L;
}

void Inductor::Init()
{
    this->nodep = GetNextNode();
}

void Inductor::Step(double t, double dt)
{
    double rL = L / dt;
    double eL = -rL * GetState(nodep);

    AddJacobian(nodei, nodep, -1.0);
    AddJacobian(nodej, nodep, 1.0);
    AddJacobian(nodep, nodei, -1.0);
    AddJacobian(nodep, nodej, 1.0);
    AddJacobian(nodep, nodep, -rL);

    AddBEquivalent(nodep, eL);
}

void Inductor::DC()
{
    AddJacobian(nodei, nodep, -1.0);
    AddJacobian(nodej, nodep, 1.0);
    AddJacobian(nodep, nodei, -1.0);
    AddJacobian(nodep, nodej, 1.0);
    AddJacobian(nodep, nodep, 1.0e-9);
}

double Inductor::GetVoltage()
{
    return GetStateDifference(nodei, nodej);
}

double Inductor::GetCurrent()
{
    return -GetState(nodep);
}

double Inductor::GetPower()
{
    return GetVoltage() * GetCurrent();
}