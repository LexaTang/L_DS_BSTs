//
// Created by lexa on 2019/10/16.
//

#ifndef UNTITLED_SBTREE_H
#define UNTITLED_SBTREE_H

#include "BinTree.h"

namespace BinTrees {
    template<class T>
    class SBTree : public BinSTree<T> {
    public:
        template<class F>
        explicit SBTree(F &&v, BinTree <T> *p = nullptr);

        static SBTree *gen(std::initializer_list<T> l, T &sum);

        template<class F>
        SBTree *i(F &&v);

        SBTree *p();

        SBTree *l();

        SBTree *r();

    private:
        int bf() const;

        bool ub() const;

        int s;

    };

    template<class T>
    int SBTree<T>::bf() const {
        return (this->L() ? this->L()->height() + 1 : 0) - (this->R() ? this->R()->height() + 1 : 0);
    }

    template<class T>
    bool SBTree<T>::ub() const {
        return abs(bf()) > 1;
    }

    template<class T>
    template<class F>
    SBTree<T> *SBTree<T>::i(F &&v) {
        BinTree<T> *xp = nullptr;
        BinTree<T> *&ip = this->unsafe_search(v, xp);
        auto root = this;
        if (ip) throw std::runtime_error("Repeated insert.");
        else {
            ip = new SBTree(std::forward<F>(v), xp);
        }
        auto i = static_cast<SBTree<T> *>(ip);
        SBTree<T> *b = nullptr;
        while (i->P()) {
            if (i == i->p()->l()) {
                if (b = i->p()->r()) {
                    if (b->r() && i->size() < b->r()->size())
                        root = static_cast<SBTree<T> *>(root->LR(i->p()));
                    else if (b->l() && i->size() < b->l()->size()) {
                        root = static_cast<SBTree<T> *>(root->RR(b));
                        root = static_cast<SBTree<T> *>(root->LR(i->p()));
                    }
                }
            } else {
                if (b = i->p()->l()) {
                    if (b->l() && i->size() < b->l()->size())
                        root = static_cast<SBTree<T> *>(root->RR(i->p()));
                    else if (b->r() && i->size() < b->r()->size()) {
                        root = static_cast<SBTree<T> *>(root->LR(b));
                        root = static_cast<SBTree<T> *>(root->RR(i->p()));
                    }
                }
            }
            i = i->p();
        }

        return root;
    }

    template<class T>
    template<class F>
    SBTree<T>::SBTree(F &&v, BinTree <T> *p) : BinSTree<T>(std::forward<F>(v), p), s(0) {}

    template<class T>
    SBTree<T> *SBTree<T>::p() {
        return static_cast<SBTree<T> *>(this->Pr());
    }

    template<class T>
    SBTree<T> *SBTree<T>::l() {
        return static_cast<SBTree<T> *>(this->Lr());
    }

    template<class T>
    SBTree<T> *SBTree<T>::r() {
        return static_cast<SBTree<T> *>(this->Rr());
    }

    template<class T>
    SBTree<T> *SBTree<T>::gen(std::initializer_list<T> l, T &sum) {
        sum = 0;
        auto t = new SBTree<T>(*(l.begin()));
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

#endif //UNTITLED_SBTREE_H
