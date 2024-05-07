#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <set>
#include <algorithm>

using namespace std;

int Random_Matrix(vector<vector<int>>& matrix, int lines, int columns) { //заполнение матрицы случайными числами

    srand(static_cast<unsigned int>(time(nullptr)));
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {
            matrix[i][j] = std::rand() % 100 + 1; // случайное число от 1 до 100
        }
    }
    return 0;
}

int number1 (vector<vector<int>>& matrix, int size){
    // Создание новой матрицы с двумя строками, содержащими элементы диагоналей
    vector<vector<int>> diagonal_matrix(2, vector<int>(size));
    
    // Заполнение новой матрицы
    for (int i = 0; i < size; i++) {
        diagonal_matrix[0][i] = matrix[i][i]; // главная диагональ
        diagonal_matrix[1][i] = matrix[i][size-1-i]; // побочная диагональ
    }
    
    // Вывод результата 
    cout << "Матрица диагоналей:\n";
    for (const auto& row : diagonal_matrix) {
        for (int element : row) {
            cout << element << " ";
        }
        cout << "\n";
    }
    
    return 0;
}

int number2(vector<vector<int>>& matrix, int lines, int columns) {
    // Поиск наибольшего и второго наименьшего элементов матрицы
    vector<int> all_elements;
    for (const auto& row : matrix) {
        for (int element : row) {
            all_elements.push_back(element);
        }
    }
    
    sort(all_elements.begin(), all_elements.end());
    int max_element = all_elements.back();
    cout << "Максимальный элемент в матрице: " << max_element << endl;
    int second_min_element = all_elements[1];
    cout << "Второй минимальный элемент в матрице: " << second_min_element << endl;
    
    // Замена элементов диагоналей на разность наибольшего и второго наименьшего элементов
    int diff = max_element - second_min_element;
    for (int i = 0; i < min(lines, columns); i++) {
        matrix[i][i] = diff;           // главная диагональ
        matrix[i][columns-1-i] = diff; // побочная диагональ
    }
    
    // Вывод результата
    cout << "\nПолученная матрица:\n";
    for (const auto& row : matrix) {
        for (int element : row) {
            cout << element << " ";
        }
        cout << "\n";
    }
    
    return 0;
}

bool isValidSudoku(const vector<vector<int>>& board) {
    int N = 6;  // размер доски для судоку

    // Проверка строк
    for (int i = 0; i < N; i++) {
        set<int> row_set;           //для каждой строки создаем сет(уникальные)
        for (int j = 0; j < N; j++) {
            if (board[i][j] != 0) {   //проверяем только заполненные ячейки
                if (row_set.count(board[i][j])) { //если мы уже встречали в сете это число
                    return false;  //условие не выполнилось
                }
                row_set.insert(board[i][j]); //если не было, добавляем в сет
            }
        }
    }

    // Проверка столбцов
    for (int j = 0; j < N; j++) {
        set<int> col_set;         //проходимся по столбцам
        for (int i = 0; i < N; i++) {
            if (board[i][j] != 0) { //если значение в столбце есть и оно уже было, то все
                if (col_set.count(board[i][j])) {
                    return false;
                }
                col_set.insert(board[i][j]);
            }
        }
    }

    // Проверка квадратов 3x3
    for (int i = 0; i < N; i += 3) { //идем с шагом 3
        for (int j = 0; j < N; j += 3) {
            set<int> block_set;      //уникальные в тройке
            for (int x = 0; x < 3; x++) { 
                for (int y = 0; y < 3; y++) { //проходимся по каждому от 1 до 3, сначала по столбцам
                    if (board[i + x][j + y] != 0) {
                        if (block_set.count(board[i + x][j + y])) {
                            return false;
                        }
                        block_set.insert(board[i + x][j + y]);
                    }
                }
            }
        }
    }

    return true;
}

int main() {
    system("chcp 65001");
    
    //задание 1
    int N_1 = 7; // размерность матрицы
    vector<vector<int>> matrix_1(N_1, vector<int>(N_1));
    Random_Matrix(matrix_1, N_1, N_1);

    cout << "Исходная матрица:\n";
    for (const auto& row : matrix_1) {
        for (int element : row) {
            cout << element << " ";
        }
        cout << "\n";
    }
    cout << endl;
    number1(matrix_1, N_1);
    cout << endl;
    //задание 2
    int M_2 = 5;  // количество строк
    int N_2 = 8;  // количество столбцов
    vector<vector<int>> matrix_2(M_2, vector<int>(N_2));
    Random_Matrix(matrix_2, M_2, N_2);
    number2(matrix_2, M_2, N_2);
    cout << endl;

    //задание 3 с судоку
    vector<vector<int>> board = { //инициализируем доску судоку
        {5, 3, 0,   0, 7, 0},
        {6, 0, 0,   1, 9, 5},
        {0, 9, 8,   0, 0, 0},

        {8, 0, 0,   0, 6, 0},
        {4, 0, 0,   8, 0, 3},
        {7, 0, 0,   0, 2, 0}
    };

    cout << "Исходная доска судоку:\n";
    for (const auto& row : board) {
        for (int element : row) {
            cout << element << " ";
        }
        cout << "\n";
    }

    if (isValidSudoku(board)) {
        cout << "Доска судоку заполнена правильно." << endl;
    } else {
        cout << "Доска судоку заполнена неправильно." << endl;
    }

    return 0;
}