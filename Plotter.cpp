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
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include "Plotter.hpp"

Plotter::Plotter(const char* title)
{
    this->title = title;
    this->xlabel = "t (s)";
    this->ylabel = "";
    this->xdata = std::vector<double>(0);
    this->ydata = std::vector<std::vector<double> >(6);
    this->labels = std::vector<std::string>(6);
    this->curveCnt = 0;
}

void Plotter::AddRow(double x, double y)
{
    this->xdata.push_back(x);
    this->ydata[0].push_back(y);
    this->curveCnt = 1;
}

void Plotter::AddRow(double x, double y1, double y2)
{
    Plotter::AddRow(x, y1);
    this->ydata[1].push_back(y2);
    this->curveCnt = 2;
}

void Plotter::AddRow(double x, double y1, double y2, double y3)
{
    Plotter::AddRow(x, y1, y2);
    this->ydata[2].push_back(y3);
    this->curveCnt = 3;
}

void Plotter::AddRow(double x, double y1, double y2, double y3, double y4)
{
    Plotter::AddRow(x, y1, y2, y3);
    this->ydata[3].push_back(y4);
    this->curveCnt = 4;
}

void Plotter::AddRow(double x, double y1, double y2, double y3, double y4, double y5)
{
    Plotter::AddRow(x, y1, y2, y3, y4);
    this->ydata[4].push_back(y5);
    this->curveCnt = 5;
}

void Plotter::AddRow(double x, double y1, double y2, double y3, double y4, double y5, double y6)
{
    Plotter::AddRow(x, y1, y2, y3, y4, y5);
    this->ydata[5].push_back(y6);
    this->curveCnt = 6;
}

void Plotter::SetLabels(const char* label1)
{
    this->labels[0] = label1;
}

void Plotter::SetLabels(const char* label1, const char* label2)
{
    Plotter::SetLabels(label1);
    this->labels[1] = label2;
}

void Plotter::SetLabels(const char* label1, const char* label2, const char* label3)
{
    Plotter::SetLabels(label1, label2);
    this->labels[2] = label3;
}

void Plotter::SetLabels(const char* label1, const char* label2, const char* label3, const char* label4)
{
    Plotter::SetLabels(label1, label2, label3);
    this->labels[3] = label4;
}

void Plotter::SetLabels(const char* label1, const char* label2, const char* label3, const char* label4, const char* label5)
{
    Plotter::SetLabels(label1, label2, label3, label4);
    this->labels[4] = label5;
}

void Plotter::SetLabels(const char* label1, const char* label2, const char* label3, const char* label4, const char* label5, const char* label6)
{
    Plotter::SetLabels(label1, label2, label3, label4, label5);
    this->labels[5] = label6;
}


void Plotter::Plot()
{

    std::ofstream dat;
    dat.open("plot.dat");

    for (unsigned int i = 0; i < this->xdata.size(); i++)
    {
        dat << this->xdata[i] << " ";

        for (int k = 0; k < this->curveCnt; k++)
        {
            dat << this->ydata[k][i] << " ";
        }
        dat << std::endl;
    }

    dat.close();

#ifdef __APPLE__
    FILE *pipe = popen(GNUPLOT, "w");
#else
    FILE *pipe = _popen(GNUPLOT, "w");
#endif

    if (pipe != NULL)
    {

        fprintf(pipe, "set term wx\n");
        fprintf(pipe, "set title '%s'\n", this->title.c_str());
        fprintf(pipe, "set xlabel '%s'\n", this->xlabel.c_str());
        fprintf(pipe, "set ylabel '%s'\n", this->ylabel.c_str());
        fprintf(pipe, "plot ");

        for (int k = 0; k < this->curveCnt; k++)
        {
            fprintf(pipe, "'plot.dat' u 1:%d w l title '%s', \\\n", k + 2, labels[k].c_str());
        }

        fflush(pipe);
    }
    else
    {
        std::cout << "Could not open pipe" << std::endl;
    }
}

void Plotter::Title(const char* title)
{
    this->title = std::string(title);
}

void Plotter::Xlabel(const char* label)
{
    this->xlabel = std::string(label);
}

void Plotter::Ylabel(const char* label)
{
    this->ylabel = std::string(label);
}
