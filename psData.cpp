#include <sstream>
#include "psData.h"
#include "visitor.h"

/* print police data - fill in*/
std::ostream& operator<<(std::ostream &out, const psData &PD) {
    out << "Police Shotting Info: " << PD.getState();
    out << "\nPerson name: " << PD.getName();
    out << "\nAge: " << PD.getAge();
    out << "\nGender: " << PD.getGender() ;
    out << "\nRace:" << PD.getRace();
    out << "\nMental Illness:" << PD.getIllness();
    out << "\nFleeing:" << PD.getFlee();
    return out;
}
void psData:: accept(class Visitor &v){
    std::shared_ptr<psData> p{shared_from_this()};
    v.visit(p);
}
