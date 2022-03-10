#include <iostream>
#include <pqxx/pqxx>

#include "exerciser.h"

using namespace std;
using namespace pqxx;

void drop_tables(connection * C) {
    /* Create SQL statement */
    //sql = "DROP TABLE if exists " +  + " cascade;";
    sql = "DROP TABLE IF EXISTS PLAYER, TEAM, STATE, COLOR cascade;";
    /* Create a transactional object. */
    work W(C);

    /* Execute SQL query */
    W.exec( sql );
    W.commit();
    cout << "Dropped tables successfully" << endl;
}
void create_tables(connection * C) {
    string sql = "";
    //state
    sql += "CREATE TABLE STATE ("
           "STATE_ID SERIAL PRIMARY KEY NOT NULL, "
           "NAME CHAR(2));";
    //color
    sql += "CREATE TABLE COLOR ("
           "COLOR_ID SERIAL PRIMARY KEY NOT NULL, "
           "NAME VARCHAR(50));";
    //team
    sql += "CREATE TABLE TEAM ("
           "TEAM_ID SERIAL PRIMARY KEY NOT NULL, "
           "NAME VARCHAR(100),"
           "STATE_ID INT, "
           "COLOR_ID INT, "
           "WINS INT, "
           "LOSSES INT,"
           "FOREIGN KEY (STATE_ID) REFERENCES STATE(STATE_ID) ON DELETE SET NULL ON UPDATE CASCADE,"
           "FOREIGN KEY (COLOR_ID) REFERENCES COLOR(COLOR_ID) ON DELETE SET NULL ON UPDATE CASCADE);";
    //player
    sql += "CREATE TABLE PLAYER ("
          "PLAYER_ID SERIAL PRIMARY KEY NOT NULL, "
          "TEAM_ID INT, "
          "UNIFORM_NUM INT, "
          "FIRST_NAME VARCHAR(100), "
          "LAST_NAME VARCHAR(100), "
          "MPG INT, "
          "PPG INT, "
          "RPG INT, "
          "APG INT, "
          "SPG FLOAT, "
          "BPG FLOAT,"
          "FOREIGN KEY (TEAM_ID) REFERENCES TEAM(TEAM_ID) ON DELETE SET NULL ON UPDATE CASCADE);";

    /* Create a transactional object. */
    work W(C);

    /* Execute SQL query */
    W.exec( sql );
    W.commit();
    cout << "Created tables successfully" << endl;
}

int main(int argc, char *argv[]) {

    //Allocate & initialize a Postgres connection object
    connection *C;

    try {
        //Establish a connection to the database
        //Parameters: database name, user name, user password
        C = new connection("dbname=ACC_BBALL user=postgres password=passw0rd");
        if (C->is_open()) {
            cout << "Opened database successfully: " << C->dbname() << endl;
        } else {
            cout << "Can't open database" << endl;
            return 1;
        }
    } catch (const std::exception &e) {
        cerr << e.what() << std::endl;
        return 1;
    }


    //TODO: create PLAYER, TEAM, STATE, and COLOR tables in the ACC_BBALL database
    //      load each table with rows from the provided source txt files

    //create tables (drop existed tables first)
    drop_tables(C);
    create_tables(C);
    //insert
    //query

    //test
    exercise(C);

    //Close database connection
    C->disconnect();

    return 0;
}


