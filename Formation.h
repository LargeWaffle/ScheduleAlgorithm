#ifndef SCHEDULEALGORITHM_FORMATION_H
#define SCHEDULEALGORITHM_FORMATION_H

#include "Interface.h"

using namespace std;

class Formation{

public:

    int id;
    int day;

    int startHour;
    int endHour;

    int comp;
    int spec;

    float * position;

    Formation(): id(-1), day(-1), startHour(-1), endHour(-1), comp(-1), spec(-1)
    {
        position = new float [2];
        position[0] = position[1] = -1.0;
    };

    Formation(int id, int day, int hDebut, int hFin, int comp, int spec, float * pos):
            id(id), day(day), startHour(hDebut), endHour(hFin), comp(comp), spec(spec)
    {

        position = new float [2];
        position = pos;
    };

    Formation& operator=(const Formation& form)
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
    };

    inline bool getPartOfDayFormation(){
        return endHour <= 12;
    }

    friend ostream& operator<<(ostream& out_object, Formation& form)
    {
        out_object << "Formation ID "<< form.id;
        out_object << " - day " << form.day << endl;

        cout << "Slot : " << form.startHour << " - " << form.endHour << endl;

        out_object << "Position is {" << form.position[0] << ", " << form.position[1] << "}" << endl;

        return out_object;
    }

};

#endif //SCHEDULEALGORITHM_FORMATION_H
