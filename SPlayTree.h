//
// Created by lexa on 2019/10/16.
//

#ifndef UNTITLED_SPLAYTREE_H
#define UNTITLED_SPLAYTREE_H

#include "BinTree.h"

namespace BinTrees {
    template<class T>
    class SPlayTree : public BinSTree<T> {
    public:
        template<class F>
        explicit SPlayTree(F &&v, BinTree <T> *p = nullptr);

        static SPlayTree *gen(std::initializer_list<T> l, T &sum);

        template<class F>
        SPlayTree *i(F &&v);

        SPlayTree *p();

        SPlayTree *l();

        SPlayTree *r();

    };

    template<class T>
    template<class F>
    SPlayTree<T> *SPlayTree<T>::i(F &&v) {
        BinTree<T> *xp = nullptr;
        BinTree<T> *&ip = this->unsafe_search(v, xp);
        auto root = this;
        if (ip) throw std::runtime_error("Repeated insert.");
        else {
            ip = new SPlayTree(std::forward<F>(v), xp);
        }
        auto i = static_cast<SPlayTree<T> *>(ip);
        while (i->P()) {
            if (i->P()->P() == nullptr) {
                if (i == i->p()->l())
                    root = static_cast<SPlayTree<T> *>(root->RR(static_cast<BinSTree<T> *>(i->p())));
                else
                    root = static_cast<SPlayTree<T> *>(root->LR(static_cast<BinSTree<T> *>(i->p())));
            } else if (i->p()->p()->l() && i == i->p()->p()->l()->l()) {
                root = static_cast<SPlayTree<T> *>(root->RR(static_cast<BinSTree<T> *>(i->p()->p())));
                root = static_cast<SPlayTree<T> *>(root->RR(static_cast<BinSTree<T> *>(i->p())));
            } else if (i->p()->p()->r() && i == i->p()->p()->r()->r()) {
                root = static_cast<SPlayTree<T> *>(root->LR(static_cast<BinSTree<T> *>(i->p()->p())));
                root = static_cast<SPlayTree<T> *>(root->LR(static_cast<BinSTree<T> *>(i->p())));
            } else if (i->p()->p()->l() && i == i->p()->p()->l()->r()) {
                root = static_cast<SPlayTree<T> *>(root->LR(static_cast<BinSTree<T> *>(i->p())));
                root = static_cast<SPlayTree<T> *>(root->RR(static_cast<BinSTree<T> *>(i->p())));
            } else if (i->p()->p()->r() && i == i->p()->p()->r()->l()) {
                root = static_cast<SPlayTree<T> *>(root->RR(static_cast<BinSTree<T> *>(i->p())));
                root = static_cast<SPlayTree<T> *>(root->LR(static_cast<BinSTree<T> *>(i->p())));
            } else throw std::runtime_error("whoops!");
        }

        return root;
    }

    template<class T>
    template<class F>
    SPlayTree<T>::SPlayTree(F &&v, BinTree <T> *p) : BinSTree<T>(std::forward<F>(v), p) {}

    template<class T>
    SPlayTree<T> *SPlayTree<T>::p() {
        return static_cast<SPlayTree<T> *>(this->Pr());
    }

    template<class T>
    SPlayTree<T> *SPlayTree<T>::l() {
        return static_cast<SPlayTree<T> *>(this->Lr());
    }

    template<class T>
    SPlayTree<T> *SPlayTree<T>::r() {
        return static_cast<SPlayTree<T> *>(this->Rr());
    }

    template<class T>
    SPlayTree<T> *SPlayTree<T>::gen(std::initializer_list<T> l, T &sum) {
        sum = 0;
        auto t = new SPlayTree<T>(*(l.begin()));
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

#endif //UNTITLED_SPLAYTREE_H
