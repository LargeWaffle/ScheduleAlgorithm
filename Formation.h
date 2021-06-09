#ifndef SCHEDULEALGORITHM_FORMATION_H
#define SCHEDULEALGORITHM_FORMATION_H

#include "Interface.h"

using namespace std;

class Formation{

public:

    int id;
    int day;

    int hDebut;
    int hFin;

    int comp;
    int spec;

    float * position;

    Interface * assigned_interface;

    Formation(): id(-1), day(-1), hDebut(-1), hFin(-1), comp(-1), spec(-1)
    {
        assigned_interface = new Interface();
        position = new float [2];
        position[0] = position[1] = -1.0;
    };

    Formation(int id, int day, int hDebut, int hFin, int comp, int spec, float * pos):
    id(id), day(day), hDebut(hDebut), hFin(hFin), comp(comp), spec(spec)
    {
        assigned_interface = new Interface();
        position = new float [2];
        position = pos;
    };

    Formation& operator=(const Formation& form)
    {
        if (this != &form)
        {
            id = form.id;
            day = form.day;

            hDebut = form.hDebut;
            hFin = form.hFin;

            comp = form.comp;
            spec = form.spec;

            position = new int[2];
            position = form.position;

            assigned_interface = new Interface();
            assigned_interface = form.assigned_interface;
        }
        return *this;
    }

    ~Formation()
    {
        delete assigned_interface;
        delete [] position;
    };

    inline bool getPartOfDayFormation(){
        return hFin <= 12;
    }

    friend ostream& operator<<(ostream& out_object, Formation& form)
    {
        out_object << "___ Formation ___ " << endl;
        out_object << "ID : " << form.id << endl;

        out_object << "Day : " << form.day;
        cout << "Starts at : " << form.hDebut << " and ends at " << form.hFin << endl;

        out_object << "My position is : {" << form.position[0] << ", " << form.position[1] << "}" << endl;

        return out_object;
    }

};

#endif //SCHEDULEALGORITHM_FORMATION_H
