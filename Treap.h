//
// Created by lexa on 2019/10/16.
//

#ifndef UNTITLED_TREAP_H
#define UNTITLED_TREAP_H

#include <random>
#include "BinTree.h"

namespace BinTrees {
    template<class T>
    class Treap : public BinSTree<T> {
    public:
        template<class F>
        explicit Treap(F &&v, BinTree <T> *p = nullptr);

        static Treap *gen(std::initializer_list<T> l, T &sum);

        template<class F>
        Treap *i(F &&v);

        Treap *p();

        Treap *l();

        Treap *r();

    private:
        int rnd;

    };

    template<class T>
    template<class F>
    Treap<T> *Treap<T>::i(F &&v) {
        BinTree<T> *xp = nullptr;
        BinTree<T> *&ip = this->unsafe_search(v, xp);
        auto root = this;
        if (ip) throw std::runtime_error("Repeated insert.");
        else {
            ip = new Treap(std::forward<F>(v), xp);
        }
        auto i = static_cast<Treap<T> *>(ip);
        while (i->P() && i->rnd > i->p()->rnd) {
            if (i == i->p()->l())
                root = static_cast<Treap<T> *>(root->RR(static_cast<BinSTree<T> *>(i->p())));
            else
                root = static_cast<Treap<T> *>(root->LR(static_cast<BinSTree<T> *>(i->p())));
        }

        return root;
    }

    std::random_device rd;
    std::minstd_rand tr(10086);
    std::uniform_int_distribution<> dis(0, 300);

    template<class T>
    template<class F>
    Treap<T>::Treap(F &&v, BinTree <T> *p) : BinSTree<T>(std::forward<F>(v), p), rnd(dis(tr)) {}

    template<class T>
    Treap<T> *Treap<T>::p() {
        return static_cast<Treap<T> *>(this->Pr());
    }

    template<class T>
    Treap<T> *Treap<T>::l() {
        return static_cast<Treap<T> *>(this->Lr());
    }

    template<class T>
    Treap<T> *Treap<T>::r() {
        return static_cast<Treap<T> *>(this->Rr());
    }

    template<class T>
    Treap<T> *Treap<T>::gen(std::initializer_list<T> l, T &sum) {
        sum = 0;
        auto t = new Treap<T>(*(l.begin()));
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

#endif //UNTITLED_TREAP_H
