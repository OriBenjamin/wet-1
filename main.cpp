#include <iostream>
#include "Tree.h"
#include "Player.h"
#include "worldcup23a1.h"
using namespace std;

int main() {
    //cout << "hello!";
    /* Tree<int,int> tree1;
     int x = 0, y= 3, z = 4, a= 5, b= 9, d= 121, e = 66, g= 18;
     tree1.insert(x, &x);
     tree1.insert(y, &y);
     tree1.insert(z, &z);
     tree1.insert(a, &a);
     tree1.insert(b, &b);
     tree1.insert(d, &d);
     tree1.createAndInsertNode(e, &e);
     tree1.createAndInsertNode(g, &g);



     tree1.print();
     cout<< "\n";

   //  tree1.remove(c);
     tree1.remove(a);
 //    tree1.remove(g);
   //  tree1.remove(x);
     //tree1.remove(99);
     Team* t1 = new Team(22,5);
     tree1.print();

     Tree<Player&,Player> tree2;
     Player* p1 = new Player(214,3,3,8,true, t1);
     Player* p2 = new Player(213,3,3,2,true, t1);
     tree2.insert(*p1,p1);
     tree2.insert(*p2,p2);
     Player* p2Pointer = tree2.remove(*p2);
     p2Pointer->updatePlayer(3,0,2);
     tree2.insert(*p2Pointer,p2Pointer);
     cout<<"\n";
     tree2.print();
     cout<<"\n";

     t1->insertPlayer(*p1);
     t1->insertPlayer(*p2);
     //cout<<*t1;
     cout<< "\ntop scorer:"<<*t1->getTopScorerPlayer();

     Tree<int,int> tree1;
     int* a = new int(40);
     int* b= new int(32);
     int* c = new int(2);
     int* d=  new int(8);
     int* e=  new int(80);
     int* f=  new int(70);
     int* g = new int( 6);
     int* h=  new int(777);
     tree1.insert(a, a);
     tree1.insert(b, b);
     tree1.insert(c, c);
     tree1.insert(d, d);

     Tree<int,int> tree2;
     tree2.insert(e,e);
     tree2.insert(f, f);
     tree2.insert(g, g);
     tree2.insert(h, h);

     cout << tree1 <<"\n" << tree2;

     Tree<int,int> tree3 = mergeTrees(tree1,tree2);
     //Tree<int,int> t3 = *tree3;

     tree3.print();
     //cout << tree3[0];
  //   delete tree3;
     tree2.deleteTree(false);
     tree1.deleteTree(false);
     //tree3->deleteTree(false);
     tree3.deleteTree(true);
 //delete[] tree3;
 */
/*
    world_cup_t worldCup2022;
    worldCup2022.add_team(213,2);
    worldCup2022.add_team(214,3);
    worldCup2022.add_team(215,4);
    worldCup2022.add_team(216,5);
  //  cout << "\nteam 1: " << worldCup2022.teams;
    worldCup2022.add_player(1,213,1,3,4,true);
    worldCup2022.add_player(2,214,6,2,4,true);
    worldCup2022.add_player(3,213,6,2,4,true);
    worldCup2022.add_player(4,215,6,2,4,true);
    worldCup2022.add_player(5,213,6,2,4,true);
    worldCup2022.update_player_stats(1,6,3,8);
    worldCup2022.add_player(6,213,6,2,3,true);
    worldCup2022.add_player(7,216,6,2,3,true);
    worldCup2022.add_player(9,216,6,2,3,true);
    worldCup2022.add_player(8,213,9,2,4,true);
    worldCup2022.add_player(11,213,8,2,4,true);
    worldCup2022.add_player(10,213,6,1,1,true);

    //cout << "ans:" << worldCup2022.get_closest_player(1,213).ans() <<".";
  //  worldCup2022.unite_teams(213,214,218);
    worldCup2022.update_player_stats(2,6,2,8);
    worldCup2022.update_player_stats(2,5,2,8);
    worldCup2022.update_player_stats(4,6,2,8);

    worldCup2022.update_player_stats(1,6,2,8);
    worldCup2022.remove_player(4);
    worldCup2022.remove_player(8);
    worldCup2022.remove_player(2);
    worldCup2022.remove_player(10);
    worldCup2022.remove_player(9);
    worldCup2022.remove_player(5);
    worldCup2022.remove_player(4);
    worldCup2022.remove_player(6);
    worldCup2022.remove_player(7);
    worldCup2022.update_player_stats(5,6,2,8);
  //  cout << "\nclosest player: " << worldCup2022.get_closest_player(2,213).ans()<<"\n";
  //  cout << "\nteam 1: " << worldCup2022.teams;
    worldCup2022.remove_player(1);
    worldCup2022.remove_player(5);
    worldCup2022.add_player(2,213,7,2,8,false);
  //  cout << "\nteam 1: " << worldCup2022.teams;
*/
    world_cup_t *obj = new world_cup_t();
    int playerId = 1;
    StatusType res;
    for (int teamId = 1; teamId < 10; teamId += 2)
    {
        res = obj->add_team(teamId, 1000 / ((6 - teamId) * (6 - teamId)));
        cout << (res == StatusType::SUCCESS);

        for (int startingId = playerId; playerId < startingId + 10 + teamId; ++playerId)
        {
            res = obj->add_player(playerId, teamId, 1, playerId, 3, true);
            cout << (res == StatusType::SUCCESS);
        }
        ++playerId;
    }
    // Strengths team1:73 team3:319 team5:1485 team7:1816 team9:1384

    res = obj->add_team(4, 1000000);
    cout << (res == StatusType::SUCCESS);

    output_t<int> res1 = obj->knockout_winner(8, 9);
    cout << (res1.status() == StatusType::SUCCESS);
    cout << (res1.ans() == 9);

    output_t<int> res2 = obj->knockout_winner(1, 1);
    cout << (res2.status() == StatusType::SUCCESS);
    cout << (res2.ans() == 1);

    output_t<int> res3 = obj->knockout_winner(2, 4);
    cout << (res3.status() == StatusType::SUCCESS);
    cout << (res3.ans() == 3);

    output_t<int> res4 = obj->knockout_winner(3, 9);
    cout << (res4.status() == StatusType::SUCCESS);
    cout << (res4.ans() == 7);

    output_t<int> res5 = obj->knockout_winner(2, 8);
    cout << (res5.status() == StatusType::SUCCESS);
    cout << (res5.ans() == 7);

    output_t<int> res6 = obj->knockout_winner(0, 5);
    cout << (res6.status() == StatusType::SUCCESS);
    cout << (res6.ans() == 5);

    output_t<int> res7 = obj->knockout_winner(1, 9);
    cout << (res7.status() == StatusType::SUCCESS);
    cout << (res7.ans() == 7);

    res = obj->add_player(999, 3, 1, 3000, 200, false);
    cout << (res == StatusType::SUCCESS);
    // Strengths team1:73 team3:3119 team5:1485 team7:1816 team9:1384

    output_t<int> res8 = obj->knockout_winner(1, 999);
    cout << (res8.status() == StatusType::SUCCESS);
    cout << (res8.ans() == 7);

    res = obj->add_player(998, 3, 1, 2000, 0, false);
    cout << (res == StatusType::SUCCESS);
    // Strengths team1:73 team3: 5119 team5:1485 team7:1816 team9:1384

    output_t<int> res9 = obj->knockout_winner(0, 13);
    cout << (res9.status() == StatusType::SUCCESS);
    cout << (res9.ans() == 3);

    res = obj->add_player(997, 3, 1, 1, 5001, false);
    cout << (res == StatusType::SUCCESS);
    // Strengths team1:73 team3:119 team5:1485 team7:1816 team9:1384

    output_t<int> res9andahalf = obj->knockout_winner(0, 13);
    cout << (res9andahalf.status() == StatusType::SUCCESS);
    cout << (res9andahalf.ans() == 7);

    res = obj->update_player_stats(79, 1, 10000, 0);
    cout << (res == StatusType::SUCCESS);
    // Strengths team1:73 team3:119 team5:1485 team7:1816 team9:11384

    output_t<int> res10 = obj->knockout_winner(1, 9);
    cout << (res10.status() == StatusType::SUCCESS);

    cout << (res10.ans() == 9);

    delete obj;

    return 0;
}