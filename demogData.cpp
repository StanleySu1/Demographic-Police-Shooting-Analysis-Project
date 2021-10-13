#include "demogData.h"
#include <sstream>
#include <iomanip>
#include "visitor.h"

/* print county demographic data */
std::ostream& operator<<(std::ostream &out, const demogData &DD) {
    out << "County Demographics Info: " << DD.getRegionName() << ", " << DD.getState();
    out << std::setprecision(2) << std::fixed;
    //fill in
    out << " total population: " << DD.getPop();
    //consider re-writing with getters....
    out << "\nPopulation info: \n(\% over 65): " << DD.getpopOver65Percent();
    out <<  " Count: " << DD.getpopOver65Count();
    out << "\n(\% under 18): " << DD.getpopUnder18Percent();
    out <<  " Count: " << DD.getpopUnder18Count();
    out << "\n(\% under 5): " << DD.getpopUnder5();
    out <<  " Count: " << DD.getpopUnder5Count();
    out << "\nEducation info: \n(\% Bachelor degree or more): " << DD.getBAup();
    out <<  " Count: " << DD.getBAupCount();
    out << "\n(\% high school or more): " << DD.getHSup();
    out <<  " Count: " << DD.getHSupCount();
    out << "\n(\% below poverty): " << DD.getBelowPoverty();
    out <<  " Count: " << DD.getBelowPovertyCount();
    return out;
}

void demogData:: accept(class Visitor &v){
    std::shared_ptr<demogData> p{shared_from_this()};
    v.visit(p);
}

