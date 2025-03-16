#include <iostream>
#include "Combi.h"
#include "Salesman.h"
#include <iomanip>
#include <ctime>
using namespace std;

#define N 10
#define INF 0x7fffffff

void TestSubsets()
{
    cout << endl << "Генератор множества всех подмножеств";
    char AA[][2] = { "A", "B", "C", "D" };
    cout << endl << "Исходное множество: { A, B, C, D }";
    combi::subset s1(sizeof(AA) / 2);
    int n = s1.getfirst();
    while (n >= 0)
    {
        cout << endl << "{ ";
        for (int i = 0; i < n; i++)
            cout << AA[s1.ntx(i)] << ((i < n - 1) ? ", " : " ");
        cout << "}";
        n = s1.getnext();
    }
    cout << endl << "Всего: " << s1.count() << endl;
}

void TestCombinations()
{
    cout << endl << "Генератор сочетаний";
    char AA[][2] = { "A", "B", "C", "D" };
    cout << endl << "Исходное множество: { A, B, C, D }";
    combi::comb c1(sizeof(AA) / 2, 2);
    int n = c1.getfirst();
    while (n >= 0)
    {
        cout << endl << "{ ";
        for (int i = 0; i < n; i++)
            cout << AA[c1.ntx(i)] << ((i < n - 1) ? ", " : " ");
        cout << "}";
        n = c1.getnext();
    }
    cout << endl << "Всего: " << c1.count() << endl;
}

void TestPermutations()
{
    cout << endl << "Генератор перестановок";
    char AA[][2] = { "A", "B", "C", "D" };
    cout << endl << "Исходное множество: { A, B, C, D }";
    combi::permutation p1(sizeof(AA) / 2);
    int n = p1.getfirst();
    while (n >= 0)
    {
        cout << endl << "{ ";
        for (int i = 0; i < n; i++)
            cout << AA[p1.ntx(i)] << ((i < n - 1) ? ", " : " ");
        cout << "}";
        n = p1.getnext();
    }
    cout << endl << "Всего: " << p1.count() << endl;
}

void TestArrangements()
{
    cout << endl << "Генератор размещений";
    char AA[][2] = { "A", "B", "C", "D" };
    cout << endl << "Исходное множество: { A, B, C, D }";
    combi::arr a1(sizeof(AA) / 2, 2);
    int n = a1.getfirst();
    while (n >= 0)
    {
        cout << endl << "{ ";
        for (int i = 0; i < n; i++)
            cout << AA[a1.ntx(i)] << ((i < n - 1) ? ", " : " ");
        cout << "}";
        n = a1.getnext();
    }
    cout << endl << "Всего: " << a1.count() << endl;
}

void generateDistances(int n, int* d)
{
    srand(time(0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                d[i * n + j] = 0;
            else
                d[i * n + j] = (rand() % 291) + 10;
        }
    }

    d[(rand() % n) * n + (rand() % n)] = INF;
    d[(rand() % n) * n + (rand() % n)] = INF;
    d[(rand() % n) * n + (rand() % n)] = INF;
}

void printDistances(int n, int* d)
{
    cout << "матрица расстояний" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (d[i * n + j] == INF)
                cout << setw(4) << "INF";
            else
                cout << setw(4) << d[i * n + j];
        }
        cout << endl;
    }
}

int main()
{
    setlocale(LC_ALL, "rus");

    cout << "Задания Лабораторной работы" << endl;

    cout << "Задание 1. Разобрать и разработать генератор подмножеств заданного множества." << endl;
    TestSubsets();

    cout << endl << "Задание 2. Разобрать и разработать генератор сочетаний." << endl;
    TestCombinations();

    cout << endl << "Задание 3. Разобрать и разработать генератор перестановок." << endl;
    TestPermutations();

    cout << endl << "Задание 4. Разобрать и разработать генератор размещений." << endl;
    TestArrangements();

    cout << endl << "Задание 5. Решить в соответствии с вариантом задачу и результат занести в отчет:" << endl;
    cout << "вариант 13: коммивояжера (расстояния сгенерировать случайным образом: 10 городов, расстояния 10 – 300 км, 3 расстояния между городами задать бесконечными);" << endl;

    int d[N * N];
    generateDistances(N, d);

    cout << "Задача коммивояжера" << endl;
    cout << "Количество городов: " << N << endl;
    printDistances(N, d);

    int r[N];
    int s = salesman(N, d, r);

    cout << "оптимальный маршрут: ";
    for (int i = 0; i < N; i++) cout << r[i] << "-->";
    cout << 0 << endl;
    cout << "длина маршрута: " << s << endl;

    cout << endl << "Задание 6. Исследовать зависимость времени вычисления необходимое для решения задачи (в соответствии с вариантом) от размерности задачи и результат в виде графика с небольшим пояснением занести в отчет:" << endl;
    cout << "вариант 13: коммивояжера (6 – 12 городов);" << endl;

    const int minCities = 6;
    const int maxCities = 12;

    for (int n = minCities; n <= maxCities; n++)
    {
        int* d = new int[n * n];
        generateDistances(n, d);

        cout << endl << "количество городов: " << n << endl;
        printDistances(n, d);

        int* r = new int[n];
        clock_t startTime = clock();
        int s = salesman(n, d, r);
        clock_t endTime = clock();

        double duration = double(endTime - startTime) / CLOCKS_PER_SEC;
        cout << "оптимальный маршрут: ";
        for (int i = 0; i < n; i++) cout << r[i] << "-->";
        cout << 0 << endl;
        cout << "длина маршрута: " << s << endl;
        cout << "время выполнения: " << duration << " секунд" << endl;

        delete[] d;
        delete[] r;
    }

    system("pause");
    return 0;
}