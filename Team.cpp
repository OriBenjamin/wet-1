//
// Created by liels on 28/11/2022.
//

#include "Team.h"
#include "Player.h"

Team::Team(int teamId, int points, int goalsSum, int cardsSum, int teamGamesPlayed,
           int goalKeepers, const Player* topScorerPlayer):
           teamId(teamId), points(points), topScorerPlayer(nullptr), players(), playersByStatistics()
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
    topScorerPlayer = playersByStatistics.getLastNode();
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
    topScorerPlayer = playersByStatistics.getLastNode();
    if(player.getPlayerCanBeGooalkeeper())
    {
        goalKeepers--;
    }
}

/*std::ostream &operator<<(std::ostream &os, const Team &team) {
    os << "teamId: " << team.teamId << " players: " << team.players << " playersByStatistics: "
       << team.playersByStatistics;
    return os;
}*/

Player *Team::getTopScorerPlayer() const {
    return topScorerPlayer;
}

int Team::getID() const {
    return teamId;
}

int Team::getSize() const {
    return players.getSize();
}

void Team::setGoalKeepers(int goalKeepers) {
    this->goalKeepers = goalKeepers;
}

int Team::getGoalKeepers() const {
    return this->goalKeepers;
}

int Team::getPoints() const {
    return points;
}

int Team::getGoalSum() const {
    return goalSum;
}

int Team::getCardSum() const {
    return cardSum;
}

int Team::getTeamGamesPlayed() const {
    return teamGamesPlayed;
}

void Team::setPoints(int points) {
    Team::points = points;
}

void Team::setGoalSum(int goalSum) {
    Team::goalSum = goalSum;
}

void Team::setCardSum(int cardSum) {
    Team::cardSum = cardSum;
}

void Team::setTeamGamesPlayed(int teamGamesPlayed) {
    Team::teamGamesPlayed = teamGamesPlayed;
}


