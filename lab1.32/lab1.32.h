#include <iostream>
#include <vector>

namespace lab1 {
    class Matrix;

    class Element {
    private:
        friend class Matrix;

    public:
        int value, x, y;

        Element(int x, int y, int value) {
            this->value = value;
            this->x = x;
            this->y = y;
        }

        friend std::ostream &operator<<(std::ostream &, Element &);

        friend std::ostream &operator<<(std::ostream &, Matrix &);
    };

    class RowElement {
    private:
        Element el;
        RowElement *next;

    public:
        RowElement(int x, int y, int value) : el(x, y, value) {
            next = nullptr;
        };

        friend std::ostream &operator<<(std::ostream &, Matrix &);

        friend std::ostream &operator<<(std::ostream &, RowElement &);

        friend class Matrix;
    };

    class Matrix {
    private:
        int count;
        RowElement *head;
        int rows, columns;

    public:

        friend std::ostream &operator<<(std::ostream &, Matrix &);

        void createVector();

        Matrix(int, int);

        Matrix();

        void addElement(int y, int x, int value);

    };

    class WrongIndexException {
    public:
        WrongIndexException(int, int);
    };


    int getNaturalIntWithUpperBound(int *a, const int *upperBound);

    int getNaturalInt(int *a);

    int sumOfDigits(int n);

    Matrix input();
}
