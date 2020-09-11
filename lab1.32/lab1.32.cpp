#include <iostream>
#include "lab1.32.h"
#include <vector>

namespace lab1 {
    int sumOfDigits(int n) {
        int sum = 0;
        if (n < 0) n = -n;
        if (n / 10 == 0)
            return 1;
        else {
            while (n > 0) {
                sum += n % 10;
                n /= 10;
            }
            return sum;
        }
    }

    Matrix input() {
        int rows, columns;

        std::cout << "Input number of columns (x):";
        getNaturalInt(&columns);
        std::cout << "Input number of rows (y):";
        getNaturalInt(&rows);

        Matrix matrix = Matrix(columns, rows);

        char choice;
        bool run = true;
        while (run) {
            std::cout << "Do you want to type in the next item? [Y/n]\n";
            std::cin >> choice;
            while (choice != 'n' && choice != 'y') {
                choice = tolower(choice);

                int x, y, value;

                std::cout << "Type in X coord: [" << 0 << ";" << columns - 1 << "]\n";
                getNaturalIntWithUpperBound(&x, &columns);
                std::cout << "Type in Y coord: [" << 0 << ";" << rows - 1 << "]\n";
                getNaturalIntWithUpperBound(&y, &rows);
                std::cout << "Type in Value:\n";
                getNaturalInt(&value);

                printf("\nAdding element | x: %d | y: %d | value: %d\n", x, y, value);
                matrix.addElement(x, y, value);
            }

            if (choice == 'n') {
                run = false;
            }
        }

        return matrix;
    }

    int getNaturalIntWithUpperBound(int *a, const int *upperBound) {
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
            if (n == 0 || *a < 0) {
                printf("%s\n", "\nError! Wrong type. Please, repeat your input: ");
                scanf("%*[^\n]");
            }
        } while (n == 0 || *a < 0);
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

    void Matrix::addElement(int x, int y, int value) {
        RowElement *current, *tmp, *prev;
        bool insert = false;
        printf("Cols: %d | Rows: %d\n", columns, rows);

        if (x < columns && y < rows) {
            // check to see if it can be the first element
            if (head == nullptr || y < head->el.y
                || (y == head->el.y && x < head->el.x)) {

                tmp = new RowElement(x, y, value);
                tmp->next = head;
                head = tmp;
                count++;
                return;
            } // else:
            // insert position search
            prev = head;
            current = head->next;

            //  skip elements with rows with less number
            while (current != nullptr && x > current->el.x) {
                current = current->next;
                prev = prev->next;
            }

            if (current != nullptr && x == current->el.x) {
                // skip elements in current row with less number of column
                while (current != nullptr && y > current->el.y) {
                    current = current->next;
                    prev = prev->next;
                }

                if (current != nullptr && y == current->el.y) {
                    current->el.value = value;
                    insert = true;
                }
            }

            if (!insert) {
                tmp = new RowElement(x, y, value);
                prev->next = tmp;
                tmp->next = current;
                count++;
            }
        } else {
            throw WrongIndexException(x, y);
        }
    }

    std::ostream &operator<<(std::ostream &out, Element &element) {
        out << element.value;
        return out;
    }

    std::ostream &operator<<(std::ostream &out, RowElement &rowElement) {
        out << rowElement.el;
        return out;
    }

    std::ostream &operator<<(std::ostream &out, Matrix &matrix) {
        int y = 0, x = 0;

        RowElement *curr = matrix.head;

        while (curr != nullptr) {
            for (; x < curr->el.x; x++) {
                for (; y < matrix.rows; x++)
                    out << "0\t";
                out << std::endl;
                y = 0;
            }

            for (; y < curr->el.y; y++)
                out << "0\t";
            out << *curr << "\t";

            y++;
            if (y == matrix.rows) {
                x++;
                y = 0;
                out << std::endl;
            }
            curr = curr->next;
        }

        if (y != 0) {
            for (; y < matrix.rows; y++)
                out << "0\t";
            out << std::endl;
            x++;
        }

        for (; x < matrix.columns; x++) {
            for (y = 0; y < matrix.rows; y++)
                out << "0\t";
            out << std::endl;
        }

        return out;
    }

    void Matrix::createVector() {

        RowElement *curr = this->head;
        int currentSum = 0, currentDigitSum = 0;
        int y = 0;

        std::vector<int> vector;

        while (curr != nullptr) {
            currentDigitSum = sumOfDigits(curr->el.value);
            printf("Current Digit Sum: %d\n", currentDigitSum);

            printf("Curr y: %d\n", curr->el.y);
//            printf("Curr x: %d\n", curr->el.x);
            if (curr->el.y == y) {
                if (sumOfDigits(curr->el.value) == currentDigitSum) {
                    currentSum += curr->el.value;
                } else {
//                    curr = curr->next;
                }
            } else {
                y++;
                vector.push_back(currentSum);

            }

            currentSum = 0;
            curr = curr->next;
        }

        std::cout << "Output vector:\n";
        for (int &i : vector) {
            std::cout << i << " ";
        }

    }

    WrongIndexException::WrongIndexException(int x, int y) {
        std::cout << "There are wrong indices: (" << x << "," << y << ")\n";
    }
}