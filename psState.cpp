#include <iomanip>
#include "psState.h"

/* print state data - as aggregate of all incidents in this state */
//fill in for lab4
std::ostream& operator<<(std::ostream &out, const psState& PD) {
    out << "State Info: " << PD.state;
    out << "\nNumber of incidents: " << PD.totalnum;
    out << std::setprecision(2) << std::fixed;
    out << "\nIncidents with age \n(over 65): " << PD.over65;
    out << "\n(19 to 64): " << PD.totalnum-PD.over65-PD.under18;
    out << "\n(under 18): " << PD.under18;
    out << "\nIncidents involving fleeing: " << PD.fleeing;
    out << "\nIncidents involving mental illness: " << PD.mentalill;
    out << "\nMale incidents: " << PD.male << " female incidents: " << PD.female;
    out << "\nRacial demographics of state incidents: " << PD.racialData;
    return out;
}