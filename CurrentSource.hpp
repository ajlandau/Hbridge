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

#ifndef CURRENT_SOURCE_H
#define CURRENT_SOURCE_H

#include "Device.hpp"

class CurrentSource : public Device
{
public:

    ///////// Constructors:

    // DC source constructor:
    CurrentSource(int nodei, int nodej, double Idc, double R = 0.0, double C = 0.0);

    // SINE source constructor:
    CurrentSource(int nodei, int nodej, double Idc, double Ia,
        double f, double phi = 0.0, double R = 0.0, double C = 0.0);

    // Device interface:
    void Step(double t, double dt);
    void DC();

    // Viewable accessors:
    double GetVoltage();
    double GetCurrent();
    double GetPower();

    void SetIdc(double Idc);
    void SetIa(double Ia);
    void SetFrequency(double f);
    void SetPhi(double phi);

private:

    // Node indices:
    int nodei;
    int nodej;

    // Parameters:
    sourceType type;
    double Idc;
    double Ia;
    double f;
    double phi;
    double R;
    double C;

    // states:
    double current;
};


#endif
