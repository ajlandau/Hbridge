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
    S1 = Switch(nodei, nodek);
    S2 = Switch(nodei, nodel);
    S3 = Switch(nodek, nodej);
    S4 = Switch(nodel, nodej);


    
}


void H_Bridge::Step(double t, double dt){
    
    int state = (int)GetSignal(signal);
    
    // call Switch model Step functions in switch...

switch(state){
    case 0: // "off" state with all open
        S1.Signal(0);
        
    case 1: // Forward state
        Switch(nodei, nodek, 1);
        Switch(nodei, nodel, 0);
        Switch(nodek, nodej, 0);
        Switch(nodel, nodej, 1);
        
    case 2: //Reverse state
        Switch(nodei, nodek, 0);
        Switch(nodei, nodel, 1);
        Switch(nodek, nodej, 1);
        Switch(nodel, nodej, 0);
        
}
}
