//
// Created by liels on 28/11/2022.
//

#include "Team.h"
#include "Player.h"

Team::Team(int teamId, int points, int goalsSum, int cardsSum, int teamGamesPlayed,
           int goalKeepers, const Player* topScorerPlayer):
           teamId(teamId), points(points), players(), playersByStatistics() {}

void Team::insertPlayer(Player& player)
{

    players.insert(player.getPlayerId(), &player);
    playersByStatistics.insert(player, &player);
    goalSum+=player.getPlayerGoals();
    cardSum+=player.getPlayerCardsReceived();
    if(player.getPlayerGoals() > topScorerPlayer->getPlayerGoals())
    {
        topScorerPlayer = &player;
        topScorerPlayer->getPlayerId() = player.getPlayerId();
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


