#ifndef POLICE_H
#define POLICE_H

#include <string>
#include <iostream>
#include <utility>

using namespace std;

/*
  class to represent police shooting data
  from CORGIS
*/
class psData {
  public:
    //add appropriate function paramaters to constructor once you add data
    psData(string inState, string inname, int inage, string ingender, string inrace, string incounty, bool inillness, string inflee) : 
      state(inState), name(inname), age(inage), gender(ingender), race(inrace), county(incounty), illness(inillness), flee(inflee) {}


    string getState() const { return state; }
    string getName() const { return name; }
    int    getAge() const { return age; }
    string getgender() const { return gender; }
    string getrace() const { return race; }
    string getcounty() const { return county; }
    bool   getillness() const { return illness; }
    string getflee() const { return flee; }

    friend std::ostream &operator<<(std::ostream &out, const psData &PD);

  private:
    const string state;
    const string name;
    const int age;
    const string gender;
    const string race;
    const string county;
    const bool illness;
    const string flee;
};

#endif
