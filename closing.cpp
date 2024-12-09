#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void loadData(const string& filename, map<string, vector<string>>& data) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Не вдалося відкрити файл!" << endl;
        return;
    }

    string country, city;
    while (file >> country >> city) {
        data[country].push_back(city);
    }

    file.close();
}

void saveData(const string& filename, const map<string, vector<string>>& data) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Не вдалося відкрити файл!" << endl;
        return;
    }

    for (const auto& [country, cities] : data) {
        for (const auto& city : cities) {
            file << country << " " << city << endl;
        }
    }

    file.close();
}

void displayData(const map<string, vector<string>>& data) {
    for (const auto& [country, cities] : data) {
        cout << "Країна: " << country << endl;
        cout << "Міста: ";
        for (const auto& city : cities) {
            cout << city << " ";
        }
        cout << endl;
    }
}

int countCities(const map<string, vector<string>>& data) {
    int count = 0;
    for (const auto& [_, cities] : data) {
        count += cities.size();
    }
    return count;
}

int main() {
    map<string, vector<string>> data;

    string filename = "data.txt";
    loadData(filename, data);

    int choice;
    do {
        cout << "\nМеню:\n";
        cout << "1. Відобразити всі країни та міста\n";
        cout << "2. Додати країну або місто\n";
        cout << "3. Видалити країну або місто\n";
        cout << "4. Змінити назву міста\n";
        cout << "5. Підрахувати кількість міст\n";
        cout << "6. Зберегти дані у файл\n";
        cout << "0. Вийти\n";
        cout << "Ваш вибір: ";
        cin >> choice;

        switch (choice) {
        case 1:
            displayData(data);
            break;
        case 2: {
            string country, city;
            cout << "Введіть назву країни: ";
            cin >> country;
            cout << "Введіть назву міста: ";
            cin >> city;
            data[country].push_back(city);
            break;
        }
        case 3: {
            string country, city;
            cout << "Введіть назву країни: ";
            cin >> country;
            cout << "Введіть назву міста (або залиште порожнім для видалення країни): ";
            cin.ignore();
            getline(cin, city);

            if (city.empty()) {
                data.erase(country);
            } else {
                auto& cities = data[country];
                cities.erase(remove(cities.begin(), cities.end(), city), cities.end());
                if (cities.empty()) {
                    data.erase(country);
                }
            }
            break;
        }
        case 4: {
            string country, oldCity, newCity;
            cout << "Введіть назву країни: ";
            cin >> country;
            cout << "Введіть назву міста для заміни: ";
            cin >> oldCity;
            cout << "Введіть нову назву міста: ";
            cin >> newCity;

            auto& cities = data[country];
            replace(cities.begin(), cities.end(), oldCity, newCity);
            break;
        }
        case 5:
            cout << "Загальна кількість міст: " << countCities(data) << endl;
            break;
        case 6:
            saveData(filename, data);
            break;
        case 0:
            cout << "Вихід із програми." << endl;
            break;
        default:
            cout << "Невірний вибір. Спробуйте ще раз." << endl;
        }
    } while (choice != 0);

    return 0;
}
