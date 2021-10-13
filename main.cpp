#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "demogData.h"
#include "psData.h"
#include "parse.h"
#include "dataAQ.h"
#include "visitorReport.h"
#include "visitorCombineState.h"
#include "visitorCombineCounty.h"
#include "statTool.h"
using namespace std;

int main() {

    std::vector<shared_ptr<regionData>> pileOfData;
    //read police shooting data
    read_csv(pileOfData, "police_shootings_cleaned.csv", POLICE);
   
    //read in the demographic data
    read_csv(pileOfData, "county_demographics.csv", DEMOG); 
    //create a visitor to combine the state data
    visitorCombineState theStates;
    statTool::createStateData(pileOfData, theStates);
    theStates.printAllCombo(&demogData::getBelowPovertyCount, &psCombo::getNumberOfCases);

    //create a visitor to combine the county data
    visitorCombineCounty theCounties;
    statTool::createCountyData(pileOfData, theCounties);
    theCounties.printAllCombo(&demogData::getBelowPovertyCount, &psCombo::getNumberOfCases);

    statTool::computeStatsDemogRegionData(&theStates, &demogData::getHSup, 
    &demogData::getBelowPoverty,&demogData::getHSupCount, &demogData::getBelowPovertyCount);
    /*
    //Do stats work here
    cout << "State data Pop under 18 and below poverty: " << endl;
    statTool::computeStatsDemogRegionData(&theStates, &demogData::getpopUnder18Percent, 
    &demogData::getBelowPoverty,&demogData::getpopUnder18Count, &demogData::getBelowPovertyCount);

    cout << endl;
    cout << "County data Pop under 18 and below poverty: " << endl;
    statTool::computeStatsDemogRegionData(&theCounties, &demogData::getpopUnder18Percent, 
    &demogData::getBelowPoverty, &demogData::getpopUnder18Count, &demogData::getBelowPovertyCount);
    
    cout << endl;
    cout << "State data Pop below poverty and  HS up : " << endl;
    statTool::computeStatsDemogRegionData(&theStates, &demogData::getBelowPoverty, 
    &demogData::getHSup,&demogData::getBelowPovertyCount, &demogData::getHSupCount);
    cout << endl;
    cout << "County data Pop below poverty and  HS up : " << endl;
    statTool::computeStatsDemogRegionData(&theCounties, &demogData::getBelowPoverty, 
    &demogData::getHSup,&demogData::getBelowPovertyCount, &demogData::getHSupCount);
    cout << endl;
    statTool::computeStatsPSData(&theCounties, &psCombo::getNumMentalI, &psCombo::getWhiteNHNum);
    cout << endl; 
    statTool::computeStatsPSData(&theCounties, &psCombo::getNumMentalI, &psCombo::getBlackNum);
    cout << endl;
    statTool::computeStatsMixRegionData(&theCounties, &demogData::getPopD, &psCombo::getNumberOfCases);
    cout << endl;
    statTool::computeStatsMixRegionData(&theCounties, &demogData::getpopUnder18Count, &psCombo::getCasesUnder18);
    cout << endl;
    statTool::computeStatsRaceProportion(&theCounties, &raceDemogData::getWhiteNHCount, &raceDemogData::getWhiteNHCount);
    cout << endl;
    statTool::computeStatsRaceProportion(&theCounties, &raceDemogData::getBlackCount, &raceDemogData::getBlackCount);
    cout << endl; 
    statTool::computeStatsRaceProportion(&theStates, &raceDemogData::getWhiteNHCount, &raceDemogData::getWhiteNHCount);
    cout << endl;
    statTool::computeStatsRaceProportion(&theStates, &raceDemogData::getBlackCount, &raceDemogData::getBlackCount);
    cout << endl;
    statTool::computeStatsRaceProportion(&theStates, &raceDemogData::getLatinoCount, &raceDemogData::getLatinoCount);
    cout << endl;
    statTool::computeStatsRaceProportion(&theStates, &raceDemogData::getNativeCount, &raceDemogData::getNativeCount);
    cout << endl;
    statTool::computeStatsRaceProportion(&theStates, &raceDemogData::getAsianCount, &raceDemogData::getAsianCount);
    */
    return 0;
}

