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

#ifndef DEVICE_H
#define DEVICE_H

enum sourceType { DCSOURCE, SINESOURCE, SQUARESOURCE, TRISOURCE };


class Simulator;

/**
Generic device type that defines the interface that needs to be implemented by derived
device classes, like Resistor, Inductor, Capacitor, Voltage, etc
**/
class Device
{

public:

    /////////////// Device Interface ///////////////

    /*
    NOTE:  The derived device must implement it's own contructor that takes in the node
    indices and device parameters, and stores them in member variables
    */

    /**
    This function is where you should do any pre-simulation set up. Also, you should
    get and store integer values for internal nodes here with the GetNextNode() function
    (example: nodep = GetNextNode())
    */
    virtual void Init();

    /**
    Stamps the DC model of the device for DC operating point calculation (optional,
    default behavior is to call Step(0, 0)).
    */
    virtual void DC();

    /**
    Steps the device for transient analysis.
    Its function is to implement the behavior needed for transient analysis (.trans).
    It takes in the current time (s) and time step (s), and applies the stamps to the J
    and B matrices accordingly
    @param t is the current simulation time in seconds
    @param dt is the current simulation time step in seconds
    */
    virtual void Step(double t, double dt);

    /**
    Steps the device to update the simulator signals.
    It takes in the current time (s) and time step (s), and you should get and/or set
    signals her with the GetSignal() and SetSignal() function
    @param t is the current simulation time in seconds
    @param dt is the current simulation time step in seconds
    */
    virtual void SignalStep(double t, double dt);


    ///////////// End Device Interface /////////////

    // This function exists to set the parent simulator instance: 
    void SetSim(Simulator& sim);

protected:

    // reference to the parent simulator object:
    Simulator* sim;

    // utility functions for accessing sim matrices
    // (wrappers around simulator accessors):

    /*
    Wrapper for Simulator::GetTime() const
    */
    double GetTime() const;

    /*
    Wrapper for Simulator::GetTimeStep() const
    */
    double GetTimeStep() const;
    
    /*
    Wrapper for Simulator::GetState(const int i) const
    */
    double GetState(const int i) const;

    /*
    Wrapper for Simulator::GetIterationState(const int i) const
    */
    double GetIterationState(const int i) const;

    /*
    Wrapper for Simulator::GetStateDifference(const int i, const int j) const
    */
    double GetStateDifference(const int i, const int j) const;

    /*
    Wrapper for Simulator::GetIterationStateDifference(const int i, const int j) const
    */
    double GetIterationStateDifference(const int i, const int j) const;

    /*
    Wrapper for Simulator::GetJacobian(const int i, const int j)  const
    */
    double GetJacobian(const int i, const int j) const;

    /*
    Wrapper for Simulator::GetBEquivalent(const int i)  const
    */
    double GetBEquivalent(const int i) const;

    /*
    Allows the addition of internal nodes
    */
    int GetNextNode();

    /*
    Wrapper for Simulator::SetInitialState(const int i, const double value)
    */
    void SetInitialState(const int i, const double value); 

    /*
    Wrapper for Simulator::AddJacobian(const int i, const int j, const double value)
    */
    void AddJacobian(const int i, const int j, const double value); 

    /*
    Wrapper for Simulator::AddBEquivalent(const int i, const double value)
    */
    void AddBEquivalent(const int i, const double value);     

    ///////////////// Signal Solver interface //////////////////////

    /*
    Wrapper for const double Simulator::GetSignal(const int signal) const
    */
    double GetSignal(const int signal) const;

    /*
    Wrapper for Simulator::SetSignal(const int signal, const double value)
    */
    void SetSignal(const int signal, const double value);

};

#endif
