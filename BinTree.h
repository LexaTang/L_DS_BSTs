//
// Created by lexa on 2019/10/13.
//

#ifndef UNTITLED_BINTREE_H
#define UNTITLED_BINTREE_H

#include <cstdio>
#include <utility>
#include <memory>
#include <algorithm>
#include <initializer_list>

namespace BinTrees {
    template<class T> //template T need override operate <
    class BinTree {
    public:
        explicit BinTree(T v, BinTree *p = nullptr);

        ~BinTree();

        const T &V() const;

        BinTree<T> *const &P() const;

        BinTree<T> *const &L() const;

        BinTree<T> *const &R() const;

        void mid() const;

        int height() const;

        int size() const;

        BinTree *&Pr();

        BinTree *&Lr();

        BinTree *&Rr();

        const T v;

    private:
        BinTree *l;
        BinTree *r;
        BinTree *p;

    };

    template<class T>
    class BinSTree : public BinTree<T> {
    public:
        explicit BinSTree(T v, BinTree<T> *p = nullptr);

        ~BinSTree();

        const BinSTree &search(const T &v) const;

        BinSTree &insert(T v);

        const BinSTree &min() const;

        const BinSTree &predecessor() const;

        const BinSTree &max() const;

        const BinSTree &successor() const;

        BinSTree *LR(BinSTree<T> *x);

        BinSTree *RR(BinSTree<T> *x);

        static BinSTree<T> *gen(std::initializer_list<T> l, T &sum);

        int pre() const;

        int suc() const;

    protected:
        BinTree<T> *&unsafe_search(const T &v, BinTree<T> *&x);

    };

    template<class T>
    BinSTree<T>::BinSTree(T v, BinTree<T> *p) : BinTree<T>(v, p) {}

    template<class T>
    BinTree<T> *&BinSTree<T>::unsafe_search(const T &v, BinTree<T> *&x) {
        x = this;
        while (x->V() != v) {
            if (x->V() < v) {
                if (x->R()) x = x->Rr();
                else return x->Rr();
            } else {
                if (x->L()) x = x->Lr();
                else return x->Lr();
            }
        }
        return x;
    }

    template<class T>
    const BinSTree<T> &BinSTree<T>::search(const T &v) const {
        if (this->v > v) {
            if (this->L() == nullptr) throw std::runtime_error("Not found");
            return static_cast<BinSTree<T> *>(this->L())->search(v);
        } else if (this->v == v) return *this;
        else {
            if (this->R() == nullptr) throw std::runtime_error("Not found");
            return static_cast<BinSTree<T> *>(this->R())->search(v);
        }
    }

    template<class T>
    BinSTree<T> &BinSTree<T>::insert(T v) {
        BinTree<T> *xp = nullptr;
        BinTree<T> *&ip = unsafe_search(v, xp);
        if (ip) throw std::runtime_error("Repeated insert.");
        else {
            ip = new BinSTree(v, xp);
            return *this;
        }
    }

    template<class T>
    const BinSTree<T> &BinSTree<T>::min() const {
        auto x = this;
        while (x->L()) x = static_cast<BinSTree<T> *>(x->L());
        return *x;
    }

    template<class T>
    const BinSTree<T> &BinSTree<T>::predecessor() const {
        const BinSTree *x = this;
        if (x->L()) return static_cast<BinSTree<T> *>(x->L())->max();
        BinTree<T> *y = (x->P());
        while (y && x == y->L()) {
            x = static_cast<BinSTree<T> *>(y);
            y = y->P();
        }
        if (y == nullptr) throw std::runtime_error("Predecessor not found.");
        return *(static_cast<BinSTree<T> *>(y));
    }

    template<class T>
    int BinSTree<T>::pre() const {
        try {
            return this->predecessor().V();
        } catch (const std::runtime_error &e) {
            return INT32_MIN;
        }

    }

    template<class T>
    int BinSTree<T>::suc() const {
        try {
            return this->successor().V();
        } catch (const std::runtime_error &e) {
            return INT32_MAX;
        }

    }

    template<class T>
    const BinSTree<T> &BinSTree<T>::max() const {
        auto x = this;
        while (x->R()) x = static_cast<BinSTree<T> *>(x->R());
        return *x;
    }

    template<class T>
    const BinSTree<T> &BinSTree<T>::successor() const {
        const BinSTree *x = this;
        if (x->R()) return static_cast<BinSTree<T> *>(x->R())->min();
        BinTree<T> *y = (x->P());
        while (y && x == y->R()) {
            x = static_cast<BinSTree<T> *>(y);
            y = y->P();
        }
        if (y == nullptr) throw std::runtime_error("Successor not found.");
        return *(static_cast<BinSTree<T> *>(y));
    }

    template<class T>
    BinSTree<T> *BinSTree<T>::LR(BinSTree<T> *x) {
        BinTree<T> *y = x->Rr();
        BinSTree<T> *root = this;
        x->Rr() = y->L();
        if (y->L())
            y->Lr()->Pr() = x;
        y->Pr() = x->P();
        if (x->Pr() == nullptr)
            root = static_cast<BinSTree<T> *>(y);
        else if (x->Pr()->L() == x)
            x->Pr()->Lr() = y;
        else
            x->Pr()->Rr() = y;
        y->Lr() = x;
        x->Pr() = y;
        return root;
    }

    template<class T>
    BinSTree<T> *BinSTree<T>::RR(BinSTree<T> *x) {
        BinTree<T> *y = x->Lr();
        BinSTree<T> *root = this;
        x->Lr() = y->R();
        if (y->R())
            y->Rr()->Pr() = x;
        y->Pr() = x->P();
        if (x->P() == nullptr)
            root = static_cast<BinSTree<T> *>(y);
        else if (x->Pr()->R() == x)
            x->Pr()->Rr() = y;
        else
            x->Pr()->Lr() = y;
        y->Rr() = x;
        x->Pr() = y;
        return root;
    }

    template<class T>
    BinSTree<T>::~BinSTree() {
        if (this->L()) {
            delete static_cast<BinSTree *>(this->L());
            this->Lr() = nullptr;
        }
        if (this->R()) {
            delete static_cast<BinSTree *>(this->R());
            this->Rr() = nullptr;
        }
    }

    template<class T>
    BinTree<T>::BinTree(T v, BinTree *p) : v(v), p(p), l(nullptr), r(nullptr) {}

    template<class T>
    const T &BinTree<T>::V() const {
        return v;
    }

    template<class T>
    BinTree<T>::~BinTree() {
        if (this->L()) delete this->L();
        if (this->R()) delete this->R();
    }

    template<class T>
    BinTree<T> *&BinTree<T>::Pr() {
        return p;
    }

    template<class T>
    BinTree<T> *&BinTree<T>::Lr() {
        return l;
    }

    template<class T>
    BinTree<T> *&BinTree<T>::Rr() {
        return r;
    }

    template<class T>
    BinTree<T> *const &BinTree<T>::P() const {
        return p;
    }

    template<class T>
    BinTree<T> *const &BinTree<T>::L() const {
        return l;
    }

    template<class T>
    BinTree<T> *const &BinTree<T>::R() const {
        return r;
    }

    template<class T>
    int BinTree<T>::height() const {
        return std::max(R() ? R()->height() + 1 : 0, L() ? L()->height() + 1 : 0);
    }

    template<class T>
    int BinTree<T>::size() const {
        return (R() ? R()->size() : 0) + (L() ? L()->size() : 0) + 1;
    }

    template<class T>
    void BinTree<T>::mid() const {
        if (l) l->mid();
        printf("%d\n", v);
        if (r) r->mid();
    }

    template<class T>
    BinSTree<T> *BinSTree<T>::gen(std::initializer_list<T> l, T &sum) {
        auto t = new BinSTree(*(l.begin()));
        const BinTrees::BinSTree<int> *p = t;
        sum += *(l.begin());
        auto i = l.begin() + 1;
        for (i; i < l.end(); i++) {
            t = &(t->insert(*i));
            p = &(t->search(*i));
            sum += std::min(p->suc() - p->V(), p->V() - p->pre());
        }
        return t;
    }
}
#endif //UNTITLED_BINTREE_H
