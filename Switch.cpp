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

Switch::Switch(int nodei, int nodej, int state){
    this->nodei = nodei;
    this->nodej = nodej;
    
    this->state = state;
}
void Switch::Init(){
    this-> nodep = GetNextNode();
}

void Switch::Step(double t, double dt){
    AddJacobian(nodei, nodep, 1.0);
    AddJacobian(nodej, nodep, -1.0);
    AddJacobian(nodep, nodei, 1.0);
    AddJacobian(nodep, nodej, -1.0);
    
    switch(state)
    {
        case 0:
            AddJacobian(nodep, nodep, Roff);
            AddBEquivalent(nodep, GetVoltage());
        case 1:
            AddJacobian(nodep, nodei, Ron);
            AddBEquivalent(nodep, -Ron*GetCurrent());
            
            
    }
    
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
