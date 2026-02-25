#include "Matrix.hpp"
#include <functional>
#include <windows.h>

/**
 * 
 */
template <typename T>
using Operation = std::function<void(Matrix<T>&)>;

/**
 * Ассоциативный массив команд, для реализации
 * паттерна Command
 */
std::unordered_map<int, Operation<int>> ops;

/**
 * Метод добавления операций/комманд
 */
template <typename T>
void addOperation(int n,Operation<T> op, std::unordered_map<int, Operation<T>>& ops) {
    ops[n] = op;
}
int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    int rows,cols;
    Matrix<int> A,B,C;
    int choice = 1,number;

    while(true) {
        std::cout<<"1)Умножение матриц A*B"<<std::endl;
        std::cout<<"2)Умножение матрицы на число A*number"<<std::endl;
        std::cout<<"3)Транспонирование матрицы:"<<std::endl;
        std::cout<<"0)Выход:"<<std::endl;

        std::cin>>choice;

        if(choice == 0) {
            std::cout<<"Выход"<<std::endl;
            return 0;
        }
        std::cout<<"Введите размерность матрицы A <количество строк> <количество столбцов>:";
        std::cin>>rows>>cols;
        Matrix<int>A(rows,cols);
        std::cout<<"Введите данные в матрицу:";
        std::cin>>A;
        Matrix<int> C(rows,cols);

        /**
         * Операция умножения  матриц
         */
        Operation<int> multiplyMatrixes = [&B,&C,&rows,&cols](Matrix<int>& A) {
            std::cout<<"Введите размерность матрицы B <количество строк> <количество столбцов>:";
            std::cin>>rows>>cols;
            Matrix<int>B(rows,cols);
            std::cout<<"Введите данные в матрицу:";
            std::cin>>B;
            C=A*B;
            std::cout<<"Результат:"<<std::endl;
            std::cout<<C;
        };

        /**
         * Операция умножения матрицы на число
         */
        Operation<int> multiplyMatrixOnNumber = [&number,&C](Matrix<int>& A) {
            std::cout<<"Введите число:"<<std::endl;
            std::cin>>number;
            C = A*number;
            std::cout<<"Результат:"<<std::endl;
            std::cout<<C;
        };

        /**
         * Транпонирование матрицы
         */
        Operation<int> transponseMatrix = [&C](Matrix<int>& A) {
            C = !A;
            std::cout<<"Результат:"<<std::endl;
            std::cout<<C;
        };

       
        /**
         * Регистрация операций
         */
        addOperation(1,multiplyMatrixes,ops);
        addOperation(2,multiplyMatrixOnNumber,ops);
        addOperation(3,transponseMatrix,ops);
        Operation<int> f = ops[choice]; //выбор операции
        f(A);//вызов метода
    }
}