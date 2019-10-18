//
// Created by lexa on 2019/10/16.
//

#ifndef UNTITLED_RBTREE_H
#define UNTITLED_RBTREE_H

#include "BinTree.h"

namespace BinTrees {
    template<class T>
    class RBTree : public BinSTree<T> {
    public:
        template<class F>
        explicit RBTree(F &&v, BinTree <T> *p = nullptr);

        static RBTree *gen(std::initializer_list<T> l, T &sum);

        template<class F>
        RBTree *i(F &&v);

        RBTree *p();

        RBTree *l();

        RBTree *r();

    private:
        bool c;

    };

    template<class T>
    template<class F>
    RBTree<T> *RBTree<T>::i(F &&v) {
        BinTree<T> *xp = nullptr;
        BinTree<T> *&ip = this->unsafe_search(v, xp);
        auto root = this;
        if (ip) throw std::runtime_error("Repeated insert.");
        else {
            ip = new RBTree(std::forward<F>(v), xp);
        }
        auto i = static_cast<RBTree<T> *>(ip);
        RBTree<T>* y = nullptr;
        while (i->p() && i->p()->c) {
            if (i->p() == i->p()->p()->l()) {
                y = i->p()->p()->r();
                if (y && y->c) {
                    i->p()->c = false;
                    y->c = false;
                    i->p()->p()->c = true;
                    i = i->p()->p();
                }
                else {
                    if (i == i->p()->r()) {
                        i = i->p();
                        root = static_cast<RBTree<T>*>(root->LR(i));
                    }
                    i->p()->c = false;
                    i->p()->p()->c = true;
                    root = static_cast<RBTree<T>*>(root->RR(i->p()->p()));
                }
            } else {
                y = i->p()->p()->l();
                if (y && y->c) {
                    i->p()->c = false;
                    y->c = false;
                    i->p()->p()->c = true;
                    i = i->p()->p();
                }
                else {
                    if (i == i->p()->l()) {
                        i = i->p();
                        root = static_cast<RBTree<T>*>(root->RR(i));
                    }
                    i->p()->c = false;
                    i->p()->p()->c = true;
                    root = static_cast<RBTree<T>*>(root->LR(i->p()->p()));
                }
            }
        }
        root->c = false;

        return root;
    }

    template<class T>
    template<class F>
    RBTree<T>::RBTree(F &&v, BinTree <T> *p) : BinSTree<T>(std::forward<F>(v), p), c(p != nullptr) {}

    template<class T>
    RBTree<T> *RBTree<T>::p() {
        return static_cast<RBTree<T> *>(this->Pr());
    }

    template<class T>
    RBTree<T> *RBTree<T>::l() {
        return static_cast<RBTree<T> *>(this->Lr());
    }

    template<class T>
    RBTree<T> *RBTree<T>::r() {
        return static_cast<RBTree<T> *>(this->Rr());
    }

    template<class T>
    RBTree<T> *RBTree<T>::gen(std::initializer_list<T> l, T &sum) {
        sum = 0;
        auto t = new RBTree<T>(*(l.begin()));
        const BinTrees::BinSTree<int> *p = t;
        sum += *(l.begin());
        auto i = l.begin() + 1;
        for (i; i < l.end(); i++) {
            t = t->i(*i);
            p = &(t->search(*i));
            sum += std::min(p->suc() - p->V(), p->V() - p->pre());
        }
        return t;
    }

}

#endif //UNTITLED_RBTREE_H
