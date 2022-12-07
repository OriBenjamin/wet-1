#include <iostream>
#include "Tree.h"
#include "Player.h"
using namespace std;

int main() {
    //cout << "hello!";
    Tree<int,int> tree1;
    int x = 0, y= 3, z = 4, a= 5, b= 9, d= 121, e = 66, g= 18;
    tree1.insert(x, &x);
    tree1.insert(y, &y);
    tree1.insert(z, &z);
    tree1.insert(a, &a);
    tree1.insert(b, &b);
    tree1.insert(d, &d);
 /*   tree1.createAndInsertNode(e, &e);
    tree1.createAndInsertNode(g, &g);*/



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
    cout<<*t1;
    cout<< "\ntop scorer:"<<*t1->getTopScorerPlayer();

    return 0;
}