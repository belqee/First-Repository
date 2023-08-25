#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum error_flag {
	toupper_error,
	tolower_error
} flag;

char translate_to_uppercase(char* string, flag* error_code) { //char чтобы возвращать код ошибки и не занимать много места
	int i = 0;
	while (string[i] != '\0') {
		if (string[i] == ' ') {
			string[i] = '_';
		} else {
			string[i] = toupper(string[i]); // потом проверю 
			if (string[i] < 65 || string[i] > 90) {
				*error_code = toupper_error;
			}
		}
		
		++i;
	}
	return 0;
}

char translate_to_lowercase(char* string, flag* error_code) { //char чтобы возвращать код ошибки и не занимать много места
	int i = 0;
	while (string[i] != '\0') {
		if (string[i] == '_') {
			string[i] = ' ';
		}
		else {
			string[i] = tolower(string[i]);
			if (string[i] < 97 || string[i] > 122) {
				*error_code = tolower_error;
			}
		}

		++i;
	}
	return 0;
}

int find_number(char a, char* alphabet) {
	int i = 0;
	while (a != alphabet[i]) {
		++i;
	}
	return i;
}

char encode(char* string, int current_shift) {
	char alphabet[37] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_"; // k = 37
	translate_to_uppercase(string); // потом на ошибку проверить
	int i = 0;
	while (string[i] != '\0') {
		string[i] = alphabet[1 + (find_number(string[i], alphabet) + current_shift) % 37];
		++current_shift;
		current_shift = current_shift % 37;
		++i;
	}
	return 0;
}

char decode(char* string, int current_shift) {
	char alphabet[37] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_";
	int i = 0;
	while (string[i] != '\0') {
		string[i] = alphabet[(find_number(string[i], alphabet) - current_shift - 1 + 37) % 37];
		++current_shift;
		current_shift = current_shift % 37;
		++i;
	}
	translate_to_lowercase(string); // потом на ошибку проверить
}

int main(int argc, char** argv) {
	int param = atoi(argv[1]);
	if (argc != 2) {
		printf("Error first");
		return 1;
	}
	printf("Enter text: ");
	char string[50] = "";
	int a = -1;
	int i = 0;
	while (a != '\n' && i < 50) {
		a = getchar();
		if (a == '\n') {
			string[i] = '\0';
		} else string[i] = a;
		++i;
	}
	if (a == -1){
		printf("Error during reading");
	}
	printf("Enter shift: ");
	int shift;
	int code = 0;
	code = scanf("%d", &shift);
	if (code == EOF || code <= 0 ) {
		perror("Scanf error: ");
		return 1;
	}
	if (param == 0){
		encode(string, shift);
	}
	if (param == 1) {
		decode(string, shift);
	}
	printf("%s", string);
	return 0;
}