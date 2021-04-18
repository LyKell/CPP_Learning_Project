#pragma once

#include "geometry.hpp"

#include <stdexcept>
#include <string>

class AircraftCrash : public std::runtime_error
{
private:
    static std::string build_crash_message(const std::string& flight_number, Point3D& position, Point3D& speed, const std::string& crash_reason)
    {
        using namespace std::string_literals;

        std::string message;
        message += "Aircraft " + flight_number;
        message += " crashed at position " + position.to_string();
        message += " with a speed of " + speed.to_string();
        message += " because of " + crash_reason;

        return message;
    }

public:

    AircraftCrash(const std::string& flight_number, Point3D& position, Point3D& speed, const std::string& crash_reason) :
        std::runtime_error { build_crash_message(flight_number, position, speed, crash_reason) }
    {};
};