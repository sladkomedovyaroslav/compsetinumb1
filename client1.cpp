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



В БИНАРНОМ ВИДЕ 

#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <cstring>
using namespace std;

struct Person {
    char name[32];
    int marks[4];
};

int main() {
    setlocale(LC_ALL, "rus");

    const string requestFile = "C:/Users/s0177102/source/repos/file/REQUEST.bin";

    while (true) {
        string name;
        Person p = {};

        cout << "Введите фамилию студента: ";
        cin >> name;
        strncpy(p.name, name.c_str(), sizeof(p.name) - 1);

        cout << "Введите 4 оценки через пробел: ";
        for (int i = 0; i < 4; i++)
            cin >> p.marks[i];

        // Создаём бинарный файл клиента
        string path = "C:/Users/s0177102/source/repos/file/" + name + ".bin";
        ofstream fout(path, ios::binary | ios::trunc);
        fout.write(reinterpret_cast<char*>(&p), sizeof(Person));
        fout.close();

        // Добавляем фамилию в общий бинарный файл запросов
        ofstream foutReq(requestFile, ios::binary | ios::app);
        foutReq.write(p.name, sizeof(p.name)); // только имя
        foutReq.close();

        cout << "Запрос отправлен серверу. Ожидание ответа..." << endl;

        // Ожидаем, пока сервер запишет "ответ"
        bool answered = false;
        while (!answered) {
            Sleep(500);
            ifstream fin(path, ios::binary);
            if (!fin.is_open()) continue;

            fin.seekg(0, ios::end);
            streampos size = fin.tellg();
            if (size > sizeof(Person)) {
                fin.seekg(sizeof(Person)); // читаем часть после структуры
                string answer;
                getline(fin, answer, '\0');
                cout << answer << endl;
                answered = true;
            }
            fin.close();
        }

        cout << "----------------------------------\n";
    }

    return 0;
}
