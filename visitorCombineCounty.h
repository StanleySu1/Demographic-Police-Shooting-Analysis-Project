#ifndef VCOMBOC_H
#define VCOMBOC_H

#include "psData.h"
#include "psCombo.h"
#include "demogData.h"
#include "demogCombo.h"
#include "visitorCombine.h"
#include "parse.h"
#include <memory>
#include <fstream>
#include <cassert>


class visitorCombineCounty : public visitorCombine {
public:
    visitorCombineCounty() {
    }

    //store demographic data by county name
	void visit(shared_ptr<demogData> obj) {
        //cout << "here" << endl;
        //fill in
        demogData &temp = *obj;
        string word = " County";
        string region = temp.getRegionName(); 
        if (region.find(word) != string::npos)
        {
            size_t p = -1;
  
            string tempWord = word + " ";
            while ((p = region.find(word)) != string::npos)
                region.replace(p, tempWord.length(), "");
            tempWord = " " + word;
            while ((p = region.find(word)) != string::npos)
                region.replace(p, tempWord.length(), "");
        }
        region = region + temp.getState();
        //cout << region << endl;
        allComboDemogData[region] = make_shared<demogCombo> (region, temp.getState());
        allComboDemogData[region]->addPopOver65(temp.getpopOver65Count());
        allComboDemogData[region]->addPopUnder18(temp.getpopUnder18Count());
        allComboDemogData[region]->addPopUnder5(temp.getpopUnder5Count());
        allComboDemogData[region]->addPopDegree(temp.getBAupCount());
        allComboDemogData[region]->addPopHS(temp.getHSupCount());
        allComboDemogData[region]->addPopPoverty(temp.getBelowPovertyCount());
        allComboDemogData[region]->addPop(temp.getPopD());
        allComboDemogData[region]->addCounties();
        allComboDemogData[region]->addRaceCount(temp.getCommunityRaceMix());
    }
    
    //aggregate police shooting data by county
    void visit(shared_ptr<psData> obj) {
        //fill in
        psData &temp = *obj;
        string word = " County";
        string region = temp.getRegionName(); 
        if (region.find(word) != string::npos)
        {
            size_t p = -1;
  
            string tempWord = word + " ";
            while ((p = region.find(word)) != string::npos)
                region.replace(p, tempWord.length(), "");
            tempWord = " " + word;
            while ((p = region.find(word)) != string::npos)
                region.replace(p, tempWord.length(), "");
        }
        region = region + temp.getState();
        //cout << region << endl;
        if (allComboPoliceData.find(region) == allComboPoliceData.end())
        {
            allComboPoliceData[region] = make_shared<psCombo> (region, temp.getState());
        }
        //Plus 1 if mentally ill
        if (temp.getIllness())
        {
        allComboPoliceData[region]->addNumMentalI();
        }
     
        //Plus 1 if fleed 
        if (temp.getFlee() != "Not fleeing" && temp.getFlee() != "unknown" && temp.getFlee() != "")
        {
            allComboPoliceData[region]->addFleeingCount();
        }
        //Plus 1 if 65 or older 
        if (temp.getAge() >= 65)
        {
            allComboPoliceData[region]->addCasesOver65();
        }
        //Plus 1 if 18 or younger
        else if (temp.getAge() <= 18)
        {
            allComboPoliceData[region]->addCasesUnder18();
        }
        //Plus 1 for the race 
        allComboPoliceData[region]->addRacialData(temp.getRace());
        //if (temp.getState() == "MS")
        //{
            //cout << temp.getRace() << endl;
        //}
        //Plus 1 if male
        if (temp.getGender() == "M")
        {
            allComboPoliceData[region]->addnumMales();
        }
        //Plus 1 if female
        else if (temp.getGender() == "F")
        {
            allComboPoliceData[region]->addnumFemales();
        }
    
        //Plus 1 for the case 
        allComboPoliceData[region]->addNumberOfCases(); 
    }
    void visit(shared_ptr<psCombo> obj) {}
    private:
        //only inherited data at this point
};

#endif
