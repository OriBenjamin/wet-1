#include "worldcup23a1.h"

world_cup_t::world_cup_t():
teams(), playersById(), playersByStatistics(), knockoutTeams(), topScorerPlayer(nullptr) {}

/*world_cup_t::~world_cup_t()
{

}*/

StatusType world_cup_t::add_team(int teamId, int points)
{
    try
    {
        Team *team = new Team(teamId, points);
        teams.insert(teamId,team);
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
    if(teamId<=0) return StatusType::INVALID_INPUT;
    Team* team;

    try {
        team = teams.find(teamId);
        if (team->getSize() != 0)
        {
            return StatusType::FAILURE;
        }
        team = teams.remove(teamId);
        delete team;
    }
    catch (NodeDoesNotExist&)
    {
        return StatusType::FAILURE;
    }

    try{
        knockoutTeams.remove(teamId);
    }
    catch(NodeDoesNotExist&) //nothing to do
    {}

    return StatusType::SUCCESS;
}

StatusType world_cup_t::add_player(int playerId, int teamId, int gamesPlayed,
                                   int goals, int cards, bool goalKeeper)
{
    try
    {
        if(playerId<=0 || gamesPlayed<0 || goals<0 || cards<0 ||
           (gamesPlayed == 0 && (cards>0 || goals>0)) ) //Invalid Input should be checked first
        {
            return StatusType::INVALID_INPUT;
        }
        Team* team = teams.find(teamId);
        Player* player = new Player(playerId,gamesPlayed,goals,cards,goalKeeper,team);
        team->insertPlayer(*player);
        playersById.insert(player->getPlayerId(), player);
        playersByStatistics.insert(*player, player);
        if(topScorerPlayer == nullptr)
        {
            topScorerPlayer = player;
        }
        else if(player->getPlayerGoals() > topScorerPlayer->getPlayerGoals())
        {
            topScorerPlayer = player;
        }
        if(goalKeeper) team->setGoalKeepers(team->getGoalKeepers() + 1);
        team->setCardSum(team->getCardSum() + cards);
        team->setGoalSum(team->getGoalSum() + goals);
    }
    catch(std::invalid_argument&)
    {
        return StatusType::INVALID_INPUT;
    }
    catch(std::bad_alloc&)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    catch(NodeAlreadyExist&)
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
        Player* player = playersById.remove(playerId);
        playersByStatistics.remove(*player);
        Team* team = player->getTeam();
        team->removePlayer(*player);
        if(player->getPlayerCanBeGooalkeeper()) team->setGoalKeepers(team->getGoalKeepers() - 1);
        team->setCardSum(team->getCardSum() - player->getPlayerCardsReceived());
        team->setGoalSum(team->getGoalSum() - player->getPlayerGoals());
        delete player;
    }
    catch(NodeDoesNotExist&)
    {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType world_cup_t::update_player_stats(int playerId, int gamesPlayed,
                                            int scoredGoals, int cardsReceived)
{
    if(playerId<=0 || gamesPlayed<0 || scoredGoals<0 || cardsReceived<0)
    {
        return  StatusType::INVALID_INPUT;
    }
    try {
        Player *player = playersById.find(playerId);
        playersByStatistics.remove(*player);
        player->getTeam()->removePlayer(*player);
        player->setGamesPlayed(player->getPlayerGamesPlayed()+gamesPlayed);
        player->setCardsReceived(player->getPlayerCardsReceived()+cardsReceived);
        player->setGoals(player->getPlayerGoals()+scoredGoals);
        playersByStatistics.insert(*player,player);
        player->getTeam()->insertPlayer(*player);
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
    try {
        Team* team1 = teams.find(teamId1);
        Team* team2 = teams.find(teamId2);
        if(team1->getSize() < 11 || team2->getSize() < 11
            || team1->getGoalKeepers()<=0 || team2->getGoalKeepers()<=0)
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
    // TODO: Your code goes here
    return 22;
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
    // TODO: Your code goes here
    return 30003;
}

StatusType world_cup_t::unite_teams(int teamId1, int teamId2, int newTeamId)
{
    // TODO: Your code goes here
    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_top_scorer(int teamId)
{
    // TODO: Your code goes here
    return 2008;
}

output_t<int> world_cup_t::get_all_players_count(int teamId)
{
    // TODO: Your code goes here
    static int i = 0;
    return (i++==0) ? 11 : 2;
}

StatusType world_cup_t::get_all_players(int teamId, int *const output)
{
    // TODO: Your code goes here
    output[0] = 4001;
    output[1] = 4002;
    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_closest_player(int playerId, int teamId)
{
    // TODO: Your code goes here
    return 1006;
}

output_t<int> world_cup_t::knockout_winner(int minTeamId, int maxTeamId)
{
    // TODO: Your code goes here
    return 2;
}

