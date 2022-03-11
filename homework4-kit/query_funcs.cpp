#include "query_funcs.h"


void add_player(connection *C, int team_id, int jersey_num, string first_name, string last_name,
                int mpg, int ppg, int rpg, int apg, double spg, double bpg) {
    stringstream ss_sql;
    work W(*C);
    ss_sql << "INSERT INTO PLAYER (TEAM_ID, UNIFORM_NUM, FIRST_NAME, "
              "LAST_NAME, MPG, PPG, RPG, APG, SPG, BPG) "
              "VALUES (" << team_id << ", " << jersey_num << ", "
              << W.quote(first_name) << ", " << W.quote(last_name)
              << ", " << mpg << ", " << ppg << ", " << rpg << ", " << apg
              << ", " << spg << ", " << bpg << ");";

    W.exec( ss_sql.str() );
    W.commit();
}


void add_team(connection *C, string name, int state_id, int color_id, int wins, int losses) {
    stringstream ss_sql;
    work W(*C);
    ss_sql << "INSERT INTO TEAM (NAME, STATE_ID, COLOR_ID, WINS, LOSSES) "
              "VALUES (" << W.quote(name) << ", " << state_id << ", "
              << color_id << ", " << wins << ", " << losses << ");";

    W.exec( ss_sql.str() );
    W.commit();
}


void add_state(connection *C, string name) {
    work W(*C);
    string sql = "INSERT INTO STATE (NAME) VALUES (" + W.quote(name) + ");";

    W.exec( sql );
    W.commit();
}


void add_color(connection *C, string name) {
    work W(*C);
    string sql = "INSERT INTO COLOR (NAME) VALUES (" + W.quote(name) + ");";

    W.exec( sql );
    W.commit();
}


void query1(connection *C,
            int use_mpg, int min_mpg, int max_mpg,
            int use_ppg, int min_ppg, int max_ppg,
            int use_rpg, int min_rpg, int max_rpg,
            int use_apg, int min_apg, int max_apg,
            int use_spg, double min_spg, double max_spg,
            int use_bpg, double min_bpg, double max_bpg
) {
    nontransaction N(*C);
    stringstream ss_sql;
    ss_sql << "select * from PLAYER where PLAYER_ID > 0";
    vector<string> names { "MPG", "PPG", "RPG", "APG", "SPG", "BPG" };
    vector<int> uses { use_mpg, use_ppg, use_rpg, use_apg, use_spg, use_bpg };
    vector<int> mins1 { min_mpg, min_ppg, min_rpg, min_apg };
    vector<double> mins2 { min_spg, min_bpg };
    vector<int> maxs1 { max_mpg, max_ppg, max_rpg, max_apg };
    vector<double> maxs2 { max_spg, max_bpg };
    for (int i = 0; i < mins1.size(); i++) {
        if (uses[i]) {
            ss_sql << " and " << names[i] << " BETWEEN " << mins1[i] << " AND " << maxs1[i];
        }
    }
    for (int i = 0; i < mins2.size(); i++) {
        if (uses[i + 4]) {
            ss_sql << " and " << names[i + 4] << "BETWEEN " << mins2[i] << " AND " << maxs2[i];
        }
    }
    ss_sql << ";";
    cout << ss_sql.str() << endl;

    result R( N.exec( ss_sql.str() ));

    //cout << "FIRST_NAME LAST_NAME NAME WINS\n";
    for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
        //cout << c[0].as<string>() << " " << c[1].as<string>() << " "
        //     << c[2].as<string>() << " " << c[3].as<int>() << endl;
    }
    cout << "Query 1 done successfully" << endl;
}


void query2(connection *C, string team_color) {
    nontransaction N(*C);
    string sql = "select TEAM.NAME from TEAM, COLOR where COLOR.NAME="
            + N.quote(team_color) + " and COLOR.COLOR_ID=TEAM.COLOR_ID;";

    result R( N.exec( sql ));

    cout << "NAME\n";
    for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
        cout << c[0].as<string>() << endl;
    }
    cout << "Query 2: team_color=" << team_color << " done successfully" << endl;
}


void query3(connection *C, string team_name) {
    nontransaction N(*C);
    string sql = "select PLAYER.FIRST_NAME, PLAYER.LAST_NAME from TEAM, PLAYER "
                 "where TEAM.NAME=" + N.quote(team_name) +
                 " and PLAYER.TEAM_ID=TEAM.TEAM_ID order by PPG desc;";

    result R( N.exec( sql ));

    cout << "FIRST_NAME LAST_NAME\n";
    for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
        cout << c[0].as<string>() << " " << c[1].as<string>() << endl;
    }
    cout << "Query 3: team_name=" << team_name << " done successfully" << endl;
}


void query4(connection *C, string team_state, string team_color) {
    nontransaction N(*C);
    stringstream ss_sql;
    ss_sql << "select PLAYER.FIRST_NAME, PLAYER.LAST_NAME, PLAYER.UNIFORM_NUM "
              "from PLAYER, STATE, COLOR, TEAM "
              "where STATE.NAME=" << N.quote(team_state) <<
              " and COLOR.NAME=" << N.quote(team_color) <<
              " and COLOR.COLOR_ID=TEAM.COLOR_ID and "
              "STATE.STATE_ID=TEAM.STATE_ID and PLAYER.TEAM_ID=TEAM.TEAM_ID;";

    result R( N.exec( ss_sql.str() ));

    cout << "FIRST_NAME LAST_NAME UNIFORM_NUM\n";
    for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
        cout << c[0].as<string>() << " " << c[1].as<string>() << " "
                << c[2].as<int>() << endl;
    }
    cout << "Query 4: team_state=" << team_state << ", team_color="
    << team_color << " done successfully" << endl;
}


void query5(connection *C, int num_wins) {
    nontransaction N(*C);
    stringstream ss_sql;
    ss_sql << "select FIRST_NAME, LAST_NAME, TEAM.NAME, WINS from PLAYER, TEAM "
              "where WINS > " << num_wins <<
              " and PLAYER.TEAM_ID=TEAM.TEAM_ID;";

    result R( N.exec( ss_sql.str() ));

    cout << "FIRST_NAME LAST_NAME NAME WINS\n";
    for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
        cout << c[0].as<string>() << " " << c[1].as<string>() << " "
             << c[2].as<string>() << " " << c[3].as<int>() << endl;
    }
    cout << "Query 5: num_wins > " << num_wins << " done successfully" << endl;
}
