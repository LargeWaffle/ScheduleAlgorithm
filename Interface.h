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
    // map < int, list<int> >
    int distance;   // distance travelled by the Interface

    Interface(): assigned_apprentice(), time_table(), distance(0){

        competence = new int[2];
        speciality = new int[3];
    }

    ~Interface(){

        delete [] competence;
        delete [] speciality;
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

    }
};

#endif //SCHEDULEALGORITHM_INTERFACE_H