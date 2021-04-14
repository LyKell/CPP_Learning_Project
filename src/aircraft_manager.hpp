#pragma once

#include "GL/dynamic_object.hpp"
#include "aircraft.hpp"

#include <memory>
#include <vector>

class AircraftManager : public GL::DynamicObject
{
private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts;

public:
    void add(std::unique_ptr<Aircraft> aircraft);
    bool move();
    int count_aircraft_per_airline(const std::string&) const;
    bool compare_two_aircrafts(std::unique_ptr<Aircraft>&, std::unique_ptr<Aircraft>&);
    int get_required_fuel();
};