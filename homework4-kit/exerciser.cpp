#include "exerciser.h"

void exercise(connection *C) {
    cout << "====== test query 1 =======\n";

    cout << "====== test query 2 =======\n";
    query2(C, "LightBlue");
    query2(C, "Maroon");

    cout << "====== test query 3 =======\n";
    query3(C, "Duke");

    cout << "====== test query 4 =======\n";
    query4(C, "NC", "LightBlue"); //UNC 12
    query4(C, "PA", "LightBlue"); //no match

    cout << "====== test query 5 =======\n";

}
