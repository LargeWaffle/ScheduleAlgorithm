#ifndef SCHEDULEALGORITHM_INTERFACE_H
#define SCHEDULEALGORITHM_INTERFACE_H

#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Interface{

public:

    float distance;     // distance travelled by the Interface
    float fitness;      // fitness value for genetic selection
    int *competence;   // sign and/or LPC
    int *speciality;   // list of the interface's specialty (max 3)

    vector<float> currentPosition;

    vector<int> assigned_missions;   // list of missions ids

    map < int, vector<int> > time_table; //<day, schedule list>

    Interface(): assigned_missions(), distance(0){

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

    void display(){
        cout << "___ Interface ___ " << endl;
        displayInterface();
        cout << "\nTimetable" << endl;
        displayTimeTable();
        cout << "_________________ " << endl << endl;
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

            cout << "List of apprentices" << endl;

            cout << "IDs =  { ";
            for (int elem : assigned_missions)
                cout << elem << ", ";
            cout << " };\n";
        }
        else
            cout << "Interface has no one to work with !" << endl;

        cout << "and he travelled " << distance << " kms" << endl;
    }

    void displayTimeTable(){

        auto it = time_table.begin();

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

        cout << endl;
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
        //TODO: To reconsider if values are weird

        int nbSpeciality = (int)assigned_missions.size() - getPenalty();
        return 0.7 * nbSpeciality + 0.3 * 1/ abs(meandistance - distance);
    }
};

#endif //SCHEDULEALGORITHM_INTERFACE_H