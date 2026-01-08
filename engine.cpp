#include "engine.h"
#include <iostream>
#include <cmath>
#include <algorithm>

double MatchingEngine::dist2(double x1,double y1,double x2,double y2){
    return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
}

int MatchingEngine::registerDriver(const std::string& n,double x,double y){
    drivers.push_back({(int)drivers.size()+1,n,x,y,true,5.0,0});
    return drivers.size();
}

int MatchingEngine::registerPassenger(const std::string& n,double x,double y){
    passengers.push_back({(int)passengers.size()+1,n,x,y});
    return passengers.size();
}

int MatchingEngine::requestRide(int pid,double dx,double dy){
    auto& p = passengers[pid-1];
    rides.push_back({(int)rides.size()+1,pid,-1,p.x,p.y,dx,dy,RideState::REQUESTED});
    return rides.size();
}

bool MatchingEngine::assignDriver(int rid){
    Ride& r = rides[rid-1];
    if(r.state!=RideState::REQUESTED) return false;

    int best=-1; double bestD=1e18;
    for(int i=0;i<drivers.size();i++){
        if(drivers[i].available){
            double d=dist2(drivers[i].x,drivers[i].y,r.sx,r.sy);
            if(d<bestD){bestD=d;best=i;}
        }
    }
    if(best==-1) return false;

    drivers[best].available=false;
    r.driverId=drivers[best].id;
    r.state=RideState::ASSIGNED;
    std::cout<<"Driver "<<r.driverId<<" assigned\n";
    return true;
}

bool MatchingEngine::startRide(int rid){
    Ride& r = rides[rid-1];
    if(r.state!=RideState::ASSIGNED) return false;
    r.state=RideState::ONRIDE;
    return true;
}

void MatchingEngine::updateRating(Driver& d,double r){
    d.rating=(d.rating*d.ratingCount+r)/(d.ratingCount+1);
    d.ratingCount++;
}

bool MatchingEngine::completeRide(int rid,double duration){
    Ride& r = rides[rid-1];
    if(r.state!=RideState::ONRIDE) return false;

    double dist=std::sqrt(dist2(r.sx,r.sy,r.ex,r.ey));
    double fare=50+dist*10+duration;

    for(auto& d:drivers){
        if(d.id==r.driverId){
            d.available=true;
            double rating;
            std::cout<<"Rate driver (1-5): ";
            std::cin>>rating;
            updateRating(d,rating);
        }
    }
    r.state=RideState::COMPLETED;
    std::cout<<"Ride completed. Fare: "<<fare<<"\n";
    return true;
}

bool MatchingEngine::cancelRide(int rid){
    Ride& r = rides[rid-1];
    if(r.state==RideState::COMPLETED) return false;
    r.state=RideState::CANCELLED;
    std::cout<<"Ride cancelled\n";
    return true;
}

void MatchingEngine::showDrivers(){
    std::sort(drivers.begin(),drivers.end(),
        [](auto&a,auto&b){return a.rating>b.rating;});
    for(auto& d:drivers)
        std::cout<<d.id<<" | "<<d.name
                 <<" | Rating "<<d.rating
                 <<" | "<<(d.available?"available":"onride")<<"\n";
}
