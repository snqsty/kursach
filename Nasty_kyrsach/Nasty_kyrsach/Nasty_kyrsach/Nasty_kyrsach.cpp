#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

// Функция генерации перестановок (лексикографический порядок)
void permute(string str, int l, int r, vector<string>& result) {
    if (l == r) {
        result.push_back(str);
    }
    else {
        for (int i = l; i <= r; i++) {
            swap(str[l], str[i]);
            permute(str, l + 1, r, result);
            swap(str[l], str[i]);
        }
    }
}

// Функция генерации случайной строки
void generateRandomString(string& str, int length) {
    const string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (int i = 0; i < length; ++i) {
        str += charset[rand() % charset.length()];
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    srand(time(NULL));
    string inputString;
    int choice;

    do {
        cout << "Выберите способ ввода строки:\n";
        cout << "1. Ввести строку вручную\n";
        cout << "2. Сгенерировать случайную строку\n";
        cout << "0. Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        //Проверка на корректность ввода
        if (cin.fail()) {
            cout << "Некорректный ввод. Попробуйте снова.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 0) break;

        if (choice == 1) {
            cout << "Введите строку: ";
            cin.ignore();
            getline(cin, inputString);
        }
        else if (choice == 2) {
            int length;
            cout << "Введите длину случайной строки: ";
            cin >> length;
            if (cin.fail() || length <= 0) {
                cout << "Некорректная длина строки. Попробуйте снова.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            inputString = "";
            generateRandomString(inputString, length);
            cout << "Сгенерированная строка: " << inputString << endl;
        }
        else {
            cout << "Некорректный выбор. Попробуйте снова.\n";
        }


        if (!inputString.empty()) {
            vector<string> permutations;
            permute(inputString, 0, inputString.length() - 1, permutations);
            sort(permutations.begin(), permutations.end());

            cout << "Перестановки в лексикографическом порядке:\n";
            for (const string& p : permutations) {
                if (p > inputString) {
                    cout << p << endl;
                }
            }

            char saveChoice;
            cout << "Сохранить результаты в файл? (y/n): ";
            cin >> saveChoice;
            cin.ignore();

            if (tolower(saveChoice) == 'y') {
                string filename;
                cout << "Введите имя файла: ";
                getline(cin, filename);

                ofstream outfile(filename);
                if (outfile.is_open()) {
                    for (const string& p : permutations) {
                        if (p > inputString) {
                            outfile << p << endl;
                        }
                    }
                    outfile.close();
                    cout << "Результаты сохранены в файл " << filename << endl;
                }
                else {
                    cerr << "Ошибка при открытии файла!" << endl;
                }
            }

            permutations.clear();
        }
    } while (choice != 0);

    return 0;
}
