//
// Created by liels on 28/11/2022.
///

#ifndef HW1_TEAM_H
#define HW1_TEAM_H

#include <stdlib.h>
#include <string>
#include "Tree.h"
#include "Player.h"

const int INITIAL_SIZE_OF_TEAM = 0;
class Team
{
    private:
    int teamId;
    int points;
    Tree<int,Player> players;
    Tree<Player,Player> fightingPlayers;
    int goalSum;
    int cardSum;
    int teamGamesPlayed;=0
    int topScorer;=update in every insert
    bool hasGoalKeeper;=upate in every insert

    public:
    Team() = delete;
    Team(int TeamId, int Points, int GoalsSum, int CardsSum,int TeamGamesPlayed, int TopScorer, bool HasGoalKeeper):
    TeamId(TeamId), Points(Points), Size(INITIAL_SIZE_OF_TEAM), GoalsSum(GoalsSum), CardsSum(CardsSum),
    TeamGamesPlayed(TeamGamesPlayed), TopScorer(TopScorer), HasGoalKeeper(HasGoalKeeper) {}
    ~Team() = default;
    Team(const Team& t) = delete;
    Team& operator=(const Team& t) = delete;
    insertPlayer
    removePlayer

    class InvalidArgument: public std::exception
    {
        public:
        const std::string what() const override {return "An invalid argument has passed";}
    };
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
    void setHasGoalKeeper(bool HasGoalKeeper); //not sure
};

*/
#endif //HW1_TEAM_H
