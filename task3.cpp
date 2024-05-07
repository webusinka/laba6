// -1.14(x1) - 0.04(x2) + 0.21(x3) - 18.0(x4) = -1.24
//  0.25(x1) - 1.23(x2) - 0.17(x3) - 0.09(x4) = 0.95
// -0.21(x1) - 0.17(x2) + 0.80(x3) - 0.13(x4) = 2.56
//  0.15(x1) - 1.31(x2) + 0.06(x3) + 0.95(x4) = -1.14

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

// Функция для обмена двух строк матрицы
void swapRows(vector<vector<double>>& matrix, int r1, int r2) {
    swap(matrix[r1], matrix[r2]);
}

int main(){
    int n = 4;  // Количество уравнений и неизвестных

    // Создаем матрицу коэффициентов и вектор свободных членов
    vector<vector<double>> matrix = {
        {-1.14, -0.04,  0.21, -18.0, -1.24},
        { 0.25, -1.23, -0.17, -0.09,  0.95},
        {-0.21, -0.17,  0.80, -0.13,  2.56},
        { 0.15, -1.31,  0.06,  0.95, -1.14}
    };

    //создаем вектор решения, размером кол-ва неизвестных
    vector<double> solution(n);

    // Вывод решения
    cout << "Решение системы уравнений:" << endl;
    for (double x : solution) {
        cout << fixed << setprecision(2) << x << " ";
    }
    cout << endl;

    return 0;
}