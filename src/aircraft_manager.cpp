#include "aircraft_manager.hpp"

#include <algorithm>
#include <utility>

void AircraftManager::add(std::unique_ptr<Aircraft> aircraft)
{
    aircrafts.emplace_back(std::move(aircraft));
}


bool AircraftManager::move()
{
    aircrafts.erase(std::remove_if(aircrafts.begin(), aircrafts.end(), [](std::unique_ptr<Aircraft>& a) { return !(a->move()); }), aircrafts.end());
    return true;
}


int AircraftManager::count_aircraft_per_airline(const std::string& airline) const {
    return std::count_if(aircrafts.begin(), aircrafts.end(),
        [&airline](const std::unique_ptr<Aircraft>& aircraft) {
            return aircraft->get_flight_num().compare(0, airline.size(), airline) == 0;
        });
}