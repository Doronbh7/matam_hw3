#include "ParkingLot.h"

namespace MtmParkingLot{

    ParkingLot::ParkingLot(unsigned int parkingBlockSizes[]) {
        parking_lot = new UniqueArray<Parking, Compare>* [ARR_SIZE];
        for (int i = 0; i < ARR_SIZE; i++) {
            parking_lot[i] = new UniqueArray<Parking, Compare>
                    (parkingBlockSizes[i]);
        }
    }

    ParkingLot::~ParkingLot() {
        for (int i = 0; i < ARR_SIZE; i++) {
            delete parking_lot[i];
        }
        delete[] parking_lot;
    }

    ParkingResult ParkingLot::enterParking(VehicleType vehicleType,
            LicensePlate licensePlate, Time entranceTime) {
        const Parking* park_ptr = getParkingInLot(vehicleType, licensePlate);
        if (park_ptr != nullptr) {
            ParkingLotPrinter::printVehicle(std::cout, vehicleType,
                    licensePlate, park_ptr->getEntranceTime());
            ParkingLotPrinter::printEntryFailureAlreadyParked(std::cout,
                    park_ptr->getParkingSpot());
            return VEHICLE_ALREADY_PARKED;
        }

        //trying to insert
        unsigned int index = 0;
        VehicleType blockType = vehicleType;
        if (!parking_lot[blockType]->getFirstEmptyIndex(index)) {
            if (vehicleType == HANDICAPPED &&
                parking_lot[CAR]->getFirstEmptyIndex(index)) {
                blockType = CAR;
            }
            else {
                ParkingLotPrinter::printVehicle(std::cout, vehicleType,
                        licensePlate, entranceTime);
                ParkingLotPrinter::printEntryFailureNoSpot(std::cout);
                return NO_EMPTY_SPOT;
            }
        }
        //else
        park_ptr = new Parking(blockType, index, vehicleType, licensePlate,
                entranceTime);
        parking_lot[blockType]->insert(*park_ptr);
        ParkingLotPrinter::printVehicle(std::cout, vehicleType, licensePlate,
                entranceTime);
        ParkingLotPrinter::printEntrySuccess(std::cout, park_ptr->
        getParkingSpot());
        delete park_ptr;
        return SUCCESS;
    }

    ParkingResult ParkingLot::exitParking(LicensePlate licensePlate,
            Time exitTime) {
        VehicleType blockType;
        const Parking* park_ptr = getParkingInLot(licensePlate, blockType);
        if (park_ptr == nullptr) {
            ParkingLotPrinter::printExitFailure(std::cout, licensePlate);
            return VEHICLE_NOT_FOUND;
        }
        //else
        ParkingLotPrinter::printVehicle(std::cout, park_ptr->getVehicleType(),
                licensePlate, park_ptr->getEntranceTime());
        ParkingLotPrinter::printExitSuccess(std::cout, park_ptr->
        getParkingSpot(), exitTime, park_ptr->calculatePrice(exitTime));
        Parking park_to_remove(licensePlate);
        parking_lot[blockType]->remove(park_to_remove);
        return SUCCESS;
        //park_ptr memory is gone!!! dont use it[need to check]
    }

    ParkingResult ParkingLot::getParkingSpot(LicensePlate licensePlate,
            ParkingSpot& parkingSpot) const {
        const Parking* temp_park;
        for (int i = 0; i < ARR_SIZE; i++) {
            temp_park = this->getParkingInLotBlock((VehicleType)i,
                    licensePlate);
            if (temp_park != nullptr) {
                parkingSpot = temp_park->getParkingSpot();
                return SUCCESS;
            }
        }
        return VEHICLE_NOT_FOUND;
    }

    ostream& operator<<(ostream& os, const ParkingLot& parkingLot) {
        bool* cur_index_arr;
        Parking** cur_parking_arr;
        unsigned int cur_max_size = 0;
        ParkingLotPrinter::printParkingLotTitle(os);
        for (int i = 0; i < ARR_SIZE; i++) {
            cur_index_arr = parkingLot.parking_lot[i]->getIndexArr();
            cur_parking_arr = parkingLot.parking_lot[i]->getElementArr();
            cur_max_size = parkingLot.parking_lot[i]->getSize();
            for (unsigned int j = 0; j < cur_max_size; j++) {
                if (cur_index_arr[j])
                {
                    ParkingLotPrinter::
                    printVehicle(os, cur_parking_arr[j]->getVehicleType(), 
                                     cur_parking_arr[j]->getLicensePlate(), 
                                     cur_parking_arr[j]->getEntranceTime());
                    ParkingLotPrinter::
                    printParkingSpot(os, cur_parking_arr[j]->getParkingSpot());
                }
            }
            //ALEADY SORTED!
        }
        return os;
    }

    void ParkingLot::inspectParkingLot(Time inspectionTime) {
        unsigned int cur_max_size = 0;
        bool* cur_index_arr;
        Parking** cur_parking_arr;
        unsigned int hours = 0, vehicles_fined = 0;
        for (int i = 0; i < ARR_SIZE; i++) {
            cur_index_arr = parking_lot[i]->getIndexArr();
            cur_max_size = parking_lot[i]->getSize();
            cur_parking_arr = parking_lot[i]->getElementArr();
            for (unsigned int j = 0; j < cur_max_size; j++) {
                if (cur_index_arr[j])
                {
                    hours = (inspectionTime - cur_parking_arr[j]->
                            getEntranceTime()).toHours();
                    if (hours > MAX_HOURS_TILL_FINE && !cur_parking_arr[j]->
                    getPenalty()) {
                        cur_parking_arr[j]->setPenalty();
                        vehicles_fined++;
                    }
                }
            }
        }
        ParkingLotPrinter::printInspectionResult(std::cout, inspectionTime,
                vehicles_fined);
    }



    //added
    const Parking* ParkingLot::getParkingInLotBlock(VehicleType blockType,
            LicensePlate licensePlate) const {
        Parking temp_park(licensePlate);
        return (*parking_lot[(int)blockType]).operator[](temp_park);
    }
    const Parking* ParkingLot::getParkingInLot(VehicleType vehicleType,
            LicensePlate licensePlate) const {
        const Parking* temp_park = getParkingInLotBlock(vehicleType,
                licensePlate);
        if (vehicleType == HANDICAPPED && temp_park == nullptr) {
            temp_park = getParkingInLotBlock(CAR, licensePlate);
        }
        return temp_park;
    }
    const Parking* ParkingLot::getParkingInLot(LicensePlate licensePlate,
            VehicleType& blockType) const {
        const Parking* temp_park;
        for (int i = 0; i < ARR_SIZE; i++) {
            temp_park = getParkingInLotBlock((VehicleType)i, licensePlate);
            if (temp_park != nullptr) {
                blockType = (VehicleType)i;
                return temp_park;
            }
        }
        return nullptr;
    }

    UniqueArray<Parking, Compare>** ParkingLot::getParkingLot() {
        return parking_lot;
    }
}




