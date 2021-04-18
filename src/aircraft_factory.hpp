#pragma once

#include "aircraft.hpp"
#include "airport.hpp"

#include <set>
#include <string>
#include <vector>

constexpr size_t NUM_AIRCRAFT_TYPES = 3;

class AircraftFactory
{
private:
    std::unordered_set<std::string> registered_flights;

    bool is_flight_registered(std::string&) const;
    std::string generate_random_unique_flight_number();

public:
    AircraftType* aircraft_types[NUM_AIRCRAFT_TYPES] {};
    const std::vector<std::string> airlines = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };

    void init_aircraft_types();
    [[nodiscard]] std::unique_ptr<Aircraft> create_aircraft(const AircraftType& type, Airport* airport);
    [[nodiscard]] std::unique_ptr<Aircraft> create_random_aircraft(Airport* airport);
};