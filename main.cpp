#include <iostream>
#include <vector>
#include <cmath>

#include "InstanceFormations.h"
#include "Interface.h"

using namespace std;
/*
float evaluatePop(Interface Population[])
{
    float score;

    int penalty = 3;//get total number of specialties non fufilled

    for (auto Individu : Population) {

    }

    float mindistance;
    float variance = NBR_INTERFACES / (NBR_INTERFACES- mindistance * mindistance);
    float ecart_type = sqrt(variance);

    score = (float)(0.5 * penalty);
    return score
}
*/

int main(){
    cout << "IT45 - Probleme d’affectation d’employes\n" << endl;
    cout << "Configuration of the problem" << endl;
    cout << "\tNumber of Interfaces = " << NBR_INTERFACES << endl;
    cout << "\tNumber of Apprentices = " << NBR_APPRENANTS << endl;
    cout << "\tNumber of nodes = " << NBR_NODES << endl;

    Interface Population[NBR_INTERFACES];

    // Remplir solution initiale dans population

    //float eval = evaluatePop(Population);

    return 0;
};

