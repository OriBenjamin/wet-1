//
// Created by liels on 28/11/2022.
//

#ifndef wet_1_PLAYER_H
#define wet_1_PLAYER_H

#include <stdexcept>
#include <string>
#include "Team.h"

class Player
{
    private:
    int playerId;
    int teamId;
    int gamesPlayed;
    int goals;
    int cardsReceived;
    bool canBeGoalkeeper;
    Team* team;


    public:
    Player() = delete;
    Player(int playerId, int teamId, int gamesPlayed, int goals, int cardsReceived, bool canBeGoalkeeper, Team* team);
    ~Player() = default;
    Player(const Player& p) = delete;
    Player& operator=(const Player& p) = delete;


    void updatePlayer(int gamesPlayed, int goals, int cardsReceived);
    bool operator<(const Player& player) const;
    bool operator==(const Player& player) const;

    //const getters
    int getPlayerId() const {return this->playerId;}
    int getPlayerTeamId() const {return this->teamId;}
    int getPlayerGamesPlayed() const {return this->gamesPlayed;}
    int getPlayerGoals() const {return this->goals;}
    int getPlayerCardsReceived() const {return this->cardsReceived;}
    bool getPlayerCanBeGooalkeeper() const {return this->canBeGoalkeeper;}

    //getters
    int& getPlayerId() {return this->playerId;}


};

bool operator>(const Player& player1, const Player& player2);


#endif //wet_1_PLAYER_H
