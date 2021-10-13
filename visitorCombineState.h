#ifndef VCOMBOS_H
#define VCOMBOS_H


#include "visitorCombine.h"
#include <memory>


class visitorCombineState : public visitorCombine{
public:
    visitorCombineState() {}

	void visit(shared_ptr<demogData> obj) {
        //fill in
        //cout << "here" << endl; 
        demogData &temp = *obj;
        //if the state hasn't been saved 
        if (allComboDemogData.find(temp.getState()) == allComboDemogData.end())
        {
            string region = "";
            allComboDemogData[temp.getState()] = make_shared<demogCombo> (region, temp.getState());
        }
        allComboDemogData[temp.getState()]->addPopOver65(temp.getpopOver65Count());
        allComboDemogData[temp.getState()]->addPopUnder18(temp.getpopUnder18Count());
        allComboDemogData[temp.getState()]->addPopUnder5(temp.getpopUnder5Count());
        allComboDemogData[temp.getState()]->addPopDegree(temp.getBAupCount());
        allComboDemogData[temp.getState()]->addPopHS(temp.getHSupCount());
        allComboDemogData[temp.getState()]->addPopPoverty(temp.getBelowPovertyCount());
        allComboDemogData[temp.getState()]->addPop(temp.getPopD());
        //cout << temp.getPopD() << endl; 
        /*
        if (temp.getState() == "MS")
        {
            //cout << "pop" << temp.getPop() << endl; 
            //cout << "mon" << allComboDemogData[temp.getState()]->getHSupCount() << endl; 
            //cout << allComboDemogData[temp.getState()]->getPop() << endl; 
            cout << allComboDemogData[temp.getState()]->getpopUnder18Count()  << endl; 
            cout <<  allComboDemogData[temp.getState()]->getPopD() << endl; 
            cout << allComboDemogData[temp.getState()]->getpopUnder18Percent() << endl; 
        }
        */
        allComboDemogData[temp.getState()]->addCounties();
        allComboDemogData[temp.getState()]->addRaceCount(temp.getCommunityRaceMix());
    }
    
    void visit(shared_ptr<psData> obj) {
        //fill in
        psData &temp = *obj;
        //if the state hasn't been saved 
        if (allComboPoliceData.find(temp.getState()) == allComboPoliceData.end())
        {
            string region = "";
            allComboPoliceData[temp.getState()] = make_shared<psCombo> (region, temp.getState());
        }
        //Plus 1 if mentally ill
        if (temp.getIllness())
        {
        allComboPoliceData[temp.getState()]->addNumMentalI();
        }
        //Plus 1 if fleed 
        if (temp.getFlee() != "Not fleeing" && temp.getFlee() != "unknown" && temp.getFlee() != "")
        {
            allComboPoliceData[temp.getState()]->addFleeingCount();
        }
        //Plus 1 if 65 or older 
        if (temp.getAge() >= 65)
        {
            allComboPoliceData[temp.getState()]->addCasesOver65();
        }
        //Plus 1 if 18 or younger
        else if (temp.getAge() <= 18)
        {
            allComboPoliceData[temp.getState()]->addCasesUnder18();
        }
        //Plus 1 for the race 
        allComboPoliceData[temp.getState()]->addRacialData(temp.getRace());
        
        //Plus 1 if male
        if (temp.getGender() == "M")
        {
            allComboPoliceData[temp.getState()]->addnumMales();
        }
        //Plus 1 if female
        else if (temp.getGender() == "F")
        {
            allComboPoliceData[temp.getState()]->addnumFemales();
        }
        
        //Plus 1 for the case 
        allComboPoliceData[temp.getState()]->addNumberOfCases(); 
        /*
        if (temp.getState() == "MS")
        {
            cout << "1." << allComboPoliceData[temp.getState()]->getNumberOfCases() << endl; 
        }
        */
        //cout << "1." << allComboPoliceData[temp.getState()]->getNumberOfCases() << endl; 
    }
    void visit(shared_ptr<psCombo> obj) {}
    private:
       //inherited
};

#endif
