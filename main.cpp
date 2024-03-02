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
                
                if (act1 == "���") {
                    tabs -= tab;
                }
                for (int i = 0; i < tabs; i++) CppCode << " ";

                if (act1 == "���") {
                    CppCode << "}\n";
                }

                if (act1 == "�����" || act1 == "����") {
                    if (act1 == "�����") range = "int";
                    if (act1 == "����") range = "bool";

                    if (act3 == "=")
                        CppCode << range << " " << act2 << " = " << act4 << ";\n";
                    if (act3 == "")
                        CppCode << range << " " << act2 << ";\n";
                }
                else if (act1 == "����") {
                    CppCode << "if ( " << act2 << " ){\n";
                    tabs += tab;
                }
                else if (act1 == "������") {
                    if (act3 == "����") {
                        if (act4 == "����") {
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
                
                else if (act1 == "��������") {
                    CppCode << "#define " << act2 << " " << act3 << endl;
                }
                else if (act1 == "����������") {
                    CppCode << "#include" << " " << act2 << endl;
                }
                else if (act1 == "���������") {
                    CppCode << "void setup(){" << endl;
                    tabs += tab;
                }
                else if (act1 == "���" && act2 == "���") {
                    if (act4 == "����") range = "INPUT";
                    if (act4 == "�����") range = "OUTPUT";
                    CppCode << "pinMode( " << act3 << ", " << range << ");\n";
                }
                else if (act1 == "���") {
                    CppCode << "void loop(){\n";
                    tabs += tab;
                }
                else if (act1 == "��������") {
                    CppCode << "delay(" << act2 << ");\n";
                }
                else if (act1 == "��������") {
                    if (act3 == "��������" || act3 == "�������") {
                        if (act3 == "��������") range = "HIGH";
                        if (act3 == "�������") range = "LOW";
                        CppCode << "digitalWrite( " << act2 << ", " << range << ");\n";
                    } else{
                        CppCode << "analogWrite(" << act2 << ", " << act3 << ");\n";
                    }
                }
                else if (act1 == "�����") break;

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
        std::cout << "�� ������� ������� ���� settings.fs ��� ������" << std::endl;
    }
}

int main() {
    setlocale(LC_ALL, "RU");

    std::cout << "�����������, ���� �� �� ������ �++ �� ���� ��� ��������� �������." << endl;
    std::cout << "���� �� ������ ��� ������ ����������� ���� ���������� �� ������ \"documentation\" ��� �� ������� ������������. " << endl;
    std::cout << "��� �� ������ ����������� �������� \"start\"" << endl;
    std::cout << "��� �� ����� �� ��������� �������� \"exit\"" << endl << endl;
    string action;

    while (true){
        cin >> action;
        if (action == "documentation") {

            const char* filePath = "start documentation\\documentation.html";

            int exitCode = system(filePath);

            if (exitCode == 0) {
                std::cout << "���� ������� �������" << std::endl;
            }
            else {
                std::cerr << "������ ������� �����" << std::endl;
            }

        }
        else if (action == "exit") exit(0);
        else if (action == "start") break;
        else {
            std::cout << "����������� �������: " << action << endl;
        }
    }

    system("cls");
    cout << "��� �� �������������� ��� ������� SPACE\n��� �� ����� �� ��������� ������� ESCAPE";

    while (true) {
        if (GetKeyState(VK_SPACE) & 0x8000) {
            system("cls");
            std::string path, nextCodePath;

            readSettings(path, nextCodePath);

            ReCoding(path, nextCodePath);

            cout << "\n��� �� �������������� ��� ������� SPACE\n��� �� ����� �� ��������� ������� ESCAPE";

            Sleep(1000);
        }
        if (GetKeyState(VK_ESCAPE) & 0x8000) break;
    }
    return 0;
}
