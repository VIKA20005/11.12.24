#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

// Функція для приведення слова до нижнього регістру
string toLowerCase(const string& word) {
    string result = word;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Функція для видалення пунктуації з слова
string removePunctuation(const string& word) {
    string result;
    for (char ch : word) {
        if (isalnum(ch)) { // Залишаємо тільки літери та цифри
            result += ch;
        }
    }
    return result;
}

int main() {
    // Відкрити вхідний файл
    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cerr << "Помилка: Не вдалося відкрити файл input.txt" << endl;
        return 1;
    }

    // Частотний словник
    map<string, int> wordFrequency;
    string line, word;

    // Обробка рядків тексту
    while (getline(inputFile, line)) {
        stringstream ss(line);
        while (ss >> word) {
            word = removePunctuation(toLowerCase(word));
            if (!word.empty()) {
                wordFrequency[word]++;
            }
        }
    }

    inputFile.close();

    // Перевірка наявності слів у словнику
    if (wordFrequency.empty()) {
        cout << "Файл порожній або не містить слів." << endl;
        return 0;
    }

    // Виведення частотного словника
    cout << "Частотний словник слів:\n";
    for (const auto& entry : wordFrequency) {
        cout << entry.first << ": " << entry.second << endl;
    }

    // Пошук найбільш часто вживаного слова
    string mostFrequentWord;
    int maxFrequency = 0;
    for (const auto& entry : wordFrequency) {
        if (entry.second > maxFrequency) {
            maxFrequency = entry.second;
            mostFrequentWord = entry.first;
        }
    }

    cout << "\nНайчастіше слово: " << mostFrequentWord
        << " (" << maxFrequency << " разів)\n";

    // Запис результатів у вихідний файл
    ofstream outputFile("output.txt");
    if (!outputFile.is_open()) {
        cerr << "Помилка: Не вдалося створити файл output.txt" << endl;
        return 1;
    }

    outputFile << "Частотний словник слів:\n";
    for (const auto& entry : wordFrequency) {
        outputFile << entry.first << ": " << entry.second << endl;
    }
    outputFile << "\nНайчастіше слово: " << mostFrequentWord
        << " (" << maxFrequency << " разів)\n";

    outputFile.close();
    cout << "\nРезультати записані у файл output.txt\n";

    return 0;
}