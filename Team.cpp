//
// Created by liels on 28/11/2022.
//

#include "Team.h"
#include "Player.h"

Team::Team(int teamId, int points):
           teamId(teamId), points(points), goalSum(0), cardSum(0), teamGamesPlayed(0), goalKeepers(0),
           topScorerPlayer(nullptr), players(), playersByStatistics()
{
    if(teamId<=0 || points<0)
    {
        throw std::invalid_argument("Invalid input- can't build such team");
    }
}

void Team::insertPlayer(Player& player)
{

    players.insert(&player.getPlayerIdRef(), &player);
    playersByStatistics.insert(&player, &player);
    goalSum+=player.getPlayerGoals();
    cardSum+=player.getPlayerCardsReceived();
    if(topScorerPlayer == nullptr)
    {
        topScorerPlayer = &player;
    }
    topScorerPlayer = playersByStatistics.getLastNodeValue();
    if(player.getPlayerCanBeGooalkeeper())
    {
        goalKeepers++;
    }
}

void Team::removePlayer( Player& player)
{
    Player* p = players.remove(&player.getPlayerId());
    playersByStatistics.remove(&player);
    goalSum-=player.getPlayerGoals();
    cardSum-=player.getPlayerCardsReceived();
    topScorerPlayer = playersByStatistics.getLastNodeValue();
    if(player.getPlayerCanBeGooalkeeper())
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


std::ostream &operator<<(std::ostream &os, const Team &team) {
    os << "teamId: " << team.teamId << " players: " << team.players << " playersByStatistics: "
       << team.playersByStatistics;
    return os;
}

void Team::setPlayers(const Tree<int, Player> &players) {
    Team::players = players;
}

void Team::setPlayersByStatistics(const Tree<Player, Player> &playersByStatistics) {
    Team::playersByStatistics = playersByStatistics;
}



void Team::updatePlayersGamePlayed() //O(n)
{
    Node<int,Player>** nodeArray = new Node<int,Player>*[this->getSize()];
    int index = 0;
    convertTreeToPointersArray(this->players.getRoot(), nodeArray,index);
    for(int i=0; i<this->getSize(); i++)
    {
        nodeArray[i]->value->setGamesPlayed(nodeArray[i]->value->getPlayerGamesPlayed()+teamGamesPlayed);
    }
    this->setTeamGamesPlayed(0);
}