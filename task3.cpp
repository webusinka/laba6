#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// Функция для выбора главного элемента в текущем столбце
int findPivot(const vector<vector<double>>& matrix, int col, int start_row) {
    double max_val = 0.0;
    int pivot_row = start_row;

    for (int i = start_row; i < matrix.size(); i++) { //проходимся по текущей строке
        if (fabs(matrix[i][col]) > max_val) {      //находим максимальный  по модулю элемент в столбце проходясь по всем строкам
            max_val = fabs(matrix[i][col]);
            pivot_row = i;                        //проходимся по строке
        }
    }
    return pivot_row + 1;              //возвращаем номер строки, начиная с 1
}

// Функция для решения системы линейных уравнений
vector<double> solveLinearSystem(const vector<vector<double>>& matrix) {
    int n = matrix.size();
    int m = matrix[0].size() - 1;
    vector<vector<double>> working_matrix = matrix; //копия матрицы

    // Прямой ход
    cout << "Прямой ход:" << endl;
    for (int col = 0; col < m; col++) {
        int pivot_row = findPivot(working_matrix, col, col); //находим номер строки
        double pivot_value = working_matrix[pivot_row - 1][col]; //находим главный элемент
        cout << "Выбран главный элемент " << pivot_value << " в строке " << pivot_row << endl;

        if (pivot_row != col + 1) {
            //меняем местами строки, если необходимо, так как галвные на диагонали
            swap(working_matrix[col], working_matrix[pivot_row - 1]); //используем индекс, начиная с 0
            cout << "Меняем местами строки " << col + 1 << " и " << pivot_row << endl;
        }

        //элементарные преобразования для получения нулей под главным элементом
        for (int i = col + 1; i < n; i++) {
            double factor = working_matrix[i][col] / working_matrix[col][col];
            cout << "Вычитаем из строки " << i + 1 << " " << factor << endl;

            for (int j = col; j < m + 1; j++) {
                working_matrix[i][j] -= factor * working_matrix[col][j];
            }
        }

        //выводим промежуточную матрицу
        cout << "Промежуточная матрица после " << col + 1 << "-го столбца:" << endl;
        for (const auto& row : working_matrix) {
            for (double elem : row) {
                cout << elem << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    //обратный ход
    cout << "Обратный ход:" << endl;
    vector<double> solution(m, 0.0);
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0.0;
        for (int j = i + 1; j < m; j++) {
            sum += working_matrix[i][j] * solution[j]; //начиная с последней строки, вычисляются значения по Крамеру
        }
        solution[i] = (working_matrix[i][m] - sum) / working_matrix[i][i];
        cout << "x" << i + 1 << " = " << solution[i] << endl;
    }

    cout << endl;
    return solution;
}

int main() {
    system("chcp 65001");
    
    vector<vector<double>> matrix = {
        {-1.14, -0.04,  0.21, -18.0, -1.24},
        { 0.25, -1.23, -0.17, -0.09,  0.95},
        {-0.21, -0.17,  0.80, -0.13,  2.56},
        { 0.15, -1.31,  0.06,  0.95, -1.14}
    };

    cout << "\tРешение СЛАУ с выбором главного элемента:\n" << endl;
    vector<double> solution = solveLinearSystem(matrix);
    cout << "Матрица решений СЛАУ: " << endl;
    for (double x : solution) {
        cout << x << " ";
    }
    cout << endl;

    cout << "\n\tРешение СЛАУ методом трехточечной прогонки:" << endl;

    return 0;
}