#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

class Clock
{
public:
    string model;
    string brand;
    string dialType;
    double price;

    Clock() {}

    Clock(string m, string b, string d, double p) : model(m), brand(b), dialType(d), price(p) {}
};

bool compareAscending(const Clock& a, const Clock& b) {
    return a.price < b.price;
}

bool compareDescending(const Clock& a, const Clock& b) {
    return a.price > b.price;
}

void writeToFile(const Clock clocks[], int countClocks, const string& filename) {
    if (countClocks == 0) {
        cout << "Нет данных!" << endl;
        return;
    }

    ofstream outFile(filename);

    if (!outFile.is_open()) {
        cout << "Не удалось открыть файл!" << endl;
        return;
    }

    for (int i = 0; i < countClocks; i++)
    {
        outFile << "Модель: " << clocks[i].model << endl
            << "Марка: " << clocks[i].brand << endl
            << "Вариант циферблата: " << clocks[i].dialType << endl
            << "Цена: " << clocks[i].price << endl;
    }

    outFile.close();
}

int main()
{
    setlocale(LC_ALL, "RU");
    system("chcp 1251");

    int countClocks = 0;
    int maxClocks;

    cout << "Введите кол-во часов: ";
    cin >> maxClocks;

    Clock* clocks = new Clock[maxClocks];

    int choice;
    while (true) {
        cout << "1. Добавить часы\n";
        cout << "2. Записать в файл\n";
        cout << "3. Выйти\n";
        cout << "Введите ваш выбор: ";
        cin >> choice;

        switch (choice)
        {
        case 1: {
            if (countClocks >= maxClocks) {
                cout << "Максимальное кол-во данных!" << endl;
                return 0;
            }

            string model, brand, dialType;
            double price;

            cout << "Введите модель: ";
            cin.ignore();
            getline(cin, model);
            cout << "Введите марку: ";
            cin >> brand;
            getline(cin, brand);
            cout << "Введите вариант циферблата: ";
            getline(cin, dialType);
            cout << "Введите цену: ";
            cin >> price;

            clocks[countClocks++] = Clock(model, brand, dialType, price);
            break;
        }
        case 2: {
            cout << "1. Сортировать по возрастанию\n";
            cout << "2. Сортировать по убыванию\n";
            cout << "Введите ваш выбор: ";
            cin >> choice;
            switch (choice)
            {
            case 1: {
                sort(clocks, clocks + countClocks, compareAscending);
                writeToFile(clocks, countClocks, "clocks.txt");
                cout << "Данные записаны в файл clocks.txt\n";
                break;
            }
            case 2: {
                sort(clocks, clocks + countClocks, compareDescending);
                writeToFile(clocks, countClocks, "clocks.txt");
                cout << "Данные записаны в файл clocks.txt\n";
                break;
            }
            default:
                break;
            }
            break;
        }
        case 3:
            return 0;
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
            break;
        }
    }

    delete[] clocks;

    return 0;
}
