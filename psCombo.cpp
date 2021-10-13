#include <iomanip>
#include "psCombo.h"
#include "visitor.h"



/* print state data - as aggregate of all incidents in this state */
std::ostream& operator<<(std::ostream &out, const psCombo& PD) {
    out << "State Info: " << PD.printState();
    out << "\nNumber of incidents: " << PD.getNumberOfCases();
    out << std::setprecision(2) << std::fixed;
    //fill in
    out << "\nIncidents with age \n(over 65): " << PD.getCasesOver65() << " %: " << PD.getOver65Percent();
    out << "\n(19 to 64): " << PD.getCases19to64() << " %: " << PD.get19to64Percent();
    out << "\n(under 18): " << PD.getCasesUnder18()<< " %: " << PD.getUnder18Percent();
    out << "\nIncidents involving fleeing: " << PD.getFleeingCount()<< " %: " << PD.getFleeingPercent();
    out << "\nIncidents involving mental illness: " << PD.getNumMentalI()<< " %: " << PD.getMentalIPercent();
    out << "\nMale incidents: " << PD.getnumMales() <<  " female incidents: " << PD.getnumFemales();
    out << "\nRacial demographics of state incidents: "; 
    out << PD.getRacialData();
    return out;
}

void psCombo:: accept(class Visitor &v){
    std::shared_ptr<psCombo> p{shared_from_this()};
    v.visit(p);
}

