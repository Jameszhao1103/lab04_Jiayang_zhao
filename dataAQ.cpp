/* aggregate data */
#include "dataAQ.h"
#include "demogData.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <math.h>
#include <iomanip>

dataAQ::dataAQ() {}

/* necessary function to aggregate the data - this CAN and SHOULD vary per
   student - depends on how they map, etc. */
void dataAQ::createStateData(std::vector<shared_ptr<demogData> > theData)
{
  string statename = "";
  for (const auto obj : theData)
  {
    if (statename == "")
    {
      statename = obj->getState();
      statedata[obj->getState()] = make_shared<demogState>(obj->getState(), 1, obj->getpopOver65Count(), obj->getpopUnder18Count(),
                                                           obj->getpopUnder5Count(), obj->getBAupCount(), obj->getHSupCount(), obj->getpopPoorCount(), obj->getPop());
    }
    else if (obj->getState() != statename)
    {
      statename = obj->getState();
      statedata[obj->getState()] = make_shared<demogState>(obj->getState(), 1, obj->getpopOver65Count(), obj->getpopUnder18Count(),
                                                           obj->getpopUnder5Count(), obj->getBAupCount(), obj->getHSupCount(), obj->getpopPoorCount(), obj->getPop());
    }
    else
    {
      int number = statedata[obj->getState()]->getNumber();
      double popOver65Count = statedata[obj->getState()]->getpopOver65Count();
      double popUnder18Count = statedata[obj->getState()]->getpopUnder18Count();
      double popUnder5Count = statedata[obj->getState()]->getpopUnder5Count();
      double popBACount = statedata[obj->getState()]->getBAupCount();
      double popHSCount = statedata[obj->getState()]->getHSupCount();
      double popPoorCount = statedata[obj->getState()]->getpopPoorCount();
      int totalPopulation2014 = statedata[obj->getState()]->getTotalPopulationCount();

      statedata[obj->getState()] = make_shared<demogState>(obj->getState(), number += 1, obj->getpopOver65Count() + popOver65Count, obj->getpopUnder18Count() + popUnder18Count,
                                                           obj->getpopUnder5Count() + popUnder5Count, obj->getBAupCount() + popBACount, obj->getHSupCount() + popHSCount, obj->getpopPoorCount() + popPoorCount,
                                                           obj->getPop() + totalPopulation2014);
    }
  }
}

void dataAQ::createStateDemogData(std::vector<shared_ptr<demogData> > theData){
  string statename = "";
  for (const auto obj : theData)
  {
    if (statename == "")
    {
      statename = obj->getState();
      statedata[obj->getState()] = make_shared<demogState>(obj->getState(), 1, obj->getpopOver65Count(), obj->getpopUnder18Count(),
                                                           obj->getpopUnder5Count(), obj->getBAupCount(), obj->getHSupCount(), obj->getpopPoorCount(), obj->getRacedata(), obj->getPop());
    }
    else if (obj->getState() != statename)
    {
      statename = obj->getState();
      statedata[obj->getState()] = make_shared<demogState>(obj->getState(), 1, obj->getpopOver65Count(), obj->getpopUnder18Count(),
                                                           obj->getpopUnder5Count(), obj->getBAupCount(), obj->getHSupCount(), obj->getpopPoorCount(), obj->getRacedata(), obj->getPop());
    }
    else
    {
      int number = statedata[obj->getState()]->getNumber();
      double popOver65Count = statedata[obj->getState()]->getpopOver65Count();
      double popUnder18Count = statedata[obj->getState()]->getpopUnder18Count();
      double popUnder5Count = statedata[obj->getState()]->getpopUnder5Count();
      double popBACount = statedata[obj->getState()]->getBAupCount();
      double popHSCount = statedata[obj->getState()]->getHSupCount();
      double popPoorCount = statedata[obj->getState()]->getpopPoorCount();
      int totalPopulation2014 = statedata[obj->getState()]->getTotalPopulationCount();
      raceDemogData oldrace = statedata[obj->getState()]->getRacedata();

      statedata[obj->getState()] = make_shared<demogState>(obj->getState(), number += 1, obj->getpopOver65Count() + popOver65Count, obj->getpopUnder18Count() + popUnder18Count,
                                                           obj->getpopUnder5Count() + popUnder5Count, obj->getBAupCount() + popBACount, obj->getHSupCount() + popHSCount, 
                                                           obj->getpopPoorCount() + popPoorCount, obj->getRacedata() += oldrace, obj->getPop() + totalPopulation2014);
                                                           
                                                           
    }
  }
}

void dataAQ::createStatePoliceData(std::vector<shared_ptr<psData>> theData){
    for(const auto obj: theData){
      if(statepolicedata[obj->getState()]==nullptr){
        int male = 0;
        int female = 0;
        if (obj->getgender() == "M"){
          male += 1;
        }else{
          female += 1;
        }
        int Over = 0;
        if(obj->getAge()>65){
          Over += 1;
        }
        int Under = 0;
        if(obj->getAge()<18){
          Under += 1;
        }
        int ill = 0;
        if (obj->getillness()){
          ill += 1;
        }
        int flee = 0;
        if (obj->getflee() != "Not fleeing"&&obj->getflee() != ""){
          flee += 1;
        }

      
        vector<int> race(6, 0);
        if (obj->getrace() == "A")
        {
          race[0] = 1;
        }else if(obj->getrace() =="B"){
          race[1] = 1;
        }else if(obj->getrace() =="N"){
          race[4] = 1;
        }else if(obj->getrace() =="H"){
          race[3] = 1;
        }else if(obj->getrace() =="O"){
          race[5] = 1;
        }else if(obj->getrace() =="W"){
          race[2] = 1;
        }

        int constant = 1;
        if (race[2] == 1){
          constant = 2;
        }
        if (obj->getrace() ==""){
          constant = 0;
        }
        raceDemogData racedata(race[4], race[0], race[1], race[3], 0, 0, race[2], race[2], constant);
        
        statepolicedata[obj->getState()] = make_shared<psState>(obj->getState(), ill, flee, Over, Under, racedata, male, female, 1);
      }
      else
      {
        int male    = statepolicedata[obj->getState()]->getnumMales();
        int female  = statepolicedata[obj->getState()]->getnumFemales();
        int over    = statepolicedata[obj->getState()]->getCasesOver65();
        int under   = statepolicedata[obj->getState()]->getCasesUnder18();
        int ill     = statepolicedata[obj->getState()]->getNumMentalI();
        int flee    = statepolicedata[obj->getState()]->getFleeingCount();
        
        if (obj->getgender() == "M"){
          male += 1;
        }else{
          female += 1;
        }
        if(obj->getAge()>65){
          over += 1;
        }
        if(obj->getAge()<18){
          under += 1;
        }
       if (obj->getillness()){
          ill += 1;
        }
        if (obj->getflee() != "Not fleeing"&&obj->getflee() != ""){
          flee += 1;
        }

        vector<int> race(6, 0);
        if (obj->getrace() == "A"){
          race[0] = 1;
        }else if(obj->getrace() =="B"){
          race[1] = 1;
        }else if(obj->getrace() =="N"){
          race[4] = 1;
        }else if(obj->getrace() =="H"){
          race[3] = 1;
        }else if(obj->getrace() =="O"){
          race[5] = 1;
        }else if(obj->getrace() =="W"){
          race[2] = 1;
        }

        int constant = 1;
        if (race[2] == 1){
          constant = 2;
        }
        if (obj->getrace() ==""){
          constant = 0;
        }
        raceDemogData racedata(race[4], race[0], race[1], race[3], 0, 0, race[2], race[2], constant);
        racedata += statepolicedata[obj->getState()]->getRacialData();

        int total = statepolicedata[obj->getState()]->getNumberOfCases();
        statepolicedata[obj->getState()] = make_shared<psState>(obj->getState(), ill, flee, over, under, racedata, male, female, total+1);
      }
    }
}

//return the name of the state with the largest population under age 5
string dataAQ::youngestPop()
{
  double youngest = -999.0;
  string youngeststate = "";
  for (auto entry : statedata)
  {
    if (entry.second->getpopUnder5() > youngest)
    {
      youngest = entry.second->getpopUnder5();
      youngeststate = entry.first;
    }
  }
  return youngeststate;
}

//return the name of the state with the largest population under age 18
string dataAQ::teenPop()
{
  double youngest = -999.0;
  string youngeststate = "";
  for (auto entry : statedata)
  {
    if (entry.second->getpopUnder18() > youngest)
    {
      youngest = entry.second->getpopUnder18();
      youngeststate = entry.first;
    }
  }
  return youngeststate;
}

//return the name of the state with the largest population over age 65
string dataAQ::wisePop()
{
  double oldest = -999.0;
  string state = "";
  for (auto entry : statedata)
  {
    if (entry.second->getpopOver65() > oldest)
    {
      oldest = entry.second->getpopOver65();
      state = entry.first;
    }
  }
  return state;
}

//return the name of the state with the largest population who did not receive high school diploma
string dataAQ::underServeHS()
{
  double HS = 999;
  string state = "";
  for (auto entry : statedata)
  {
    if (entry.second->getHSup() < HS)
    {
      HS = entry.second->getHSup();
      state = entry.first;
    }
  }
  return state;
}

//return the name of the state with the largest population who did receive bachelors degree and up
string dataAQ::collegeGrads()
{
  double BA = -999;
  string state = "";
  for (auto entry : statedata)
  {
    if (entry.second->getBAup() > BA)
    {
      BA = entry.second->getBAup();
      state = entry.first;
    }
  }
  return state;
}

//return the name of the state with the largest population below the poverty line
string dataAQ::belowPoverty()
{
  double Poor = -999;
  string state = "";
  for (auto entry : statedata)
  {
    if (entry.second->getpopPoor() > Poor)
    {
      Poor = entry.second->getpopPoor();
      state = entry.first;
    }
  }
  return state;
}

std::ostream &operator<<(std::ostream &out, const dataAQ &allStateData)
{
  for (const auto &obj : (allStateData.statedata)) {
    // if(obj.second->getState()!=""){
      std::cout << *obj.second << std::endl;
    // }    
 }
 for (const auto &obj : (allStateData.statepolicedata)) {
    std::cout << *obj.second << std::endl;
    
 }
 return out;

}

bool cmp1(const pair<string,shared_ptr<psState>> &p1, pair<string,shared_ptr<psState>> &p2){
  return p1.second->getNumberOfCases() > p2.second->getNumberOfCases();
}
 
void dataAQ::reportTopTenStatesPS(){
  vector<pair<string,shared_ptr<psState>>> vec;
  for (map<string, shared_ptr<psState>>::iterator it = statepolicedata.begin();it != statepolicedata.end();++it){
    vec.push_back(make_pair(it->first,it->second));
  }
  sort(vec.begin(), vec.end(), cmp1);
  cout << "Top ten states sorted on Below Poverty data & the associated police shooting data:" << endl;
  for (int i = 0; i < 10; i++){
    cout << vec[i].first << endl;
    cout << "Total population: " << statedata[vec[i].first]->getTotalPopulationCount() << endl;
    cout << "Police shooting incidents: " << statepolicedata[vec[i].first]->getNumberOfCases() << endl;
    cout << "Percent below poverty: " << double(int(round(statedata[vec[i].first]->getpopPoor()*100)))/100 << endl;
    
  }
  cout << "..." << endl;
  cout << "**Full listings for top 3 Below Poverty data & the associated police shooting data for top 3:" << endl;
  for (int i = 0; i < 3;i++){
    cout << *statedata[vec[i].first] << endl;
    cout << "**Police shooting incidents:" << *statepolicedata[vec[i].first] << endl;
  }
}



bool cmp2(const pair<string,shared_ptr<demogState>> &p1, pair<string,shared_ptr<demogState>> &p2){
  return p1.second->getpopPoor() > p2.second->getpopPoor();
}

void dataAQ::reportTopTenStatesBP(){
  vector<pair<string,shared_ptr<demogState>>> vec;
  for (map<string, shared_ptr<demogState>>::iterator it = statedata.begin();it != statedata.end();++it){
    vec.push_back(make_pair(it->first,it->second));
  }
  sort(vec.begin(), vec.end(), cmp2);
  cout << "Top ten states sorted on Below Poverty data & the associated police shooting data:" << endl;
  for (int i = 0; i < 10; i++){
    cout << vec[i].first << endl;
    cout << "Total population: " << statedata[vec[i].first]->getTotalPopulationCount() << endl;
    cout << "Percent below poverty: " << setprecision(2)<<fixed<<double(int(round(statedata[vec[i].first]->getpopPoor()*100)))/100 << endl;
    cout << "Police shooting incidents: " << statepolicedata[vec[i].first]->getNumberOfCases() << endl;
    
    
  }
  cout << "..." << endl;
  cout << "**Full listings for top 3 Below Poverty data & the associated police shooting data for top 3:" << endl;
  for (int i = 0; i < 3;i++){
    cout << *statedata[vec[i].first] << endl;
    cout << "**Police shooting incidents:" << *statepolicedata[vec[i].first];
  }
}

