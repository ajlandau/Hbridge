//
//  H_bridge.cpp
//  Hbridge
//
//  Created by Amy Landau on 3/31/17.
//  Copyright © 2017 Amy Landau. All rights reserved.
//
//                       o  Positive
//                       | nodei
//        _______________|_______________
//       |_____                     _____|
//       |     |                   |     |
// s1  \     -----               -----     /
//      \     /_\ D1          D2  /_\     /  s2
//       |     |                   |     |
//       |_____|                   |_____|
// nodek |                               | nodel
//    o--|                               |--o neg
//  pos |_____                     _____|
//       |     |                   |     |
//     \     -----               -----     /
//  s3  \     /_\ D3          D4  /_\     /  s4
//       |     |                   |     |
//       |_____|                   |_____|
//       |_______________________________|
//                       |
//              negative o nodej

#include "H_bridge.hpp"
#include "Switch.hpp"
#include "Diode.hpp"


H_Bridge::H_Bridge(int nodei, int nodej, int nodek, int nodel, int signal){
    
    
    this->signal = signal;
    //define components
    Diode(nodek, nodei);
    Diode(nodej, nodek);
    Diode(nodej, nodel);
    Diode(nodel, nodei);
    
    
   
    
    
    /*
     
     0. add Switch instance refernces as members to H_Bridge
     1. construct switches in constuctor, no state argument (just nodes)
     2. implement Step(bool state) for switch model
     3. call Step(bool state) from H_Braige.Step(...)
     
     */
    

    
}


void H_Bridge::Step(double t, double dt){
    
    int state = (int)GetSignal(signal);

    
    // call Switch model Step functions in switch...

switch(state){
    case 0: // "off" state with all open
        S1.Changestate(0);
        S2.Changestate(0);
        S3.Changestate(0);
        S4.Changestate(0);
        output = 'W';
        
        
    case 1: // Forward state
        S1.Changestate(1);
        S2.Changestate(0);
        S3.Changestate(0);
        S4.Changestate(1);
        output = 'F';
        
    case 2: //Reverse state
        S1.Changestate(0);
        S2.Changestate(1);
        S3.Changestate(1);
        S4.Changestate(0);
        output = 'R';
        
}
    
    
}
