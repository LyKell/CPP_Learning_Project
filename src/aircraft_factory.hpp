#pragma once

#include "aircraft.hpp"
#include "airport.hpp"

#include <string>

constexpr size_t NUM_AIRCRAFT_TYPES = 3;

class AircraftFactory
{
private:
    AircraftType* aircraft_types[NUM_AIRCRAFT_TYPES] {};
    const std::string airlines[8] = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };

public:
    void init_aircraft_types();
    std::unique_ptr<Aircraft> create_aircraft(const AircraftType& type, Airport* airport) const;
    std::unique_ptr<Aircraft> create_random_aircraft(Airport* airport) const;
};