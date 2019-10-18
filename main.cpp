#include <iostream>
#include "BinTree.h"
#include "AVLTree.h"
#include "Treap.h"
#include "SPlayTree.h"
#include "RBTree.h"

using namespace BinTrees;
using std::cout, std::endl;

template<class T>
void test();

int main() {

    cout << "BST:" << endl;
    test<BinSTree<int>>();
    cout << "AVL:" << endl;
    test<AVLTree<int>>();
    cout << "Treap:" << endl;
    test<Treap<int>>();
    cout << "SPlay:" << endl;
    test<SPlayTree<int>>();
    cout << "RBTree:" << endl;
    test<RBTree<int>>();

    return 0;
}

template<class T>
void test() {
    int sum = 0;
    auto *t = T::gen({3566, 2472, 1180, 2948, 2286, 4414, 1207, 2110, 1951, 4271,
                      1690, 3574, 4297, 4232, 2609, 1367, 3893, 1693, 1997, 1589,
                      3140, 2063, 2359, 3291, 2699, 4179, 2333, 3786, 1458, 3427}
                      , sum);

    cout << "for Treap and SPlayTree, show the root:" << t->V() << endl << "Result:" << sum << endl;

    delete t;
}