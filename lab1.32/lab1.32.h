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

    class ListElement {
    private:
        Element el;
        ListElement *next;

    public:
        ListElement(int x, int y, int value) : el(x, y, value) {
            next = nullptr;
        };

        friend std::ostream &operator<<(std::ostream &, Matrix &);

        friend std::ostream &operator<<(std::ostream &, ListElement &);

        friend class Matrix;
    };

    class Matrix {
    private:
        int count;
        ListElement *head;
        int rows, columns;

    public:

        friend std::ostream &operator<<(std::ostream &, Matrix &);

        void createVector();

        Matrix(int, int);

        Matrix();

        void addElement(int x, int y, int value);

    };

    class WrongIndexException {
    public:
        WrongIndexException(int, int);
    };

    int getNaturalInt(int *a, const int *upperBound, bool withZero);

    int getNaturalInt(int *a, const int *upperBound);

    int getNaturalInt(int *a);

    int getInt(int *a);

    int sumOfDigits(int n);

    Matrix input();
}
