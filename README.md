# Schedule Algorithm

This a school project given by our profesors to implement optimization techniques seen in class to address a scheduling problem. 

## Description 

You'll find in this repo different instances of the problem in the file `"instances"`. To select it you'll have to change the `#include "instances/instance-formation.h"` at line 7. Segmentation faults may occur. If so try to run in debug or run it multiple times.

At the start of the program, you'll be asked to select the search time of our algorithms.

To explain quickly what we're doing. We're starting with an empty solution, we fill it first via a greedy algorithm and then we balance the formations assigned via our balancing function. 

Finally during the search time given, we'll apply one crossing operator that will switch formations between interfaces and we'll also apply a mutation operator that will try, after each generation to assign the formations that had not been assigned yet.

## Running
```
$ git clone https://github.com/LargeWaffle/ScheduleAlgorithm
$ cd ScheduleAlgorithm

$ bash build.sh
$ bash run.sh
```
