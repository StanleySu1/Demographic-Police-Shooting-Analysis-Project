/* helper routines to read out csv data */
#include "parse.h"
#include <algorithm>
#include <cmath>

/* helper to strip out quotes from a string */
string stripQuotes(std::string temp) {
    temp.erase(
        remove(temp.begin(), temp.end(), '\"' ),
        temp.end());
    return temp;
}

/* helper: get field from string stream */
/* assume field has quotes for CORGIS */
string getField(std::stringstream &ss) {
    string data, junk;
    //ignore the first quotes
    std::getline(ss, junk, '\"');
    //read the data (not to comma as some data includes comma (Hospital names))
    std::getline(ss, data, '\"');
    //read to comma final comma (to consume and prep for next)
    std::getline(ss, junk, ',');
    //data includes final quote (see note line 18)
    return stripQuotes(data);
}

string getFieldNQ(std::stringstream &ss)
{
    string temp;
    std::getline(ss, temp, ',');
    //std::cout << temp << std:: endl;
    return temp;
}

/* helper: read out column names for CSV file */
void consumeColumnNames(std::ifstream &myFile) {
    std::string line;
    std::string colname;

    // Extract the first line in the file
    std::getline(myFile, line);

    // Create a stringstream from line
    std::stringstream ss(line);

    // Read the column names (for debugging)
    // Extract each column name for debugging
    while(std::getline(ss, colname, ',')) {
    //    std::cout << colname << std::endl;
    }
}

/* Read one line from a CSV file for county demographic data specifically */
shared_ptr<demogData> readCSVLineDemog(std::string theLine) {
    std::stringstream ss(theLine);
    
    string name = getField(ss);
    string state = getField(ss);
    //turn into mathematical percent
    double popOver65Percent = stod(getField(ss))/100.0;
    double popUnder18Percent = stod(getField(ss))/100.0;
    double popUnder5Percent = stod(getField(ss))/100.0;
    double bachelorDegreeUpPercent = stod(getField(ss))/100.0;
    double highSchoolUpPercent = stod(getField(ss))/100.0;

    //now skip over some data
    for (int i=0; i < 4; i++)
        getField(ss);

    //store initial data as percent (then convert to count)
    double NativePercent= stod(getField(ss))/100.0;
    double AsianPercent= stod(getField(ss))/100.0;
    double BlackPercent= stod(getField(ss))/100.0;
    double LatinoPercent= stod(getField(ss))/100.0;
    double HIPacificIslePercent= stod(getField(ss))/100.0;
    double MultiRacePercent= stod(getField(ss))/100.0;
    double WhitePercent= stod(getField(ss))/100.0;
    double WhiteNHPercent = stod(getField(ss))/100.0;
    //cout << NativePercent << endl; 
    //now skip over some data 
    for (int i=0; i < 6; i++)
        getField(ss);

    int medHouseIncome = stoi(getField(ss)); //dont use
    //skip per capita
    getField(ss);
    double belowPovertyPercent = stod(getField(ss))/100.0;

    //now skip over some data 
    for (int i=0; i < 10; i++)
        getField(ss);

    int totalPop2014 = stoi(getField(ss));

    //Convert percent to count 
    int popOver65 = round(popOver65Percent*totalPop2014);
    int popUnder18 = round(popUnder18Percent*totalPop2014);
    int popUnder5 = round(popUnder5Percent*totalPop2014);
    int bachelorDegreeUp = round(bachelorDegreeUpPercent*totalPop2014);
    int highSchoolUp = round(highSchoolUpPercent*totalPop2014);
    int belowPoverty = round(belowPovertyPercent*totalPop2014);
    int Native = round(NativePercent*totalPop2014);
    int Asian = round(AsianPercent*totalPop2014);
    int Black = round(BlackPercent*totalPop2014);
    int Latino = round(LatinoPercent*totalPop2014);
    int HIPacificIsle = round(HIPacificIslePercent*totalPop2014);
    int MultiRace = round(MultiRacePercent*totalPop2014);
    int White = round(WhitePercent*totalPop2014);
    int WhiteNH = round(WhiteNHPercent*totalPop2014);
    //cout << "1." << round(NativePercent*totalPop2014) << endl; 
    //cout << "2." << Native << endl; 
    //Store race count in raceDemogData object 
    raceDemogData popRace(Native, Asian, Black, Latino, HIPacificIsle, MultiRace, White, WhiteNH, totalPop2014);

    //update as needed this is lab3 version
    return make_shared<demogData>(name, state, popOver65, popUnder18,
            popUnder5, bachelorDegreeUp, highSchoolUp, totalPop2014, belowPoverty, popRace);
}

//read one line of police data
shared_ptr<psData> readCSVLinePolice(std::string theLine) {
    std::stringstream ss(theLine);
    
    getFieldNQ(ss); //ignore id
    string name = getFieldNQ(ss);
    for(int i = 0; i < 3; i++){
        getFieldNQ(ss);
    }
    int age = 0;
    string tmp = getFieldNQ(ss);
    if(tmp != ""){
        age = stoi(tmp);
    }
    else{
        age = -1;
    }
    string gender = getFieldNQ(ss);
    string race = getFieldNQ(ss);
    string county = getFieldNQ(ss);
    string state = getFieldNQ(ss);
    //finish reading other data fields and initialize police data
    //convert string to bool 
    tmp = getFieldNQ(ss);
    bool illness;
    transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
    istringstream is(tmp);
    is >> boolalpha >> illness;
    getFieldNQ(ss); //ignore Threat_level
    string flee = getFieldNQ(ss);
    return make_shared<psData>(state, name, age, gender, race, county, illness, flee);
}


//read from a CSV file (for a given data type) return a vector of the data
// DO NOT modify 
std::vector<shared_ptr<regionData>> read_csv(std::string filename, typeFlag fileType) {
    //the actual data
    std::vector<shared_ptr<regionData>> theData;

    // Create an input filestream
    std::ifstream myFile(filename);

    // Make sure the file is open
    if(!myFile.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    if(myFile.good()) {
        consumeColumnNames(myFile);

        // Helper vars
        std::string line;

        // Now read data, line by line and create demographic dataobject
        while(std::getline(myFile, line)) {
            if (fileType == DEMOG) {
                theData.push_back(readCSVLineDemog(line));
            } 
            else if (fileType == POLICE) {
                theData.push_back(readCSVLinePolice(line));
            }
            else {
                cout << "ERROR - unknown file type" << endl;
                exit(0);
            }
        }

        // Close file
        myFile.close();
    }

    return theData;
}
void read_csv(std::vector<shared_ptr<regionData>>& pileOfData, std::string filename, typeFlag fileType) {
    //the actual data
    //std::vector<shared_ptr<regionData>> theData;

    // Create an input filestream
    std::ifstream myFile(filename);

    // Make sure the file is open
    if(!myFile.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    if(myFile.good()) {
        consumeColumnNames(myFile);

        // Helper vars
        std::string line;

        // Now read data, line by line and create demographic dataobject
        while(std::getline(myFile, line)) {
            if (fileType == DEMOG) {
                pileOfData.push_back(readCSVLineDemog(line));
            } 
            else if (fileType == POLICE) {
                pileOfData.push_back(readCSVLinePolice(line));
            }
            else {
                cout << "ERROR - unknown file type" << endl;
                exit(0);
            }
        }

        // Close file
        myFile.close();
    }
}

/*
// Reads a CSV file 
std::vector<shared_ptr<psData>> read_csvPolice(std::string filename, typeFlag fileType) {
    //the actual data
    std::vector<shared_ptr<psData> > theData;

    // Create an input filestream
    std::ifstream myFile(filename);

    // Make sure the file is open
    if(!myFile.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    if(myFile.good()) {
        consumeColumnNames(myFile);

        // Helper vars
        std::string line;

        // Now read data, line by line and create a county info object
        while(std::getline(myFile, line)) {
            if (fileType == POLICE) {
                theData.push_back(readCSVLinePolice(line));
            } else {
                cout << "ERROR - unknown file type" << endl;
                exit(0);
            }
            
        }

        // Close file
        myFile.close();
    }

    return theData;
}
*/

