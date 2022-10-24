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

#ifndef PLANTIME_H
#define PLANTIME_H

#include <ctime>
#include <string>


struct PlanTime
{
public:
    int dayToday;           //  day of the month
    int monthToday;         //  month, -1 !!! (0-11)
    int yearToday;          //  year, -1900
    int weekDay;            //  day of the week, starting 0=Sunday
    int daysSinceDate;      //  days since date given in Document.txt

    PlanTime(std::string date)
    {
        time_t time_now = time(0);
        tm *now = localtime(&time_now);
        tm today = { 0 };
        today.tm_year = now->tm_year;
        yearToday = now->tm_year + 1900;
        today.tm_mon = monthToday = now->tm_mon;
        today.tm_mday = dayToday = now->tm_mday;
        weekDay = now->tm_wday;
        time_t today_secs = mktime(&today);

        tm start = { 0 };
        start.tm_year = stoi(date.substr(6, 4)) - 1900;
        start.tm_mon = stoi(date.substr(3, 2)) - 1;
        start.tm_mday = stoi(date.substr(0, 2));
        time_t start_secs = mktime(&start);

        daysSinceDate = ((today_secs - start_secs) / 86400);
    }
};


#endif