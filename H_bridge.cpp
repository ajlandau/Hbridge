//
//  H_bridge.cpp
//  Hbridge
//
//  Created by Amy Landau on 3/31/17.
//  Copyright © 2017 Amy Landau. All rights reserved.
//
//                       o
//                       | nodei
//        _______________|_______________
//       |_____                     _____|
//       |     |                   |     |
// s1  \     -----               -----     /
//      \     /_\ D1          D2  /_\     /  s2
//       |     |                   |     |
//       |_____|                   |_____|
// nodek |                               | nodel
//    o--|                               |--o
//       |_____                     _____|
//       |     |                   |     |
//     \     -----               -----     /
//  s3  \     /_\ D3          D4  /_\     /  s4
//       |     |                   |     |
//       |_____|                   |_____|
//       |_______________________________|
//                       |
//                       o nodej

#include "H_bridge.hpp"
#include "Switch.hpp"
#include "Diode.hpp"


H_Bridge::H_Bridge(int nodei, int nodej, int nodek, int nodel, int state){
    
    //define components
    Diode(nodek, nodei);
    Diode(nodej, nodek);
    Diode(nodej, nodel);
    Diode(nodel, nodei);
    
    switch(state){
        case 0: // "off" state with all open
            Switch(nodei, nodek, 0);
            Switch(nodei, nodel, 0);
            Switch(nodek, nodej, 0);
            Switch(nodel, nodej, 0);
            
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
