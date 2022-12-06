//
// Created by liels on 28/11/2022.
///

#ifndef wet_1_TEAM_H
#define wet_1_TEAM_H

#include <cstdlib>
#include "Tree.h"
#include "Player.h"

class Team
{
    private:
    int teamId;
    int points;
    int goalSum;
    int cardSum;
    int teamGamesPlayed;
    int goalKeepers;
    Player* topScorerPlayer;
    Tree<int,Player> players;
    Tree<Player,Player> playersByStatistics;

    public:
    Team() = delete;
    Team(int teamId, int points, int goalsSum = 0, int cardsSum = 0, int teamGamesPlayed = 0,
         int goalKeepers = 0, const Player* topScorerPlayer= nullptr);
    ~Team() = default;
    Team(const Team& t) = delete;
    Team& operator=(const Team& t) = delete;
    void insertPlayer(Player& player);
    void removePlayer(const Player& player);

/*
    //const getters
    int getTeamId() const {return this->TeamId;}
    int getPoints() const {return this->Points;}
    int getSize() const {return this->Size;}
    Tree<Shared_ptr<Player>, Comperator> getPlayers() const {return this->Players;}
    int getGoalsSum() const {return this->GoalsSum;}
    int getCardsSum() const {return this->CardsSum;}
    int getTeamGamesPlayed() const {return this->TeamGamesPlayed;}
    int getTopScorer() const {return this->TopScorer;}
    bool getHasGoalKeeper() const {return this->HasGoalKeeper;}

    //getters
    int& getTeamId() {return this->TeamId;}
    int& getPoints() {return this->Points;}
    int& getSize() {return this->Size;}
    Tree<Shared_ptr<Player>, Comperator>& getPlayers() {return this->Players;}
    int& getGoalsSum() {return this->GoalsSum;}
    int& getCardsSum() {return this->CardsSum;}
    int& getTeamGamesPlayed() {return this->TeamGamesPlayed;}
    int& getTopScorer() {return this->TopScorer;}
    bool& getHasGoalKeeper() {return this->HasGoalKeeper;}

    //setters
    void setPoints(int points);
    int setSize(int size);
    void setPlayers(const Tree<Shared_ptr<Player>, Comperator>& players); //not sure
    void setGoalsSum(int GoalsSum);
    void setCardsSum(int CardsSum);
    void setTeamGamesPlayed(int TeamGamesPlayed);
    void setHasGoalKeeper(bool HasGoalKeeper); //not sure */
};


#endif //wet_1_TEAM_H