import os
os.environ.setdefault("DJANGO_SETTINGS_MODULE", "mysite.settings")

import django
django.setup()

from orm.models import *
import query_funcs


def create_state():
    file = open("state.txt")
    for line in file:
        state_id, name = line.split(' ')
        query_funcs.add_state(state_id, name)
    file.close()

def create_color():
    file = open("color.txt")
    for line in file:
        color_id, name = line.split(' ')
        query_funcs.add_color(color_id, name)
    file.close()

def create_team():
    file = open("team.txt")
    for line in file:
        team_id, name, state_id, color_id, wins, losses = line.split(' ')
        query_funcs.add_team(team_id, name, state_id, color_id, wins, losses)
    file.close()

def create_player():
    file = open("player.txt")
    for line in file:
        player_id, team_id, uniform_num, first_name, last_name, mpg, ppg, rpg, apg, spg, bpg = line.split(' ')
        query_funcs.add_player(player_id, team_id, uniform_num, first_name, last_name, mpg, ppg, rpg, apg, spg, bpg)
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
    query_funcs.exercise()

if __name__ == "__main__":
    main()