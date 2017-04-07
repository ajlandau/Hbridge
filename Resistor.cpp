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

#include "Resistor.hpp"

Resistor::Resistor(int nodei, int nodej, double R)
{
    this->nodei = nodei;
    this->nodej = nodej;
    this->R = R;
}

void Resistor::Step(double t, double dt)
{
    double g = 1.0 / R;

    AddJacobian(nodei, nodei, g);
    AddJacobian(nodei, nodej, -g);
    AddJacobian(nodej, nodei, -g);
    AddJacobian(nodej, nodej, g);
}

double Resistor::GetVoltage()
{
    return GetStateDifference(nodei, nodej);
}

double Resistor::GetCurrent()
{
    return Resistor::GetVoltage() / R;
}

double Resistor::GetPower()
{
    return Resistor::GetVoltage() * Resistor::GetCurrent();
}