#ifndef POLICE_H
#define POLICE_H

#include <string>
#include <iostream>
#include <utility>
#include "regionData.h"
#include <memory>
using namespace std;

/*
  class to represent police shooting data
  from CORGIS
*/
class Visitor;
class psData : public regionData, public enable_shared_from_this <psData> {
  public:
    //add appropriate function paramaters to constructor once you add data
    psData(string inState, string inName, int inAge, string inGender, string inRace, 
        string inCounty, bool inIllness, string inFlee) :
            regionData{inCounty, inState}, name(inName), age(inAge), gender(inGender), race(inRace), illness(inIllness), flee(inFlee) {}


    //string getState() const { return state; }
    //add getters
    string getName() const { return name;}
    int getAge() const { return age;}
    string getGender() const { return gender;}
    string getRace() const { return race;}
    //string getCounty() const { return county;}
    bool getIllness() const { return illness;}
    string getFlee() const { return flee;}

    friend std::ostream& operator<<(std::ostream &out, const psData &PD);
    void toString(ostream& os) const{};
    void accept(class Visitor &v) override;
private:
    //const string state;
    //add others
    const string name;
    const int age;
    const string gender;
    const string race;
    //const string county;
    const bool illness;
    const string flee; //"Not fleeing" "unknown"

};

#endif
