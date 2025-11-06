/ #include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
using namespace std;

struct Person {
    string name;
    int marks[4];
};

// Определяем результат
int evaluate(const Person& p) {
    bool has2 = false, has3 = false;
    int sum = 0;
    for (int i = 0; i < 4; i++) {
        if (p.marks[i] == 2) has2 = true;
        if (p.marks[i] == 3) has3 = true;
        sum += p.marks[i];
    }

    if (has2) return 0;      // отчислен
    if (has3) return 1;      // нет стипендии
    if (sum == 20) return 3; // повышенная
    return 2;                // обычная
}

int main() {
    setlocale(LC_ALL, "rus");
    cout << "Сервер запущен. Ожидание клиентов...\n";

    const string requestFile = "C:/Users/s0177102/source/repos/file/REQUEST.txt";

    string lastProcessed; // чтобы знать, какой запрос уже обработан

    while (true) {
        Sleep(500);

        ifstream fin(requestFile);
        if (!fin.is_open()) continue;

        string currentName;
        string lastName = "";
        while (fin >> currentName) { // читаем последнюю строку
            lastName = currentName;
        }
        fin.close();

        // Проверяем, появился ли новый запрос
        if (lastName.empty() || lastName == lastProcessed)
            continue;

        lastProcessed = lastName;

        // Открываем файл клиента (например, Ivanov.txt)
        string path = "C:/Users/s0177102/source/repos/file/" + lastName + ".txt";
        ifstream fperson(path);
        if (!fperson.is_open()) continue;

        Person p;
        p.name = lastName;
        for (int i = 0; i < 4; i++) fperson >> p.marks[i];
        fperson.close();

        int answer = evaluate(p);

        cout << "Обработан клиент " << p.name << " → результат " << answer << endl;

        // Записываем ответ в конец файла клиента
        ofstream fout(path, ios::app);
        fout << "\nОтвет: ";
        switch (answer) {
        case 0: fout << "Отчислен"; break;
        case 1: fout << "Нет стипендии"; break;
        case 2: fout << "Есть стипендия"; break;
        case 3: fout << "Повышенная стипендия"; break;
        }
        fout.close();
    }

    return 0;
}
