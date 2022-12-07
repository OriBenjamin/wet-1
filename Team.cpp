//
// Created by liels on 28/11/2022.
//

#include "Team.h"
#include "Player.h"

Team::Team(int teamId, int points, int goalsSum, int cardsSum, int teamGamesPlayed,
           int goalKeepers, const Player* topScorerPlayer):
           teamId(teamId), points(points), players(), playersByStatistics(), topScorerPlayer(nullptr)
           {
               if(teamId<=0 || points<0)
               {
                   throw std::invalid_argument("Invalid input- can't build such team");
               }
           }

void Team::insertPlayer(Player& player)
{

    players.insert(player.getPlayerId(), &player);
    playersByStatistics.insert(player, &player);
    goalSum+=player.getPlayerGoals();
    cardSum+=player.getPlayerCardsReceived();
    if(topScorerPlayer == nullptr)
    {
        topScorerPlayer = &player;
    }
    else if(player.getPlayerGoals() > topScorerPlayer->getPlayerGoals())
    {
        topScorerPlayer = &player;
        //topScorerPlayer->getPlayerId() = player.getPlayerId();
    }
    if(player.getPlayerCanBeGooalkeeper())
    {
        goalKeepers++;
    }
}

void Team::removePlayer( Player& player)
{
    players.remove(player.getPlayerId());
    playersByStatistics.remove(player);
    goalSum-=player.getPlayerGoals();
    cardSum-=player.getPlayerCardsReceived();
    topScorerPlayer = playersByStatistics.getLast();
    if(player.getPlayerCanBeGooalkeeper())
    {
        goalKeepers--;
    }
}

std::ostream &operator<<(std::ostream &os, const Team &team) {
    os << "teamId: " << team.teamId << " players: " << team.players << " playersByStatistics: "
       << team.playersByStatistics;
    return os;
}

Player *Team::getTopScorerPlayer() const {
    return topScorerPlayer;
}

int Team::getID() const {
    return teamId;
}

int Team::getSize() const {
    return players.getSize();
}


