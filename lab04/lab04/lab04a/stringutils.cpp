#include <stdlib.h>
#include <string>
#include "stringutils.h";


const char DEFAULT_SYMBOLS[] = "abcdefghijklmnopqrstuvwxyz";


int len(char* str) {
	return strlen(str);
}


char* prefix(char* str, int n) {
	if (n > len(str)) {
		n = len(str);
	}
	char* copy = new char[n];
	memcpy(copy, str, n);
	copy[n] = '\0';
	return copy;
}


char* rstring(int n) {
	return rstring(n, (char*)DEFAULT_SYMBOLS);
}


char* rstring(int n, char* symbols) {
	char* random_string = new char[n];
	int nb_symbols = len(symbols);

	for (int i = 0; i < n; i++) {
		int c = rand() % nb_symbols;
		random_string[i] = symbols[c];
	}
	random_string[n] = '\0';

	return random_string;
}
