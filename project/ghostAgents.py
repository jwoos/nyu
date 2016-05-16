# ghostAgents.py
# --------------
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


from game import Agent
from game import Actions
from game import Directions
import random
from util import manhattanDistance
import util

class GhostAgent( Agent ):
    def __init__( self, index ):
        self.index = index

    def getAction( self, state ):
        dist = self.getDistribution(state)
        if len(dist) == 0:
            return Directions.STOP
        else:
            return util.chooseFromDistribution( dist )

    def getDistribution(self, state):
        "Returns a Counter encoding a distribution over actions from the provided state."
        util.raiseNotDefined()

class RandomGhost( GhostAgent ):
    "A ghost that chooses a legal action uniformly at random."
    def getDistribution( self, state ):
        dist = util.Counter()
        for a in state.getLegalActions( self.index ): dist[a] = 1.0
        dist.normalize()
        return dist

class DirectionalGhost( GhostAgent ):
    "A ghost that prefers to rush Pacman, or flee when scared."
    def __init__( self, index, prob_attack=0.8, prob_scaredFlee=0.8 ):
        self.index = index
        self.prob_attack = prob_attack
        self.prob_scaredFlee = prob_scaredFlee

    def getDistribution( self, state ):
        # Read variables from state
        ghostState = state.getGhostState( self.index )
        legalActions = state.getLegalActions( self.index )
        pos = state.getGhostPosition( self.index )
        isScared = ghostState.scaredTimer > 0

        speed = 1
        if isScared: speed = 0.5

        actionVectors = [Actions.directionToVector( a, speed ) for a in legalActions]
        newPositions = [( pos[0]+a[0], pos[1]+a[1] ) for a in actionVectors]
        pacmanPosition = state.getPacmanPosition()

        # Select best actions given the state
        distancesToPacman = [manhattanDistance( pos, pacmanPosition ) for pos in newPositions]
        if isScared:
            bestScore = max( distancesToPacman )
            bestProb = self.prob_scaredFlee
        else:
            bestScore = min( distancesToPacman )
            bestProb = self.prob_attack
        bestActions = [action for action, distance in zip( legalActions, distancesToPacman ) if distance == bestScore]

        # Construct distribution
        dist = util.Counter()
        for a in bestActions: dist[a] = bestProb / len(bestActions)
        for a in legalActions: dist[a] += ( 1-bestProb ) / len(legalActions)
        dist.normalize()
        return dist


# python2 pacman.py -g Clyde -k 1
class Clyde(GhostAgent):
    def __init__(self, index, prob_attack=0.85, prob_scaredFlee=0.85):
        self.index = index
        self.prob_attack = prob_attack
        self.prob_scaredFlee = prob_scaredFlee
        # custom scared value for when getting too near pacman
        # no way to access scared value or set it
        self.scared = 0

    def getDistribution(self, state):
        ghost_state = state.getGhostState(self.index)
        legal_actions = state.getLegalActions(self.index)
        position = state.getGhostPosition(self.index)
        is_scared = ghost_state.scaredTimer > 0
        pacman_position = state.getPacmanPosition()
        left_corner = (1,1)

        speed = 1 if not is_scared or self.scared else 0.5

        # list comprehension to generate possible new positions
        # first it gets possible movements in the form of a list of tuples of the x and y
        # 1 means right/up -1 left/down
        possible_new_positions = [
            (position[0] + move[0], position[1] + move[1])\
                    for move in [Actions.directionToVector(action, speed) for action in legal_actions]
        ]

        # check distances to Pacman
        distances_to_pacman = [manhattanDistance(possible_position, pacman_position) \
                for possible_position in possible_new_positions]

        distances_to_corner = [manhattanDistance(possible_position, left_corner)\
                 for possible_position in possible_new_positions]

        if manhattanDistance(position, pacman_position) <= 5 and not self.scared:
            # 15 second scared timer when too close to pacman
            self.scared = 15

        if self.scared > 0:
            self.scared -= 1

        best_actions = []
        best_prob = 0

        if is_scared or self.scared:
            # if scared currently, the best option is the distance furthest
            # from pacman as it is trying to run away
            best_to_pacman = max(distances_to_pacman)
            best_to_corner = min(distances_to_corner)
            for x, y in zip(legal_actions, distances_to_corner):
                if y == best_to_corner:
                    best_actions.append(x)
            for x, y in zip(legal_actions, distances_to_pacman):
                if y == best_to_pacman:
                    best_actions.append(x)
            best_prob = self.prob_scaredFlee
        else:
            best_to_pacman = min(distances_to_pacman)
            best_prob = self.prob_attack
            for x, y in zip(legal_actions, distances_to_pacman):
                if y == best_to_pacman:
                    best_actions.append(x)

        # Construct distribution
        dist = util.Counter()

        for action in best_actions:
            if dist[action]:
                dist[action] += best_prob / len(best_actions)
            else:
                dist[action] = best_prob / len(best_actions)

        for action in legal_actions:
            dist[action] += ( 1 - best_prob ) / len(legal_actions)

        dist.normalize()
        return dist
