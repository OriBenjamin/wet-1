//
// Created by liels on 28/11/2022.
//

#include "Player.h"

Player::Player(int playerId, int gamesPlayed, int goals, int cardsReceived, bool canBeGoalkeeper, Team* team):
playerId(playerId), gamesPlayed(gamesPlayed), goals(goals), playerNodeInStats(nullptr),
cardsReceived(cardsReceived), canBeGoalkeeper(canBeGoalkeeper), team(team) {}


bool Player::operator<(const Player& player) const
{
    if(this->playerId == player.playerId)
    {
        throw std::invalid_argument("invalid argument- cant compare player to himself");
    }
    if(this->goals < player.goals)
    {
        return true;
    }
    else if(this->goals > player.goals)
    {
        return false;
    }
    else
    {
        if(this->cardsReceived > player.cardsReceived)
        {
            return true;
        }
        else if(this->cardsReceived < player.cardsReceived)
        {
            return false;
        }
        else
        {
            if(this->playerId < player.playerId)
            {
                return true;
            }
            else if(this->playerId > player.playerId)
            {
                return false;
            }
        }
    }
    throw std::logic_error("logic error- something went wrong with players comparison");
}

bool operator>(const Player& player1, const Player& player2)
{
    return (!(player1 < player2) && !(player1==player2));
}

bool Player::operator==(const Player& player) const
{
    return this->playerId == player.playerId;
}

Node<Player, Player> *Player::getPlayerNodeInStats() const {
    return playerNodeInStats;
}

void Player::setPlayerNodeInStats(Node<Player, Player> *playerNodeInStats) {
    Player::playerNodeInStats = playerNodeInStats;
}

void Player::setTeam(Team *team) {
    Player::team = team;
}


void updatePlayersFields(Tree<Player,Player>* statsTree)
{
    Node<Player,Player>** nodeArray = new Node<Player,Player>*[statsTree->getSize()];
    int index = 0;
    convertTreeToPointersArray(statsTree->getRoot(), nodeArray,index);
    for(int i=0; i<statsTree->getSize(); i++)
    {
        nodeArray[i]->value->setPlayerNodeInStats(nodeArray[i]);
    }
    delete[] nodeArray;
}