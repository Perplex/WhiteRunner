//
// Created by Ceegan on 2017-12-23.
//

#include "vector3.h"

bool vector3::operator==(const vector3 &vec) {
    return (this->X == vec.X) && (this->Y == vec.Y) && (this->Z == vec.Z);
}

std::ostream& operator<<(std::ostream &os, const vector3 &v3) {
    os << v3.X << ", " << v3.Y << ", " << v3.Z;
    return os;
}