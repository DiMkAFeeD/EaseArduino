#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <cstdlib>
#include <sstream>

#define sizeACT 10

using namespace std;
void ReCoding(string codeFile, string InputCode) {
    fstream code(codeFile);
    if (code.is_open()) {
        cout << "Your ease code open!" << endl;
        fstream CppCode(InputCode, std::ios::out | std::ios::trunc);
        if (CppCode.is_open()){
            cout << "Your CPP code open!" << endl;


            string action;
            string range[10];

            int tabs = 0;
            int tab = 4;

            while (std::getline(code >> std::ws, action)) {
                std::istringstream iss(action);
                string act[sizeACT];
                for (int idx = 0; idx < sizeACT && iss >> act[idx]; idx++);

                if (act[0] == "все") tabs -= tab;
                for (int t = 0; t < tabs; t++) {
                    CppCode << " ";
                }
                if (act[0] == "все") CppCode << "}\n";

                if (act[0] == "установка") {
                    CppCode << "void setup(){\n";
                    tabs += tab;
                }
                if (act[0] == "пин" && act[1] == "мод") {
                    if (act[3] == "вход") range[0] = "INPUT";
                    if (act[3] == "выход") range[0] = "OUTPUT";
                    CppCode << "pinMode( " << act[2] << ", " << range[0] << ");\n";
                }
                if (act[0] == "переменная") {
                    if (act[1] == "число") {
                        range[0] = "int";
                        range[1] = act[4];
                    }
                    if (act[1] == "флаг") {
                        range[0] = "bool";
                        if (act[4] == "вкл") range[1] = "true";
                        if (act[4] == "выкл") range[1] = "false";
                    }
                    if (act[3] == "=") {
                        CppCode << range[0]<< " " << act[2] << " = " << range[1] << ";\n";
                    }
                    else {
                        CppCode << range[0] << " " << act[2] << ";\n";
                    }
                }
                if (act[0] == "задать") {
                    range[0] = act[2];
                    if (act[2] == "вход") {
                        if (act[3] == "силы") {
                            CppCode << act[1] << " = analogWrite( " << act[4] << " );\n";
                        }
                        else {
                            CppCode << act[1] << " = digitalWrite( " << act[3] << " );\n";
                        }
                    }
                    else {
                        CppCode << act[1] << " = " << act[2] << ";\n";
                    }
                }
                if (act[0] == "код") {
                    CppCode << "void loop(){\n";
                    tabs += tab;
                }

                if (act[0] == "задержка") {
                    CppCode << "delay( " << act[1] << " );\n";
                }

                if (act[0] == "подать") {
                    if (act[2] == "силу") {
                        CppCode << "analogWrite( " << act[1] << ", " << act[3] << " );\n";
                    }
                    else {
                        if (act[2] == "вкл") range[0] = "true";
                        else if (act[2] == "выкл") range[0] = "false";
                        else range[0] = act[2];
                        CppCode << "digitalWrite( " << act[1] << ", " << range[0] << " );\n";
                    }
                }
                if (act[0] == "если") {
                    CppCode << "if ( " << act[1] << " ){\n";
                    tabs += tab;
                }
                if (act[0] == "иначе") {
                    CppCode << "else{\n";
                    tabs += tab;
                }
                if (act[0] == "заменять") {
                    CppCode << "#define " << act[1] << " " << act[2] << endl;
                }
                if (act[0] == "конец") break;
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
