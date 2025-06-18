#include <ctime>
#include <time.h>
#include <iomanip>
#include <iostream>
#include "stringutils.h"
#include "Levenshtein.h"
using namespace std;


void main() {
	setlocale(LC_ALL, "rus");
	srand(time(nullptr));

	char* s1 = rstring(300);
	char* s2 = rstring(150);

	double ks[] = {1.0/25, 1.0/20, 1.0/15, 1.0/10, 1.0/5, 1.0/2, 1.0};

	int ls1 = len(s1);
	int ls2 = len(s2);

	int lps1, lps2;
	char* ps1, * ps2;
	clock_t lr1, lr2, ld1, ld2;

	cout << "s1 (" << len(s1) << "): " << s1 << endl << endl;
	cout << "s2 (" << len(s2) << "): " << s2 << endl << endl;
	cout << "----- Расстояние Левенштейна -----" << endl << endl;
	cout << "-- Длина -- Рекурсия -- Дин. Програм. ---" << endl;

	for (double k : ks) {
		lps1 = round(k * ls1);
		lps2 = round(k * ls2);
		ps1 = prefix(s1, lps1);
		ps2 = prefix(s2, lps2);

		lr1 = clock();
		levenshtein_r(lps1, ps1, lps2, ps2);
		lr2 = clock();
		ld1 = clock();
		levenshtein(lps1, ps1, lps2, ps2);
		ld2 = clock();

		cout << right << setw(3) << lps1 << "|" << setw(3) << lps2
			<< "        " << left << setw(10) << (lr2 - lr1)
			<< "   " << setw(10) << (ld2 - ld1) << endl;
	}

	system("pause");
}
