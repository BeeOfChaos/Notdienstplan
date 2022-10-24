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

#include "group.h"

using namespace std;


/*  add a pharmacy to a group's grouplist   */
void Group::addPharmacy(std::string name, std::string streetAndNumber, std::string plzAndCity, std::string telNumber)
{
    Pharmacy pharmacy(name, streetAndNumber, plzAndCity, telNumber);
    groupList.push_back(pharmacy);
}


/*  create a string for a group to write to rtf-document    */
string Group::toStringForRTF(int scriptSize)
{
    string answer = "\\cols" + to_string(groupList.size()) + "\\colsx100\n{\\f0\\fs" + to_string(scriptSize * 2) + " ";
    for (auto pharmacy : groupList)
    {
        answer += "\\b " + writeAWord(pharmacy.name) + "\\b0\\par " + writeAWord(pharmacy.streetAndNumber) + "\\par " + writeAWord(pharmacy.plzAndCity) + "\\par " + writeAWord(pharmacy.telNumber) + "\\par ";
    }
    return (answer + "\\sect}\n\\sectd\\sbknone\n\n\\line");
}


/*  create a string for the Saturday-group to write to rtf-document    */
string Group::toStringSaturdayForRTF(int scriptSize)
{
    string answer = "{\\f0\\fs" + to_string(scriptSize * 2) + "\\tx300\\tx3800\\tx6000\\tx7600\\tab\\b Name\\tab Telefon\\tab Adresse\\tab \\b0\\line{\\fs6  \\line}";
    for (auto pharmacy : groupList)
    {
        answer += "\\tab\\b " + writeAWord(pharmacy.name) + "\\b0\\tab " + writeAWord(pharmacy.streetAndNumber) + "\\tab " + writeAWord(pharmacy.plzAndCity) + "\\tab " + writeAWord(pharmacy.telNumber) + "\\line";
    }
    return (answer + "\\sect}\\sectd\\sbknone\n");
}


/*  create a string for CMD output - only for control purposes  */
string Group::toStringForCMD()
{
    string answer = groupName + "\t\t";
    for (auto pharmacy : groupList)
    {
        answer += pharmacy.name + "\n\t\t";
    }
    return (answer + "\n");
}