#ifndef DATAAQ_H
#define DATAAQ_H

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "demogState.h"
#include "psState.h"
/*
  data aggregator and query for testing
*/


class dataAQ {
  public:
    dataAQ();

    void createStateData(std::vector<shared_ptr<demogData>> theData);
    
    void createStateDemogData(std::vector<shared_ptr<demogData>> theData);
    
    void createStatePoliceData(std::vector<shared_ptr<psData>> theData);

    //return the name of the state with the largest population under age 5
    string youngestPop(); 
    //return the name of the state with the largest population under age 18
    string teenPop(); 
    //return the name of the state with the largest population over age 65
    string wisePop(); 
    //return the name of the state with the largest population who did not finish high school
    string underServeHS(); 
    //return the name of the state with the largest population who completed college
    string collegeGrads(); 
    //return the name of the state with the largest population below the poverty line
    string belowPoverty();

    string getMinTeenPop();

    void reportTopTenStatesPS();
    void reportTopTenStatesBP();

    //getter given a state name return a pointer to demogState data
    shared_ptr<demogState> getStateData(string stateName) { return statedata[stateName]; }

    shared_ptr<psState> getStatePoliceData(string stateName) { return statepolicedata[stateName]; }

    //must implement output per aggregate data
    friend std::ostream& operator<<(std::ostream &out, const dataAQ &allStateData);

    //core data private for dataAQ
    private:
       //Decide how to aggregate the data into a map ADD here
      map<string, shared_ptr<demogState>> statedata;
      
      map<string, shared_ptr<psState>>    statepolicedata;

};
#endif
