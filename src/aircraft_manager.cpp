#include "aircraft_manager.hpp"

#include <utility>

void AircraftManager::add(std::unique_ptr<Aircraft> aircraft)
{
    aircrafts.emplace_back(std::move(aircraft));
}


bool AircraftManager::move()
{
    for (auto aircraft_it = aircrafts.begin(); aircraft_it != aircrafts.end();)
    {
        auto& aircraft = **aircraft_it;
        if (aircraft.move())
        {
            ++aircraft_it;
        }
        else
        {
            aircraft_it = aircrafts.erase(aircraft_it);
        }            
    }
    return true;
}