#include "worldcup23a1.h"

world_cup_t::world_cup_t(): teams(), players(), playersByStatistics(), topScorer(nullptr)
{

}

world_cup_t::~world_cup_t()
{
    // TODO: Your code goes here
}


StatusType world_cup_t::add_team(int teamId, int points)
{
    try {
        Team *team = new Team(teamId, points);
        teams.insert(teamId,team);
    }
    catch(std::invalid_argument)
    {
        return StatusType::INVALID_INPUT;
    }
    catch (std::bad_alloc&)
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
        if (team->getSize() != 0) {
            return StatusType::FAILURE;
        }
        team = teams.remove(teamId);
        delete team;
    }
    catch (NodeDoesNotExist)
    {
        return StatusType::FAILURE;
    }
    catch (std::bad_alloc&) //?
    {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType world_cup_t::add_player(int playerId, int teamId, int gamesPlayed,
                                   int goals, int cards, bool goalKeeper)
{
    try {
        if(playerId<=0 || gamesPlayed<0 || goals<0 || cards<0 ||
           (gamesPlayed == 0 && (cards>0 || goals>0)) ) //Invalid Input should be checked first
        {
            return StatusType::INVALID_INPUT;
        }
        Team* team = teams.find(teamId);
        Player* player = new Player(playerId,gamesPlayed,goals,cards,goalKeeper,team);
        team->insertPlayer(*player);
        players.insert(player->getPlayerId(), player);
        playersByStatistics.insert(*player, player);
        if(topScorerPlayer == nullptr)
        {
            topScorerPlayer = player;
        }
        else if(player->getPlayerGoals() > topScorerPlayer->getPlayerGoals())
        {
            topScorerPlayer = player;
        }
    }
    catch(std::invalid_argument)
    {
        return StatusType::INVALID_INPUT;
    }
    catch(std::bad_alloc)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    catch(NodeAlreadyExist)
    {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_player(int playerId)
{
    // TODO: Your code goes here
    return StatusType::SUCCESS;
}

StatusType world_cup_t::update_player_stats(int playerId, int gamesPlayed,
                                            int scoredGoals, int cardsReceived)
{
    // TODO: Your code goes here
    return StatusType::SUCCESS;
}

StatusType world_cup_t::play_match(int teamId1, int teamId2)
{
    // TODO: Your code goes here
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

