#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    const string requestFile = "C:/Users/s0177102/source/repos/file/REQUEST.txt";

    while (true) {
        string name;
        int marks[4];

        cout << "Введите фамилию студента: ";
        cin >> name;
        cout << "Введите 4 оценки через пробел: ";
        for (int i = 0; i < 4; i++)
            cin >> marks[i];

        // Создаём файл клиента
        string path = "C:/Users/s0177102/source/repos/file/" + name + ".txt";
        ofstream fout(path);
        for (int i = 0; i < 4; i++)
            fout << marks[i] << " ";
        fout.close();

        // Добавляем фамилию в общий файл запросов
        ofstream foutReq(requestFile, ios::app);
        foutReq << name << endl;
        foutReq.close();

        cout << "Запрос отправлен серверу. Ожидание ответа..." << endl;

        // Ожидаем, пока сервер запишет "Ответ:"
        string line;
        bool answered = false;
        while (!answered) {
            Sleep(500);
            ifstream fin(path);
            while (getline(fin, line)) {
                if (line.find("Ответ:") != string::npos) {
                    cout << line << endl;
                    answered = true;
                    break;
                }
            }
            fin.close();
        }

        cout << "----------------------------------\n";
    }

    return 0;
}
