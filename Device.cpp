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

#include <cstdio>
#include <vector>
#include <string>

#include "Device.hpp"
#include "Simulator.hpp"


void Device::Init()
{
    
}

void Device::DC()
{
    // by default, call transient step function with t=0 and dt=0:
    this->Step(0.0, 0.0);
}

void Device::Step(double t, double dt)
{

}

void Device::SignalStep(double t, double dt)
{

}

void Device::SetSim(Simulator& sim)
{
    this->sim = &sim;
}

double Device::GetTime() const
{
    return sim->GetTime();
}

double Device::GetTimeStep() const
{
    return sim->GetTimeStep();
}

double Device::GetState(const int i)  const
{
    return sim->GetState(i);
}

double Device::GetIterationState(const int i)  const
{
    return sim->GetIterationState(i);
}

double Device::GetStateDifference(const int i, const int j)  const
{
    return sim->GetStateDifference(i, j);
}

double Device::GetIterationStateDifference(const int i, const int j)  const
{
    return sim->GetIterationStateDifference(i, j);
}

double Device::GetJacobian(const int i, const int j)  const
{
    return sim->GetJacobian(i, j);
}

double Device::GetBEquivalent(const int i) const
{
    return sim->GetBEquivalent(i);
}

int Device::GetNextNode()
{
    return sim->GetNextNode();
}

void Device::SetInitialState(const int i, const double value)
{
    sim->SetInitialState(i, value);
}

void Device::AddJacobian(const int i, const int j, const double value)
{
    sim->AddJacobian(i, j, value);
}

void Device::AddBEquivalent(const int i, const double value)
{
    sim->AddBEquivalent(i, value);
}

double Device::GetSignal(const int signal) const
{
    return sim->GetSignal(signal);
}

void Device::SetSignal(const int signal, const double value)
{
    sim->SetSignal(signal, value);
}