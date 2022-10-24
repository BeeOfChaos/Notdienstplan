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

#ifndef GROUP_H
#define GROUP_H

#include "pharmacy.h"
#include "stringFuncts.h"
#include <string>
#include <vector>


class Group {
private:
    std::string groupName;
    std::vector<Pharmacy> groupList;

public:
    Group(std::string groupName) { this->groupName = groupName; }
    void addPharmacy(std::string name, std::string streetAndNumber, std::string plzAndCity, std::string telNumber);
    int getGroupSize() { return groupList.size(); }

    std::string toStringForRTF(int scriptSize);
    std::string toStringSaturdayForRTF(int scriptSize);
    std::string toStringForCMD();
};


#endif