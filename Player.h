//
// Created by liels on 28/11/2022.
//

#ifndef wet_1_PLAYER_H
#define wet_1_PLAYER_H

#include <stdexcept>
#include <string>
#include <ostream>
#include "Team.h"

class Player
{
    private:
    int playerId;
    int gamesPlayed;
    int goals;

private:
    int cardsReceived;
    bool canBeGoalkeeper;
    Team* team;

public:
    Player() = delete;
    Player(int playerId, int gamesPlayed, int goals, int cardsReceived, bool canBeGoalkeeper, Team* team);
    ~Player() = default;
    Player(const Player& p) = default;
    Player& operator=(const Player& p) = default;


    void updatePlayer(int gamesPlayed, int goals, int cardsReceived);
    bool operator<(const Player& player) const;
    bool operator==(const Player& player) const;

    //const getters
    int getPlayerId() const {return this->playerId;}
    int& getPlayerIdRef() {return this->playerId;}
    int getPlayerGamesPlayed() const {return this->gamesPlayed;}
    int getPlayerGoals() const {return this->goals;}
    int getPlayerCardsReceived() const {return this->cardsReceived;}
    bool getPlayerCanBeGooalkeeper() const {return this->canBeGoalkeeper;}
    Team *getTeam() const {return team;}

    //getters
    int& getPlayerId() {return this->playerId;}

    /*friend std::ostream &operator<<(std::ostream &os, const Player &player);

    void setGamesPlayed(int gamesPlayed);
    void setGoals(int goals);
    void setCardsReceived(int cardsReceived);*/
};

bool operator>(const Player& player1, const Player& player2);


#endif //wet_1_PLAYER_H
