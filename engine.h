#pragma once
#include <string>
#include <vector>

enum class RideState {
    REQUESTED,
    ASSIGNED,
    ONRIDE,
    COMPLETED,
    CANCELLED
};

struct Driver {
    int id;
    std::string name;
    double x, y;
    bool available;
    double rating;
    int ratingCount;
};

struct Passenger {
    int id;
    std::string name;
    double x, y;
};

struct Ride {
    int id;
    int passengerId;
    int driverId;
    double sx, sy, ex, ey;
    RideState state;
};

class MatchingEngine {
public:
    int registerDriver(const std::string&, double, double);
    int registerPassenger(const std::string&, double, double);

    int requestRide(int passengerId, double dx, double dy);
    bool assignDriver(int rideId);
    bool startRide(int rideId);
    bool completeRide(int rideId, double duration);
    bool cancelRide(int rideId);

    void showDrivers();

private:
    std::vector<Driver> drivers;
    std::vector<Passenger> passengers;
    std::vector<Ride> rides;

    double dist2(double, double, double, double);
    void updateRating(Driver&, double);
};
