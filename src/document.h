
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

#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "stringfuncts.h"
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>


class Document {
private:
    std::string date;                 //  date since which the grouplist is valid
    int daysPerPage;                  //  how many days per page
    std::string script;
    int scriptSize = 10;
    std::string open_weekday = "";    //  when does the emergency service start and end 
    int open = 1;                     //  open "Notdienst.rtf" after creating it, accepts j or J for Ja/Yes 
    int saturday = 0;                 //  is there a special group for saturdays, accepts j or J for Ja/Yes
    std::string open_saturday = "";   //  if saturday, from which time
    std::string close_saturday = "";  //  if saturday, til which time
    std::vector<std::string> holidays = { "01.01.", "01.05.", "03.10,", "25.12.", "26.12." };   //  holidays that can fall on saturdays
    std::string errorFlag = "";       //  if any information in "Dokument.txt" is missing/obviously wrong

public:
    Document();
    std::string getDate() { return date; }
    int getDaysPerPage() { return daysPerPage; }
    std::string getScript() { return script; }
    int getScriptSize() { return scriptSize; }
    std::string getOpen_Weekday() { return open_weekday; }
    int getOpen() { return open; }                                        
    int getSaturday() { return saturday; }
    std::string getOpen_Saturday() { return open_saturday; }
    std::string getClose_Saturday() { return close_saturday; }
    std::vector<std::string> getHolidays() { return holidays; }
    std::string getFlag() { return errorFlag; }
};


#endif