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

#ifndef PLOTTER_H
#define PLOTTER_H

#include <iostream>
#include <vector>
#include <string>


#ifdef __APPLE__
#	define GNUPLOT "gnuplot -persist"
#else
#	define GNUPLOT "C:/PROGRA~2/gnuplot/bin/gnuplot -persist"
#endif

class Plotter
{

public:

    Plotter(const char* title = "");

    void AddRow(double x, double y);
    void AddRow(double x, double y1, double y2);
    void AddRow(double x, double y1, double y2, double y3);
    void AddRow(double x, double y1, double y2, double y3, double y4);
    void AddRow(double x, double y1, double y2, double y3, double y4, double y5);
    void AddRow(double x, double y1, double y2, double y3, double y4, double y5, double y6);

    void SetLabels(const char* label1);
    void SetLabels(const char* label1, const char* label2);
    void SetLabels(const char* label1, const char* label2, const char* label3);
    void SetLabels(const char* label1, const char* label2, const char* label3, const char* label4);
    void SetLabels(const char* label1, const char* label2, const char* label3, const char* label4, const char* label5);
    void SetLabels(const char* label1, const char* label2, const char* label3, const char* label4, const char* label5, const char* label6);

    void Plot();
    void Title(const char* title);
    void Xlabel(const char* label);
    void Ylabel(const char* label);

private:

    std::string title;
    std::string xlabel;
    std::string ylabel;
    std::vector<double> xdata;
    std::vector<std::vector<double> > ydata;
    std::vector<std::string> labels;
    int curveCnt;
};

#endif
