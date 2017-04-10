//
//  Switch.hpp
//  Hbridge
//
//  Created by Amy Landau on 3/24/17.
//  Copyright © 2017 Amy Landau. All rights reserved.
//
<<<<<<< HEAD
//can you hear me now?
//penis club
=======
//
>>>>>>> origin/master
#ifndef Switch_hpp
#define Switch_hpp

#include <stdio.h>
#include "Device.hpp"

class Switch : public Device
{
public:
    //Constructor
    Switch(int nodei, int nodej, int state);
    
    // Device interface:
    void Init();
    void DC();
    void Step(double t, double dt);
    
    //viewable accessors:
    double GetVoltage();
    double GetCurrent();

private:
    
    //Node indices:
    int nodei;
    int nodej;
    
    //Internal
    int nodep;
    
    //Params
    double Ron = 1.0e-3;
    double Roff = 1.0e6;
    int state;
};


#endif /* Switch_hpp */
