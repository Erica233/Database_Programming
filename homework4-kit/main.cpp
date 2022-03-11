#include <iostream>
#include <pqxx/pqxx>
#include <fstream>
#include <string>
#include <sstream>

#include "exerciser.h"
#include "query_funcs.h"

using namespace std;
using namespace pqxx;

void drop_tables(connection * C) {
    /* Create SQL statement */
    //sql = "DROP TABLE if exists " +  + " cascade;";
    string sql = "DROP TABLE IF EXISTS PLAYER, TEAM, STATE, COLOR cascade;";
    /* Create a transactional object. */
    work W(*C);

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

    work W(*C);
    W.exec( sql );
    W.commit();
    cout << "Created tables successfully" << endl;
}

void insert_states_or_colors(connection * C, const char * filename) {
    ifstream file;
    file.open(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open " << filename << endl;
        exit(EXIT_FAILURE);
    }
    string name, line;
    int id;
    while (getline(file, line)) {
        stringstream ssline(line);
        ssline >> id >> name;
        //cout << "id: " << id << " name: " << name << endl;
        if (strcmp(filename, "state.txt") == 0) {
            add_state(C, name);
        } else {
            add_color(C, name);
        }
    }
    file.close();
    cout << "Added tuples according to " << filename << " successfully\n";
}

void insert_teams(connection * C) {
    ifstream file;
    file.open("team.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open team.txt\n";
        exit(EXIT_FAILURE);
    }
    string name, line;
    int team_id, state_id, color_id, wins, losses;
    while (getline(file, line)) {
        stringstream ssline(line);
        ssline >> team_id >> name >> state_id >> color_id >> wins >> losses;
        add_team(C, name, state_id, color_id, wins, losses);
    }
    file.close();
    cout << "Added teams successfully\n";
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
    insert_states_or_colors(C, "state.txt");
    insert_states_or_colors(C, "color.txt");
    insert_teams(C);
    //query

    //test
    exercise(C);

    //Close database connection
    C->disconnect();

    return 0;
}


