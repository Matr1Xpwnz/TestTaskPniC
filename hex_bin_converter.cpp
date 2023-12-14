#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <bitset>
#include <iomanip>

using namespace std;

// ������� ��� �������������� hex(16) � binary(2)
string hexToBinary(const string& hexString) {
    stringstream ss;
    ss << hex << hexString;
    
    unsigned int num;
    ss >> num;

    bitset<32> bits(num);
    return bits.to_string();
}

// ������� ��� �������������� binary(2) � hex(16)
string binaryToHex(const string& binaryString) {
    if (binaryString.length() % 8 != 0) {
        cerr << "�������� ����� �������� ������." << endl;
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
    
    // ���� ��������� �����
    cout << "������� ��� ����� ��� ��������������: ";
    cin >> inputFileName;

    // ���� �����-����������
    cout << "������� ��� �����-����������: ";
    cin >> outputFileName;

    ifstream inputFile(inputFileName, ios::binary);
    ofstream outputFile(outputFileName);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cerr << "������ �������� ������." << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line)) {
        if (line.empty()) {
            cerr << "�������� ������ �����." << endl;
            return 1;
        }

        // �������������� ������ �� 16-������� � �������� ������
        string hexData = line;
        string binaryData = hexToBinary(hexData);

        // ����� � ����-���������
        outputFile << binaryData << endl;
    }

    cout << "�������������� ��������� �������." << endl;

    inputFile.close();
    outputFile.close();

    return 0;
}
