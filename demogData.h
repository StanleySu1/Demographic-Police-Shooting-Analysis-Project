#ifndef DEMOG_H
#define DEMOG_H

#include <string>
#include<iostream>
#include <math.h>
#include <memory>
#include "raceDemogData.h"
#include "regionData.h"

using namespace std;

/*
  class to represent county demographic data
  from CORGIS - LAB01 starter - replace with your FULL version!
*/
class Visitor;
class demogData : public regionData, public enable_shared_from_this <demogData> {
  public:
    demogData(string inN, string inS, int in65, int in18,
        int in5, int totPop14) :
            regionData{inN, inS, totPop14}, popOver65(in65), popUnder18(in18),
            popUnder5(in5), popDegree(-1), popHS(-1), popPoverty(-1) {}
    
    demogData(string inN, string inS, int in65, int in18,
        int in5, int inD, int inHS, int totPop14) :
            regionData{inN, inS, totPop14}, popOver65(in65), popUnder18(in18),
            popUnder5(in5),  popDegree(inD), popHS(inHS), popPoverty(-1) {}

    demogData(string inN, string inS, int in65, int in18,
        int in5, int inD, int inHS, int totPop14, int inPov) :
            regionData{inN, inS, totPop14}, popOver65(in65), popUnder18(in18),
            popUnder5(in5),  popDegree(inD), popHS(inHS), popPoverty(inPov) {} 

    demogData(string inN, string inS, int in65, int in18,
        int in5, int inD, int inHS, int totPop14, int inPov, raceDemogData inR) :
            regionData{inN, inS, totPop14}, popOver65(in65), popUnder18(in18),
            popUnder5(in5),  popDegree(inD), popHS(inHS), popPoverty(inPov), raceCount(inR) {}              

    int getpopOver65Count() const { return popOver65; }
    int getpopUnder18Count() const { return popUnder18; }
    int getpopUnder5Count() const { return popUnder5; }
    int getBAupCount() const { return popDegree; }
    int getHSupCount() const { return popHS; }
    int getBelowPovertyCount() const { return popPoverty; }
    int getTotalCountiesCount() const { return totalCounties; }
    string getCounties() const { return "comboData, many";  }
    int getPop() const { return pop;}
    int getWhiteNHNum() const {return raceCount.getWhiteNHCount();}

    //Use these methods to get percent
    double getpopOver65Percent() const { return ((double) popOver65/(double) pop)*100; }
    double getpopUnder18Percent() const { 
      //cout << "here" << endl; 
      return ((double) popUnder18/(double)pop)*100; 
    }
    double getpopUnder5() const { return ((double) popUnder5/ (double) pop)*100;}
    double getBAup() const { return ((double)popDegree/(double)pop)*100; }
    double getHSup() const { return ((double)popHS/(double)pop)*100; }
    double getBelowPoverty() const { return ((double)popPoverty/(double)pop)*100; }
    raceDemogData getCommunityRaceMix() const {return raceCount;}
    
    void addPopOver65(int pop65) {popOver65 += pop65;}
    void addPopUnder18(int pop18) {popUnder18 += pop18;}
    void addPopUnder5(int pop5) {popUnder5 += pop5;}
    void addPopDegree(int popBA) {popDegree += popBA;}
    void addPopHS(int popHigh) {popHS += popHigh;}
    void addPopPoverty(int popPov) {popPoverty += popPov;} 
    void addCounties() {totalCounties++;}
    void addPop(int pops) {pop += pops;}
    void addRaceCount(raceDemogData race) {
      raceCount.addNativeNoComCount(race.getNativeCount()); 
      raceCount.addAsianNoComCount(race.getAsianCount());
      raceCount.addBlackNoComCount(race.getBlackCount());
      raceCount.addLatinoNoComCount(race.getLatinoCount());
      raceCount.addHIPacificIsleNoComCount(race.getHIPacificIsleCount());
      raceCount.addMultiRaceNoComCount(race.getMultiRaceCount());
      raceCount.addWhiteNoComCount(race.getWhiteCount());
      raceCount.addWhiteNHNoComCount(race.getWhiteNHCount());
      raceCount.addOtherNoComCount(race.getOtherCount());
      raceCount.addCommunityCount(race.getCommunityCount());  
    }
    
    
    friend std::ostream& operator<<(std::ostream &out, const demogData &DD);
    void toString(ostream& os) const{};
    void accept(class Visitor &v) override;
    
private: //By Count
    //const string name;
    //const string state;
    //const double popOver65;
    //const double popUnder18;
    //const double popUnder5;
    //const int totalPopulation2014;
    //const double popDegree;
    //const double popHS; 
    //const double popPoverty;
    //const raceDemogData popRace;
    int popOver65;
    int popUnder18;
    int popUnder5;
    int popDegree;
    int popHS; 
    int popPoverty;
    int totalCounties; 
    int pop; 
    raceDemogData raceCount; 

};
#endif

