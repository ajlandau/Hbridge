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
//

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
        case 0: // "off" state
            
        case 1: // Forward state
            
        case 2: //Reverse state
            
            
    }
    
}
