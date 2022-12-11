//
// Created by liels on 28/11/2022.
//

#include "Team.h"
#include "Player.h"

Team::Team(int teamId, int points):
           teamId(teamId), points(points), goalSum(0), cardSum(0), teamGamesPlayed(0), goalKeepers(0),
           topScorerPlayer(nullptr), players(), playersByStatistics() {}

void Team::insertPlayer(Player& player)
{

    players.insert(&player.getPlayerId(), &player);
    playersByStatistics.insert(&player, &player);
    goalSum+=player.getPlayerGoals();
    cardSum+=player.getPlayerCardsReceived();
    if(topScorerPlayer == nullptr)
    {
        topScorerPlayer = &player;
    }
    topScorerPlayer = playersByStatistics.getLastNodeValue();
    if(player.getPlayerCanBeGoalkeeper())
    {
        goalKeepers++;
    }
}

void Team::removePlayer( Player& player)
{
    players.remove(&player.getPlayerId());
    playersByStatistics.remove(&player);
    player.setPlayerNodeInStats(nullptr);
    goalSum-=player.getPlayerGoals();
    cardSum-=player.getPlayerCardsReceived();
    if(playersByStatistics.getSize() == 0) topScorerPlayer = nullptr;
    else topScorerPlayer = playersByStatistics.getLastNodeValue();
    if(player.getPlayerCanBeGoalkeeper())
    {
        goalKeepers--;
    }
}


void Team::deleteTeamNodes(bool deleteValues)
{
    if(deleteValues)
    {
        playersByStatistics.deleteTree(true);
        players.deleteTree(true);
    }
    else
    {
        playersByStatistics.deleteTree(false);
        players.deleteTree(false);
    }
}

void Team::setPlayers(const Tree<int, Player> &players) {
  //  this->players.setRoot(nullptr);
    this->players = players;
}

void Team::setPlayersByStatistics(const Tree<Player, Player> &playersByStatistics) {
  //  Team::players.setRoot(nullptr);
    Team::playersByStatistics = playersByStatistics;
}


void Team::updatePlayersFields(Team* thisTeam) //O(n)
{
    Node<Player,Player>** nodeArray = new Node<Player,Player>*[this->getSize()];
    int index = 0;
    convertTreeToPointersArray(this->playersByStatistics.getRoot(), nodeArray,index);
    for(int i=0; i<this->getSize(); i++)
    {
        nodeArray[i]->value->setGamesPlayed(nodeArray[i]->value->getPlayerGamesPlayed()+teamGamesPlayed);
        nodeArray[i]->value->setTeam(thisTeam);
    }
    this->setTeamGamesPlayed(0);
    delete[] nodeArray;
}