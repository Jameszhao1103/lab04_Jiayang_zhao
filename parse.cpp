/* helper routines to read out csv data */
#include "parse.h"
#include <algorithm>
#include <cmath>

/* helper to strip out quotes from a string */
string stripQuotes(std::string temp) {
    temp.erase(
        remove(temp.begin(), temp.end(), '\"' ),
        temp.end());
    return temp;
}

/* helper: get field from string stream */
/* assume field has quotes for CORGIS */
string getField(std::stringstream &ss) {
    string data, junk;
    //ignore the first quotes
    std::getline(ss, junk, '\"');
    //read the data (not to comma as some data includes comma (Hospital names))
    std::getline(ss, data, '\"');
    //read to comma final comma (to consume and prep for next)
    std::getline(ss, junk, ',');
    //data includes final quote (see note line 18)
    return stripQuotes(data);
}

string getFieldNQ(std::stringstream &ss)
{
    string temp;
    std::getline(ss, temp, ',');
    //std::cout << temp << std:: endl;
    return temp;
}

/* helper: read out column names for CSV file */
void consumeColumnNames(std::ifstream &myFile) {
    std::string line;
    std::string colname;

    // Extract the first line in the file
    std::getline(myFile, line);

    // Create a stringstream from line
    std::stringstream ss(line);

    // Read the column names (for debugging)
    // Extract each column name for debugging
    while(std::getline(ss, colname, ',')) {
    //    std::cout << colname << std::endl;
    }
}

/* Read one line from a CSV file for county demographic data specifically */
shared_ptr<demogData> readCSVLineDemog(std::string theLine) {
    std::stringstream ss(theLine);
    
    string name = getField(ss);
    string state = getField(ss);
    //turn into mathematical percent
    double popOver65 = stod(getField(ss));
    double popUnder18 = stod(getField(ss));
    double popUnder5 = stod(getField(ss));
    double bachelorDegreeUp = stod(getField(ss));
    double highSchoolUp = stod(getField(ss));

    //now skip over some data
    for (int i=0; i < 4; i++)
        getField(ss);

    //store initial data as percent (then convert to count)
    double FirstNation= stod(getField(ss))/100.0;
    double Asian= stod(getField(ss))/100.0;
    double Black= stod(getField(ss))/100.0;
    double Latinx= stod(getField(ss))/100.0;
    double HIPacificIsle= stod(getField(ss))/100.0;
    double MultiRace= stod(getField(ss))/100.0;
    double White= stod(getField(ss))/100.0;
    double WhiteNH = stod(getField(ss))/100.0;

    //now skip over some data 
    for (int i=0; i < 6; i++)
        getField(ss);

    int medHouseIncome = stoi(getField(ss)); //dont use
    //skip per capita
    getField(ss);
    double belowPoverty = stod(getField(ss));

    //now skip over some data 
    for (int i=0; i < 10; i++)
        getField(ss);

    int totalPop2014 = stoi(getField(ss));

    int FirstNationCount = FirstNation * totalPop2014;
    int AsianCount = Asian * totalPop2014;
    int BlackCount = Black * totalPop2014;
    int LatinxCount = Latinx * totalPop2014;
    int HIPacificIsleCount = HIPacificIsle * totalPop2014;
    int MultiRaceCount = MultiRace * totalPop2014;
    int WhiteCount = White * totalPop2014;
    int WhiteNHCount = WhiteNH * totalPop2014;

    raceDemogData race(FirstNationCount, AsianCount, BlackCount, LatinxCount, HIPacificIsleCount, MultiRaceCount, WhiteCount, WhiteNHCount, totalPop2014);
    
    return make_shared<demogData>(name, state, popOver65, popUnder18,
            popUnder5, bachelorDegreeUp, highSchoolUp, belowPoverty, race, totalPop2014);
}

//read one line of police data
shared_ptr<psData> readCSVLinePolice(std::string theLine) {
    std::stringstream ss(theLine);
    
    getFieldNQ(ss); //ignore id
    string name = getFieldNQ(ss);
    for(int i = 0; i < 3; i++){
        getFieldNQ(ss);
    }
    int age = 0;
    string tmp = getFieldNQ(ss);
    if(tmp != ""){
        age = stoi(tmp);
    }
    else{
        age = -1;
    }
    string gender = getFieldNQ(ss);
    string race = getFieldNQ(ss);
    string city = getFieldNQ(ss);
    string state = getFieldNQ(ss);
    //finish reading other data fields and initialize police data
    string ill = getFieldNQ(ss);
    bool illness = true;
    if (ill == "True"){
        illness = true;
    }else{
        illness = false;
    }
    //skip one line
    getFieldNQ(ss);
    string flee = getFieldNQ(ss);
    return make_shared<psData>(state, name, age, gender, race, city, illness, flee);
}


//read from a CSV file (for a given data type) return a vector of the data
// DO NOT modify 
std::vector<shared_ptr<demogData>> read_csv(std::string filename, typeFlag fileType) {
    //the actual data
    std::vector<shared_ptr<demogData>> theData;

    // Create an input filestream
    std::ifstream myFile(filename);

    // Make sure the file is open
    if(!myFile.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    if(myFile.good()) {
        consumeColumnNames(myFile);

        // Helper vars
        std::string line;

        // Now read data, line by line and create demographic dataobject
        while(std::getline(myFile, line)) {
            if (fileType == DEMOG) {
                theData.push_back(readCSVLineDemog(line));
            } else {
                cout << "ERROR - unknown file type" << endl;
                exit(0);
            }
        }

        // Close file
        myFile.close();
    }

    return theData;
}


// Reads a CSV file 
std::vector<shared_ptr<psData>> read_csvPolice(std::string filename, typeFlag fileType) {
    //the actual data
    std::vector<shared_ptr<psData> > theData;

    // Create an input filestream
    std::ifstream myFile(filename);

    // Make sure the file is open
    if(!myFile.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    if(myFile.good()) {
        consumeColumnNames(myFile);

        // Helper vars
        std::string line;

        // Now read data, line by line and create a county info object
        while(std::getline(myFile, line)) {
            if (fileType == POLICE) {
                theData.push_back(readCSVLinePolice(line));
            } else {
                cout << "ERROR - unknown file type" << endl;
                exit(0);
            }
            
        }

        // Close file
        myFile.close();
    }

    return theData;
}


