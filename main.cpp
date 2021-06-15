#include <iostream>
#include <cmath>
#include <random>
#include <functional>
#include <ctime>

#include "instances/instance-formations96.h"
#include "Interface.h"

using namespace std;

Formation *formations_list[NBR_FORMATIONS];
vector<int> FORMATION_INDEXES(NBR_FORMATIONS);


inline float getMean(float travelDistance){
    return travelDistance / NBR_INTERFACES;
}

float evaluatePopulation(Interface *(&population)[NBR_INTERFACES])
{
    int nbPenalty = 0;    //get total number of specialties non fufilled

    float travelDistance = 0.0, varianceValue = 0.0;
    float variance, ecart_type, mean_distance, correlation;      // Correlation factor (cf. pdf)

    for (auto & indiv : population) {
        nbPenalty += indiv->getPenalty();
        travelDistance += indiv->distance;
        varianceValue += indiv->distance * indiv->distance;
    }

    mean_distance = getMean(travelDistance);
    correlation = travelDistance / NBR_FORMATIONS;

    variance = float(varianceValue / pow((NBR_INTERFACES - mean_distance), 2));

    ecart_type = sqrt(variance);

    return (float)(0.5 * (mean_distance + ecart_type) + 0.5 * correlation * nbPenalty);
}

vector<float> getFormationPosition(int indexFormation) //return formation center position according to formation's speciality
{
    if (formation[indexFormation][1] == SPECIALITE_MENUISERIE) {
        return {coord[1][0], coord[1][1]};
    } else if (formation[indexFormation][1] == SPECIALITE_ELECTRICITE) {
        return {coord[2][0], coord[2][1]};
    } else if (formation[indexFormation][1] == SPECIALITE_MECANIQUE) {
        return {coord[3][0], coord[3][1]};
    } else if (formation[indexFormation][1] == SPECIALITE_INFORMATIQUE) {
        return {coord[4][0], coord[4][1]};
    } else {
        return {coord[5][0], coord[5][1]};
    }
}

void fillPopulation(Interface *(&population)[NBR_INTERFACES]) //fill starting population according to instance
{
    for(int i = 0; i < NBR_INTERFACES; i++)
    {
        auto *intervenant = new Interface(); //we create a new instance of class interface each time

        intervenant->competence = competences_interfaces[i];
        intervenant->speciality = specialite_interfaces[i];
        intervenant->currentPosition = {coord[0][0], coord[0][1]};
        population[i] = intervenant;
    }
}

void fillFormations(Formation *(&form_list)[NBR_FORMATIONS]) //fill formations_lists according to instance
{
    for (int i = 0; i < NBR_FORMATIONS; i++)
    {
        auto *form = new Formation(); //we create a new instance of class formation each time

        form->id = formation[i][0];
        form->indexSpec = formation[i][1];
        form->comp = formation[i][2];
        form->day = formation[i][3];
        form->startHour = formation[i][4];
        form->endHour = formation[i][5];
        form->position = getFormationPosition(i);

        form_list[i] = form;
    }
}

bool isSolutionFeasible(Interface *(&population)[NBR_INTERFACES]) // true if all missions have been assigned
{
    int sum = 0;
    for(Interface *i : population)
    {
        sum += int(i->assigned_missions.size()); //we sum all the missions we've assigned
    }
    int difference  = int(sum - ((sizeof(formation)/sizeof(*formation)))); //diffe
    cout << abs(difference) << " formations missing" << endl;

    return sum == ((sizeof(formation)/sizeof(*formation))); // true if we assigned all the missions false otherwise
}


inline bool hasSameCompetence(int indexFormation, int indexInterface) //true if interface has required competence for formation
{
    int competence_form = formation[indexFormation][2];

    return competence_form == 0 ?
                  competences_interfaces[indexInterface][0] == 1
                                 : competences_interfaces[indexInterface][1] == 1;

}


inline bool areRangesOverlapping(int startTime1, int endTime1, int startTime2, int endTime2)
{
    return (endTime1 <= startTime2) || (endTime2 <= startTime1);
}

inline int day(int indexFormation) //return the day of the given formation
{
    return formations_list[indexFormation]->day;
}

//true if daily hours limit (12h) isn't reached
inline bool isAmplitudeOutpassed(Interface *(&population)[NBR_INTERFACES], int indexInterface, int indexFormation)
{
    return (population[indexInterface]->hoursWorkedPerDay[day(indexFormation)] + (formations_list[indexFormation]->endHour - formations_list[indexFormation]->startHour)) <= 12;
}

//true if weekly hours limits isn't reached
inline bool isWeeklyHoursQuotaOutpassed(Interface *(&population)[NBR_INTERFACES], int indexInterface, int indexFormation)
{
    return population[indexInterface]->hoursWorked + (formations_list[indexFormation]->endHour - formations_list[indexFormation]->startHour) < 35;
}

//check if interface's available for a formation, if yes returns true and where to insert the formation in the timetable
pair<bool, int> isFree(int indexInterface, int indexFormation, Interface *(&population)[NBR_INTERFACES])
{

    pair <bool, int> result (false, -1);
    int day_ = day(indexFormation);
    int dayScheduleSize = int(population[indexInterface]->time_table[day_].size());

    if(isAmplitudeOutpassed(population, indexInterface, indexFormation) && isWeeklyHoursQuotaOutpassed(population, indexInterface, indexFormation))
    {
        if(dayScheduleSize == 0 || // day_schedule's empty
                population[indexInterface]->time_table[day_][0]->id == -1 || //day_schedules only has the default formation
                formations_list[indexFormation]->endHour <=
                population[indexInterface]->time_table[day_][0]->startHour //can be inserted at the beginning of the day
        )
        {
            result.first = true;
            result.second = 0;
            return result;
        }
            // can we inserted at the end of the day
        else if (formations_list[indexFormation]->startHour >=
                   population[indexInterface]->time_table[day_][
                           population[indexInterface]->time_table[day_].size()-1]->endHour)
        {
            result.first = true;
            result.second = int(population[indexInterface]->time_table[day_].size()); //index at the end
            return result;

        }
        else //we browse the list of formations to find a place
        {
            int indexOnDaySchedule = 0;
            for (auto &currForm : population[indexInterface]->time_table[day_])
            {
                if (formations_list[indexFormation]->startHour > currForm->endHour)
                {
                    if (indexOnDaySchedule != population[indexInterface]->time_table[day_].size() - 1)
                    {
                        if (formations_list[indexFormation]->endHour <=
                            population[indexInterface]->time_table[day_][indexOnDaySchedule +
                                                                                        1]->startHour)
                        {
                            result.first = true;
                            result.second = indexOnDaySchedule + 1;
                            return result;
                        }
                    }
                } else if (indexOnDaySchedule !=
                           population[indexInterface]->time_table[day_].size() - 1)
                {
                    if (formations_list[indexFormation]->startHour == currForm->endHour)
                    {
                        if (formations_list[indexFormation]->endHour <=
                            population[indexInterface]->time_table[day_][indexOnDaySchedule +
                                                                                        1]->startHour)
                        {
                            result.first = true;
                            result.second = indexOnDaySchedule + 1;
                            return result;
                        }
                    }
                }
            }
        }
    }
    return result;
}

auto euclideanDistance(float x1, float x2, float y1, float y2)  //return the euclidean distance between A(x1,y1) and B(x2,y2)
{
    return float(sqrt(pow(x2 - x1, 2.0)+pow(y2 - y1,2.0)));
}

void resetDistance(Interface *(&population)[NBR_INTERFACES]) //reset the distance traveled before updateInterfaceDistance()
{
    for (auto &currInterface : population)
    {
        currInterface->distance = 0;
    }
}

void updateInterfaceDistance(Interface *(&population)[NBR_INTERFACES]) //compute distance traveled by all the interfaces during a week
{
    vector<float> formationPlace;

    resetDistance(population); //reset distance traveled to avoid summation on previous distances

    for (auto &currInterface : population)
    {
        for (auto &timetable : currInterface->time_table)
        {
            for (int i = 0; i < 6; i++)
            {
                for (auto & j : timetable.second)
                {
                    formationPlace = getFormationPosition(j->indexSpec);

                    currInterface->distance += euclideanDistance(currInterface->currentPosition[0], formationPlace[0], currInterface->currentPosition[1], formationPlace[1]);
                    currInterface->currentPosition = formationPlace;
                }
                //Distance from last formation to HQ at the end of the day
                currInterface->distance += euclideanDistance(currInterface->currentPosition[0], coord[0][0], currInterface->currentPosition[1], coord[0][1]);
                currInterface->currentPosition = {coord[0][0], coord[0][1]};

            }

        }

    }
}

void greedyFirstSolution(Interface *(&population)[NBR_INTERFACES])
{
    int day_;
    pair<bool,int> result;

    //vector created to keep track of missing formations at the end of greedy
    for (int i = 0; i < NBR_FORMATIONS; i++) {
        FORMATION_INDEXES[i] = i;
    }

    for (int indexFormation = 0; indexFormation < NBR_FORMATIONS; indexFormation++)
    {
        for (int indexInterface = 0; indexInterface < NBR_INTERFACES; indexInterface++)
        {
            if (hasSameCompetence(indexFormation, indexInterface) == 1) //if interface has required competence
            {
                day_ = day(indexFormation); //get day of curr formation
                result = isFree(indexInterface, indexFormation, population);

                if (result.first)
                {
                    //we have to place the formation at the right place on the day
                    if (result.second == 0) //replace first null formation
                    {
                        population[indexInterface]->time_table[day_].at(0) = formations_list[indexFormation];
                    }
                    else //insert at right time of the day
                    {
                        population[indexInterface]->time_table[day_].insert(
                                population[indexInterface]->time_table[day_].begin() + result.second, formations_list[indexFormation]);
                    }
                    //delete assigned formation from formationIndexes vector
                    FORMATION_INDEXES.erase(remove(FORMATION_INDEXES.begin(), FORMATION_INDEXES.end(), indexFormation), FORMATION_INDEXES.end());

                    //update hours worked
                    population[indexInterface]->hoursWorked += (formations_list[indexFormation]->endHour - formations_list[indexFormation]->startHour);
                    population[indexInterface]->hoursWorkedPerDay[day_] += (formations_list[indexFormation]->endHour - formations_list[indexFormation]->startHour);

                    //add assigned mission to current interface assigned missions vector
                    population[indexInterface]->assigned_missions.insert(population[indexInterface]->assigned_missions.begin(),indexFormation);
                    break;
                }
            }
        }
    }
    updateInterfaceDistance(population); //compute the distance traveled in this solution
}

// Crossover Operator on two interfaces given two formation slots
void crossingOperator(Interface *(&population)[NBR_INTERFACES], int indexInterfaceOne, int indexInterfaceTwo, int indexFormationOne, int indexFormationTwo, int index1, int index2)
{
    int durationFormationOne = formations_list[indexFormationOne]->endHour - formations_list[indexFormationOne]->startHour;
    int durationFormationTwo = formations_list[indexFormationTwo]->endHour - formations_list[indexFormationTwo]->startHour;
    int dayF1 = day(indexFormationOne);
    int dayF2 = day(indexFormationTwo);

    //MODIFY THE ASSIGNED MISSIONS OF EACH INTERFACE
    population[indexInterfaceOne]->assigned_missions.erase(remove(population[indexInterfaceOne]->assigned_missions.begin(), population[indexInterfaceOne]->assigned_missions.end(), indexFormationOne), population[indexInterfaceOne]->assigned_missions.end());
    population[indexInterfaceTwo]->assigned_missions.erase(remove(population[indexInterfaceTwo]->assigned_missions.begin(), population[indexInterfaceTwo]->assigned_missions.end(), indexFormationTwo), population[indexInterfaceTwo]->assigned_missions.end());
    population[indexInterfaceOne]->assigned_missions.insert(population[indexInterfaceOne]->assigned_missions.begin(),indexFormationTwo);
    population[indexInterfaceTwo]->assigned_missions.insert(population[indexInterfaceTwo]->assigned_missions.begin(),indexFormationOne);

    //DELETE FORMATION FORM EACH INTERFACE
    population[indexInterfaceOne]->time_table[dayF1].erase(population[indexInterfaceOne]->time_table[dayF1].begin() + index1);
    population[indexInterfaceTwo]->time_table[dayF2].erase(population[indexInterfaceTwo]->time_table[dayF2].begin() + index2);

    //UPDATE DISTANCE WORKED PER WEEK / DAY
    population[indexInterfaceOne]->hoursWorked -= durationFormationOne;
    population[indexInterfaceOne]->hoursWorkedPerDay[dayF1] -= durationFormationOne;
    population[indexInterfaceTwo]->hoursWorked -= durationFormationTwo;
    population[indexInterfaceTwo]->hoursWorkedPerDay[dayF2] -= durationFormationTwo;
    population[indexInterfaceOne]->hoursWorked += durationFormationTwo;
    population[indexInterfaceOne]->hoursWorkedPerDay[dayF2] += durationFormationTwo;
    population[indexInterfaceTwo]->hoursWorked += durationFormationOne;
    population[indexInterfaceTwo]->hoursWorkedPerDay[dayF1] += durationFormationOne;

    if (!population[indexInterfaceOne]->time_table[dayF2].empty())
    {
        population[indexInterfaceOne]->time_table[dayF2].insert(
                population[indexInterfaceOne]->time_table[dayF2].begin() + index1, formations_list[indexFormationTwo]);
    }
    else
    {
        population[indexInterfaceOne]->time_table[dayF2].push_back(formations_list[indexFormationTwo]);
    }


    if (!population[indexInterfaceTwo]->time_table[dayF1].empty())
    {
        population[indexInterfaceTwo]->time_table[dayF1].insert(
                population[indexInterfaceTwo]->time_table[dayF1].begin() + index2, formations_list[indexFormationOne]);
    }
    else
    {
        population[indexInterfaceTwo]->time_table[dayF1].push_back(formations_list[indexFormationOne]);
    }
}


bool containsValue(pair<int, int> value, vector<pair<int, int>>& visitedIndex)
{
    bool found = false;

    for (auto & elem : visitedIndex)

        if (value == elem)
        {
            found = true;
            break;
        }

    return found;
}

bool containsValue(int value, vector<int>& visitedIndex)
{
    bool found = false;

    for (auto & elem : visitedIndex)

        if (value == elem)
        {
            found = true;
            break;
        }

    return found;
}

pair<int, int> tournamentSelection(Interface *(&population)[NBR_INTERFACES], vector<Interface*>& competencePool, vector<int>& competencePoolIndexes, vector<int>& visitedInterfaces, float mean_distance) {

    // SELECT PARTICIPANTS
    pair<int, int> result;
    bool exec = false;

    if (competencePool.size() == 1)
    {
        visitedInterfaces.push_back(competencePoolIndexes[0]);
        competencePool.erase(remove(competencePool.begin(), competencePool.end(), competencePool[0]), competencePool.end());
        competencePoolIndexes.erase(remove(competencePoolIndexes.begin(), competencePoolIndexes.end(), competencePoolIndexes[0]), competencePoolIndexes.end());

    }
    else
    {
        do
        {
            int bestIndexPool, secondBestIndexPool;
            float bestScore, secondBestScore, currScore;

            bestScore = competencePool[1]->getInterfaceEvaluation(mean_distance);
            result.first = competencePoolIndexes[1];
            bestIndexPool = 1;

            secondBestScore = competencePool[0]->getInterfaceEvaluation(mean_distance);
            result.second = competencePoolIndexes[0];
            secondBestIndexPool = 0;

            if(secondBestScore > bestScore){
                bestScore = competencePool[0]->getInterfaceEvaluation(mean_distance);
                result.first = competencePoolIndexes[0];
                bestIndexPool = 0;

                secondBestScore = competencePool[1]->getInterfaceEvaluation(mean_distance);
                result.second = competencePoolIndexes[1];
                secondBestIndexPool = 1;
            }

            for (int i = 2; i < competencePool.size(); i++) {
                currScore = competencePool[i]->getInterfaceEvaluation(mean_distance);

                if (currScore > bestScore) {
                    secondBestScore = bestScore;
                    result.second = result.first;
                    secondBestIndexPool = bestIndexPool;

                    bestScore = currScore;
                    result.first = competencePoolIndexes[i];
                    bestIndexPool = i;
                }
                else if (currScore > secondBestScore && currScore != bestScore) {
                    secondBestScore = currScore;
                    result.second = competencePoolIndexes[i];
                    secondBestIndexPool = i;
                }
            }

            if ((!containsValue(result.first, visitedInterfaces) && !containsValue(result.second, visitedInterfaces)) && competencePool.size() >= 2)
            {
                competencePool.erase(remove(competencePool.begin(), competencePool.end(), competencePool[bestIndexPool]), competencePool.end());
                competencePoolIndexes.erase(remove(competencePoolIndexes.begin(), competencePoolIndexes.end(), competencePoolIndexes[bestIndexPool]), competencePoolIndexes.end());

                int updatedIndex = bestIndexPool > secondBestIndexPool ? secondBestIndexPool : secondBestIndexPool - 1;
                competencePool.erase(remove(competencePool.begin(), competencePool.end(), competencePool[updatedIndex]), competencePool.end());
                competencePoolIndexes.erase(remove(competencePoolIndexes.begin(), competencePoolIndexes.end(), competencePoolIndexes[updatedIndex]), competencePoolIndexes.end());

                exec = true;
            }

        } while (!exec);
    }


    return result;
}

pair<int, int> getNonSpecialityForm(Interface * (&inter), vector<pair<int, int>>& visitedIndex)
{
    bool quit = false;
    pair<int, int> result(-1, -1);

    for (int i = 1; i < inter->time_table.size() + 1; i++)
    {
        for (int j = 0; j < inter->time_table[i].size(); j++)
        {
            if(inter->time_table[i][j]->id != -1 && inter->speciality[inter->time_table[i][j]->indexSpec] == 0 )
            {
                result.first = i; result.second = j;

                if (!containsValue(result, visitedIndex))
                {
                    quit = true;
                    break;
                }

            }
        }

        if(quit)
            break;
    }

    visitedIndex.push_back(result);
    return result;
}

pair<int, int> getRandomForm(Interface * (&inter), vector<pair<int, int>>& visitedIndex)
{
    random_device rd;
    mt19937 nb_gen(rd());

    int rd_day; int rd_form;
    pair<int, int> result{-1, -1};

    while (containsValue(result, visitedIndex) || inter->time_table[result.first][result.second]->id != -1)
    {
        cout << "boucle" << endl;
        uniform_int_distribution<int> day_distribution(1, 6);
        rd_day = day_distribution(nb_gen);

        if(!inter->time_table[rd_day].empty())
        {
            cout << "in" << endl;
            uniform_int_distribution<int> form_distribution(0,  int(inter->time_table[rd_day].size() - 1));
            rd_form = form_distribution(nb_gen);
            result.first = rd_day, result.second = rd_form;
        }
        else
        {
            continue;
        }

    }

    visitedIndex.push_back(result);

    return result;
}

//returns index of the formation in FORMATIONS_LISTS given id, day, hour
int getIndexFromID(int id, int day, int startHour, int endHour)
{
    int result = -1;

    int initialValue = (NBR_FORMATIONS / NBR_APPRENANTS) * id;
    int limit = initialValue + (NBR_FORMATIONS / NBR_APPRENANTS);

    for (int k = initialValue; k < limit; k++)
    {
        if (formation[k][3] == day && formation[k][4] == startHour && formation[k][5] == endHour)
            result = k;
    }
    return result;
}

tuple <bool, int, int> isSwappable(int indexFirstInterface, int indexSecondInterface, pair<int, int>& firstFormIndexes, pair<int, int>& secondFormIndexes, Interface *(&population)[NBR_INTERFACES])
{
    Interface * copy_pop[NBR_INTERFACES];

    for (int i = 0; i < NBR_INTERFACES; i++)
    {
        copy_pop[i] = new Interface(*population[i]);
    }


    Interface * firstInter = copy_pop[indexFirstInterface];
    Interface * secondInter = copy_pop[indexSecondInterface];

    vector<Formation *> schedule = firstInter->time_table[firstFormIndexes.first];

    int durationFormationOne = firstInter->time_table[firstFormIndexes.first][firstFormIndexes.second]->endHour - firstInter->time_table[firstFormIndexes.first][firstFormIndexes.second]->startHour;
    firstInter->hoursWorked -= durationFormationOne;
    firstInter->hoursWorkedPerDay[day(firstFormIndexes.second)] -= durationFormationOne;

    int index1 = getIndexFromID(schedule[firstFormIndexes.second]->id, schedule[firstFormIndexes.second]->day, schedule[firstFormIndexes.second]->startHour, schedule[firstFormIndexes.second]->endHour);

    schedule.erase(remove(schedule.begin(), schedule.end(), schedule[firstFormIndexes.second]), schedule.end());

    firstInter->time_table[firstFormIndexes.first] = schedule;



    schedule = secondInter->time_table[secondFormIndexes.first];

    int durationFormationTwo = secondInter->time_table[secondFormIndexes.first][secondFormIndexes.second]->endHour - secondInter->time_table[secondFormIndexes.first][secondFormIndexes.second]->startHour;
    secondInter->hoursWorked -= durationFormationTwo;
    secondInter->hoursWorkedPerDay[day(secondFormIndexes.second)] -= durationFormationTwo;

    int index2 = getIndexFromID(schedule[secondFormIndexes.second]->id, schedule[secondFormIndexes.second]->day, schedule[secondFormIndexes.second]->startHour, schedule[secondFormIndexes.second]->endHour);

    schedule.erase(remove(schedule.begin(), schedule.end(), schedule[secondFormIndexes.second]), schedule.end());

    secondInter->time_table[secondFormIndexes.first] = schedule;

    auto r1 = isFree(indexFirstInterface, index1, copy_pop);
    auto r2 = isFree(indexSecondInterface, index2, copy_pop);

    return {r1.first && r2.first, r1.second, r2.second};
}

// add pair<Interface*, Interface*> instead of void if problems occur
void crossInterfaces(int indexFirstInterface, int indexSecondInterface, Interface *(&population)[NBR_INTERFACES])
{
    bool swap = false;

    pair<int, int> firstFormIndexes;
    pair<int, int> secondFormIndexes;
    tuple<bool, int, int> result;

    vector<pair<int, int>> visitedIndexesFirst;
    vector<pair<int, int>> visitedIndexesSecond;

    Interface * firstInterface = population[indexFirstInterface];
    Interface * secondInterface = population[indexSecondInterface];

    while (visitedIndexesFirst.size() != firstInterface->assigned_missions.size() && visitedIndexesSecond.size() != secondInterface->assigned_missions.size())
    {
        firstFormIndexes = getNonSpecialityForm(firstInterface, visitedIndexesFirst);
        secondFormIndexes = getNonSpecialityForm(secondInterface, visitedIndexesSecond);

        if (firstFormIndexes.first == -1)
            firstFormIndexes = getRandomForm(firstInterface, visitedIndexesFirst);

        if (secondFormIndexes.first == -1)
            secondFormIndexes = getRandomForm(secondInterface, visitedIndexesSecond);

    }

    for (int i = 0; i < visitedIndexesFirst.size(); i++)
    {
        for (int j = 0; j < visitedIndexesSecond.size(); j++)
        {
            //firstFormIndexes.first = secondFormIndexes.first = 1;
            //firstFormIndexes.second = secondFormIndexes.second = 0;
            //result = isSwappable(1,2,firstFormIndexes, secondFormIndexes, population);

            result = isSwappable(indexFirstInterface, indexSecondInterface, visitedIndexesFirst[i], visitedIndexesSecond[j], population);
            //cout << "after is_swappable" << endl;
            swap = get<0>(result);

            if (swap)
            {
                firstFormIndexes = visitedIndexesFirst[i];
                secondFormIndexes = visitedIndexesSecond[j];
                break;
            }
        }

        if(swap)
            break;
    }

    if (swap)
    {
        int indexF1 = getIndexFromID(firstInterface->time_table[firstFormIndexes.first][firstFormIndexes.second]->id, firstInterface->time_table[firstFormIndexes.first][firstFormIndexes.second]->day, firstInterface->time_table[firstFormIndexes.first][firstFormIndexes.second]->startHour, firstInterface->time_table[firstFormIndexes.first][firstFormIndexes.second]->endHour);
        int indexF2 = getIndexFromID(secondInterface->time_table[secondFormIndexes.first][secondFormIndexes.second]->id, secondInterface->time_table[secondFormIndexes.first][secondFormIndexes.second]->day, secondInterface->time_table[secondFormIndexes.first][secondFormIndexes.second]->startHour, secondInterface->time_table[secondFormIndexes.first][secondFormIndexes.second]->endHour);
        //crossingOperator(population, 1, 2, 28, 47, get<1>(result), get<2>(result));

        if(indexF1 != -1 && indexF2 != -1)
        {
            crossingOperator(population, indexFirstInterface, indexSecondInterface, indexF1, indexF2, get<1>(result), get<2>(result));
        }
    }
}

inline void print_population(Interface *(&population)[NBR_INTERFACES])
{
    int index = 0;

    for( auto &elem : population)
    {
        cout << "interface : " << index << endl;
        elem->displayTimeTable();
        index++;
    }
}

//return the index of the busiest and least busy interface from given population
tuple<int, int> getExtremumInterface(Interface *(&population)[NBR_INTERFACES])
{
    int max, min, indexMax, indexMin;
    max = indexMax = indexMin = -1;
    min = 999;

    for (int indexInterface = 0; indexInterface < NBR_INTERFACES; indexInterface++)
    {
        if (population[indexInterface]->hoursWorked > max)
        {
            max = population[indexInterface]->hoursWorked;
            indexMax = indexInterface;
        }
        else if(population[indexInterface]->hoursWorked < min)
        {
            min = population[indexInterface]->hoursWorked;
            indexMin = indexInterface;
        }
    }
    return {indexMax, indexMin};
}

//return the busiest day of the busiest interface and the least busy day of the least busy interface
tuple<int, int> getExtremumDays(Interface *(&population)[NBR_INTERFACES], int indexBusiestInterface, int indexLeastBusyInterface)
{
    int max,min,indexMax, indexMin;
    max = indexMax = indexMin = -1;
    min = 999;

    for(int k = 0; k<5; k++)
    {
        if(population[indexBusiestInterface]->hoursWorkedPerDay[k] > max)
        {
            max = population[indexBusiestInterface]->hoursWorkedPerDay[k];
            indexMax = k;
        }
        else if(population[indexBusiestInterface]->hoursWorkedPerDay[k] < min)
        {
            min = population[indexBusiestInterface]->hoursWorkedPerDay[k];
            indexMin = k;
        }
    }
    return {indexMax, indexMin};
}

void balancingPopulation(Interface *(&population)[NBR_INTERFACES])
{

        auto extremumInterfaces = getExtremumInterface(population);
        auto extremumDays = getExtremumDays(population, get<0>(extremumInterfaces), get<1>(extremumInterfaces));
        int indexBusiest = get<0>(extremumInterfaces);
        int indexLeastBusy = get<1>(extremumInterfaces);
        int busiestDay = get<0>(extremumDays);
        

        Interface * busiestInterface = population[indexBusiest];
        for(int k = 0; k < busiestInterface->time_table[busiestDay].size(); k+=1)
        {
            Formation * currFormation = population[indexBusiest]->time_table[busiestDay][k];
            int id = currFormation->id;
            int indexForm = getIndexFromID(currFormation->id, currFormation->day, currFormation->startHour, currFormation->endHour);

            //we check if the least busy interface is free
            auto result = isFree(indexLeastBusy, indexForm, population);
            if (result.first)
            {
                int durationFormation = formations_list[indexForm]->endHour - formations_list[indexForm]->startHour;

                busiestInterface->assigned_missions.erase(remove(population[indexBusiest]->assigned_missions.begin(), population[indexBusiest]->assigned_missions.end(), indexForm), population[indexBusiest]->assigned_missions.end());
                busiestInterface->time_table[currFormation->day].erase(busiestInterface->time_table[currFormation->day].begin() + k);
                busiestInterface->hoursWorked -= durationFormation;
                busiestInterface->hoursWorkedPerDay[currFormation->day] -= durationFormation;

                population[indexLeastBusy]->assigned_missions.insert(population[indexLeastBusy]->assigned_missions.begin(),indexForm);
                population[indexLeastBusy]->hoursWorked += durationFormation;
                population[indexLeastBusy]->hoursWorkedPerDay[currFormation->day] += durationFormation;
                population[indexLeastBusy]->time_table[currFormation->day].insert(
                        population[indexLeastBusy]->time_table[currFormation->day].begin() +
                        result.second, formations_list[indexForm]);
            }

        }
}

// try to assign remaining formations to given population
void mutationOperator(Interface *(&population)[NBR_INTERFACES])
{
    if(!FORMATION_INDEXES.empty())
    {
        for (auto &formationIndex : FORMATION_INDEXES)
        {
            for (int indexInterface = 0; indexInterface < NBR_INTERFACES; indexInterface++)
            {
                if (hasSameCompetence(formationIndex, indexInterface) == 1) //if interface has required competence
                {
                    int day_ = day(formationIndex); //get day of curr formation
                    pair<bool,int> result = isFree(indexInterface, formationIndex, population);

                    if (result.first)
                    {
                        //we have to place the formation at the right place on the day
                        if (result.second == 0) //replace first null formation
                        {
                            population[indexInterface]->time_table[day_].at(0) = formations_list[formationIndex];
                        }
                        else //insert at right time of the day
                        {
                            population[indexInterface]->time_table[day_].insert(
                                    population[indexInterface]->time_table[day_].begin() + result.second, formations_list[formationIndex]);
                        }
                        //delete assigned formation from formationIndexes vector
                        FORMATION_INDEXES.erase(remove(FORMATION_INDEXES.begin(), FORMATION_INDEXES.end(), formationIndex), FORMATION_INDEXES.end());

                        //update hours worked
                        population[indexInterface]->hoursWorked += (formations_list[formationIndex]->endHour - formations_list[formationIndex]->startHour);
                        population[indexInterface]->hoursWorkedPerDay[day_] += (formations_list[formationIndex]->endHour - formations_list[formationIndex]->startHour);

                        //add assigned mission to current interface assigned missions vector
                        population[indexInterface]->assigned_missions.insert(population[indexInterface]->assigned_missions.begin(),formationIndex);

                        cout << "mutated" << endl;
                        break;
                    }
                }
            }
        }
    }
}


vector<int> getPool(Interface *(&population)[NBR_INTERFACES], vector<Interface*>& pool, float& mean_distance, bool secondPool = false)
{
    float travelDistance = 0.0;
    vector<int> indexes;

    // POOL FILLING
    for(int i = 0; i < NBR_INTERFACES; i++){
        travelDistance += population[i]->distance;
        int true_index = i;

        if (secondPool){
            if (population[i]->competence[0] == 1)
            {
                pool.push_back(population[i]);
                indexes.push_back(true_index);
            }
        }
        else{
            if(population[i]->competence[1] == 1)
            {
                pool.push_back(population[i]);
                indexes.push_back(true_index);
            }
        }
    }

    mean_distance = getMean(travelDistance);

    return indexes;

}

int main()
{
    // Main algo
    cout << "IT45 - Probleme d affectation d employes\n" << endl;
    cout << "Configuration of the problem" << endl;
    cout << "* Number of Interfaces = " << NBR_INTERFACES << endl;
    cout << "* Number of Apprentices = " << NBR_APPRENANTS << endl;
    cout << "* Number of nodes = " << NBR_NODES << endl << endl;

    Interface *starting_population[NBR_INTERFACES];
    //Interface *next_population[NBR_INTERFACES];

    vector<int> visitedInterfaces;

     //1. Init pop - DONE
    fillPopulation(starting_population);// Fill starting population
    fillFormations(formations_list);

    greedyFirstSolution(starting_population);

    isSolutionFeasible(starting_population);

     //2. Eval pop - DONE
    float eval = evaluatePopulation(starting_population);

    for (int times = 0; times < 100; times+=1)
    {
        balancingPopulation(starting_population);
    }

    updateInterfaceDistance(starting_population);

    mutationOperator(starting_population);

    float eval2 = evaluatePopulation(starting_population);

    print_population(starting_population);

    cout << "Eval of starting pop is " << eval << endl;
    cout << "Eval of balanced pop is " << eval2 << endl;

     //3.
     //while(nbIteration < limit || score qui stagne) // Pas sur que score qui stagne soit relevantdouble t = clock();
     //

     clock_t t = clock();
     bool stop = false;
     //while(t / CLOCKS_PER_SEC < 30)
     //while(!stop)
    for (int x = 0; x < 5; x++)
     {
         Interface *next_population[NBR_INTERFACES];

         for (int i = 0; i < NBR_INTERFACES; i++) {
             next_population[i] = starting_population[i];
         }

         float mean_distance = 0;
         vector<Interface*> firstCompetencePool;
         vector<int> firstCompetencePoolIndexes = getPool(starting_population, firstCompetencePool, mean_distance);

         mean_distance = 0;
         vector<Interface*> secondCompetencePool;
         vector<int> secondCompetencePoolIndexes= getPool(starting_population, secondCompetencePool, mean_distance, true);

        //4. next_pop filled grâce à la selection = selection des parents - DONE
        //5. Croisement dans next_population

        int poolLimit = int(firstCompetencePool.size());

         while (visitedInterfaces.size() != poolLimit){

             pair<int, int> to_cross = tournamentSelection(next_population, firstCompetencePool, firstCompetencePoolIndexes, visitedInterfaces, mean_distance);
            //cout << "after to cross2" << endl;
            cout << to_cross.first << " | "<< to_cross.second << endl;
             if(to_cross.first != to_cross.second)
             {
                 crossInterfaces(to_cross.first, to_cross.second, next_population);
                 visitedInterfaces.push_back(to_cross.first);
                 visitedInterfaces.push_back(to_cross.second);
             }

            //cout << "after crossInterfaces2" << endl;
        }

         visitedInterfaces.clear();
         poolLimit = int(secondCompetencePool.size());

         while (visitedInterfaces.size() != poolLimit){

             pair<int, int> to_cross = tournamentSelection(next_population, secondCompetencePool, secondCompetencePoolIndexes, visitedInterfaces, mean_distance);
             //cout << "after to cross2" << endl;
             cout << to_cross.first << " | "<< to_cross.second << endl;

             if(to_cross.first != to_cross.second)
             {
                crossInterfaces(to_cross.first, to_cross.second, next_population);
                 visitedInterfaces.push_back(to_cross.first);
                 visitedInterfaces.push_back(to_cross.second);

             }

             //cout << "after crossInterfaces2" << endl;
         }
         visitedInterfaces.clear();
        //6. Contenu de next pop dans starting pop | Passage à la nouvelle gen
        for (int i = 0; i < NBR_INTERFACES; i++) {
            starting_population[i] = next_population[i];
        }

         updateInterfaceDistance(starting_population);

         //7. Evaluer new pop - DONE
         float eval8 = evaluatePopulation(starting_population);
         cout << "New pop eval is : " << eval8 << endl;

        //stop = true;
         t = clock();

     } //FIN WHILE

    print_population(starting_population);

    float eval3 = evaluatePopulation(starting_population);

    cout << "Eval of starting pop is " << eval << endl;
    cout << "Eval of balanced pop is " << eval2 << endl;
    cout << "Final pop eval is : " << eval3 << endl;

    cout << "Time out !" << endl;

    return 0;
}

