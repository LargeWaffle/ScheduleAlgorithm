#ifndef SCHEDULEALGORITHM_FORMATION_H
#define SCHEDULEALGORITHM_FORMATION_H

#include "Interface.h"

using namespace std;

class Formation{

public:

    int id;     // Missions ID
    int day;    // Day of the formation

    int startHour;  // Starting hour of the formation
    int endHour;    // Ending hour of the formation

    int comp;   // Required competence
    int indexSpec;   // Required speciality if possible

    vector<float> position;   // Place of the formation

    Formation(): id(-1), day(-1), startHour(-1), endHour(-1), comp(-1), indexSpec(-1)
    {
        position = {-1,-1};
    }

    Formation(int id, int day, int hDebut, int hFin, int comp, int spec, vector<float> pos):
            id(id), day(day), startHour(hDebut), endHour(hFin), comp(comp), indexSpec(spec)
    {
        position = {pos[0],pos[1]};
    }

    Formation& operator=(Formation &form)
    {
        if (this != &form)
        {
            id = form.id;
            day = form.day;

            startHour = form.startHour;
            endHour = form.endHour;

            comp = form.comp;
            indexSpec = form.indexSpec;

            position = form.position;

        }
        return *this;
    }

    ~Formation()
    {
        //delete [] position;
    }

    friend ostream& operator<<(ostream& out_object, Formation& form)
    {
        out_object << form.startHour << " - " << form.endHour;

        return out_object;
    }

    void displayFormation()
    {
        cout << "Formation ID "<< id;
        cout << " - day " << day << endl;

        cout << "Slot : " << startHour << " - " << endHour << endl;

        cout << "Position is {" << position[0] << ", " << position[1] << "}" << endl;
        cout << startHour << " - " << endHour;
    }

};

#endif //SCHEDULEALGORITHM_FORMATION_H
