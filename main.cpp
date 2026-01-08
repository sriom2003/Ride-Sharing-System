#include "engine.h"
#include <iostream>

int main(){
    MatchingEngine engine;
    int ch;
    while(true){
        std::cout<<"\n1.Driver 2.Passenger 3.Request 4.Start 5.Complete 6.Cancel 7.Show 8.Exit\n";
        std::cin>>ch;

        if(ch==1){std::string n;double x,y;std::cin>>n>>x>>y;engine.registerDriver(n,x,y);}
        else if(ch==2){std::string n;double x,y;std::cin>>n>>x>>y;engine.registerPassenger(n,x,y);}
        else if(ch==3){int p;double dx,dy;std::cin>>p>>dx>>dy;int r=engine.requestRide(p,dx,dy);engine.assignDriver(r);}
        else if(ch==4){int r;std::cin>>r;engine.startRide(r);}
        else if(ch==5){int r;double t;std::cin>>r>>t;engine.completeRide(r,t);}
        else if(ch==6){int r;std::cin>>r;engine.cancelRide(r);}
        else if(ch==7){engine.showDrivers();}
        else if(ch==8) break;
    }
}
