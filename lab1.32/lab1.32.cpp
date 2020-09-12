#include <iostream>
#include "lab1.32.h"
#include <vector>

namespace lab1 {
    int sumOfDigits(int n) {
        int sum = 0;
        if (n < 0) n = -n;
        if (n / 10 == 0)
            return n;
        else {
            while (n > 0) {
                sum += n % 10;
                n /= 10;
            }
            return sum;
        }
    }

    Matrix input() {
        int rows, cols;
        std::cout << "Input number of columns (x):";
        getNaturalInt(&cols);

        std::cout << "Input number of rows (y):";
        getNaturalInt(&rows);

        Matrix matrix = Matrix(rows, cols);

        char choice;
        bool run = true;
        while (run) {
            std::cout << "Do you want to type in the next item? [Y/n]\n";
            std::cin >> choice;

            choice = tolower(choice);

            if (choice == 'y') {
                int x, y, value;

                std::cout << "Type in X coord: [" << 0 << ";" << cols - 1 << "]\n";
                getNaturalInt(&x, &cols, true);
                std::cout << "Type in Y coord: [" << 0 << ";" << rows - 1 << "]\n";
                getNaturalInt(&y, &rows, true);
                std::cout << "Type in Value:\n";
                getInt(&value);

                printf("\nAdding element | x: %d | y: %d | value: %d\n", x, y, value);
                matrix.addElement(x, y, value);

            }

            if (choice == 'n') {
                run = false;
            }
        }

        return matrix;
    }

    int getNaturalInt(int *a, const int *upperBound) {
        int n;
        do {
            n = scanf("%d", a);
            if (n < 0)
                return 0;

            if (*a > *upperBound - 1) {
                printf("%s\n", "Error! You went beyond the boundaries. Please, repeat your input: ");
                scanf("%*[^\n]");
            }

            if (n == 0 || *a <= 0) {
                printf("%s\n", "Error! Wrong type. Please, repeat your input: ");
                scanf("%*[^\n]");
            }

        } while (n == 0 || *a < 0 || *a > *upperBound - 1);
        return 1;
    }

    int getNaturalInt(int *a, const int *upperBound, bool withZero) {
        int n;
        do {
            n = scanf("%d", a);
            if (n < 0)
                return 0;

            if (*a > *upperBound - 1) {
                printf("%s\n", "Error! You went beyond the boundaries. Please, repeat your input: ");
                scanf("%*[^\n]");
            }

            if (n == 0 || *a < 0) {
                printf("%s\n", "Error! Wrong type. Please, repeat your input: ");
                scanf("%*[^\n]");
            }


        } while (n == 0 || *a < 0 || *a > *upperBound - 1);
        return 1;
    }

    int getNaturalInt(int *a) {
        int n;
        do {
            n = scanf("%d", a);
            if (n < 0)
                return 0;
            if (n == 0 || *a <= 0) {
                printf("%s\n", "\nError! Wrong type. Please, repeat your input: ");
                scanf("%*[^\n]");
            }
        } while (n == 0 || *a <= 0);
        return 1;
    }

    int getInt(int *a) {
        int n;
        do {
            n = scanf("%d", a);
            if (n < 0)
                return 0;
            if (n == 0) {
                printf("%s\n", "\nError! Wrong type. Please, repeat your input: ");
                scanf("%*[^\n]");
            }
        } while (n == 0);
        return 1;
    }

    Matrix::Matrix(int columns, int rows) {
        this->columns = columns;
        this->rows = rows;
        head = nullptr;
        count = 0;
    }

    Matrix::Matrix() {
        this->rows = 0;
        this->columns = 0;
        head = nullptr;
        count = 0;
    }

    void Matrix::addElement(int i, int j, int v) {
        ListElement *current, *help, *prev;
        bool insert = false;
        // проверка корректности позиции
        // вставляемого элемента
        if (i < rows && j < columns) {
            // проверка, вставляется ли элемент
            // на первое место
            if (head == nullptr || j < head->el.y ||
                (j == head->el.y && i < head->el.x)) {
                // вставка элемента в начало списка
                help = new ListElement(i, j, v);
                help->next = head;
                head = help;
                count++;
                return;
            }
            // поиск позиции вставляемого элемента
            prev = head;
            current = head->next;

            // пропускаем элементы, находящиеся в СТРОКАХ с меньшим номером
            while (current != nullptr && j > current->el.y) {
                current = current->next;//////
                prev = prev->next;
            }

            if (current != nullptr && j == current->el.y) {
                // пропускаем элементы, находящиеся в той же СТРОКЕ, но в СТОЛБЦАХ с меньшим номером
                while (current != nullptr && i > current->el.x) {
                    current = current->next;
                    prev = prev->next;
                }
                // если элемент в заданной позиции уже имеется,изменяем его значение
                if (current != nullptr && i == current->el.x) {
                    current->el.value = v;
                    insert = true;
                }
            }
            // вставляем новый элемент в список
            if (!insert) {
                help = new ListElement(i, j, v);
                prev->next = help;
                help->next = current;
                count++;
            }
        }
    }

    std::ostream &operator<<(std::ostream &out, Element &element) {
        out << element.value;
        return out;
    }

    std::ostream &operator<<(std::ostream &out, ListElement &rowElement) {
        out << rowElement.el;
        return out;
    }

    std::ostream &operator<<(std::ostream &out, Matrix &matrix) {
        int i = 0, j = 0;
        // цикл просмотра элементов списка
        ListElement *current = matrix.head;
        while (current != nullptr) {
            // вывод нулей в качестве элементов предшествующих строк
            for (; i < current->el.x; i++) {
                for (; j < matrix.columns; j++)
                    out << "0\t";
                out << std::endl;
                j = 0;
            }
            // вывод нулей в качестве элементов в той же строке, но в предшествующих столбцах
            for (; i < current->el.x; i++) ////!!!
                out << "0\t";
            // вывод текущего элемента
            out << *current << "\t";
            // корректировка индексов для просмотра следующих элементов
            i++; ////!!!

            if (i == matrix.rows) {
                j++;
                i = 0;
                out << std::endl;
            }
            current = current->next;
        }
        // вывод нулей в качестве последующих элементов строки, в которой расположен последний элемент списка
        if (j != 0) {
            for (; j < matrix.columns; j++)
                out << "0\t";
            out << std::endl;
            j++;
        }
        // вывод нулей в качестве элементов строк, расположенных после той, в которой находится последний элемент списка
        for (; j < matrix.columns; j++) {
            for (i = 0; i < matrix.rows; i++)
                out << "0\t";
            out << std::endl;
        }
        return out;
    }

    void Matrix::createVector() {
        ListElement *curr = this->head;
        int currentSum = 0, currentDigitSum = 0;
        int x = 0;

        std::vector<int> vector;
        bool isFirst = true;

        while (curr != nullptr) {

            if (isFirst) {
                currentDigitSum = sumOfDigits(curr->el.value);
                isFirst = false;
            }

            if (curr->el.y == x) {
                if (currentDigitSum == sumOfDigits(curr->el.value)) {
                    currentSum += curr->el.value;
                }
            }
            curr = curr->next;

            if (curr != nullptr) {
                if (curr->el.y != x) {
                    vector.push_back(currentSum);
                    x++;
                    isFirst = true;
                    currentDigitSum = 0;
                    currentSum = 0;
                }
            } else {
                vector.push_back(currentSum);
            }
        }

        std::cout << "\nOutput vector:\n";
        for (int &i : vector) {
            std::cout << i << " ";
        }

    }
}