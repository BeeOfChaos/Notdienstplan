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

#ifndef PHARMACY_H
#define PHARMACY_H

#include <string>


struct Pharmacy {
public:
    std::string name;
    std::string streetAndNumber;
    std::string plzAndCity;
    std::string telNumber;

    Pharmacy(std::string name, std::string streetAndNumber, std::string plzAndCity, std::string telNumber)
    {
        this->name = name;
        this->streetAndNumber = streetAndNumber;
        this->plzAndCity = plzAndCity;
        this->telNumber = telNumber;
    }
};

#endif
