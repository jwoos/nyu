# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
#
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


"""
This file contains all of the agents that can be selected to control Pacman.  To
select an agent, use the '-p' option when running pacman.py.  Arguments can be
passed to your agent using '-a'.  For example, to load a SearchAgent that uses
depth first search (dfs), run the following command:

> python pacman.py -p SearchAgent -a fn=depthFirstSearch

"""

from game import Directions
from game import Agent
from game import Actions
import util
import time
import search
import random

# this is an example Agent
class GoWestAgent(Agent):
    "An agent that goes West until it can't."

    def getAction(self, state):
        "The agent receives a GameState (defined in pacman.py)."
        if Directions.WEST in state.getLegalPacmanActions():
            return Directions.WEST
        else:
            return Directions.STOP

# Part 1
# implement this
class RandomAgent(Agent):
    def __init__(self):
        pass

    def getAction(self, state):
        mapper = {
            'WEST': Directions.WEST,
            'EAST': Directions.EAST,
            'STOP': Directions.STOP,
            'SOUTH': Directions.SOUTH,
            'NORTH': Directions.NORTH
        }
        possibilities = state.getLegalPacmanActions()
        x = random.randint(0, len(possibilities) - 1)
        return mapper[possibilities[x].upper()]

# Part 2
# implement this
class SurroundingAwareAgent(Agent):
    def __init__(self):
        self.last = None
        self.mapper = {
            'WEST': Directions.WEST,
            'EAST': Directions.EAST,
            'STOP': Directions.STOP,
            'SOUTH': Directions.SOUTH,
            'NORTH': Directions.NORTH
        }

    def get_possible_food(self, state):
        food = state.getFood()
        possible = []
        current_position = state.getPacmanPosition()
        current_position_x = current_position[0]
        current_position_y = current_position[1]

        if food[current_position_x + 1][current_position_y]:
            possible.append('EAST')
        if food[current_position_x - 1][current_position_y]:
            possible.append('WEST')
        if food[current_position_x][current_position_y + 1]:
            possible.append('NORTH')
        if food[current_position_x][current_position_y - 1]:
            possible.append('SOUTH')

        return possible

    def get_possible_power(self, state):
        capsule = state.getCapsules()
        possible = []
        current_position = state.getPacmanPosition()
        current_position_x = current_position[0]
        current_position_y = current_position[1]

        for coordinate in capsule:
            if coordinate == (current_position_x + 1, current_position_y):
                possible.append('EAST')
            if coordinate == (current_position_x - 1, current_position_y):
                possible.append('WEST')
            if coordinate == (current_position_x, current_position_y + 1):
                possible.append('NORTH')
            if coordinate == (current_position_x, current_position_y - 1):
                possible.append('SOUTH')

        return possible

    def get_legal_moves(self, state):
        legal = state.getLegalPacmanActions()
        possible = []
        current_position = state.getPacmanPosition()
        current_position_x = current_position[0]
        current_position_y = current_position[1]

        for x in legal:
            if x.upper() == 'STOP':
                pass
            else:
                possible.append(x.upper())

        return possible

    def getAction(self, state):
        power = set(self.get_possible_power(state))
        food = set(self.get_possible_food(state))
        legal = self.get_legal_moves(state)
        legal_set = set(legal)
        legal_objective_moves = list((legal_set & food) | (legal_set & power))

        if legal_objective_moves:
            index = random.randint(0, len(legal_objective_moves) - 1)
            self.last = legal_objective_moves[index]
            return self.mapper[self.last]

        if self.last not in legal:
            index = random.randint(0, len(legal) - 1)
            self.last = legal[index]
            return self.mapper[self.last]
        else:
            return self.mapper[self.last]

# EXTRA CREDIT
class AvoidGhostAgent(SurroundingAwareAgent):
    def __init__(self):
        self.last = None
        self.mapper = {
            'WEST': Directions.WEST,
            'EAST': Directions.EAST,
            'STOP': Directions.STOP,
            'SOUTH': Directions.SOUTH,
            'NORTH': Directions.NORTH
        }

    def get_possible_move_away_from_ghost(self, state):
        ghost = state.getGhostPositions()
        possible = []
        current_position = state.getPacmanPosition()
        current_position_x = current_position[0]
        current_position_y = current_position[1]

        for coordinate in ghost:
            # opposite to run away
            for diff in xrange(1, 5):
                if coordinate == (current_position_x + diff, current_position_y):
                    possible.append('WEST')
                if coordinate == (current_position_x - diff, current_position_y):
                    possible.append('EAST')
                if coordinate == (current_position_x, current_position_y + diff):
                    possible.append('SOUTH')
                if coordinate == (current_position_x, current_position_y - diff):
                    possible.append('NORTH')

        return possible

    def getAction(self, state):
        power = set(self.get_possible_power(state))
        food = set(self.get_possible_food(state))
        legal = self.get_legal_moves(state)
        legal_set = set(legal)
        legal_objective_moves = list((legal_set & food) | (legal_set & power))
        ghost = self.get_possible_move_away_from_ghost(state)
        ghost_set = set(ghost)
        legal_ghost_move = list(ghost_set & legal_set)

        if legal_ghost_move:
            print 'ghost near'
            index = random.randint(0, len(legal_ghost_move) - 1)
            self.last = legal_ghost_move[index]
            return self.mapper[self.last]

        if legal_objective_moves:
            index = random.randint(0, len(legal_objective_moves) - 1)
            self.last = legal_objective_moves[index]
            return self.mapper[self.last]

        if self.last not in legal:
            index = random.randint(0, len(legal) - 1)
            self.last = legal[index]
            return self.mapper[self.last]
        else:
            return self.mapper[self.last]
