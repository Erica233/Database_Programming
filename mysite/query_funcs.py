from orm.models import *

def exercise():
    print("====== test query 1 =======")
    query1(1, 35, 40,
           0, 1, 1,
           0, 1, 1,
           0, 1, 1,
           0, 1, 1,
           0, 1, 1)
    query1(1, 35, 40,
           1, 10, 20,
           1, 5, 10,
           1, 1, 3,
           1, 0, 2,
           1, 0, 1)

    print("\n====== test query 2 =======")
    query2("LightBlue")
    query2("Maroon")

    print("\n====== test query 3 =======")
    query3("Duke")

    print("\n====== test query 4 =======")
    query4("NC", "LightBlue") #UNC 12
    query4("PA", "LightBlue") #no match

    print("\n====== test query 5 =======")
    query5(14) #no match
    query5(13) #UNC 12
    query5(11) #4 teams

def query1(use_mpg, min_mpg, max_mpg,
           use_ppg, min_ppg, max_ppg,
           use_rpg, min_rpg, max_rpg,
           use_apg, min_apg, max_apg,
           use_spg, min_spg, max_spg,
           use_bpg, min_bpg, max_bpg):
    all = Player.objects.all()
    if use_mpg:
        all = all.filter(mpg__range=(min_mpg, max_mpg))
    if use_ppg:
        all = all.filter(ppg__range=(min_ppg, max_ppg))
    if use_rpg:
        all = all.filter(rpg__range=(min_rpg, max_rpg))
    if use_apg:
        all = all.filter(apg__range=(min_apg, max_apg))
    if use_spg:
        all = all.filter(spg__range=(min_spg, max_spg))
    if use_bpg:
        all = all.filter(bpg__range=(min_bpg, max_bpg))

    print("PLAYER_ID TEAM_ID UNIFORM_NUM FIRST_NAME LAST_NAME MPG PPG RPG APG SPG BPG")
    for player in all:
        print(player.player_id, player.team_id_id, player.uniform_num,
              player.first_name, player.last_name, player.mpg, player.ppg,
              player.rpg, player.apg, player.spg, player.bpg)

def query2(team_color):
    output = Team.objects.filter(color_id__name=team_color)
    print("NAME")
    for team in output:
        print(team.name)

def query3(team_name):
    output = Player.objects.filter(team_id__name=team_name).order_by('-ppg')
    print("FIRST_NAME LAST_NAME")
    for player in output:
        print(player.first_name, player.last_name)

def query4(team_state, team_color):
    output = Player.objects.filter(team_id__state_id__name=team_state, team_id__color_id__name=team_color)
    print("UNIFORM_NUM FIRST_NAME LAST_NAME")
    for player in output:
        print(player.uniform_num, player.first_name, player.last_name)

def query5(num_wins):
    output = Player.objects.filter(team_id__wins__gt=num_wins)
    print("FIRST_NAME LAST_NAME NAME WINS")
    for player in output:
        print(player.first_name, player.last_name, player.team_id_name, player.team_id_wins)