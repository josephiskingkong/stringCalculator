#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <vector>
#include <windows.h>

using namespace std;

void setCursorPosition(int x, int y) {
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}

void printNumber (string number) {
	
    int flag = 1;
    for (int numberIndex = 0; numberIndex < number.length() - 1; ++numberIndex) {
    	if (number[numberIndex] != '0') {
        	flag = 0;
    	}
    	if (flag == 0) {
      		cout << number[numberIndex];
    	}
  	}
  	cout << number[number.length() - 1];
}

int comparison(string firstNumber, string secondNumber, char firstNumberSign, char secondNumberSign) {
	
  	if (firstNumberSign == '+' && secondNumberSign == '-') {
    	printNumber(firstNumber);
   		cout << " > " << secondNumber;
    	return 0;
  	}
  	if (firstNumberSign == '-' && secondNumberSign == '+') {
    	printNumber(firstNumber);
    	cout << " < " << secondNumber;
    	return 0;
  	}
  	if (firstNumberSign == '+') {
    	if (firstNumber > secondNumber) {
    		printNumber(firstNumber);
    		cout << " > " << secondNumber;
    	} else if (firstNumber < secondNumber) {
      		printNumber(firstNumber);
      		cout << " < " << secondNumber;    
    	} else {
      		cout << firstNumber << " = " << secondNumber;
    	}
  	} else {
    	if (firstNumber > secondNumber) {
    		cout << secondNumberSign;
    		printNumber(firstNumber);
      		cout << " < " << secondNumber;
    	} else if (firstNumber < secondNumber) {
      		cout << firstNumberSign;
      		printNumber(firstNumber);
      		cout << " > " << secondNumber;    
    	} else {
      		cout << firstNumber << " = " << secondNumber;
    	}
  	}
  	return 0;
}

string sum(string firstNumber, string secondNumber) {
	
  	for (int numberIndex = firstNumber.length() - 1; numberIndex > 0; --numberIndex){
    	char result = firstNumber[numberIndex] + secondNumber[numberIndex] - 48;
    	if (result > 57) {
      		firstNumber[numberIndex - 1] += 1;
      		firstNumber[numberIndex] = result - 10;
    	} else {
      	firstNumber[numberIndex] = result;
    	}
  	}
  	
  	char result = firstNumber[0] + secondNumber[0] - 48;
  	if (result > 57) {
    	firstNumber[0] = result - 10;
    	firstNumber = '1' + firstNumber;
  	} else {
    firstNumber[0] = result;
  	}
  	
  	return firstNumber;
}

string subtraction(string firstNumber, string secondNumber) {
	
  	while (secondNumber.length() < firstNumber.length()) {
    	secondNumber = "0" + secondNumber;
  	}
  	
  	while (firstNumber.length() < secondNumber.length()) {
    	firstNumber = "0" + firstNumber;
  	}
  	
  	for (int numberIndex = secondNumber.length() - 1; numberIndex >= 0; --numberIndex) {
    	if (firstNumber[numberIndex] >= secondNumber[numberIndex]) {
    		firstNumber[numberIndex] = firstNumber[numberIndex] - secondNumber[numberIndex] + 48;
    	} else {
      		int reservePosition = numberIndex - 1;
      		while (firstNumber[reservePosition] == '0') {
        		firstNumber[reservePosition] = '9';
        		reservePosition -= 1;
      		}
      		firstNumber[reservePosition] = firstNumber[reservePosition] - 1;
      		firstNumber[numberIndex] = 58 - (secondNumber[numberIndex] - firstNumber[numberIndex]);
    	}
  	}
  	
  	while ((firstNumber[0] == '0') && (firstNumber.length() > 1)) {
    	firstNumber.replace(0, 1, "");
  	}
  	
  	return firstNumber;
}

void multiply(string firstNumber, string secondNumber, char firstNumberSign, char secondNumberSign) {
	
  	int nearResult;
  	int result[firstNumber.length() + secondNumber.length()];
  	
  	for (int numberIndex = 0; numberIndex < firstNumber.length() + secondNumber.length(); ++numberIndex) {
    	result[numberIndex] = 0;
  	}
  	
  	for (int firstDigit = firstNumber.length() - 1; firstDigit >= 0; --firstDigit) {
    	for (int secondDigit = secondNumber.length() - 1; secondDigit >= 0; --secondDigit) {
      		nearResult = (firstNumber[firstDigit] - 48) * (secondNumber[secondDigit] - 48) + result[firstDigit + secondDigit + 1]; // Numbers starts from 48 in ASCII
      		result[firstDigit + secondDigit] += nearResult / 10;
      		result[firstDigit + secondDigit + 1] = nearResult % 10;
    	}
  	}
  	
  	if (firstNumberSign != secondNumberSign) cout << "-";
  	int flag = 1;
  	
  	for (int numberIndex = 0; numberIndex < firstNumber.length() + secondNumber.length() - 1; ++numberIndex) {
    	if (result[numberIndex] != 0) flag = 0;
    	if (flag == 0) cout << result[numberIndex];
  	}
  	
  	cout << result[firstNumber.length() + secondNumber.length() - 1];
}

void division(string firstNumber, string secondNumber, char firstNumberSign, char secondNumberSign) {
  	
	vector <int> result;
  	
  	while ((firstNumber.length() > secondNumber.length()) || ((firstNumber >= secondNumber) && (firstNumber.length() == secondNumber.length()))) {
    	string partOfFirst;
    	partOfFirst.assign(firstNumber, 0, secondNumber.length());
    	if (partOfFirst < secondNumber) {
      		partOfFirst.assign(firstNumber, 0, secondNumber.length() + 1);
    	}
    	firstNumber.assign(firstNumber.size(), partOfFirst.size());
    	result.push_back(1);
    	partOfFirst = subtraction(partOfFirst, secondNumber);
    	while ((partOfFirst.length() > secondNumber.length()) || ((partOfFirst.length() == secondNumber.length()) && (partOfFirst >= secondNumber))) {
      		partOfFirst = subtraction(partOfFirst, secondNumber);
      		result[result.size() - 1] += 1;
    	}
    	firstNumber = partOfFirst + firstNumber;
  	}
  	
  	if (firstNumberSign != secondNumberSign) cout << "-";
  	if (result.size() == 0) cout << "0";
  	for (int numberIndex = 0; numberIndex < result.size(); ++numberIndex) {
    	cout << result[numberIndex];
  	}
}

int main() {
	
  	string firstNumber, secondNumber;
  	char action;
  	cout << "Available actions: +, -, *, /, ? (use for comparison).\n" << "Enter a mathematical expression: ";
  	cin >> firstNumber >> action >> secondNumber;
  	if (action != '?') {
  		setCursorPosition(firstNumber.size() + secondNumber.size() + 36, 1);
  		cout << " = ";
  	} else {
  		if (action == '?') setCursorPosition(33, 1);
  	}
  	char firstNumberSign = '+';
  	char secondNumberSign = '+';
  	if (firstNumber[0] == '-') {
    	firstNumberSign = '-';
    	firstNumber.erase(0, 1); 
  	}
  	if (secondNumber[0] == '-') {
    	secondNumberSign = '-';
    	secondNumber.erase(0, 1);
  	}
  
  	if (action == '*') {
    	multiply(firstNumber, secondNumber, firstNumberSign, secondNumberSign);
    	cout << "\n";
    	system("pause");
    	return 0;
  	}
  	if (action == '/') {
    	if (secondNumber == "0") {
      		cout << "Wrong, you cannot divide by 0.";
      		cout << "\n";
      		system("pause");
      		return 0;
    	}
    	division(firstNumber, secondNumber, firstNumberSign, secondNumberSign);
    	cout << "\n";
    	system("pause");
    	return 0;
  	}
  
  	while (secondNumber.length() < firstNumber.length()) {
    	secondNumber = "0" + secondNumber;
  	}
  	while (firstNumber.length() < secondNumber.length()) {
    	firstNumber = "0" + firstNumber;
  	}
  
  	if (action == '?') {
    	comparison(firstNumber, secondNumber, firstNumberSign, secondNumberSign);
    	cout << "\n";
    	system("pause");
    	return 0;
  	}
  
  	bool switchSign = false;
  	if (firstNumber < secondNumber) {
    	string reserveNumber = secondNumber;
    	secondNumber = firstNumber;
    	firstNumber = reserveNumber;
    	switchSign = true;
  	}
    
  	if (action == '+') {
    	if (firstNumberSign == secondNumberSign) {
    		if (firstNumberSign == '-') cout << '-';
    } else if (((firstNumberSign == '-') && (!switchSign)) || ((firstNumberSign == '+') && (switchSign))) {
      cout << '-';
    }
    	if (firstNumberSign == secondNumberSign) {
      		cout << sum(firstNumber, secondNumber);
    	} else {
      		cout << subtraction(firstNumber, secondNumber);
    	}
    	cout << "\n";
    	system("pause");
    	return 0;
  	}
  	
  	if (action == '-') {
    	if (firstNumberSign == secondNumberSign) {
      		string result = subtraction(firstNumber, secondNumber);
      		if ((((firstNumberSign == '+') && switchSign) || ((firstNumberSign == '-') && !switchSign)) && (result != "0")) cout << '-';
      	cout << result;
      	cout << "\n";
      	system("pause");
      	return 0;
    } else {
      	string result = sum(firstNumber, secondNumber);
      	if (firstNumberSign == '-') cout << '-';
      	cout << result;
      	cout << "\n";
      	system("pause");
      	return 0;
    	}
  	}
  	cout << "Error, unavailable action.";
  	return 0;
}
