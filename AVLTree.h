//
// Created by lexa on 2019/10/16.
//

#ifndef UNTITLED_AVLTREE_H
#define UNTITLED_AVLTREE_H

#include "BinTree.h"

namespace BinTrees {
    template<class T>
    class AVLTree : public BinSTree<T> {
    public:
        template<class F>
        explicit AVLTree(F &&v, BinTree <T> *p = nullptr);

        static AVLTree *gen(std::initializer_list<T> l, T &sum);

        template<class F>
        AVLTree *i(F &&v);

        AVLTree *p();

        AVLTree *l();

        AVLTree *r();

    private:
        int bf() const;

        bool ub() const;

        int h;

    };

    template<class T>
    int AVLTree<T>::bf() const {
        return (this->L() ? this->L()->height() + 1 : 0) - (this->R() ? this->R()->height() + 1 : 0);
    }

    template<class T>
    bool AVLTree<T>::ub() const {
        return abs(bf()) > 1;
    }

    template<class T>
    template<class F>
    AVLTree<T> *AVLTree<T>::i(F &&v) {
        BinTree<T> *xp = nullptr;
        BinTree<T> *&ip = this->unsafe_search(v, xp);
        auto root = this;
        if (ip) throw std::runtime_error("Repeated insert.");
        else {
            ip = new AVLTree(std::forward<F>(v), xp);
        }
        auto i = static_cast<AVLTree<T> *>(ip);
        while (i->P() && i->P()->P()) {
            if (i->p()->p()->ub()) {
                if (i->p()->p()->bf() > 1) {
                    if (i->p()->bf() < 0) {
                        root = static_cast<AVLTree<T> *>(root->LR(static_cast<BinSTree<T> *>(i->Pr())));
                        i = i->l();
                    }
                    root = static_cast<AVLTree<T> *>(root->RR(i->p()->p()));
                } else if (i->p()->p()->bf() < 1) {
                    if (i->p()->bf() > 0) {
                        root = static_cast<AVLTree<T> *>(root->RR(static_cast<BinSTree<T> *>(i->Pr())));
                        i = i->r();
                    }
                    root = static_cast<AVLTree<T> *>(root->LR(i->p()->p()));
                } else
                    i = i->p();
            } else i = i->p();
        }

        return root;
    }

    template<class T>
    template<class F>
    AVLTree<T>::AVLTree(F &&v, BinTree <T> *p) : BinSTree<T>(std::forward<F>(v), p), h(0) {}

    template<class T>
    AVLTree<T> *AVLTree<T>::p() {
        return static_cast<AVLTree<T> *>(this->Pr());
    }

    template<class T>
    AVLTree<T> *AVLTree<T>::l() {
        return static_cast<AVLTree<T> *>(this->Lr());
    }

    template<class T>
    AVLTree<T> *AVLTree<T>::r() {
        return static_cast<AVLTree<T> *>(this->Rr());
    }

    template<class T>
    AVLTree<T> *AVLTree<T>::gen(std::initializer_list<T> l, T &sum) {
        sum = 0;
        auto t = new AVLTree<T>(*(l.begin()));
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

#endif //UNTITLED_AVLTREE_H
