import os
os.environ.setdefault("DJANGO_SETTINGS_MODULE", "mysite.settings")

import django
django.setup()

from orm.models import *


def create_state():
    file = open("state.txt")
    for line in file:
        state_id, name = line.split(' ')
        State.objects.create(state_id=state_id, name=name)
    file.close()

def create_color():
    file = open("color.txt")
    for line in file:
        color_id, name = line.split(' ')
        Color.objects.create(color_id=color_id, name=name)
    file.close()

def create_team():
    file = open("team.txt")
    for line in file:
        team_id, name, state_id, color_id, wins, losses = line.split(' ')
        Team.objects.create(team_id=team_id, name=name, state_id_id=state_id, color_id_id=color_id, wins=wins, losses=losses)
    file.close()

def create_player():
    file = open("player.txt")
    for line in file:
        player_id, team_id, uniform_num, first_name, last_name, mpg, ppg, rpg, apg, spg, bpg = line.split(' ')
        Player.objects.create(player_id=player_id, team_team_id=team_id, uniform_num=uniform_num, first_name=first_name, last_name=last_name, mpg=mpg, ppg=ppg, rpg=rpg, apg=apg, spg=spg, bpg=bpg)
    file.close()

def drop_tables():
    Player.objects.all().delete()
    Team.objects.all().delete()
    State.objects.all().delete()
    Color.objects.all().delete()

def create_tables():
    create_state()
    create_color()
    create_team()
    create_player()

def main():
    drop_tables()
    create_tables()

if __name__ == "__main__":
    main()