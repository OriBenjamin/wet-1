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
    StatusType res = obj->add_team(1, 10000);
    cout <<(res == StatusType::SUCCESS);
//    res = obj->add_team(2, 20000);
//    cout <<(res == StatusType::SUCCESS);
    res = obj->add_team(3, 30000);
    cout <<(res == StatusType::SUCCESS);
//    res = obj->add_team(4, 40000);
//    cout <<(res == StatusType::SUCCESS);
//    res = obj->add_player(1001, 1, 10, 0, 0, false);
//    cout <<(res == StatusType::SUCCESS);
//    res = obj->add_player(1002, 1, 10, 0, 0, false);
//    cout <<(res == StatusType::SUCCESS);
//    res = obj->add_player(1003, 1, 10, 0, 0, false);
//    cout <<(res == StatusType::SUCCESS);
//    res = obj->add_player(1004, 1, 10, 0, 2, false);
//    cout <<(res == StatusType::SUCCESS);
//    res = obj->add_player(1005, 1, 10, 0, 0, false);
//    cout <<(res == StatusType::SUCCESS);
//    res = obj->add_player(1006, 1, 10, 4, 3, false);
//    cout <<(res == StatusType::SUCCESS);
//    res = obj->add_player(1007, 1, 10, 0, 0, false);
//    cout <<(res == StatusType::SUCCESS);
//    res = obj->remove_player(1007);
//    cout <<(res == StatusType::SUCCESS);
//    res = obj->remove_player(1002);
//    cout <<(res == StatusType::SUCCESS);
//    res = obj->add_player(1008, 1, 10, 0, 0, true);
//    cout <<(res == StatusType::SUCCESS);
//    res = obj->add_player(1009, 1, 10, 0, 0, false);
//    cout <<(res == StatusType::SUCCESS);
//    res = obj->add_player(1010, 1, 10, 0, 0, false);
//    cout <<(res == StatusType::SUCCESS);
//    res = obj->add_player(1011, 1, 10, 0, 0, false);
//    cout <<(res == StatusType::SUCCESS);
//    res = obj->remove_player(1001);
//    cout <<(res == StatusType::SUCCESS);
//    res = obj->add_player(1012, 1, 10, 0, 0, false);
//    cout <<(res == StatusType::SUCCESS);
//
//    res = obj->add_player(2001, 2, 20, 0, 0, false);
//    cout <<(res == StatusType::SUCCESS);
//    res = obj->add_player(2002, 2, 20, 0, 0, false);
//    cout <<(res == StatusType::SUCCESS);
//    res = obj->add_player(2003, 2, 20, 0, 0, false);
//    cout <<(res == StatusType::SUCCESS);
//    res = obj->add_player(2004, 2, 20, 0, 0, false);
//    cout <<(res == StatusType::SUCCESS);
//    res = obj->add_player(2005, 2, 20, 0, 0, false);
//    cout <<(res == StatusType::SUCCESS);
//    res = obj->remove_player(1011);
//    cout <<(res == StatusType::SUCCESS);
//    res = obj->add_player(2006, 2, 20, 0, 0, false);
//    cout <<(res == StatusType::SUCCESS);
//    res = obj->add_player(2007, 2, 20, 0, 0, false);
//    cout <<(res == StatusType::SUCCESS);
//    res = obj->add_player(2008, 2, 20, 6, 4, true);
//    cout <<(res == StatusType::SUCCESS);
//    res = obj->add_player(2009, 2, 20, 0, 0, false);
//    cout <<(res == StatusType::SUCCESS);
//    res = obj->remove_player(2001);
//    cout <<(res == StatusType::SUCCESS);
//    res = obj->add_player(2010, 2, 0, 0, 0, false);
//    cout <<(res == StatusType::SUCCESS);
//    res = obj->add_player(2011, 2, 20, 0, 0, false);
//    cout <<(res == StatusType::SUCCESS);
//    res = obj->remove_player(2010);
//    cout <<(res == StatusType::SUCCESS);

    res = obj->add_player(3001, 3, 30, 0, 0, false);
    cout <<(res == StatusType::SUCCESS);
    res = obj->add_player(3002, 3, 30, 0, 0, false);
    cout <<(res == StatusType::SUCCESS);
    res = obj->add_player(3003, 3, 30, 0, 0, false);
    cout <<(res == StatusType::SUCCESS);
    res = obj->add_player(3004, 3, 30, 0, 0, false);
    cout <<(res == StatusType::SUCCESS);
    res = obj->add_player(3005, 3, 30, 2, 0, false);
    cout <<(res == StatusType::SUCCESS);
    res = obj->add_player(3006, 3, 30, 0, 0, false);
    cout <<(res == StatusType::SUCCESS);
    res = obj->add_player(3007, 3, 30, 0, 0, false);
    cout <<(res == StatusType::SUCCESS);
    res = obj->add_player(3008, 3, 30, 0, 0, false);
    cout <<(res == StatusType::SUCCESS);
    res = obj->add_player(3009, 3, 30, 0, 2, false);
    cout <<(res == StatusType::SUCCESS);
    res = obj->add_player(3010, 3, 30, 0, 0, true);
    cout <<*(obj->teams.getRoot()->next->value->getPlayers());

    res = obj->remove_player(3008);
    cout <<(res == StatusType::SUCCESS);
    res = obj->remove_player(3002);
    cout <<(res == StatusType::SUCCESS);
    res = obj->remove_player(3010);
    cout <<(res == StatusType::SUCCESS);
    res = obj->remove_player(3009);
    cout <<(res == StatusType::SUCCESS);
    res = obj->remove_player(3005);
    cout <<(res == StatusType::SUCCESS);
    res = obj->remove_player(3004);
    cout <<(res == StatusType::SUCCESS);
    res = obj->remove_player(3006);
    cout <<(res == StatusType::SUCCESS);
//    res = obj->remove_player(3007);
//    cout <<(res == StatusType::SUCCESS);

      res = obj->remove_player(3001);
      cout <<(res == StatusType::SUCCESS);
      res = obj->remove_player(3003);
    delete obj;

    return 0;
}