#ifndef SCHEDULEALGORITHM_INTERFACE_H
#define SCHEDULEALGORITHM_INTERFACE_H

#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
/*
 * class Formation
 *
 * id
 * hDebut
 * hFin
 * day
 * Specialite
 * Competence
 * localisation
 * (interface assignée)
 *
 * map < int, vector<formation> >
 *
 *
 *
 */

class Interface{

public:

    float distance;     // distance travelled by the Interface
    float fitness;      // fitness value for genetic selection
    int *competence;   // sign and/or LPC
    int *speciality;   // list of the interface's specialty (max 3)

    vector<float> currentPosition;
    vector<int> assigned_missions;   // list of missions ids

    map < int, vector<int> > time_table; //<day, schedule list>

    Interface(): assigned_missions(), distance(0.0), fitness(0.0){

        competence = new int[2];
        speciality = new int[NBR_SPECIALITES];

        for(int i = 1; i < 7; i++)
            time_table.insert(pair<int, vector<int>>(i ,{-1, -1, -1, -1, -1, -1, -1, -1}));

        currentPosition = {coord[0][0], coord[0][1]}; //HQ position
    }

    ~Interface(){

        delete [] competence;
        delete [] speciality;
    }

    Interface& operator=(const Interface& indiv)
    {
        if (this != &indiv)
        {
            competence = new int[2];
            competence = indiv.competence;

            speciality = new int[NBR_SPECIALITES];

            for (int i = 0; i < NBR_SPECIALITES; i++)
                speciality[i] = indiv.speciality[i];

            currentPosition = indiv.currentPosition; //HQ position
            assigned_missions = indiv.assigned_missions;

            time_table = indiv.time_table;
        }
        return *this;
    }

    friend ostream& operator<<(ostream& out_object, Interface& indiv)
    {
        out_object << "___ Interface ___ " << endl;
        indiv.displayInterface();
        out_object << "\nTimetable" << endl;
        indiv.displayTimeTable();
        return out_object;
    }

    void displayInterface(){

        cout << "Competences ";
        cout << "[" << competence[0] << ", " << competence[1] << "]" << endl;

        cout << "Speciality ";

        cout << "[" << speciality[0];
        for(int i = 1; i < NBR_SPECIALITES; i++)
            cout << ", " << speciality[i];
        cout << "]" << endl << endl;

        if(!assigned_missions.empty())
        {
            // Display list of assigned apprentice

            cout << "IDs of missions  =  {";
            for (int elem : assigned_missions)
                cout << elem << ", ";
            cout << "}\n";
        }
        else
            cout << "Interface has no one to work with !" << endl;

        cout << "and he travelled " << distance << " kms" << endl;
    }

    void displayTimeTable(){

        for (pair<int, vector<int>> element : time_table) {

            int day = element.first;        // Accessing KEY from element
            vector<int> schedule = element.second;        // Accessing VALUE from element.

            cout << day << " : ";
            for(const int& hour : schedule)
            {
                cout << hour << " | ";
            }

            cout << endl;
        }
    }

    int getPenalty()
    {
        int nbPenalty = 0;

        for(int i = 0; i < assigned_missions.size(); i++){

            int index = assigned_missions[i];

            for (int j = 0; j < NBR_SPECIALITES; j++)

                if(speciality[j] == 1)

                    if(j == formation[index][1])
                        nbPenalty++;

        }

        return nbPenalty;
    }

    float evaluateIndividu(float meandistance)
    {
        int nbSpeciality = (int)assigned_missions.size() - getPenalty();
        int emptyInterface = distance == 0 ? 50 : 0;

        float score = 0.7 * (nbSpeciality + emptyInterface) + 0.3 * 1/ abs(meandistance - distance);
        this->fitness = score;

        return score;
    }
};

#endif //SCHEDULEALGORITHM_INTERFACE_H