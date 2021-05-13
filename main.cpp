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

/*
void test(){
    Interface population[NBR_INTERFACES];
    multiset<int> t;
    t.insert(3);
    list<int> lint (3,5);
    list<map<int, string>> lmapstr;
    map<int, string> bonjour;

    bonjour[0] = "c";
    bonjour[1] = "3";
    bonjour[2] = "4";

    lmapstr.push_back(bonjour);

    cout << "Entry point" << endl;

    Interface int1(3, t, lint, lmapstr);

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

