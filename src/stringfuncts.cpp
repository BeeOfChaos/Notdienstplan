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

#include "stringfuncts.h"


/*  adjust special signs for writing to rtf - works for ä,Ä,ö,Ö,ü,Ü,ß*/
std::string writeAWord(std::string str) {
    std::string answer = "";
    for (size_t i = 0; i < str.size(); i++)
    {
        if (str.substr(i, 2) == "Ã¤")           //ä
        {
            answer += "\\u228  ";
            i++;
        }
        else if (str.substr(i, 2) == "Ã„")      //Ä
        {
            answer += "\\u196  ";
            i++;
        }
        else if (str.substr(i, 2) == "Ã¶")      //ö
        {
            answer += "\\u246  ";
            i++;
        }
        else if (str.substr(i, 2) == "Ã–")      //Ö
        {
            answer += "\\u214  ";
            i++;
        }
        else if (str.substr(i, 2) == "Ã¼")      //ü
        {
            answer += "\\u252  ";
            i++;
        }
        else if (str.substr(i, 2) == "Ãœ")      //Ü
        {
            answer += "\\u220  ";
            i++;
        }
        else if (str.substr(i, 2) == "ÃŸ")      //ß
        {
            answer += "\\u223  ";
            i++;
        }
        else
        {
            answer += str[i];
        }
    }
    return answer;
}



/*  trim " " from words */
std::string trim(const std::string& str)
{
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return (((last == first) && (last != 0)) ? ("") : (str.substr(first, (last - first + 1))));
}


/*  split string at ; and add to given stringvector */
void stringToVector(std::string str, std::vector<std::string>& stringVector)
{
    std::string tokenString;
    std::stringstream sStr(str);
    while (getline(sStr, tokenString, ';'))
    {
        stringVector.push_back(trim(tokenString));
    }
}


/*  check if a string contains only numbers */
int isNumber(const std::string& str)
{
    for (char const& chara : str) {
        if (isdigit(chara) == 0)
        {
            return 0;
        }
    }
    return 1;
}


/*  check if a string is a valid date   */
int isDate(std::string date)
{
    int answer = 0;
    if ((isNumber(date.substr(0, 2))) && (isNumber(date.substr(3, 2))) && (isNumber(date.substr(6, 4))))
    {
        tm dateToCheck = { 0 };
        dateToCheck.tm_year = stoi(date.substr(6, 4)) - 1900;
        dateToCheck.tm_mon = stoi(date.substr(3, 2)) - 1;
        dateToCheck.tm_mday = stoi(date.substr(0, 2));

        answer = (((dateToCheck.tm_year == (stoi(date.substr(6, 4)) - 1900) && (dateToCheck.tm_mon == (stoi(date.substr(3, 2)) - 1))) && (dateToCheck.tm_mday == stoi(date.substr(0, 2)))) ? 1 : 0);
    }
    return answer;
}

