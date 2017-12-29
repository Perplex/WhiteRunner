//
// Created by Ceegan on 2017-12-23.
//

#ifndef WHITERUNNER_VECTOR3_H
#define WHITERUNNER_VECTOR3_H

#include <iostream>

class vector3 {
public:
    float X=0;
    float Y=0;
    float Z=0;

    bool operator==(const vector3& vec);
    friend std::ostream& operator<<(std::ostream& os, const vector3 &v3);
};


#endif //WHITERUNNER_VECTOR3_H
