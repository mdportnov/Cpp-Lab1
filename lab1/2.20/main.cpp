#include <iostream>
#include "lab2.20.h"

using namespace lab1_2;

const char *msgs[] = {" 0. Exit",
                      " 1. Input inner circle radius",
                      " 2. Get intersection length",
                      " 3. Get curve length",
                      " 4. Get curved area",
                      " 5. Input \"t\" and get (x, y)",
                      " 6. Get equation"
};

const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);

int (*functions[])(Deltoid &) = {nullptr, dialog_input,
                                 dialog_getIntersectionLength,
                                 dialog_getCurveLength,
                                 dialog_getCurvedArea,
                                 dialog_getXY,
                                 dialog_getEquation};


int main() {
    Deltoid deltoid;

    int rc = 0;

    while ((rc = dialog(msgs, NMsgs))) {
        if (!functions[rc](deltoid))
            break;
    }

}