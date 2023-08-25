#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


int get_length(char* string) {
	int k = 0;
	while (string[k] != '\0') {
		++k;
	}
	return k;
}

char translate_to_uppercase(char* string) { //char ����� ���������� ��� ������ � �� �������� ����� �����
	int i = 0;
	while (string[i] != '\0') {
		if (string[i] == ' ') {
			string[i] = '_';
		} else {
			string[i] = toupper(string[i]); // ����� ������� 
		}
		
		++i;
	}
	return 0;
}

char translate_to_lowercase(char* string) { //char ����� ���������� ��� ������ � �� �������� ����� �����
	int i = 0;
	while (string[i] != '\0') {
		if (string[i] == '_') {
			string[i] = ' ';
		}
		else {
			string[i] = tolower(string[i]); // ����� ������� 
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
	translate_to_uppercase(string); // ����� �� ������ ���������
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
	translate_to_lowercase(string); // ����� �� ������ ���������
}

int main() {
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
	printf("Enter shift: ");
	int shift;
	scanf("%d", &shift);
	printf("Enter mode: ");
	int temp = -1; // �� ���� �� � ������ ����� ������ ���� ��� ���� �������� ������ � ���� ��� �� ����� 0, 0 - ����������
	scanf("%d", &temp);
	if (temp == 0){
		encode(string, shift);
	}
	if (temp == 1) {
		decode(string, shift);
	}
	printf("%s", string);
	return 0;
}