#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// Функция для выбора главного элемента в текущем столбце
int findPivot(const vector<vector<double>>& matrix, int col, int start_row) {
    double max_val = 0.0;
    int pivot_row = start_row;

    for (int i = start_row; i < matrix.size(); i++) {
        if (fabs(matrix[i][col]) > max_val) {
            max_val = fabs(matrix[i][col]);
            pivot_row = i;
        }
    }
    
    return pivot_row;
}

// Функция для решения системы линейных уравнений
vector<double> solveLinearSystem(vector<vector<double>>& matrix) {
    int n = matrix.size();
    int m = matrix[0].size() - 1;

    // Прямой ход
    for (int col = 0; col < m; col++) {
        int pivot_row = findPivot(matrix, col, col);
        if (pivot_row != col) {
            // Меняем местами строки, если необходимо
            for (int i = 0; i < m; i++) {
                double temp = matrix[col][i];
                matrix[col][i] = matrix[pivot_row][i];
                matrix[pivot_row][i] = temp;
            }
        }

        // Элементарные преобразования для получения нулей под главным элементом
        for (int i = col + 1; i < n; i++) {
            double factor = matrix[i][col] / matrix[col][col];
            for (int j = col; j < m + 1; j++) {
                matrix[i][j] -= factor * matrix[col][j];
            }
        }
    }

    // Обратный ход
    vector<double> solution(m, 0.0);
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0.0;
        for (int j = i + 1; j < m; j++) {
            sum += matrix[i][j] * solution[j];
        }
        solution[i] = (matrix[i][m] - sum) / matrix[i][i];
    }

    return solution;
}

// -1.14(x1) - 0.04(x2) + 0.21(x3) - 18.0(x4) = -1.24
//  0.25(x1) - 1.23(x2) - 0.17(x3) - 0.09(x4) = 0.95
// -0.21(x1) - 0.17(x2) + 0.80(x3) - 0.13(x4) = 2.56
//  0.15(x1) - 1.31(x2) + 0.06(x3) + 0.95(x4) = -1.14

int main() {
    system("chcp 65001");
    
    vector<vector<double>> matrix = {
        {-1.14, -0.04,  0.21, -18.0, -1.24},
        { 0.25, -1.23, -0.17, -0.09,  0.95},
        {-0.21, -0.17,  0.80, -0.13,  2.56},
        { 0.15, -1.31,  0.06,  0.95, -1.14}
    };

    vector<double> solution = solveLinearSystem(matrix);

    cout << "Решение системы линейных уравнений:" << endl;
    for (double x : solution) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}