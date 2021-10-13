#ifndef COMBODEMOG_H
#define COMBODEMOG_H

#include <memory>
#include <string>
#include <iostream>
#include "demogData.h"
#include "raceDemogData.h"

/*
  class to represent combined demographic data 
*/
class demogCombo : public demogData {
  public:
        //write demogCombo constructor
    demogCombo(string inN, string inS) :
            aggPopOver65(0), aggPopUnder18(0), aggPopUnder5(0), aggPopDegree(0), 
            aggPopHS(0), aggPopPoverty(0), aggTotalCounties(0), aggPop(0),
            demogData{inN, inS, 0, 0, 0, 0, 0, 0, 0}{}


    //fill in
    int getaggPopOver65() const { return aggPopOver65;}
    int getaggPopUnder18() const { return aggPopUnder18;}
    int getaggPopUnder5() const { return aggPopUnder5;}
    int getaggPopDegree() const { return aggPopDegree;}
    int getaggPopHS() const { return aggPopHS;}
    int getaggPopPoverty() const { return aggPopPoverty;}
    int getaggTotalCounties() const { return aggTotalCounties;}
    int getaggPop() const { return aggPop;}
    
    raceDemogData getaggRaceCount() const { return aggRaceCount;}

    double getaggpopOver65Percent() const { return ((double) aggPopOver65/(double) aggPop)*100; }
    double getaggpopUnder18Percent() const { return ((double) aggPopUnder18/(double)aggPop)*100; }
    double getaggpopUnder5Percent() const { return ((double) aggPopUnder5/ (double) aggPop)*100;}
    double getaggBAupPercent() const { return ((double)aggPopDegree/(double)aggPop)*100; }
    double getaggHSupPercent() const { return ((double)aggPopHS/(double)aggPop)*100; }
    double getaggPovertyPercent() const { return ((double)aggPopPoverty/(double)aggPop)*100; }
    
    void setpopOver65(double pop65) {aggPopOver65 = pop65; }
    void setpopUnder18(double pop18) {aggPopUnder18 = pop18; }
    void setpopUnder5(double pop5) {aggPopUnder5 = pop5; }
    void setBAup(double popBA) {aggPopDegree = popBA; }
    void setHSup(double popHigh) {aggPopHS = popHigh; }
    void setpopPoverty(double popPov) {aggPopPoverty = popPov; }
    void setTotalCounties(double popCon) {aggTotalCounties = popCon; }
    void setRacialData(raceDemogData race) {
      aggRaceCount.addNativeNoComCount(race.getNativeCount()); 
      aggRaceCount.addAsianNoComCount(race.getAsianCount());
      aggRaceCount.addBlackNoComCount(race.getBlackCount());
      aggRaceCount.addLatinoNoComCount(race.getLatinoCount());
      aggRaceCount.addHIPacificIsleNoComCount(race.getHIPacificIsleCount());
      aggRaceCount.addMultiRaceNoComCount(race.getMultiRaceCount());
      aggRaceCount.addWhiteNoComCount(race.getWhiteCount());
      aggRaceCount.addWhiteNHNoComCount(race.getWhiteNHCount());
      aggRaceCount.addOtherNoComCount(race.getOtherCount());
      aggRaceCount.addCommunityCount(race.getCommunityCount());  
    }

    friend std::ostream& operator<<(std::ostream &out, const demogCombo &SD);

  private:
    //fill in counts 
    int aggPopOver65;
    int aggPopUnder18;
    int aggPopUnder5;
    int aggPopDegree;
    int aggPopHS;
    int aggPopPoverty; 
    int aggTotalCounties;
    int aggPop; 
    raceDemogData aggRaceCount;  

};
#endif
