#include "aircraft_manager.hpp"
#include "aircraft_crash.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>
#include <utility>


void AircraftManager::add(std::unique_ptr<Aircraft> aircraft)
{
    assert((aircraft != nullptr) && "airport can't be nullptr in AircraftManager::add");
    aircrafts.emplace_back(std::move(aircraft));
}


bool AircraftManager::move()
{
    std::sort(aircrafts.begin(), aircrafts.end(),
        [this](std::unique_ptr<Aircraft>& a1, std::unique_ptr<Aircraft>& a2)
        {
            return compare_two_aircrafts(a1, a2);
        });

    aircrafts.erase(std::remove_if(aircrafts.begin(), aircrafts.end(),
        [this](std::unique_ptr<Aircraft>& a)
        {
            try 
            {
                return !(a->move());
            }
            catch (const AircraftCrash& err)
            {
                std::cerr << err.what() << std::endl;
                aircraft_crash++;
                return true;
            }
        }), aircrafts.end());
    return true;
}


int AircraftManager::count_aircraft_per_airline(const std::string& airline) const
{
    return std::count_if(aircrafts.begin(), aircrafts.end(),
        [&airline](const std::unique_ptr<Aircraft>& aircraft)
        {
            return aircraft->get_flight_num().compare(0, airline.size(), airline) == 0;
        });
}

bool AircraftManager::compare_two_aircrafts(std::unique_ptr<Aircraft>& a1, std::unique_ptr<Aircraft>& a2) const
{
    return std::make_tuple(!a1->has_terminal(), a1->get_fuel())
        < std::make_tuple(!a2->has_terminal(), a2->get_fuel());
}

int AircraftManager::get_required_fuel()
{
    return std::accumulate(aircrafts.begin(), aircrafts.end(), 0,
        [](int sum, std::unique_ptr<Aircraft>& a)
        {
            if (a->is_low_on_fuel() && !a->has_left_airport())
            {
                return sum + (INIT_MAX_FUEL - a->get_fuel());
            }
            return sum;
        });
}

void AircraftManager::count_crash() const
{
    std::cerr << aircraft_crash << " airplanes crashed into the ground" << std::endl;
}