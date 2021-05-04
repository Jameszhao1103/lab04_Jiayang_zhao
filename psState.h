#ifndef POLICESTATEDATA_H
#define POLICESTATEDATA_H

#include "raceDemogData.h"
#include "psData.h"

using namespace std;

class psState {
public:
    psState(string inS, int inM, int inF, int inO, int inU, raceDemogData inR, int inMale, int inFemale, int intotal) : 
        state(inS), mentalill(inM), fleeing(inF), over65(inO), under18(inU), racialData(inR), male(inMale), female(inFemale), totalnum(intotal){} //add
    
    //complete these
    int getNumMentalI() const { return mentalill; }
    int getFleeingCount() const { return fleeing; }
    int getCasesOver65() const { return over65; }
    int getCasesUnder18() const { return under18; }
    raceDemogData getRacialData() const { return racialData; }
    int getnumMales() const { return male;  }
    int getnumFemales() const { return female; }
    int getNumberOfCases() const { return totalnum; }
    string getState() const {return state; } 

    //add any others needed

    friend std::ostream& operator<<(std::ostream &out, const psState& PD);



protected:
    const string state;
    const int mentalill;
    const int fleeing;
    const int over65;
    const int under18;
    const raceDemogData racialData;
    const int male;
    const int female;
    const int totalnum;
    
};

#endif