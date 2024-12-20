#ifndef PARKING_H
#define PARKING_H

#include "ParkingSpot.h"
#include "ParkingLotTypes.h"
#include "Time.h"

using namespace ParkingLotUtils;

namespace MtmParkingLot {

    class Parking {
        ParkingSpot spot;
        VehicleType type;
        LicensePlate plate;
        Time entrance;
        bool penalty;

    public:
        /**
         * Constructor
         * @param blockType
         * @param num
         * @param vehicleType
         * @param licensePlate
         * @param entranceTime
         * @param vehiclePenalty
         */

        Parking(VehicleType blockType, unsigned int num, VehicleType
        vehicleType,LicensePlate licensePlate, Time entranceTime,
        bool vehiclePenalty = false);

        /**
         * Constructor
         * @param licensePlate
         */
        Parking(LicensePlate licensePlate);

        /**
         * Constructor
         * @param other
         */
        Parking(const Parking& other);

        /**
         * get the license plate
         * @return LicensePlate plate
         */
        LicensePlate getLicensePlate() const;

        /**
         * get the parking spot
         * @return ParkingSpot spot
         */
        ParkingSpot getParkingSpot() const;

        /**
         * get the vehicle type
         * @return VehicleType type
         */
        VehicleType getVehicleType() const;

        /**
         * get the entrance time
         * @return Time entrance
         */
        Time getEntranceTime() const;

        /**
         * get if the vehicle got penalty
         * @return bool penalty
         */
        bool getPenalty() const;

        /**
         * if the vehicle get penalty the function set penalty=true
         *
         */
        void setPenalty();

        /**
         * the function calculates the total price of the vehicle
         * @param exit time of the vehicle
         * @return unsigned total_price
         */
        unsigned int calculatePrice(Time exit) const;
    };
}

#endif //PARKING_H
