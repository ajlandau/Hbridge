//
//  Switch.cpp
//  Hbridge
//
//  Created by Amy Landau on 3/24/17.
//  Copyright © 2017 Amy Landau. All rights reserved.
//

#include "Switch.hpp"
#include <cmath>

#include <iostream>

Switch::Switch(int nodei, int nodej){
    this->nodei = nodei;
    this->nodej = nodej;
    
}
void Switch::Init(){
    this-> nodep = GetNextNode();
    AddJacobian(nodei, nodep, 1.0);
    AddJacobian(nodej, nodep, -1.0);
    AddJacobian(nodep, nodei, 1.0);
    AddJacobian(nodep, nodej, -1.0);
}

void Switch::Signal(int state){

    
    switch(state)
    {
        case 0:
            AddJacobian(nodep, nodep, Roff);
            AddBEquivalent(nodep, GetVoltage());
        case 1:
            AddJacobian(nodep, nodep, Ron);
            AddBEquivalent(nodep, -Ron*GetCurrent());
            
            
    }
    
}


void Switch::Changestate(int newstate)
{
    if( newstate != state)
    {
        switch(newstate)
        {
            case 0:
                AddJacobian(nodep, nodep, Roff);
                AddBEquivalent(nodep, GetVoltage());
            case 1:
                AddJacobian(nodep, nodep, Ron);
                AddBEquivalent(nodep, -Ron*GetCurrent());

    }
}
    return;
}
void Switch::DC(){
    
    Step(0, 0);
    
}

double Switch::GetVoltage(){
    
    return GetStateDifference(nodei, nodej);
}

double Switch::GetCurrent(){
    
    // look at diode:
    switch(state)
    {
        case 0:
            return GetVoltage() / Roff;
        case 1:
            return GetVoltage() / Ron;
    }
    return 0;
}
