#include "worldcup23a1.h"

world_cup_t::world_cup_t():
teams(), playersById(), playersByStatistics(), knockoutTeams(), topScorerPlayer(nullptr) {}

world_cup_t::~world_cup_t()
{
    knockoutTeams.deleteTree(false);
    teams.deleteTree(true);
    playersByStatistics.deleteTree(false);
    playersById.deleteTree(true);
}

StatusType world_cup_t::add_team(int teamId, int points)
{
    try
    {
        Team *team = new Team(teamId, points);
        teams.insert(&team->getTeamIdRef(),team);
    }
    catch(std::invalid_argument& e)
    {
        return StatusType::INVALID_INPUT;
    }
    catch (std::bad_alloc& e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    catch (NodeAlreadyExist&)
    {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId)
{
    if(teamId<=0)
    {
        return StatusType::INVALID_INPUT;
    }
    Team* team;
    try
    {
        team = teams.find(&teamId);
        if (team->getSize() != 0)
        {
            return StatusType::FAILURE;
        }
        team = teams.remove(&teamId);
        delete team;
        team = nullptr;
        if(knockoutTeams.exists(&teamId)) knockoutTeams.remove(&teamId);
    }
    catch (NodeDoesNotExist&)
    {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType world_cup_t::add_player(int playerId, int teamId, int gamesPlayed,
                                   int goals, int cards, bool goalKeeper)
{
    try
    {
        if(playerId<=0 || teamId<=0 || gamesPlayed<0 || goals<0 || cards<0 ||
           (gamesPlayed == 0 && (cards>0 || goals>0)) ) //Invalid Input should be checked first
        {
            return StatusType::INVALID_INPUT;
        }
        if(playersById.exists(&playerId)) return StatusType::FAILURE;
        Team* team = teams.find(&teamId);
        Player* player = new Player(playerId,gamesPlayed-team->getTeamGamesPlayed(),goals,cards,goalKeeper,team);
        team->insertPlayer(*player);
        playersById.insert(&(player->getPlayerIdRef()), player);
        playersByStatistics.insert(player, player);
        topScorerPlayer =  playersByStatistics.getLastNodeValue();
        Node<Player,Player>* playerNode = playersByStatistics.findNode(playersByStatistics.getRoot(), player);
        player->setPlayerNodeInStats(playerNode);
        if(team->getSize() >= 11 && team->getGoalKeepers() > 0 && !knockoutTeams.exists(&team->getTeamIdRef()))
        {
            knockoutTeams.insert(&team->getTeamIdRef(), team);
        }
    }
    catch(std::invalid_argument& e)
    {
        return StatusType::INVALID_INPUT;
    }
    catch(std::bad_alloc& e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    catch(NodeAlreadyExist& e)
    {
        return StatusType::FAILURE;
    }
    catch(NodeDoesNotExist& e)
    {
        return StatusType::FAILURE;
    }

    return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_player(int playerId)
{
    try
    {
        if(playerId <= 0)
        {
            return StatusType::INVALID_INPUT;
        }
        Player* player = playersById.remove(&playerId);
        playersByStatistics.remove(player);
        Team* team = player->getTeam();
        team->removePlayer(*player);
        if(playersByStatistics.getSize() == 0) topScorerPlayer = nullptr;
        else topScorerPlayer = playersByStatistics.getLastNodeValue();
        if(team->getSize() < 11 || team->getGoalKeepers() <= 0) {
            if (knockoutTeams.exists(&(team->getTeamIdRef()))) knockoutTeams.remove(&(team->getTeamIdRef()));
        }
        delete player;
        player = nullptr;
    }
    catch(NodeDoesNotExist&)
    {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType world_cup_t::update_player_stats(int playerId, int gamesPlayed,
                                            int scoredGoals, int cardsReceived) //knockout teams!!!
{
    if(playerId<=0 || gamesPlayed<0 || scoredGoals<0 || cardsReceived<0)
    {
        return  StatusType::INVALID_INPUT;
    }
    try
    {
        Player *player = playersById.find(&playerId);
        playersByStatistics.remove(player);
        player->getTeam()->removePlayer(*player);
        playersById.remove(&playerId);
        player->setGamesPlayed(player->getPlayerGamesPlayed()+gamesPlayed);
        player->setCardsReceived(player->getPlayerCardsReceived()+cardsReceived);
        player->setGoals(player->getPlayerGoals()+scoredGoals);
        playersById.insert(&(player->getPlayerId()), player);
        playersByStatistics.insert(player,player);
        player->getTeam()->insertPlayer(*player);
        topScorerPlayer =  playersByStatistics.getLastNodeValue();
    }
    catch (NodeDoesNotExist&)
    {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType world_cup_t::play_match(int teamId1, int teamId2)
{
    if(teamId1<=0 || teamId2<=0 || teamId1==teamId2)
    {
        return StatusType::INVALID_INPUT;
    }
    try
    {
        Team* team1 = teams.find(&teamId1);
        Team* team2 = teams.find(&teamId2);
        if(!knockoutTeams.exists(&teamId1) || !knockoutTeams.exists(&teamId2))
        {
           return StatusType::FAILURE;
        }
        int team1Result = team1->getPoints() + team1->getGoalSum() - team1->getCardSum();
        int team2Result = team2->getPoints() + team2->getGoalSum() - team2->getCardSum();
        if(team1Result == team2Result)
        {
            team1->setPoints(team1->getPoints() + 1);
            team2->setPoints(team2->getPoints() + 1);
        }
        else if(team1Result > team2Result)
        {
            team1->setPoints(team1->getPoints() + 3);
        }
        else if(team1Result < team2Result)
        {
            team2->setPoints(team2->getPoints() + 3);
        }
        team1->setTeamGamesPlayed(team1->getTeamGamesPlayed() + 1);
        team2->setTeamGamesPlayed(team2->getTeamGamesPlayed() + 1);
    }
    catch(NodeDoesNotExist&)
    {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_num_played_games(int playerId)
{
    if(playerId<=0)
    {
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    try
    {
        Player* player = playersById.find(&playerId);
        int totalGames = player->getPlayerGamesPlayed() + (player->getTeam())->getTeamGamesPlayed();
        if(totalGames < 0) totalGames = 0;
        return output_t<int>(totalGames);
    }
    catch(NodeDoesNotExist& e)
    {
        return output_t<int>(StatusType::FAILURE);
    }
    catch(std::bad_alloc& e)
    {
        return output_t<int>(StatusType::ALLOCATION_ERROR);
    }
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
    if(teamId<=0)
    {
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    try
    {
        Team* team = teams.find(&teamId);
        return output_t<int>(team->getPoints());
    }
    catch(NodeDoesNotExist& e)
    {
        return output_t<int>(StatusType::FAILURE);
    }
}

StatusType world_cup_t::unite_teams(int teamId1, int teamId2, int newTeamId) {
    if(teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2 || newTeamId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }

    if(teams.exists(&newTeamId) && newTeamId != teamId1 && newTeamId != teamId2) return StatusType::FAILURE;

    try {
            Team *team1 = teams.find(&teamId1);
            team1->updatePlayersGamePlayed();
            Team *team2 = teams.find(&teamId2);
            team2->updatePlayersGamePlayed();
            Team *team3 = new Team(newTeamId, team1->getPoints() + team1->getPoints());
            team3->setPlayers(mergeTrees(*team1->getPlayers(), *team2->getPlayers()));
            team3->setPlayersByStatistics(mergeTrees(*team1->getPlayersByStatistics(), *team2->getPlayersByStatistics()));
            team3->setTeamGamesPlayed(0); //update team games
            team3->setCardSum(team1->getCardSum() + team2->getCardSum());
            team3->setGoalSum(team1->getGoalSum() + team2->getGoalSum());
            team3->setGoalKeepers(team1->getGoalKeepers() + team2->getGoalKeepers());
            remove_team(teamId1);
            remove_team(teamId2);
            teams.insert(&team3->getTeamIdRef(), team3);
            if (team3->getSize() >= 11 && team3->getGoalKeepers() > 0) {
                knockoutTeams.insert(&team3->getTeamIdRef(), team3);
            }
            return StatusType::SUCCESS;
    }
    catch(std::bad_alloc&)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    catch(NodeDoesNotExist&)
    {
        return StatusType::FAILURE;
    }
}

output_t<int> world_cup_t::get_top_scorer(int teamId)
{
    if(teamId==0)
    {
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    try
    {
        if(teamId>0)
        {
            Team* team = teams.find(&teamId);
            if(team->getSize() == 0)
            {
                return output_t<int>(StatusType::FAILURE);
            }
            return output_t<int>(team->getTopScorerPlayer()->getPlayerId());
        }
        else
        {
            if(topScorerPlayer == nullptr)
            {
                return output_t<int>(StatusType::FAILURE);
            }
            return output_t<int>(topScorerPlayer->getPlayerId());
        }
    }
    catch(NodeDoesNotExist& e)
    {
        return output_t<int>(StatusType::FAILURE);
    }
}

output_t<int> world_cup_t::get_all_players_count(int teamId)
{
    if(teamId==0)
    {
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    try
    {
        if(teamId>0)
        {
            Team* team = teams.find(&teamId);
            return output_t<int>(team->getSize());
        }
        else
        {
            return output_t<int>(playersById.getSize());
        }
    }
    catch(NodeDoesNotExist& e)
    {
        return output_t<int>(StatusType::FAILURE);
    }
}

StatusType world_cup_t::get_all_players(int teamId, int *const output)
{
    if(teamId==0 || output == NULL)
    {
        return StatusType::INVALID_INPUT;
    }
    if(playersById.getSize() == 0)
    {
        return StatusType::FAILURE;
    }
    try
    {
        int start = 0;
        int& index = start;

        if(teamId>0)
        {
            Team* team = teams.find(&teamId);
            Node<Player,Player>** nodesArray = new Node<Player,Player>*[team->getPlayersByStatistics()->getSize()];
            convertTreeToPointersArray(team->getPlayersByStatistics()->getRoot(), nodesArray, index);
            for(int i=0; i<index; i++)
            {
                output[i] = nodesArray[i]->getKey().getPlayerId();
            }
            delete[] nodesArray;
        }
        else
        {
            Node<Player,Player>** nodesArray = new Node<Player,Player>*[playersByStatistics.getSize()];
            convertTreeToPointersArray(playersByStatistics.getRoot(), nodesArray, index);
            for(int i=0; i<index; i++)
            {
                output[i] = nodesArray[i]->getKey().getPlayerId();
            }
            delete[] nodesArray;
        }
    }
    catch(NodeDoesNotExist& e)
    {
        return StatusType::FAILURE;
    }
    catch(std::bad_alloc& e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

int absolute(int a)
{
    return (a>0) ? a : -a;
}
output_t<int> world_cup_t::get_closest_player(int playerId, int teamId)
{
    if(playerId <= 0 || teamId <= 0)
    {
        return  output_t<int>(StatusType::INVALID_INPUT);
    }
    try
    {
        Team* team = teams.find(&teamId);
        Player* player = team->getPlayers()->find(&playerId);

        Node<Player,Player>* next = player->getPlayerNodeInStats()->next;
        Node<Player,Player>* prev = player->getPlayerNodeInStats()->prev;
        if(!next && prev) return prev->value->getPlayerId();
        if(next && !prev) return next->value->getPlayerId();
        if(!next && !prev) throw OnlyOneNodeInTree();
        //return output_t<int>((absolute(next->value->getPlayerId()-playerId) > absolute(prev->value->getPlayerId()-playerId)) ? prev->value->getPlayerId() : next->value->getPlayerId());
        return output_t<int>((*next->value > *prev->value) ? prev->value->getPlayerId() : next->value->getPlayerId());
    }
    catch(NodeDoesNotExist&)
    {
        return output_t<int>(StatusType::FAILURE);
    }
    catch(OnlyOneNodeInTree&)
    {
        return output_t<int>(StatusType::FAILURE);
    }
}

output_t<int> world_cup_t::knockout_winner(int minTeamId, int maxTeamId)
{
    if(minTeamId<0 || maxTeamId< 0 || minTeamId>maxTeamId)
    {
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    try
    {
        int start = 0;
        int& index = start;
        Node<int,Team>** allKnockoutTeamsArray = new Node<int,Team>*[knockoutTeams.getSize()];
        convertTreeToPointersArray(knockoutTeams.getRoot(), allKnockoutTeamsArray, index);
        int numOfKnockoutTeams = 0;
        for(int i=0; i<knockoutTeams.getSize(); i++)
        {
            int teamId = allKnockoutTeamsArray[i]->value->getTeamId();
            if(teamId>=minTeamId && teamId<=maxTeamId)
            {
                numOfKnockoutTeams++;
            }
        }
        if(numOfKnockoutTeams == 0)
        {
            return output_t<int>(StatusType::FAILURE);
        }
        Pair<int,int>* lastTeam = new Pair<int,int>(-1,-1);
        if(numOfKnockoutTeams % 2  != 0)
        {
            lastTeam->getFirst() = allKnockoutTeamsArray[numOfKnockoutTeams-1]->value->getTeamId();
            lastTeam->getSecond() = allKnockoutTeamsArray[numOfKnockoutTeams-1]->value->getPoints() +
                                    allKnockoutTeamsArray[numOfKnockoutTeams-1]->value->getGoalSum() -
                                    allKnockoutTeamsArray[numOfKnockoutTeams-1]->value->getCardSum();
            numOfKnockoutTeams--;
        }
        Pair<int,int>* finalKnockoutTeamArray = new Pair<int,int>[2*numOfKnockoutTeams];
        for(int i=numOfKnockoutTeams; i<2*numOfKnockoutTeams; i++)
        {
            finalKnockoutTeamArray[i].getFirst() = allKnockoutTeamsArray[i-numOfKnockoutTeams]->value->getTeamId();
            finalKnockoutTeamArray[i].getSecond() = allKnockoutTeamsArray[i-numOfKnockoutTeams]->value->getPoints() +
                                                       allKnockoutTeamsArray[i-numOfKnockoutTeams]->value->getGoalSum() -
                                                       allKnockoutTeamsArray[i-numOfKnockoutTeams]->value->getCardSum();
        }
        delete[] allKnockoutTeamsArray;
        playKnockout(finalKnockoutTeamArray, numOfKnockoutTeams);
        if(finalKnockoutTeamArray[1].getSecond() > lastTeam->getSecond())
        {
            int winner = finalKnockoutTeamArray[1].getFirst();
            delete lastTeam;
            delete[] finalKnockoutTeamArray;
            return winner;
        }
        else if(finalKnockoutTeamArray[1].getSecond() < lastTeam->getSecond())
        {
            int winner = lastTeam->getFirst();
            delete lastTeam;
            delete[] finalKnockoutTeamArray;
            return winner;
        }
        else
        {
            if(finalKnockoutTeamArray[1].getFirst() > lastTeam->getFirst())
            {
                int winner = finalKnockoutTeamArray[1].getFirst();
                delete lastTeam;
                delete[] finalKnockoutTeamArray;
                return winner;
            }
            else
            {
                int winner = lastTeam->getFirst();
                delete lastTeam;
                delete[] finalKnockoutTeamArray;
                return winner;
            }
        }
    }
    catch(std::bad_alloc& e)
    {
        return output_t<int>(StatusType::ALLOCATION_ERROR);
    }
}


void playKnockout(Pair<int,int>* finalKnockoutTeamArray, int numOfKnockoutTeams)
{
    if(numOfKnockoutTeams == 1)
    {
        return;
    }
    for(int i=0; i<numOfKnockoutTeams/2; i++)
    {
        if(finalKnockoutTeamArray[numOfKnockoutTeams].getSecond() > finalKnockoutTeamArray[numOfKnockoutTeams+1].getSecond())
        {
            finalKnockoutTeamArray[i].getFirst() = finalKnockoutTeamArray[numOfKnockoutTeams].getFirst();
            finalKnockoutTeamArray[i].getSecond() = finalKnockoutTeamArray[numOfKnockoutTeams].getSecond() +
                    finalKnockoutTeamArray[numOfKnockoutTeams+1].getSecond() + 3;
        }
        else if(finalKnockoutTeamArray[numOfKnockoutTeams].getSecond() < finalKnockoutTeamArray[numOfKnockoutTeams+1].getSecond())
        {
            finalKnockoutTeamArray[i].getFirst() = finalKnockoutTeamArray[numOfKnockoutTeams+1].getFirst();
            finalKnockoutTeamArray[i].getSecond() = finalKnockoutTeamArray[numOfKnockoutTeams].getSecond() +
                                                    finalKnockoutTeamArray[numOfKnockoutTeams+1].getSecond() + 3;
        }
        else
        {
            if(finalKnockoutTeamArray[numOfKnockoutTeams].getFirst() > finalKnockoutTeamArray[numOfKnockoutTeams+1].getFirst())
            {
                finalKnockoutTeamArray[i].getFirst() = finalKnockoutTeamArray[numOfKnockoutTeams].getFirst();
                finalKnockoutTeamArray[i].getSecond() = finalKnockoutTeamArray[numOfKnockoutTeams].getSecond() +
                                                           finalKnockoutTeamArray[numOfKnockoutTeams+1].getSecond() + 3;
            }
            else
            {
                finalKnockoutTeamArray[i].getFirst() = finalKnockoutTeamArray[numOfKnockoutTeams+1].getFirst();
                finalKnockoutTeamArray[i].getSecond() = finalKnockoutTeamArray[numOfKnockoutTeams].getSecond() +
                                                        finalKnockoutTeamArray[numOfKnockoutTeams+1].getSecond() + 3;
            }
        }
    }
    playKnockout(finalKnockoutTeamArray, numOfKnockoutTeams/2);
}
