/*
   Copyright 2022 Sabine Kaeschner

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

*/

#ifndef PLAN_H
#define PLAN_H


#include "document.h"
#include "group.h"
#include "stringFuncts.h"
#include "plantime.h"
#include <iostream>
#include <sstream>  
#include <stdlib.h>
#include <vector>
#include <windows.h>
#include <ShellAPI.h>



class Plan {
private:
    Document document;
    std::vector<Group> allGroups;
    Group saturdayGroup = Group("Saturday");
    std::string errorFlag = document.getFlag();

    void writeToFile(std::string text);
    std::string writeTextForFile();
    void dateFunc(int daysdaysInTheFuture, PlanTime* planTime);
    int readGroups();
    int isHoliday(std::vector<std::string> holidays, std::string checkForHoliday);

public:
    Plan();
    void writePlan();
    void openPlan();
};

#endif