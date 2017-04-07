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

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>
#include <cstdio>
#include <vector>
#include <string>

#include "Matrix.hpp"
#include "Device.hpp"

using std::vector;
using std::string;

class Device;

/**
Simulation engine class that contains system state, device references, and various
utility functions.
**/
class Simulator
{
public:

    /**
    Constructor
    @param nodes is the integer number of nodes (including internal, excluding ground)
    **/
    Simulator(const int nodes, const int signals = 0);

    /**
    initializes the simulator for transient analysis.
    @param dt is the time step in seconds
    @param tf is the final simulation time in seconds
    @param solveDCOperatingPoint if true, initializes the states by solving the DC operating point
    **/
    void Init(const double dt=0.0, const double tf=0.0, const int maxIter=100, const double tolerance=1e-6, bool solveDCOperatingPoint=false);

    /**
    Solves the DC operating point of the system.
    **/
    void SolveDC();

    /**
    Adds a device to the simulator.
    @param device: The device to add of base type Device
    **/
    void Add(Device& device);

    /**
    Gets the current simulation time
    @return the current simulation time in seconds
    **/
    double GetTime() const;

    /**
    Gets the current simulation time step
    @returns the current time step in seconds 
    **/
    double GetTimeStep() const;

    /**
    Calls all device SignalStep functions
    **/
    void SignalStep();

    /**
    Clears Jacobian and B-Equivalent, calls step on all devices, updates the
    system states, and increments the time
    **/
    void Step();

    /**
    Gets the running state of the simulator
    @return true if t < tf, and false if t >= tf
    **/
    bool IsRunning() const;

    /**
    Sets the maximum number of Newton iterations (minor steps)
    @param value is the integer number of interations
    **/
    void SetMaxIterations(const int value);

    /**
    Sets the Newton iteration error tolerance magnitude 
    @param value is the double tolerance value (Volts or Amperes)
    **/
    void SetTolerance(const double value);

    /**
    Gets the value of a state variable
    @param i is the node index of the state
    @return The state value at node i
    **/
    double GetState(const int i) const;

    /**
    Gets the value of a state variable for the previous Newton iteration
    @param i is the node index of the state
    @return The state value at node i
    **/
    double GetIterationState(const int i) const;

    /**
    Gets the difference between the value of two state variables
    @param i is the node index of the first state
    @param i is the node index of the second state
    @return The difference bewteen state i and j (X(i) - X(j))
    **/
    double GetStateDifference(const int i, const int j) const;

    /**
    Gets the difference between the value of two state variables
    at the previous iteration for the Newton solution
    @param i is the node index of the first state
    @param i is the node index of the second state
    @return The difference bewteen state i and j (X(i) - X(j))
    **/
    double GetIterationStateDifference(const int i, const int j) const;

    /**
    Gets the value at Jacobian matrix cell (i, j)
    @param i the Jacobian matrix row
    @param i the Jacobian matrix column
    @return The Jacobian matrix cell value at row i and column j
    **/
    double GetJacobian(const int i, const int j) const;

    /**
    Gets the value at B-Equivalent vector row i
    @param i the B-Equivalent vector row
    @return The B-Equivalent vector row value at row i
    **/
    double GetBEquivalent(const int i) const;

    /**
    Sets the initial value of the state at index i
    @param i is the state index to set
    @param value is the value to set at state i
    **/
    void SetInitialState(const int i, const double value);

    /**
    Sets the value at Jacobian matrix cell (i, j)
    @param i the Jacobian matrix row
    @param i the Jacobian matrix column
    @param The Jacobian matrix cell value to set at row i and column j
    **/
    void AddJacobian(const int i, const int j, const double value);

    /**
    Sets the value at B-Equivalent vector row i
    @param i the B-Equivalent vector row
    @param The B-Equivalent vector row value to set at row i
    **/
    void AddBEquivalent(const int i, const double value);

    /**
    Returns the current iteration number
    **/
    int GetIterations() const;

    /**
    Get a pointer to the Jacobian Matrix
    @return A pointer to the Jacobian Matrix
    **/
    Matrix* GetJacobian();

    /**
    Get a pointer to the B-Equivalent Vector
    @return A pointer to the B-Equivalent Vector
    **/
    ColumnVector* GetBEquivalent();

    /**
    Get a pointer to the State Vector
    @return A pointer to the State Vector
    **/
    ColumnVector* GetStateVector();

    /**
    Get a pointer to the Iteration State Vector
    @return A pointer to the Iteration State Vector
    **/
    ColumnVector* GetIterationStateVector();

    /**
    Get the next node integer and adds to the system
    @return the next node added to the system
    **/
    int GetNextNode();

    /*
    Get the current value for a signal
    @param signal is the signal index
    @return the value for signal at the index
    */
    double GetSignal(const int signal) const;

    /*
    Sets the current value for a signal
    @param signal is the signal index
    @param value is the value to set to the signal at the index
    */
    void SetSignal(const int signal, const double value);

private:

    /**
    Updates the states for transient and DC analysis (X = J\B)
    @param dc is a flag for solving the dc state (otherwise transient)
    **/
    void Solve(bool dc=false); 

    // Transient analysis:
    double t;                     ///< Current simualtion time for transient simulation (s)
    double tf;                    ///< Final time for the transient simulation (s) 
    double dt;                    ///< Current time step for the transient simulation (s) 

    // Linear Solver:
    Matrix J;                     ///< System Jacobian Matrix
    ColumnVector B;               ///< System B-Equivalent Vector
    ColumnVector X;               ///< System State Vector
    ColumnVector X0;              ///< System Initial State Vector
    vector<Device*> devices;      ///< List of System Devices
    int nodes;                    ///< Number of Nodes (including internal, excluding reference)
    int externalNodes;
    
    // Newton Solver:
    ColumnVector Xk;              ///< State vector for last iteration 
    int iteration;                ///< Current Newton iteration
    int maxIter;                  ///< Maximum number of Newton iterations
    double tolerance;             ///< Maximum error magnitude for states in X vector for Newton solver

    // Signal Solver:
    ColumnVector S;               ///< Signal vector
    int signals;
};

#endif