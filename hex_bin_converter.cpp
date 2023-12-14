#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <bitset>
#include <iomanip>

using namespace std;

// Функция для преобразования hex(16) в binary(2)
string hexToBinary(const string& hexString) {
    stringstream ss;
    ss << hex << hexString;
    
    unsigned int num;
    ss >> num;

    bitset<32> bits(num);
    return bits.to_string();
}

// Функция для преобразования binary(2) в hex(16)
string binaryToHex(const string& binaryString) {
    if (binaryString.length() % 8 != 0) {
        cerr << "Неверная длина двоичной строки." << endl;
        return "";
    }

    stringstream ss;
    for (size_t i = 0; i < binaryString.length(); i += 8) {
        string byte = binaryString.substr(i, 8);
        bitset<8> bits(byte);
        ss << setw(2) << setfill('0') << hex << uppercase << bits.to_ulong();
    }

    return ss.str();
}

int main() {
    string inputFileName, outputFileName;
    
    // Ввод исходного файла
    cout << "Введите имя файла для преобразования: ";
    cin >> inputFileName;

    // Ввод файла-результата
    cout << "Введите имя файла-результата: ";
    cin >> outputFileName;

    ifstream inputFile(inputFileName, ios::binary);
    ofstream outputFile(outputFileName);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cerr << "Ошибка открытия файлов." << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line)) {
        if (line.empty()) {
            cerr << "Неверный формат файла." << endl;
            return 1;
        }

        // Преобразование данных из 16-ричного в двоичный формат
        string hexData = line;
        string binaryData = hexToBinary(hexData);

        // Вывод в файл-результат
        outputFile << binaryData << endl;
    }

    cout << "Преобразование завершено успешно." << endl;

    inputFile.close();
    outputFile.close();

    return 0;
}
