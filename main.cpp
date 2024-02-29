#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <cstdlib>

using namespace std;
void ReCoding(string codeFile, string InputCode) {
    fstream code(codeFile);
    if (code.is_open()) {
        cout << "Your ease code open!" << endl;
        fstream CppCode(InputCode);
        if (CppCode.is_open()){
            cout << "Your CPP code open!" << endl;

            string action;
            string pin;
            string range;

            bool tab = false;

            while (std::getline(code >> std::ws, action)) {

                if (action == "конец") CppCode << "}" << endl;
                if (action == "установка") CppCode << "void setup(){ " << endl;

                if (action == "входной пин") {
                    std::getline(code >> std::ws, pin);
                    CppCode << "pinMode(" << pin << ", INPUT" << ");" << endl;
                }
                if (action == "выходной пин") {
                    std::getline(code >> std::ws, pin);
                    CppCode << "pinMode(" << pin << ", OUTPUT" << ");" << endl;
                }


                if (action == "основной код") CppCode << "void loop() {" << endl;

                if (action == "задержка") {
                    std::getline(code >> std::ws, range); 
                    CppCode << "delay (" << range << ");" << endl;
                }
                if (action == "подача") {
                    std::getline(code >> std::ws, pin);
                    std::getline(code >> std::ws, range);
                    CppCode << "digitalWrite( " << pin << ", " << range << ");" << endl;
                }
                if (action == "подача силы") {
                    std::getline(code >> std::ws, pin);
                    std::getline(code >> std::ws, range);
                    CppCode << "analoglWrite( " << pin << ", " << range << ");" << endl;
                }
                
                if (action == "конец кода") break;
            }
        }else{
            cout << "ERROR: YOUR CPP CODE NOT OPEN" << endl;
        }
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
