#include <iostream>
#include "Tree.h"
using namespace std;

int main() {
    //cout << "hello!";
    Tree<int,int> tree1;
    int x = 0, y= 3, z = 4, a= 5, b= 9, d= 121, e = 66, g= 18;
    tree1.createAndInsertNode(x, &x);
    tree1.createAndInsertNode(y, &y);
    tree1.createAndInsertNode(z, &z);
    tree1.createAndInsertNode(a, &a);
    tree1.createAndInsertNode(b, &b);
    tree1.createAndInsertNode(d, &d);
 /*   tree1.createAndInsertNode(e, &e);
    tree1.createAndInsertNode(g, &g);*/



    tree1.print();
    cout<< "\n";

  //  tree1.remove(c);
    tree1.remove(a);
//    tree1.remove(g);
  //  tree1.remove(x);
    //tree1.remove(99);

    tree1.print();
    return 0;
}