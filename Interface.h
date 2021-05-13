#ifndef SCHEDULEALGORITHM_INTERFACE_H
#define SCHEDULEALGORITHM_INTERFACE_H

#include <set>
#include <string>
#include <list>
#include <map>
#include <utility>
using namespace std;

class Interface{

protected:
    short int speciality;
    multiset<int> competence;
    list<int> apprentice;
    list<map<int, string>> time_table;
    /* format horaire */
    /* distance parcourue */
public:
    Interface(){};
    Interface(short int a, multiset<int> b, list<int> c, list<map<int, string>> d);
};

Interface::Interface(short int a, multiset<int> b, list<int> c, list <map<int, string>> d) {
    speciality = a;
    competence = std::move(b);
    apprentice = std::move(c);
    time_table = std::move(d);
}
#endif //SCHEDULEALGORITHM_INTERFACE_H
