//
// Created by liels on 28/11/2022.
//

#include "Player.h"

Player::Player(int playerId, int gamesPlayed, int goals, int cardsReceived, bool canBeGoalkeeper, Team* team):
playerId(playerId), gamesPlayed(gamesPlayed), goals(goals), playerNodeInStats(nullptr),
cardsReceived(cardsReceived), canBeGoalkeeper(canBeGoalkeeper), team(team)
{
    /*if(playerId<=0 || gamesPlayed<0 || goals<0 || cardsReceived<0 ||
    (gamesPlayed == 0 && (cardsReceived>0 || goals>0)) || team == nullptr)
    {
       throw std::invalid_argument("Invalid input- can't build such player");
    }*/
}

void Player::updatePlayer(int gamesPlayed, int goals, int cardsReceived)
{
    if(gamesPlayed<0 || goals<0 || cardsReceived<0)
    {
        throw std::invalid_argument("Invalid input");
    }
    this->gamesPlayed+= gamesPlayed;
    this->goals+= goals;
    this->cardsReceived+= cardsReceived;
}
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

std::ostream &operator<<(std::ostream &os, const Player &player) {
    os << "playerId: " << player.playerId << " teamId: " << player.team->getTeamId() << " gamesPlayed: " << player.gamesPlayed
       << " goals: " << player.goals << " cardsReceived: " << player.cardsReceived << " canBeGoalkeeper: "
       << player.canBeGoalkeeper;
    return os;
}


Node<Player, Player> *Player::getPlayerNodeInStats() const {
    return playerNodeInStats;
}

void Player::setPlayerNodeInStats(Node<Player, Player> *playerNodeInStats) {
    Player::playerNodeInStats = playerNodeInStats;
}



/*
void Player::setTeamId(int TeamId)
{
    if(TeamId < 0)
    {
        throw InvalidArgument();
    }
    this->TeamId = TeamId;
}
void Player::setGamesPlayed(int GamesPlayed)
{
    if(GamesPlayed < 0)
    {
        throw InvalidArgument();
    }
    this->GamesPlayed = GamesPlayed;
}
void Player::setGoals(int Goals)
{
    if(Goals < 0)
    {
        throw InvalidArgument();
    }
    this->Goals = Goals;
}
void Player::setCards_received(int Cards_received)
{
    if(Cards_received < 0)
    {
        throw InvalidArgument();
    }
    this->Cards_received = Cards_received;
}
void Player::setCan_be_Gooalkeeper(bool Can_be_Gooalkeeper)
{
    this->Can_be_Gooalkeeper = Can_be_Gooalkeeper;
}*/