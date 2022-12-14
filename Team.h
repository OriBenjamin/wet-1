//
// Created by liels on 28/11/2022.
///

#ifndef wet_1_TEAM_H
#define wet_1_TEAM_H

#include <cstdlib>
#include <ostream>
#include "Tree.h"
class Player;

class Team
{
    int teamId;
    int points;
    int goalSum;
    int cardSum;
    int teamGamesPlayed;
    int goalKeepers;
    Player* topScorerPlayer;
    Tree<int,Player> players; //sorted by Id
    Tree<Player,Player> playersByStatistics;

    public:
    Team() = delete;
    Team(int teamId, int points);
    ~Team() {this->deleteTeamNodes(false);};
    Team(const Team& t) = delete;
    Team& operator=(const Team& t) = delete;

    void insertPlayer(Player& player);
    void removePlayer(Player& player);
    void deleteTeamNodes(bool deleteValues);
    void updatePlayersFields(Team* team);

    //const getters
    int getTeamId() const {return teamId;}
    int getPoints() const {return points;}
    int getGoalSum() const {return goalSum;}
    int getCardSum() const {return cardSum;}
    int getGoalKeepers() const {return goalKeepers;}
    int getTeamGamesPlayed() const {return teamGamesPlayed;}
    Player *getTopScorerPlayer() const {return topScorerPlayer;}
    int getSize() const {return players.getSize();}
     Tree<int,Player>* getPlayers() {return &players;}
     Tree<Player,Player>* getPlayersByStatistics() {return &playersByStatistics;}

    //getter
    int& getTeamIdRef() {return this->teamId;}

    //setters
    void setGoalKeepers(int goalKeepers) {this->goalKeepers=goalKeepers;};
    void setPoints(int points) {this->points=points;};
    void setGoalSum(int goalSum) {this->goalSum=goalSum;};
    void setCardSum(int cardSum) {this->cardSum=cardSum;};
    void setTeamGamesPlayed(int teamGamesPlayed) {this->teamGamesPlayed=teamGamesPlayed;};
    void setPlayers(const Tree<int, Player> &players);
    void setPlayersByStatistics(const Tree<Player, Player> &playersByStatistics);
};


#endif //wet_1_TEAM_H