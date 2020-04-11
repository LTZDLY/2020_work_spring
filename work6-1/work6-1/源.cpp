#include<iostream>
#include<string>
#define NUM_LETTER 26

bool input_check(int &dif);
void change_letter(int dif, std::string &text);

int main() {
	///Regardless of the input beyond the range of int
	int dif = 0;//The secret key
	std::string input_text;
	std::cout << "Please enter the secret key." << std::endl;
	while (input_check(dif));
	std::cout << "Please enter the text that needs to be encrypted." << std::endl;
	while (input_text.size() == 0)std::getline(std::cin, input_text);
	change_letter(dif, input_text);
	std::cout << input_text;
	return 0;
}

bool input_check(int &dif) {
	std::cin >> dif;
	if (std::cin.fail()) {
		std::cout << "Invalue input detected, please try again." << std::endl;
		std::cin.clear();
		std::cin.ignore();
		return true;
	}
	else {
		while (dif < 0) dif += NUM_LETTER;
		while (dif > NUM_LETTER) dif -= NUM_LETTER;
		return false;
	}
}
void change_letter(int dif, std::string &text) {
	for (unsigned int i = 0; i < text.size(); i++) {
		//Change the uppercase letter
		if (text[i] >= 'A' && text[i] <= 'Z') {
			text[i] += dif;
			if (text[i] > 'Z')text[i] -= NUM_LETTER;
		}
		//Change the lowercase letter
		else if (text[i] >= 'a' && text[i] <= 'z') {
			text[i] += dif;
			if (text[i] > 'z')text[i] -= NUM_LETTER;
		}
	}
}