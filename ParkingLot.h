#ifndef MTMPARKINGLOT_PARKINGLOT_H
#define MTMPARKINGLOT_PARKINGLOT_H

#include "ParkingLotTypes.h"
#include "Time.h"
#include "ParkingSpot.h"
#include "Parking.h"
#include "UniqueArray.h"
#include "ParkingLotPrinter.h"
#include "Compare.h"

namespace MtmParkingLot {

    const int ARR_SIZE = 3;
    const int MAX_HOURS_TILL_FINE = 24;

    using namespace ParkingLotUtils;
    using std::ostream;

    class ParkingLot {

        UniqueArray<Parking,Compare>** parking_lot;

    public:

        ParkingLot(unsigned int parkingBlockSizes[]);
        ~ParkingLot();
        ParkingResult enterParking(VehicleType vehicleType, LicensePlate
        licensePlate, Time entranceTime);
        ParkingResult exitParking(LicensePlate licensePlate, Time exitTime);
        ParkingResult getParkingSpot(LicensePlate licensePlate, ParkingSpot&
        parkingSpot) const;
        void inspectParkingLot(Time inspectionTime);
        friend ostream& operator <<(ostream& os, const ParkingLot& parkingLot);


        //added
        /**
         *get parking by license plate and by block type
         * @param blockType
         * @param licensePlate
         * @return the parking in the lot
         */
        const Parking* getParkingInLotBlock(VehicleType blockType, LicensePlate
        licensePlate) const;

        /**
         *get parking by license plate and vehicle type
         * @param vehicleType
         * @param licensePlate
         * @return the parking in the lot
         */
        const Parking* getParkingInLot(VehicleType vehicleType, LicensePlate
        licensePlate) const;

        /**
         *get the parking by license plate and set the block of the parking in
         * blockType
         * @param licensePlate
         * @param blockType
         * @return
         */
        const Parking* getParkingInLot(LicensePlate licensePlate, VehicleType&
        blockType) const;

        /**
         *get the parking lot
         * @return UniqueArray<Parking, Compare>** parking_lot
         */
        UniqueArray<Parking, Compare>** getParkingLot();
    };

}

#endif //MTMPARKINGLOT_PARKINGLOT_H
