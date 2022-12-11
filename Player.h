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
    Node<Player,Player>* playerNodeInStats;
    int cardsReceived;
    bool canBeGoalkeeper;
    Team* team;

public:
    Player() = default;
    Player(int playerId, int gamesPlayed, int goals, int cardsReceived, bool canBeGoalkeeper, Team* team);
    ~Player() = default;
    Player(const Player& p) = default;
    Player& operator=(const Player& p) = default;

    bool operator<(const Player& player) const;
    bool operator==(const Player& player) const;

    //const getters
    int getPlayerGamesPlayed() const {return this->gamesPlayed;}
    int getPlayerGoals() const {return this->goals;}
    int getPlayerCardsReceived() const {return this->cardsReceived;}
    bool getPlayerCanBeGoalkeeper() const {return this->canBeGoalkeeper;}
    Node<Player, Player> *getPlayerNodeInStats() const;
    Team *getTeam() const {return team;}


    //getters
    int& getPlayerId() {return this->playerId;}

    //setters
    void setGamesPlayed(int gamesPlayed) {this->gamesPlayed = gamesPlayed;};
    void setGoals(int goals) {this->goals = goals;};
    void setCardsReceived(int cardsReceived) {this->cardsReceived = cardsReceived;};
    void setTeam(Team *team);
    void setPlayerNodeInStats(Node<Player, Player> *playerNodeInStats);
};
void updatePlayersFields(Tree<Player,Player>* statsTree);
bool operator>(const Player& player1, const Player& player2);


#endif //wet_1_PLAYER_H
