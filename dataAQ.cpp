/* aggregate data */
#include "dataAQ.h"
#include "demogData.h"
#include "psData.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include "visitorReport.h"
#include "visitor.h"

dataAQ::dataAQ() {}

string makeKeyExample(shared_ptr<demogData> theData) {


  string theKey = "Key";


  if (theData->getPovertyPercent() < 10) {
    theKey += "BelowPovLessTenPer";
  } else if (theData->getPovertyPercent() < 20) {
    theKey += "BelowPovLessTwentyPer";
  } else if (theData->getPovertyPercent() < 30) {
    theKey += "BelowPovLessThirtyPer";
  } else {
    theKey += "BelowPovAboveThirtyPer";
  }

  return theKey;
}

//swtich to a function parameter
void dataAQ::createComboDemogDataKey(std::vector<shared_ptr<demogData> >& theData) {
  //fill in
  for (const auto &obj : theData) {
    demogData &temp = *obj;
    string theKey = makeKeyExample(obj);
    //if the key hasn't been saved 
    if (allComboDemogData.find(theKey) == allComboDemogData.end())
    {
      allComboDemogData[theKey] = make_shared<demogCombo> (theKey, temp.getState());
    }
    //If the state has not been saved 
    if (!allComboDemogData[theKey]->checkState(temp.getState()))
    {
      allComboDemogData[theKey]->addState(temp.getState());
    }
    allComboDemogData[theKey]->addPopOver65(temp.getpopOver65Count());
    allComboDemogData[theKey]->addPopUnder18(temp.getpopUnder18Count());
    allComboDemogData[theKey]->addPopUnder5(temp.getpopUnder5Count());
    allComboDemogData[theKey]->addPopDegree(temp.getBAupCount());
    allComboDemogData[theKey]->addPopHS(temp.getHSupCount());
    allComboDemogData[theKey]->addPopPoverty(temp.getpopPovertyCount());
    allComboDemogData[theKey]->addPop(temp.getPop());
    allComboDemogData[theKey]->addCounties();
    allComboDemogData[theKey]->addRaceCount(temp.getRacialData());
  }

}

string makeKeyExample(shared_ptr<psData> theData) {
  
  string theKey = "Key";
  if (theData->getRace() == "W") {
    theKey += "WhiteVictim";
  } else if (theData->getRace() == "A") {
    theKey += "AsianVictim";
  } else if (theData->getRace() == "H") {
    theKey += "HispanicVictim";
  } else if (theData->getRace() == "N") {
    theKey += "NativeAmericanVictim";
  } else if (theData->getRace() == "B") {
    theKey += "AfricanAmericanVictim";
  } else if (theData->getRace() == "O") {
    theKey += "OtherRaceVictim";
  } else {
    theKey += "RaceUnspecifiedVictim";
  }
  return theKey;
}

void dataAQ::createComboPoliceDataKey(std::vector<shared_ptr<psData> >& theData) {
  //fill in
   
  for (const auto &obj : theData) {
    
    psData &temp = *obj;
    string theKey = makeKeyExample(obj);
    //if the key hasn't been saved 
    if (allComboPoliceData.find(theKey) == allComboPoliceData.end())
    {
      allComboPoliceData[theKey] = make_shared<psCombo> (theKey, temp.getState());
    }
    
    //If the state has not been saved 
    if (!allComboPoliceData[theKey]->checkState(temp.getState()))
    {
      
      allComboPoliceData[theKey]->addState(temp.getState());
    }
    //cout << "here1" << endl;
    //Plus 1 if mentally ill
    if (temp.getIllness())
    {
      //cout << "here" << endl;
      allComboPoliceData[theKey]->addNumMentalI();
      //cout << "here" << endl;
    }
     //cout << "here2" << endl;
    //Plus 1 if fleed 
    if (temp.getFlee() != "Not fleeing" && temp.getFlee() != "unknown" && temp.getFlee() != "")
    {
      allComboPoliceData[theKey]->addFleeingCount();
    }
    //Plus 1 if 65 or older 
    if (temp.getAge() >= 65)
    {
      allComboPoliceData[theKey]->addCasesOver65();
    }
    //Plus 1 if 18 or younger
    else if (temp.getAge() <= 18)
    {
      allComboPoliceData[theKey]->addCasesUnder18();
    }
    //Plus 1 for the race 
    allComboPoliceData[theKey]->addRacialData(temp.getRace());
    //if (temp.getState() == "MS")
    //{
      //cout << temp.getRace() << endl;
    //}
    //Plus 1 if male
    if (temp.getGender() == "M")
    {
      allComboPoliceData[theKey]->addnumMales();
    }
    //Plus 1 if female
    else if (temp.getGender() == "F")
    {
      allComboPoliceData[theKey]->addnumFemales();
    }
    
    //Plus 1 for the case 
    allComboPoliceData[theKey]->addNumberOfCases(); 
    //break; 
  
  }
}

/******************************************/
/* state examples */
void dataAQ::createComboDemogData(std::vector<shared_ptr<demogData> >& theData) {
  //fill in
  for (const auto &obj : theData) {
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
    allComboDemogData[temp.getState()]->addPopPoverty(temp.getpopPovertyCount());
    allComboDemogData[temp.getState()]->addPop(temp.getPop());
    allComboDemogData[temp.getState()]->addCounties();
    allComboDemogData[temp.getState()]->addRaceCount(temp.getRacialData());
    /*
    if (temp.getState() == "MS")
    {
      /*
      cout << "Pop: " << temp.getPop() << endl;
      cout << "Race: " << temp.getRacialData().getCommunityCount() << endl;
      *//*
      cout << "Pop: " << allComboDemogData[temp.getState()]->getaggPop() << endl;
      cout << "Race: " << allComboDemogData[temp.getState()]->getaggRaceCount().getCommunityCount() << endl;
    }
    */
  }
}

void dataAQ::createComboPoliceData(std::vector<shared_ptr<psData> >& theData) {
//fill in
  for (const auto &obj : theData) {
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
    //if (temp.getState() == "MS")
    //{
      //cout << temp.getRace() << endl;
    //}
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
    //break; 

  }
}

//return the name of the state with the largest population under age 5
string dataAQ::youngestPop() {
	//FILL in
  string stateYoungest = "";
  double percent = 0;
  for (auto entry : allComboDemogData) {
    demogCombo &state = *entry.second;
    if (percent < state.getpopUnder5Percent())
    {
      percent = state.getpopUnder5Percent();
      stateYoungest = state.getState(); 
    }
  } 
  return stateYoungest;  
} 

//return the name of the state with the largest population under age 18
string dataAQ::teenPop()  {
	//FILL in
  string stateTeen = "";
  double percent = 0;
  for (auto entry : allComboDemogData) {
    demogCombo &state = *entry.second;
    if (percent < state.getpopUnder18Percent())
    {
      percent = state.getpopUnder18Percent();
      stateTeen = state.getState(); 
    }
  }
  return stateTeen; 
}

//return the name of the state with the largest population over age 65
string dataAQ::wisePop()  {
	//FILL in
  string stateWise = "";
  double percent = 0;
  for (auto entry : allComboDemogData) {
    demogCombo &state = *entry.second;
    if (percent < state.getpopOver65Percent())
    {
      percent = state.getpopOver65Percent();
      stateWise = state.getState(); 
    }
  }
  return stateWise; 
}

//return the name of the state with the largest population who did not receive high school diploma
string dataAQ::underServeHS() {
	//FILL in
  //Subtract total population with population that did get hs diploma 
  string stateHS = "";
  double percent = 100;
  for (auto entry : allComboDemogData) {
    demogCombo &state = *entry.second;
    if (percent > (state.getHSupPercent()))
    {
      percent = state.getHSupPercent();
      stateHS = state.getState(); 
    }
  }
  //cout << stateHS << endl; 
  return stateHS; 
} 

//return the name of the state with the largest population who did receive bachelors degree and up
string dataAQ::collegeGrads() {
	//FILL in
  string stateGrad = "";
  double percent = 0;
  for (auto entry : allComboDemogData) {
    demogCombo &state = *entry.second;
    if (percent < state.getBAupPercent())
    {
      percent = state.getBAupPercent();
      stateGrad = state.getState(); 
    }
  }
  return stateGrad; 
}

//return the name of the state with the largest population below the poverty line
string dataAQ::belowPoverty() {
	//FILL in
  string statePov = "";
  double percent = 0;
  for (auto entry : allComboDemogData) {
    demogCombo &state = *entry.second;
    if (percent < state.getPovertyPercent())
    {
      percent = state.getPovertyPercent();
      statePov = state.getState(); 
    }
  }
  return statePov; 
} 

//Comparator function to use in sort()
bool sortByCount(const pair<string, double> &val1, const pair<string, double> &val2)
{
  return (val1.second > val2.second);
}

//sort and report the top ten states in terms of number of police shootings 
void dataAQ::reportTopTenStatesPS() {
  //fill in
  cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);
  vector<pair<string, int>> vecPS;
  map<string, shared_ptr<psCombo> > :: iterator it;
  for (it=allComboPoliceData.begin(); it != allComboPoliceData.end(); it++)
  {
    psCombo &state = *it->second;
    vecPS.push_back(make_pair(it->first, state.getNumberOfCases()));
  }
  sort(vecPS.begin(), vecPS.end(), sortByCount);
  cout << "Top ten states sorted on Police Shootings data & the associated data:" << endl;
  for (int i = 0; i < 10; i++)
  {
    cout << vecPS[i].first << endl;
    cout << "Total population: " << allComboDemogData[vecPS[i].first]->getaggPop() << endl;
    cout << "Police shooting incidents: " << allComboPoliceData[vecPS[i].first]->getNumberOfCases() << endl;
    cout << "Percent below poverty: " << allComboDemogData[vecPS[i].first]->getaggPovertyPercent() << endl;
  }
  cout << "**Full listings for top 3 Police Shootings data & the associated data for top 3:" << endl;
  for (int i = 0; i < 3; i++)
  {
    cout << *(shared_ptr<demogCombo>(allComboDemogData[vecPS[i].first])) << endl;
    cout << "**Police shooting incidents:"; 
    cout << *(shared_ptr<psCombo>(allComboPoliceData[vecPS[i].first])) << endl;
  }
}


    //sort and report the top ten states with largest population below poverty 
void dataAQ::reportTopTenStatesBP() {
  //fill in
  cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);
  vector<pair<string, double>> vecBP;
  map<string, shared_ptr<demogCombo> > :: iterator it;
  for (it=allComboDemogData.begin(); it != allComboDemogData.end(); it++)
  {
    demogCombo &state = *it->second;
    vecBP.push_back(make_pair(it->first, state.getaggPovertyPercent()));
  }
  sort(vecBP.begin(), vecBP.end(), sortByCount);
  
  cout << "Top ten states sorted on Below Poverty data & the associated police shooting data:" << endl;
  for (int i = 0; i < 10; i++)
  {
    cout << vecBP[i].first << endl;
    cout << "Total population: " << allComboDemogData[vecBP[i].first]->getaggPop() << endl;
    cout << "Percent below poverty: " << allComboDemogData[vecBP[i].first]->getaggPovertyPercent() << endl;
    cout << "Police shooting incidents: " << allComboPoliceData[vecBP[i].first]->getNumberOfCases() << endl;
  }
  
  cout << "**Full listings for top 3 Below Poverty data & the associated police shooting data for top 3:" << endl;
  for (int i = 0; i < 3; i++)
  {
    cout << *(shared_ptr<demogCombo>(allComboDemogData[vecBP[i].first])) << endl;
    cout << "**Police shooting incidents:"; 
    cout << *(shared_ptr<psCombo>(allComboPoliceData[vecBP[i].first])) << endl;
  }
}

/* print all combo data */
std::ostream& operator<<(std::ostream &out, const dataAQ &theAnswers) {
  out << "Combo Demographic Info: ";
  for (auto const& entry : theAnswers.allComboDemogData) {
      out << "key: " << entry.first << endl;
      out << *(entry.second) << "\n";

  }

  for (auto const& entry : theAnswers.allComboPoliceData) {
      out << "key: " << entry.first << endl;
      out << *(entry.second) << "\n";

  }
  return out;
}
//Prints a report of the data for any state that meets a given criteria 
void dataAQ::comboReport(double thresh) {
  std::vector<shared_ptr<regionData>> pileData;
  visitorReport report;
  map<string, shared_ptr<demogCombo> > :: iterator it;
  //cout << "here" << endl;
  for (it=allComboDemogData.begin(); it != allComboDemogData.end(); it++)
  {
    //cout << "here" << endl;
    demogCombo &state = *it->second;
    //cout << state.getaggHSupPercent() << endl; 
    if (state.getaggHSupPercent() > thresh)
    {
      pileData.push_back(it->second);
      pileData.push_back(allComboPoliceData[it->first]);
    }
  }
  for (const auto &obj : pileData) {
    obj->accept(report);
  }
}