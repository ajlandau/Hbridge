//
//  H_bridge.hpp
//  Hbridge
//
//  Created by Amy Landau on 3/31/17.
//  Copyright © 2017 Amy Landau. All rights reserved.
//
//                       o
//                       |
//        _______________|_______________
//       |_____                     _____|
//       |     |                   |     |
// s1  \     -----               -----     /
//      \     /_\ D1          D2  /_\     /  s2
//       |     |                   |     |
//       |_____|                   |_____|
//       |                               |
//     o-|                               |-o
//       |_____                     _____|
//       |     |                   |     |
//     \     -----               -----     /
//  s3  \     /_\ D3          D4  /_\     /  s4
//       |     |                   |     |
//       |_____|                   |_____|
//       |_______________________________|
//                       |
//                       |
//                       o
//
//
//

#ifndef H_bridge_hpp
#define H_bridge_hpp

#include <stdio.h>
#include "Device.hpp"


class H_Bridge:public Device
{
public:
   //Constructor
    H_Bridge(int nodei, int nodej, int nodek, int nodel, int state);
    
   //Device Interface
    
private:
    
    // Internal Construction
    
};
#endif /* H_bridge_hpp */
