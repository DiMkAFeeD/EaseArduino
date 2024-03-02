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

                if (act[0] == "���") tabs -= tab;
                for (int t = 0; t < tabs; t++) {
                    CppCode << " ";
                }
                if (act[0] == "���") CppCode << "}\n";

                if (act[0] == "���������") {
                    CppCode << "void setup(){\n";
                    tabs += tab;
                }
                if (act[0] == "���" && act[1] == "���") {
                    if (act[3] == "����") range[0] = "INPUT";
                    if (act[3] == "�����") range[0] = "OUTPUT";
                    CppCode << "pinMode( " << act[2] << ", " << range[0] << ");\n";
                }
                if (act[0] == "����������") {
                    if (act[1] == "�����") {
                        range[0] = "int";
                        range[1] = act[4];
                    }
                    if (act[1] == "����") {
                        range[0] = "bool";
                        if (act[4] == "���") range[1] = "true";
                        if (act[4] == "����") range[1] = "false";
                    }
                    if (act[3] == "=") {
                        CppCode << range[0]<< " " << act[2] << " = " << range[1] << ";\n";
                    }
                    else {
                        CppCode << range[0] << " " << act[2] << ";\n";
                    }
                }
                if (act[0] == "������") {
                    range[0] = act[2];
                    if (act[2] == "����") {
                        if (act[3] == "����") {
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
                if (act[0] == "���") {
                    CppCode << "void loop(){\n";
                    tabs += tab;
                }

                if (act[0] == "��������") {
                    CppCode << "delay( " << act[1] << " );\n";
                }

                if (act[0] == "������") {
                    if (act[2] == "����") {
                        CppCode << "analogWrite( " << act[1] << ", " << act[3] << " );\n";
                    }
                    else {
                        if (act[2] == "���") range[0] = "true";
                        else if (act[2] == "����") range[0] = "false";
                        else range[0] = act[2];
                        CppCode << "digitalWrite( " << act[1] << ", " << range[0] << " );\n";
                    }
                }
                if (act[0] == "����") {
                    CppCode << "if ( " << act[1] << " ){\n";
                    tabs += tab;
                }
                if (act[0] == "�����") {
                    CppCode << "else{\n";
                    tabs += tab;
                }
                if (act[0] == "��������") {
                    CppCode << "#define " << act[1] << " " << act[2] << endl;
                }
                if (act[0] == "�����") break;
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
