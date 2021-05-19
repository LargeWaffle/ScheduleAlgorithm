#ifndef SCHEDULEALGORITHM_INTERFACE_H
#define SCHEDULEALGORITHM_INTERFACE_H

#include <string>
#include <list>
#include <map>

using namespace std;

class Interface{

public:
    int *competence;   // sign and/or LPC
    int *speciality;   // list of the interface's specialty (max 3)
    list<int> assigned_apprentice;   // list of apprentices ids
    list< map<int, string> > time_table;
    int distance;   // distance travelled by the Interface

    Interface(): assigned_apprentice(), time_table(), distance(0)
    {
        competence = new int[2];
        speciality = new int[3];

    };

    ~Interface()
    {
        delete [] competence;
        delete [] speciality;
    }
};

#endif //SCHEDULEALGORITHM_INTERFACE_H