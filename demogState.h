#ifndef STATE_H
#define STATE_H

#include <memory>
#include <string>
#include <iostream>
#include "demogData.h"

/*
  class to represent state data - fairly redundent at this point but will use
  inheritence later - FILL IN
*/
class demogState {
  public:
   //FILL IN
   demogState(string state, int num, double in65, double in18, double in5, double inBA, double inHS, double inPoor,
    int Total):
      statename(state),
      number(num), popOver65Count(in65), popUnder18Count(in18), popUnder5Count(in5), 
      popBACount(inBA), popHSCount(inHS), popPoorCount(inPoor), stateRace(), totalPopulation2014(Total) {}

    demogState(string state, int num, double in65, double in18, double in5, double inBA, double inHS, double inPoor, raceDemogData inRace,
    int Total):
      statename(state),
      number(num), popOver65Count(in65), popUnder18Count(in18), popUnder5Count(in5), 
      popBACount(inBA), popHSCount(inHS), popPoorCount(inPoor), stateRace(inRace), totalPopulation2014(Total) {}

   string getState() const { return statename; }
   int    getNumber() const { return number; }
   double getpopOver65() const { return popOver65Count * 100 / totalPopulation2014; }
   double getpopUnder18() const { return popUnder18Count * 100 / totalPopulation2014; }
   double getpopUnder5() const { return popUnder5Count * 100 / totalPopulation2014; }
   double getBAup() const { return popBACount * 100 / totalPopulation2014; }
   double getHSup() const { return popHSCount * 100 / totalPopulation2014; }
   double getpopPoor() const { return popPoorCount * 100 / totalPopulation2014; }

   double getpopOver65Count() const { return popOver65Count; }
   double getpopUnder18Count() const { return popUnder18Count; }
   double getpopUnder5Count() const { return popUnder5Count; }
   double getBAupCount() const { return popBACount; }
   double getHSupCount() const { return popHSCount; }
   double getpopPoorCount() const { return popPoorCount; }
   int    getTotalPopulationCount() const { return totalPopulation2014; }

   friend std::ostream &operator<<(std::ostream &out, const demogState &SD);

   raceDemogData getRacedata() const { return stateRace; }

 private:
   //DATA here
   const string statename;
   const int number;
   const double popOver65Count;
   const double popUnder18Count;
   const double popUnder5Count;
   const double popBACount;
   const double popHSCount;
   const double popPoorCount;
   const raceDemogData stateRace;
   const int totalPopulation2014;
};
#endif
