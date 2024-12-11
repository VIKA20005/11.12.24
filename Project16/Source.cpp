#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

// ������� ��� ���������� ����� �� �������� �������
string toLowerCase(const string& word) {
    string result = word;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// ������� ��� ��������� ���������� � �����
string removePunctuation(const string& word) {
    string result;
    for (char ch : word) {
        if (isalnum(ch)) { // �������� ����� ����� �� �����
            result += ch;
        }
    }
    return result;
}

int main() {
    // ³������ ������� ����
    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cerr << "�������: �� ������� ������� ���� input.txt" << endl;
        return 1;
    }

    // ��������� �������
    map<string, int> wordFrequency;
    string line, word;

    // ������� ����� ������
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

    // �������� �������� ��� � ��������
    if (wordFrequency.empty()) {
        cout << "���� ������� ��� �� ������ ���." << endl;
        return 0;
    }

    // ��������� ���������� ��������
    cout << "��������� ������� ���:\n";
    for (const auto& entry : wordFrequency) {
        cout << entry.first << ": " << entry.second << endl;
    }

    // ����� ������� ����� ��������� �����
    string mostFrequentWord;
    int maxFrequency = 0;
    for (const auto& entry : wordFrequency) {
        if (entry.second > maxFrequency) {
            maxFrequency = entry.second;
            mostFrequentWord = entry.first;
        }
    }

    cout << "\n��������� �����: " << mostFrequentWord
        << " (" << maxFrequency << " ����)\n";

    // ����� ���������� � �������� ����
    ofstream outputFile("output.txt");
    if (!outputFile.is_open()) {
        cerr << "�������: �� ������� �������� ���� output.txt" << endl;
        return 1;
    }

    outputFile << "��������� ������� ���:\n";
    for (const auto& entry : wordFrequency) {
        outputFile << entry.first << ": " << entry.second << endl;
    }
    outputFile << "\n��������� �����: " << mostFrequentWord
        << " (" << maxFrequency << " ����)\n";

    outputFile.close();
    cout << "\n���������� ������� � ���� output.txt\n";

    return 0;
}