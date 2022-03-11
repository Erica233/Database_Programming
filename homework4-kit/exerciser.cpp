#include "exerciser.h"

void exercise(connection *C) {
    cout << "\n====== test query 1 =======\n";
    query1(C,
           1, 35, 40,
           0, 1, 1,
           0, 1, 1,
           0, 1, 1,
           0, 1, 1,
           0, 1, 1);

    cout << "\n====== test query 2 =======\n";
    query2(C, "LightBlue");
    query2(C, "Maroon");

    cout << "\n====== test query 3 =======\n";
    query3(C, "Duke");

    cout << "\n====== test query 4 =======\n";
    query4(C, "NC", "LightBlue"); //UNC 12
    query4(C, "PA", "LightBlue"); //no match

    cout << "\n====== test query 5 =======\n";
    query5(C, 14); //no match
    query5(C, 13); //UNC 12
    query5(C, 11); //4 teams
}
