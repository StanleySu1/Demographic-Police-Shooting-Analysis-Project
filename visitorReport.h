#ifndef VISITREP_H
#define VISITREP_H

#include "psData.h"
#include "demogData.h"
#include "visitor.h"

class visitorReport : public Visitor {
    //FILL IN
    public:
        visitorReport() : numVisited(0) {}
        void visit(demogData *data){
            demogCombo* temp = dynamic_cast<demogCombo*>(data); 
            cout.setf(ios::fixed);
	        cout.setf(ios::showpoint);
	        cout.precision(2);
            cout << "print summary demog Data:";
            cout << "\nRegion info: comboData, "<< temp->getState(); 
            cout << "\nEducation info:\n(Bachelor or more): " << temp->getaggBAupPercent();
            cout <<  "% and total: " << temp->getaggPopDegree();
            cout << "\n(high school or more): " << temp->getaggHSupPercent();
            cout <<  "% and total: " << temp->getaggPopHS();
            cout << "\nTotal population: " << temp->getaggPop();
            cout << "\n" <<temp->getaggRaceCount()<< endl;
        }
        void visit(psData *data){
            cout << "print aggregate police shooting data"; 
            cout << "\nState Info: " << data->printState();
        }
        
    private:
    	int numVisited;
};

#endif