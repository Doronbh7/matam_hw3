#ifndef CURRENTPROJECT_COMPARE_H
#define CURRENTPROJECT_COMPARE_H

#include "Parking.h"
/**
 * Compare function object.
 * The function compare vehicles that parking by their license plate
 */
namespace MtmParkingLot{
    class Compare{
    public:
        bool operator()(const Parking& a, const Parking& b )const{
            if(a.getLicensePlate()==b.getLicensePlate()){
                return true;
            }
            return false;
        }

    };
}

#endif //CURRENTPROJECT_COMPARE_H
