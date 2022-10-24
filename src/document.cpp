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

#include "document.h"

using namespace std;


/*  read Document.txt and add attribute values  */
Document::Document()
{
    string line;
    int line_Number = 0;
    ifstream fIN("..\\files\\Dokument.txt");
    if (fIN)
    {
        cout << "Dokument.txt found ..." << endl;

        while (fIN)
        {
            getline(fIN, line);
            line = trim(line);
            if (line != "")
            {
                switch (line_Number)
                {
                case 0:
                    if (isDate(line)) {
                        date = line;
                    }
                    else {
                        errorFlag += "Fehler in Dokument.txt: Das Datum für den Start der Gruppenliste muss an 1. Stelle im Format TT.MM.JJJJ eingegeben werden. Bitte korrigieren.\\line\\line ";
                    }
                    break;
                case 1:
                    if (isNumber(line)) {
                        daysPerPage = stoi(line);
                    }
                    else {
                        errorFlag += "Fehler in Dokument.txt: Die Anzahl der Apotheken pro Seite muss an 2. Stelle eingegeben werden und darf nur Ziffern enthalten. Bitte korrigieren.\\line\\line ";
                    }
                    break;
                case 2:
                    script = line;
                    break;
                case 3:
                    if (isNumber(line)) {
                        scriptSize = stoi(line);
                    }
                    else {
                        errorFlag += "Fehler in Dokument.txt: Die Schriftgr\\u246  \\u223  e muss an 4. Stelle eingegeben werden und darf nur Ziffern enthalten. Bitte korrigieren.\\line\\line ";
                    }
                    break;
                case 4:
                    open_weekday = line;
                    break;
                case 5: 
                    open = (line == "j" || line == "J") ? 1 : 0;
                    break;
                case 6:
                    saturday = (line == "j" || line == "J") ? 1 : 0;
                    break;
                case 7:
                    open_saturday = line;
                    break;
                case 8:
                    close_saturday = line;
                    break;
                case 9:
                    stringToVector(line, holidays);
                    break;
                }
                line_Number++;
            }
        }
        if (line_Number < 4)
        {
            errorFlag += "Fehler in Dokument.txt: Es fehlen Daten. Bitte korrigieren!\\line\\line  ";
        }
    }
    else
    {
        errorFlag += ("Fehler: Es wird eine Datei >>Dokument.txt<< im Verzeichnis \"files\" ben\\u246  tigt\\line Bitte Vorhandensein der Datei und korrekte Schreibweise des Dateinamens \\u252  berpr\\u252  fen und Programm neu starten!\\line\\line "); 
    }
}




