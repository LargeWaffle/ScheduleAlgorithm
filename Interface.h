#ifndef SCHEDULEALGORITHM_INTERFACE_H
#define SCHEDULEALGORITHM_INTERFACE_H

#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Interface{

public:

    float distance;   // distance travelled by the Interface
    int *competence;   // sign and/or LPC
    int *speciality;   // list of the interface's specialty (max 3)

    vector<int> assigned_apprentice;   // list of apprentices ids

    map < int, vector<int> > time_table; //<jour, liste d'horaires>

    Interface(): assigned_apprentice(), distance(0){

        competence = new int[2];
        speciality = new int[5];

        for(int i = 1; i < 7; i++)
            time_table.insert(pair<int, vector<int>>(i ,{-1, -1, -1, -1, -1, -1, -1, -1}));
    }

    ~Interface(){

        delete [] competence;
        delete [] speciality;
    }

    void display(){
        displayInterface();
        displayTimeTable();
    }

    void displayInterface(){

        cout << "___ Interface ___ " << endl;

        cout << "Competences" << endl;
        cout << "[ " << competence[0] << ", " << competence[1] << " ]" << endl;

        cout << "Speciality" << endl;
        cout << "[ " << speciality[0] << ", " << speciality[1] << " ," << speciality[2] << " ]" << endl;

        if(!assigned_apprentice.empty())
        {
            // Display list of assigned apprentice

            cout << "List of apprentices" << endl;

            cout << "IDs =  { ";
            for (int elem : assigned_apprentice)
                cout << elem << ", ";
            cout << " };\n";
        }
        else
            cout << "Interface has no one to work with !" << endl;

        cout << "and he travelled " << distance << " kms" << endl;
        cout << "___ End of display ___" << endl;
    }

    void displayTimeTable(){

        auto it = time_table.begin();

        for (pair<int, vector<int>> element : time_table) {

            int day = element.first;        // Accessing KEY from element
            vector<int> schedule = element.second;        // Accessing VALUE from element.

            cout << day << " : ";
            for(const int& hour : schedule)
            {
                cout << " | " << hour;
            }

            cout << endl;
        }

        cout << endl;
    }

};

#endif //SCHEDULEALGORITHM_INTERFACE_H