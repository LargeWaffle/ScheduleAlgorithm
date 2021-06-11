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
    int spec;   // Required speciality if possible

    float * position;   // Place of the formation

    Formation(): id(-1), day(-1), startHour(-1), endHour(-1), comp(-1), spec(-1)
    {
        position = new float [2];
        position[0] = position[1] = -1.0;
    }

    Formation(int id, int day, int hDebut, int hFin, int comp, int spec, float * pos):
            id(id), day(day), startHour(hDebut), endHour(hFin), comp(comp), spec(spec)
    {

        position = new float [2];
        position = pos;
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
            spec = form.spec;

            position = new float [2];
            position = form.position;

        }
        return *this;
    }

    ~Formation()
    {
        delete [] position;
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
