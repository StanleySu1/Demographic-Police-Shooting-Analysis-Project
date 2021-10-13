#ifndef POLICECOMBODATA_H
#define POLICECOMBODATA_H

#include "raceDemogData.h"
#include "psData.h"
#include "regionData.h"
#include <memory>
#include <cassert>

using namespace std;

class Visitor;
class psCombo : public regionData, public enable_shared_from_this <psCombo>  {
public:
    //write psCombo constructor
    psCombo(string inN, string inS) :
            regionData{inN, inS}, numMentalI(0), fleeingCount(0), casesOver65(0), casesUnder18(0), 
            numMales(0), numFemales(0), numberOfCases(0) {} //add
    //complete these
    int getNumMentalI() const {return numMentalI;}
    int getFleeingCount() const {return fleeingCount;}
    int getCasesOver65() const {return casesOver65;}
    int getCases19to64() const {return numberOfCases-casesOver65-casesUnder18;}
    int getCasesUnder18() const {return casesUnder18;}
    raceDemogData getRacialData() const {return raceCount;}
    int getnumMales() const {return numMales;}
    int getnumFemales() const {return numFemales;}
    int getNumberOfCases() const {return numberOfCases;}
    int getWhiteNHNum() const {return raceCount.getWhiteNHCount();}
    int getBlackNum() const {return raceCount.getBlackCount();}
    //string getState() const {return state; } 

    double getMentalIPercent() const  { return 100.0f*(double)(numMentalI)/numberOfCases; }
    double getOver65Percent() const  { return 100.0f*(double)(casesOver65)/numberOfCases; }
    double get19to64Percent() const  { return 100.0f*(double)(numberOfCases-casesOver65-casesUnder18)/numberOfCases; }
    double getUnder18Percent() const  { return 100.0f*(double)(casesUnder18)/numberOfCases; }
    double getFleeingPercent() const  { return 100.0f*(double)(fleeingCount)/numberOfCases; }
    double getWhiteNHPer() const {return raceCount.getWhiteNHPercent();}

    //add any others needed
    void addNumMentalI() {numMentalI++;}
    void addFleeingCount() {fleeingCount++;}
    void addCasesOver65() {casesOver65++;}
    void addCasesUnder18() {casesUnder18++;}
    void addRacialData(string race) {
        if ("N" == race){raceCount.addNativeCount(1);}
        else if ("A" == race){raceCount.addAsianCount(1);} 
        else if ("B" == race){raceCount.addBlackCount(1);}
        else if ("H" == race){raceCount.addLatinoCount(1);}
        //else if ("Pacific Islander" == race){raceCount.addHIPacificIsleCount(1);}
        //else if ("Multi" == race){raceCount.addMultiRaceCount(1);}
        else if ("W" == race){raceCount.addWhiteCount(1); raceCount.addWhiteNHNoComCount(1);}
        else if ("" == race){raceCount.addOtherCount(1);}  
        //else if ("Unknown" == race){raceCount.addOtherCount(1);} 
    }
    void addnumMales() {numMales++;}
    void addnumFemales() {numFemales++;}
    void addNumberOfCases() {numberOfCases++;}

    friend std::ostream& operator<<(std::ostream &out, const psCombo& PD);
    void toString(ostream& os) const{};
    void accept(class Visitor &v) override;
    
protected:
    //fill in
    //const string state;
    //add others
    int numMentalI;
    int fleeingCount;
    int casesOver65;
    int casesUnder18;
    raceDemogData raceCount;
    int numMales;
    int numFemales;
    int numberOfCases;  
};

#endif