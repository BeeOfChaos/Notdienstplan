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


#include "plan.h"

using namespace std;


Plan::Plan()
{
    readGroups();

    //  write errors to "Notdienstplan.rtf" and stop the program
    if (errorFlag != "")
    {
        writeToFile(errorFlag);
        openPlan();
        exit(0);
    }
}


/*  write text for "Notdienstplan.rtf" and write the text to the file   */
void Plan::writePlan()
{
    writeToFile(writeTextForFile());
}


/*  open "Notdienstplan.rtf" if a program was specified to do it with  */
void Plan::openPlan()
{
    if (document.getOpen() == 1)
    {
        int ret = (int)ShellExecuteA(NULL, "open", "..\\files\\Notdienstplan.rtf", NULL, NULL, SW_SHOWNORMAL);
        cout << ((ret>32) ? ("Plan sucessfully opened") : ("Plan couldn't be opened")) << endl;
    }
}


/*  read all the groups/pharmacies from "Gruppenliste.txt" in   */
int Plan::readGroups()
{
    vector<string> singleGroup;
    string line, tokenString;
    ifstream fIN("..\\files\\Gruppenliste.txt");
    int checkForSaturday = document.getSaturday();      //  0=false, 1=true
    if (fIN)
    {
        cout << "Gruppenliste.txt found ..." << endl;
        while (fIN)
        {
            getline(fIN, line);
            line = trim(line);
            stringstream sLine(line);
            while (getline(sLine, tokenString, ';'))
            {
                singleGroup.push_back(trim(tokenString));
            }

            //  skip empty line
            if (singleGroup.size() == 0) { continue; }

            //  stops program if group has missing data
            else if (singleGroup.size() % 4 != 1)
            {
                errorFlag = errorFlag + ("Fehler in Gruppenliste.txt in Zeile:\\line " + writeAWord(line) + "\\line Evtl. wurde ein ; vergessen.\\line Bitte in >>Gruppenliste.txt<< korrigieren und Programm neu starten\\line\\line ");
                return 1;
            }

            //  adds group for saturday 
            else if (singleGroup[0] == "Saturday")
            {
                size_t i = 1;
                while (i < singleGroup.size())
                {
                    saturdayGroup.addPharmacy(singleGroup[i], singleGroup[i + 1], singleGroup[i + 2], singleGroup[i + 3]);
                    i += 4;
                }
                singleGroup.clear();
                checkForSaturday = 0;
            }

            //  adds normal group
            else
            {
                Group newGroup(singleGroup[0]);
                for (size_t i = 0; i < (singleGroup.size() / 4); i++)
                {
                    newGroup.addPharmacy(singleGroup[4 * i + 1], singleGroup[4 * i + 2], singleGroup[4 * i + 3], singleGroup[4 * i + 4]);
                }
                allGroups.push_back(newGroup);
                singleGroup.clear();
            }
        }
        fIN.close();

        //  stops program if no groups have been added
        if (allGroups.size() == 0)
        {
            errorFlag += ("Fehler in Gruppenliste.txt: Das Dokument ist leer.\\line Bitte Gruppen eintragen und Programm neu starten!\\line\\line ");
            return 1;
        }

        //  stops program if no group "Saturday" was added if the Dokument.txt specified that there should have been one
        if (checkForSaturday != 0)
        {
            errorFlag += ("Fehler in Gruppenliste.txt: Das Dokument enth\\u228  lt keine Gruppe >>Saturday<<.\\line Bitte \\u252  berpr\\u252  fen bzw. in >>Dokument.txt<< in Zeile 5 \"n\" eintragen f\\u252  r \"keine Samstags-Gruppe\" und Programm neu starten!\\line\\line ");
            return 1;
        }
    }

    //  stops program if "Gruppenliste.txt" wasn't found
    else
    {
        errorFlag += ("Fehler: Es wird eine Datei >>Gruppenliste.txt<< im Verzeichnis \"res\" ben\\u246  tigt\\line Bitte Vorhandensein der Datei und korrekte Schreibweise des Dateinamens \\u252  berpr\\u252  fen und Programm neu starten!\\line\\line "); 
        return 1;
    }
    return 0;
}


/*  write a given text to .rtf-file */
void Plan::writeToFile(string text)
{
    ofstream fOUT;
    fOUT.open("..\\files\\Notdienstplan.rtf");
    fOUT << "{\\rtf1\\ansi\\deff0{\\fonttbl{\\f0\\froman " << document.getScript() << ";}{\\f1\\fmodern Times New Roman;}}\n\\deflang1031\\plain\\f0\\fs" << ((int)(document.getScriptSize() * 1.5)) * 2 << "\\margl567\\margr567\\margb1134\\margt1134\n" <<
        "{\\info{\\title Apotheken Notdienstplan}{\\author by Sabine}}\n\n";
    fOUT << text;
    fOUT << " }";
    fOUT.close();
}


/*  create the text to write to "Notdienstplan.rtf" */
string Plan::writeTextForFile()
{
    PlanTime planTime = PlanTime(document.getDate());
    string month[] = { "Januar", "Februar", "M\\u228  rz", "April", "Mai", "Juni", "Juli", "August", "September", "Oktober", "November", "Dezember" };
    string day[] = { "Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag" };

    //  check if a group for saturday should be written according to "Dokument.txt"
    int saturdayWritten = int((saturdayGroup.getGroupSize() / 3) * document.getSaturday());

    int todaysGroup = (planTime.daysSinceDate % allGroups.size());

    string fileText = "{\\ul Notdienstplan vom \\b " + to_string(planTime.dayToday) + ". " + month[planTime.monthToday] + " " + to_string(planTime.yearToday) + "\\b0  bis \\b ";
    dateFunc(document.getDaysPerPage() - 1, &planTime);
    fileText += to_string(planTime.dayToday) + ". " + month[planTime.monthToday] + " " + to_string(planTime.yearToday) + "\\b0\\sect}\n\\sectd\\sbknone\\line";

    //  create text for each group
    for (int i = 0; i < document.getDaysPerPage(); i++)
    {
        dateFunc(i, &planTime);
        fileText += "\n{\\fs" + to_string(int(document.getScriptSize() * 2.4)) + " Notdienst f\\u252  r \\b " + day[planTime.weekDay] + ", " + to_string(planTime.dayToday) + ". " + month[planTime.monthToday] + " " + to_string(planTime.yearToday) + ",\\b0  von \\b " + document.getOpen_Weekday() + " Uhr \\b0 bis \\b " + document.getOpen_Weekday() + " Uhr \\b0 Folgetag\\line\\fs" + to_string(document.getScriptSize()) + "  \\par\\sect}\\sectd\\sbknone\n";
        fileText += allGroups[(todaysGroup + i) % allGroups.size()].toStringForRTF(document.getScriptSize());
        cout << allGroups[(todaysGroup + i) % allGroups.size()].toStringForCMD() << endl;

        //  check if today is a saturday and if saturday is supposed to be written
        if ((planTime.weekDay == 6) && (document.getSaturday() == 1))
        {
            //  check if saturday is a holiday; if not, add pharmacies to display in "Notdienstplan.rtf"
            string checkForHoliday = to_string(planTime.dayToday) + to_string(planTime.monthToday);
            if (!isHoliday(document.getHolidays(), checkForHoliday))
            {
                fileText += (saturdayGroup.getGroupSize() == 1) ? ("\n{\\fs" + to_string(document.getScriptSize() * 2) + "\\f0\\tx300\\tab Zus\\u228  tzlich hat am \\b Samstag\\b0  in der Zeit von \\b " + document.getOpen_Saturday() + " Uhr\\b0  bis \\b " + document.getClose_Saturday() + " Uhr\\b0  folgende Apotheke ge\\u246  ffnet:\\fs" + to_string(document.getScriptSize()) + "\\line  \\sect}\n\\sectd\\sbknone") : ("\n{\\fs" + to_string(document.getScriptSize() * 2) + "\\f0\\tx300\\tab Zus\\u228  tzlich haben am \\b Samstag\\b0  in der Zeit von \\b " + document.getOpen_Saturday() + " Uhr\\b0  bis \\b " + document.getClose_Saturday() + " Uhr\\b0  folgende Apotheken ge\\u246  ffnet:\\fs" + to_string(document.getScriptSize()) + "\\line  \\sect}\n\\sectd\\sbknone");
                fileText += saturdayGroup.toStringSaturdayForRTF(document.getScriptSize());
                cout << saturdayGroup.toStringForCMD() << endl;
                saturdayWritten = 0;
            }
        }
    }

    //  extraspace - just for the page to look more balanced
    string extraspace = "";
    for (int i = 0; i < (saturdayWritten + 5 - document.getDaysPerPage()); i++) { extraspace += "\\line"; }

    fileText += "\n" + extraspace + "\n\n{\\pard\\qc\\fs" + to_string(int(document.getScriptSize() * 2.4)) + " Bei Inanspruchnahme der Notdienstapotheken ist\\line\n";
    fileText += "in der Zeit von 20:00 Uhr bis 6:00 Uhr morgens,\\line\n";
    fileText += "an Sonn- und Feiertagen ganzt\\u228  gig sowie samstags ab 20:00 Uhr\\line\n";
    fileText += "eine \\b amtliche Zusatzgeb\\u252  hr von 2,50\\u8364\\\'80\\b0  zu entrichten! \\par}\n";

    return fileText;
}


/*  get the correct date for the output text from today=0    */
void Plan::dateFunc(int daysdaysInTheFuture, PlanTime* planTime)
{
    time_t now = time(0);
    now += daysdaysInTheFuture * 84600;
    tm* ltm = localtime(&now);
    planTime->dayToday = ltm->tm_mday;
    planTime->monthToday = ltm->tm_mon;         //  month 0-11 because we use it to access the Month-name vector later       
    planTime->yearToday = ltm->tm_year + 1900;
    planTime->weekDay = ltm->tm_wday;
}


/*  check if the given DayMonth-string is in the given holiday-vector   */
int Plan::isHoliday(vector<string> holidays, string checkForHoliday)
{
    for (const auto date : holidays) {
        if (isNumber(date.substr(0, 2)))
        {
            string dayAndMonth = (isNumber(date.substr(3, 2))) ? (to_string(stoi(date.substr(0, 2))) + to_string(stoi(date.substr(3, 2)) - 1)) : "";
            if (checkForHoliday == dayAndMonth)
            {
                return 1;
            }
        }
    }
    return 0;
}
