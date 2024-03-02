#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <cstdlib>
#include <sstream>

using namespace std;
void ReCoding(string codeFile, string InputCode) {
    fstream code(codeFile);
    if (code.is_open()) {
        cout << "Your ease code open!" << endl;
        fstream CppCode(InputCode, std::ios::out | std::ios::trunc);
        if (CppCode.is_open()){
            cout << "Your CPP code open!" << endl;

            string action;
            string act1, act2, act3, act4, act5;
            string range;      
            
            int tabs = 0;
            int tab = 4;

            while (std::getline(code >> std::ws, action)) {
                std::istringstream iss(action);
                iss >> act1 >> act2 >> act3 >> act4 >> act5;
                
                if (act1 == "все") {
                    tabs -= tab;
                }
                for (int i = 0; i < tabs; i++) CppCode << " ";

                if (act1 == "все") {
                    CppCode << "}\n";
                }

                if (act1 == "число" || act1 == "флаг") {
                    if (act1 == "число") range = "int";
                    if (act1 == "флаг") range = "bool";

                    if (act3 == "=")
                        CppCode << range << " " << act2 << " = " << act4 << ";\n";
                    if (act3 == "")
                        CppCode << range << " " << act2 << ";\n";
                }
                else if (act1 == "если") {
                    CppCode << "if ( " << act2 << " ){\n";
                    tabs += tab;
                }
                else if (act1 == "задать") {
                    if (act3 == "вход") {
                        if (act4 == "силы") {
                            CppCode << act2 << " = analogRead( " << act5 << ");\n";
                        }
                        else {
                            CppCode << act2 << " = digitalRead(" << act4 << ");\n";
                        }
                    }
                    else {
                        CppCode << act2 << " = " << act3 << ";\n";
                    }
                }
                
                else if (act1 == "заменять") {
                    CppCode << "#define " << act2 << " " << act3 << endl;
                }
                else if (act1 == "подключить") {
                    CppCode << "#include" << " " << act2 << endl;
                }
                else if (act1 == "установка") {
                    CppCode << "void setup(){" << endl;
                    tabs += tab;
                }
                else if (act1 == "пин" && act2 == "мод") {
                    if (act4 == "вход") range = "INPUT";
                    if (act4 == "выход") range = "OUTPUT";
                    CppCode << "pinMode( " << act3 << ", " << range << ");\n";
                }
                else if (act1 == "код") {
                    CppCode << "void loop(){\n";
                    tabs += tab;
                }
                else if (act1 == "задержка") {
                    CppCode << "delay(" << act2 << ");\n";
                }
                else if (act1 == "подавать") {
                    if (act3 == "максимум" || act3 == "минимум") {
                        if (act3 == "максимум") range = "HIGH";
                        if (act3 == "минимум") range = "LOW";
                        CppCode << "digitalWrite( " << act2 << ", " << range << ");\n";
                    } else{
                        CppCode << "analogWrite(" << act2 << ", " << act3 << ");\n";
                    }
                }
                else if (act1 == "конец") break;

            }
            CppCode.close();
        }else{
            cout << "ERROR: YOUR CPP CODE NOT OPEN" << endl;
        }
        code.close();
    } else{
        cout << "ERROR: YOUR EASE CODE NOT OPEN" << endl;
    }
}


void readSettings(std::string& path, std::string& nextCodePath) {
    std::ifstream settingsFile("settings.fs");
    if (settingsFile.is_open()) {
        std::getline(settingsFile, path);
        std::getline(settingsFile, nextCodePath);
        settingsFile.close();
    }
    else {
        std::cout << "Не удалось открыть файл settings.fs для чтения" << std::endl;
    }
}

int main() {
    setlocale(LC_ALL, "RU");

    std::cout << "Приветствую, если ты не знаешь с++ то тебе эта программа поможет." << endl;
    std::cout << "Если не знаешь как начать пользоватся этой программой то напиши \"documentation\" что бы открыть документацию. " << endl;
    std::cout << "Что бы начать пользоватся напишите \"start\"" << endl;
    std::cout << "Что бы выйти из программы напишите \"exit\"" << endl << endl;
    string action;

    while (true){
        cin >> action;
        if (action == "documentation") {

            const char* filePath = "start documentation\\documentation.html";

            int exitCode = system(filePath);

            if (exitCode == 0) {
                std::cout << "Файл успешно запущен" << std::endl;
            }
            else {
                std::cerr << "Ошибка запуска файла" << std::endl;
            }

        }
        else if (action == "exit") exit(0);
        else if (action == "start") break;
        else {
            std::cout << "Неизвестная команда: " << action << endl;
        }
    }

    system("cls");
    cout << "Что бы скомпилировать код нажмите SPACE\nЧто бы выйти из программы нажмите ESCAPE";

    while (true) {
        if (GetKeyState(VK_SPACE) & 0x8000) {
            system("cls");
            std::string path, nextCodePath;

            readSettings(path, nextCodePath);

            ReCoding(path, nextCodePath);

            cout << "\nЧто бы скомпилировать код нажмите SPACE\nЧто бы выйти из программы нажмите ESCAPE";

            Sleep(1000);
        }
        if (GetKeyState(VK_ESCAPE) & 0x8000) break;
    }
    return 0;
}
