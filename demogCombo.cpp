#include "demogCombo.h"
#include "demogData.h"
#include <sstream>
#include <string>
#include <assert.h>
#include <iomanip>

//add member functions here

/* print state data - as aggregate of all the county data */
std::ostream& operator<<(std::ostream &out, const demogCombo& ComboD) {
    out.setf(ios::fixed);
	out.setf(ios::showpoint);
	out.precision(2);
    out << "Combo Info: " << ComboD.printState();
    out << "\nNumber of Counties: " << ComboD.getaggTotalCounties();
    out << " " << "County Demographics Info: " << ComboD.getCounties();
    //consider re-writing with getters....
    out << "\nPopulation info: \n(over 65): " << ComboD.getaggpopOver65Percent() << "";
    out <<  "% and total: " << ComboD.getaggPopOver65();
    out << "\n(under 18): " << ComboD.getaggpopUnder18Percent();
    out <<  "% and total: " << ComboD.getaggPopUnder18();
    out << "\n(under 5): " << ComboD.getaggpopUnder5Percent();
    out <<  "% and total: " << ComboD.getaggPopUnder5();
    out << "\nEducation info: \n(Bachelor or more): " << ComboD.getaggBAupPercent();
    out <<  "% and total: " << ComboD.getaggPopDegree();
    out << "\n(high school or more): " << ComboD.getaggHSupPercent();
    out <<  "% and total: " << ComboD.getaggPopHS();
    out << "\npersons below poverty: " << ComboD.getaggPovertyPercent();
    out <<  "% and total: " << ComboD.getaggPopPoverty();
    out << "\nTotal population: " << ComboD.getaggPop();
    out << "\n" <<ComboD.getaggRaceCount(); 
    
    return out; 
}
