#include "Parking.h"

namespace MtmParkingLot{

    //defines for MtmParkingLot
    const int PENALTY = 250;
    const int MOTORBIKE_FIRST_HOUR = 10;
    const int MOTORBIKE_HOUR = 5;
    const int MOTORBIKE_MAX_HOUR_PAY = 6;
    const int CAR_FIRST_HOUR = 20;
    const int CAR_HOUR = 10;
    const int CAR_MAX_HOUR_PAY = 6;
    const int HANDICAPPED_PRICE = 15;
    const int NO_PAY_TIME = 0;

    //parking c'tors
    Parking::Parking(VehicleType blockType, unsigned int num, VehicleType
    vehicleType,LicensePlate licensePlate, Time entranceTime,
    bool vehiclePenalty):
        spot(blockType,num), type(vehicleType), plate(licensePlate),
        entrance(entranceTime), penalty(vehiclePenalty) {
    }

    Parking::Parking(LicensePlate licensePlate):
        spot(), type(), plate(licensePlate),
        entrance(), penalty(false) {
    }

    Parking::Parking(const Parking& other) :
        spot(other.spot.getParkingBlock(), other.spot.getParkingNumber()),
        type(other.type), plate(other.plate),
        entrance(other.entrance), penalty(other.penalty) {
    }

    //get functions 

    bool Parking::getPenalty() const {
        return penalty;
    }

    void Parking::setPenalty() {
        penalty = true;
    }

    LicensePlate Parking::getLicensePlate() const {
        return plate;
    }

    
    Time Parking::getEntranceTime() const {
        return entrance;
    }

    VehicleType Parking::getVehicleType() const {
        return type;
    }

    ParkingSpot Parking::getParkingSpot() const {
        return spot;
    }

    //calculate price functions

    unsigned int Parking::calculatePrice(Time exit) const {
       
        unsigned int total_price = 0;
        unsigned int hours = (exit - entrance).toHours(); 
        unsigned int vehicle_first_hour = 0, vehicle_hour = 0;

        if (hours == NO_PAY_TIME) {
            total_price = 0;
        }
        else {
            if (type == MOTORBIKE) {
                if (hours > MOTORBIKE_MAX_HOUR_PAY) {
                    hours = MOTORBIKE_MAX_HOUR_PAY;
                }
                vehicle_first_hour = MOTORBIKE_FIRST_HOUR;
                vehicle_hour = MOTORBIKE_HOUR;
            }
            else if (type == CAR) {
                if (hours > CAR_MAX_HOUR_PAY) {
                    hours = CAR_MAX_HOUR_PAY;
                }
                vehicle_first_hour = CAR_FIRST_HOUR;
                vehicle_hour = CAR_HOUR;
            }
            
            if (type == HANDICAPPED) {
                total_price = HANDICAPPED_PRICE;
            }
            else {
                total_price = vehicle_first_hour + (hours - 1) * vehicle_hour;
            }
        }

        if (penalty) {
            total_price += PENALTY;
        }
        return total_price;
    }
}

