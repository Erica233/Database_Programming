from orm.models import *

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
        print(player.player_id, player.team_id, player.uniform_num,
              player.first_name, player.last_name, player.mpg, player.ppg,
              player.rpg, player.apg, player.spg, player.bpg)

#def query2(team_color):