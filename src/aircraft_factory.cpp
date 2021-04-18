#include "aircraft_factory.hpp"

#include <cassert>
#include <memory>
#include <random>

bool AircraftFactory::is_flight_registered(std::string& number) const
{
    return registered_flights.find(number) != registered_flights.end();
}

std::string AircraftFactory::generate_random_unique_flight_number()
{
    std::string flight_number;
    do {
        flight_number = airlines[std::rand() % 8] + std::to_string(1000 + (rand() % 9000));
    } while (is_flight_registered(flight_number));

    registered_flights.emplace(flight_number);
    return flight_number;
}

void AircraftFactory::init_aircraft_types()
{
    aircraft_types[0] = new AircraftType { .02f, .05f, .02f, MediaPath { "l1011_48px.png" } };
    aircraft_types[1] = new AircraftType { .02f, .05f, .02f, MediaPath { "b707_jat.png" } };
    aircraft_types[2] = new AircraftType { .02f, .08f, .04f, MediaPath { "concorde_af.png" } };
}

std::unique_ptr<Aircraft> AircraftFactory::create_aircraft(const AircraftType& type, Airport* airport)
{
    assert(airport && "airport is null in AircraftFactory::create_aircraft");

    const std::string flight_number = generate_random_unique_flight_number();
    const float angle       = (rand() % 1000) * 2 * 3.141592f / 1000.f; // random angle between 0 and 2pi
    const Point3D start     = Point3D { std::sin(angle), std::cos(angle), 0 } * 3 + Point3D { 0, 0, 2 };
    const Point3D direction = (-start).normalize();

    return std::make_unique<Aircraft>(type, flight_number, start, direction, airport->get_tower());
}

std::unique_ptr<Aircraft> AircraftFactory::create_random_aircraft(Airport* airport)
{
    assert(airport && "airport is null in AircraftFactory::create_random_aircraft");
    
    return create_aircraft(*(aircraft_types[rand() % 3]), airport);
}