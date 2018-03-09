#include <iostream>
#include <fstream>

using namespace std;
void cypher(char key[1000], char message[1000], char square[30][30], char returnCypher[1000]);
int searchIndex(char letter);
int searchRowIndex(char letter, char keyLetter, char square[30][30]);
void decypher(char key[1000], char cypher[1000], char square[30][30], char returnPlain[1000]);


int main() {
	//make a viginere square
	char alphabet[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	char VSquare[30][30];

	int offset = 0;
	for (int i = 0; i < 27; i++) {
		for (int j = 0; j < 27; j++) {
			VSquare[i][j] = alphabet[(j + offset) % 26];
		}
		offset++;
	}

	int choice;
	cout << "File or Manual? (1.File\t2.Manual)\n";
	cin >> choice;
	if (choice == 1) {
		while (true) {
			int decision;
			cout << "Welcome to the file generator!\n";
			cout << "1. Create\t2. Decrypher\t3. quit\n";
			cin >> decision;
			if (decision == 1) {
				char fileName[1000];
				cout << "Enter file name\n";
				cin >> fileName;
				ofstream out;
				out.open(fileName);

				char key[1000];
				cout << "Enter a key (Letters only)\n";
				cin >> key;
				bool done = false;
				while (done == false) {
					char message[1000];
					cout << "Enter a message (Letters only)\n";
					cin >> message;
					int length = strlen(message);
					char cypherText[1000];
					cypher(key, message, VSquare, cypherText);

					for(int i = 0; i < length; i++){
						out << cypherText[i];
					}
					out << endl;

					int decision;
					cout << "Again? 1. yes\t2. no\n";
					cin >> decision;
					if (decision != 1)
						done = true;
				}
				out.close();
			}
			else if (decision == 2) {
				char fileName[1000];
				cout << "Enter file name\n";
				cin >> fileName;
				ifstream in;
				in.open(fileName);

				char key[1000];
				cout << "Enter a key (Letters only)\n";
				cin >> key;
				cout << "Decyphered text:\n";
				while (!in.eof()) {
					char message[1000];
					in >> message;
					int length = strlen(message);
					char cypherText[1000];
					decypher(key, message, VSquare, cypherText);

					for (int i = 0; i < length; i++) {
						cout << cypherText[i];
					}
					cout << endl;
				}
				in.close();
			}
			else {
				system("pause");
				return 0;
			}
		}
	}

	else {
		while (true) {
			int decision;
			cout << "Welcome to the Vigenere Cypher Program!\n";
			cout << "1. Cypher\t2. Decypher\t3. quit\n";
			cin >> decision;
			if (decision == 1) {
				char key[1000];
				char message[1000];
				cout << "Enter a key (Letters only)\n";
				cin >> key;
				cout << "Enter a message (Letters only)\n";
				cin >> message;
				char cypherText[1000];
				cypher(key, message, VSquare, cypherText);

				cout << "Cypher Text: ";
				int cypherLength = strlen(message);
				for (int i = 0; i < cypherLength; i++) {
					cout << cypherText[i];
				}
				cout << endl;
			}
			else if (decision == 2) {
				char key[1000];
				char message[1000];
				cout << "Enter a key (Letters only)\n";
				cin >> key;
				cout << "Enter a cyphered message (Letters only)\n";
				cin >> message;
				char cypherText[1000];
				decypher(key, message, VSquare, cypherText);

				cout << "Deypher Text: ";
				int cypherLength = strlen(message);
				for (int i = 0; i < cypherLength; i++) {
					cout << cypherText[i];
				}
				cout << endl;
			}
			else {
				system("pause");
				return 0;
			}
		}
	}
	system("pause");
	return 0;
}

void decypher(char key[1000], char cypher[1000], char square[30][30], char returnPlain[1000]) {
	char alphabet[26] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
	int keySize = strlen(key);
	int cypherSize = strlen(cypher);

	for (int i = 0; i < keySize; i++) {
		toupper(key[i]);
	}
	for (int i = 0; i < cypherSize; i++) {
		toupper(cypher[i]);
	}

	bool done = false;
	int c = 0;
	while (done == false) {
		int keyIndex = searchIndex(key[c%keySize]);
		int cypherIndex = searchIndex(cypher[c]);
		int plainTextIndex = searchRowIndex(cypher[c], key[c%keySize], square);
		returnPlain[c] = alphabet[plainTextIndex];

		if (c == cypherSize)
			done = true;
		c++;
	}
}

void cypher(char key[1000], char message[1000], char square[30][30], char returnCypher[1000]) {
	int keySize = strlen(key);
	int messageSize = strlen(message);

	for (int i = 0; i < keySize; i++) {
		toupper(key[i]);
	}
	for (int i = 0; i < messageSize; i++) {
		toupper(message[i]);
	}

	bool done = false;
	int c = 0;
	while (done == false) {
		int keyIndex = searchIndex(key[c%keySize]);
		int messageIndex = searchIndex(message[c]);
		returnCypher[c] = square[keyIndex][messageIndex];

		if (c == messageSize)
			done = true;
		c++;
	}
}

int searchIndex(char letter) {
	char alphabet[26] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };

	for (int i = 0; i < 26; i++) {
		if (alphabet[i] == letter)
			return i;
	}
	return -1;
}

int searchRowIndex(char letter, char keyLetter, char square[30][30]) {
	int keyIndex = 0;
	for (int i = 0; i < 26; i++) {
		if (square[0][i] == keyLetter)
			keyIndex = i;
	}
	for (int i = 0; i < 26; i++) {
		if (square[i][keyIndex] == letter)
			return i;
	}
	return -1;
}