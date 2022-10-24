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

#ifndef STRINGFUNCTS_H
#define STRINGFUNCTS_H

#include <ctime>
#include <string>
#include <string.h>
#include <sstream>  
#include <vector>  


std::string writeAWord(std::string str);
std::string trim(const std::string& str);
void stringToVector(std::string str, std::vector<std::string>& stringVector);
int isNumber(const std::string& str);
int isDate(std::string date);

#endif
