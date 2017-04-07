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
#include <vector>
#include <string>
#include <cmath>

#include "Simulator.hpp"
#include "Matrix.hpp"

using std::vector;
using std::string;
using std::fmax;

Simulator::Simulator(const int nodes, const int signals)
{
    this->externalNodes = nodes;
    this->signals = signals;

    // init device list to empty list:
    this->devices = vector<Device*>(0);
}

void Simulator::Init(const double dt, const double tf, const int maxIter, const double tolerance, const bool solveDCOperatingPoint)
{
    // transient values:
    this->dt = dt;
    this->tf = tf;
    this->t = 0.0;

    // Newton values:
    this->maxIter = maxIter;
    this->tolerance = tolerance;

    this->nodes = this->externalNodes;

    for (unsigned int i = 0; i < devices.size(); i++)
    {
        devices[i]->Init();
    }

    J = Matrix(nodes, nodes);
    B = ColumnVector(nodes);
    X0 = ColumnVector(nodes);
    X = ColumnVector(nodes);
    Xk = ColumnVector(nodes);

    // solve for DC steady-state if requested:
    if (solveDCOperatingPoint)
    {
        SolveDC();
    } 

    S = ColumnVector(signals + 1); // add 1 for 1-based indexing
}

void Simulator::SolveDC()
{
    Solve(true);
}

void Simulator::Add(Device& device)
{
    // add reference to sim object to device:
    device.SetSim(*this);

    // add device to device list:
    this->devices.push_back(&device);
}

double Simulator::GetTime() const
{
    return this->t;
}

double Simulator::GetTimeStep() const
{
    return this->dt;
}

void Simulator::Step()
{   
    SignalStep();
    Solve();
    t += dt;
}

void Simulator::SignalStep()
{
    for (unsigned int i = 0; i < devices.size(); i++)
    {
        {
            devices[i]->SignalStep(t, dt);
        }
    }
}

bool Simulator::IsRunning() const
{
    return t < tf;
}

void Simulator::SetMaxIterations(const int value)
{
    this->maxIter = value;
}

void Simulator::SetTolerance(const double value)
{
    this->tolerance = value;
}

double Simulator::GetState(const int i) const
{
    return X(i);
}

double Simulator::GetIterationState(const int i) const
{
    return Xk(i);
}

double Simulator::GetStateDifference(const int i, const int j) const
{
    return X(i) - X(j);
}

double Simulator::GetIterationStateDifference(const int i, const int j) const
{
    return Xk(i) - Xk(j);
}

double Simulator::GetJacobian(const int i, const int j) const
{
    return J(i, j);
}

double Simulator::GetBEquivalent(const int i) const
{
    return B(i);
}

void Simulator::SetInitialState(const int i, const double value)
{
    X0(i) = value;
}

void Simulator::AddJacobian(const int i, const int j, const double value)
{
    J(i, j) += value;
}

void Simulator::AddBEquivalent(const int i, const double value)
{
    B(i) += value;
}

Matrix* Simulator::GetJacobian()
{
    return &J;
}

ColumnVector* Simulator::GetBEquivalent()
{
    return &B;
}

ColumnVector* Simulator::GetStateVector()
{
    return &X;
}

ColumnVector* Simulator::GetIterationStateVector()
{
    return &Xk;
}

int Simulator::GetIterations() const
{
    return iteration;
}

int Simulator::GetNextNode()
{
    nodes += 1;
    return nodes;
    std::cout << nodes << std::endl;
}

double Simulator::GetSignal(const int signal) const
{
    return S(signal);
}

void Simulator::SetSignal(const int signal, const double value)
{
    S(signal) = value;
}

///// private functions:

void Simulator::Solve(bool dc)
{
    double error;
    ColumnVector Xkm1;

    Xk = X;

    iteration = 0;

    while (iteration < maxIter)
    {
        J.Clear();
        B.Clear();

        
        for (unsigned int i = 0; i < devices.size(); i++)
        {
            if (dc)
            {
                devices[i]->DC();
            }
            else
            {
                devices[i]->Step(t, dt);
            }
        }

        Xkm1 = Xk;
        Xk = J.LeftDivide(B);

        error = 0.0;

        for (int i = 1; i <= nodes; i++)
        {
            error = fmax(abs(Xk(i) - Xkm1(i)), error);
        }

        if (error < tolerance)
        {
            break;
        }

        iteration += 1;
    }

    X = Xk;
}