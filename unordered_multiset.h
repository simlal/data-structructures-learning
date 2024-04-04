//
//  unordered_set.h
//  unordered_multiset
//
//  Jean Goulet
//  Copyleft 2017 UdeS
//
//  Modifie par : Vincent Ducharme, Automne 2022
//

#ifndef unordered_multiset_h
#define unordered_multiset_h

#include <vector>
#include <list>
#include <sstream>
#include <ostream>
#include <utility>

using std::vector;
using std::list;

template <typename TYPE,typename classe_de_dispersion=std::hash<TYPE>>
class unordered_multiset
{
private:
    classe_de_dispersion disperseur;
    double m_facteur_min, m_facteur_max;
    size_t m_size;
    vector<list<TYPE>*> m_rep;

    void ligne(std::ostream&, std::stringstream& s) const;
public:
    class iterator;
    unordered_multiset(size_t = 1);  //nombre minimal d'alveoles utiles
    ~unordered_multiset();
    unordered_multiset(const unordered_multiset&);
    unordered_multiset& operator=(const unordered_multiset&);

    void swap(unordered_multiset&);
    void rehash(size_t);

    iterator insert(const TYPE&);
    size_t erase(const TYPE&);
    iterator erase(iterator);

    size_t count(const TYPE&) const;

    size_t size() const { return m_size; }
    bool empty() const { return size() == 0; }

    iterator begin();
    iterator end();

    //mise au point
    friend std::ostream& operator<<(std::ostream& out, const unordered_multiset& ums)
    {
        size_t largeur = 60;
        size_t i;
        size_t nba = ums.m_rep.size() - 1;
        std::string s1;
        if (ums.size() > 1)
            s1 = "s";
        std::string s2;
        if (nba > 1)
            s2 = "s";
        std::stringstream outS;
        out << " " << std::string(largeur - 1, '-') << "\n";
        outS << ums.size() << " element" << s1;
        ums.ligne(out, outS);
        outS << nba << " alveole" << s2;
        ums.ligne(out, outS);
        for (i = 0; i < nba; ++i)
        {
            outS << "[" << i << "] ";
            if (ums.m_rep[i] != nullptr)
                for (auto x : *ums.m_rep[i])
                    outS << x << " ";
            ums.ligne(out, outS);
        }
        outS << "[" << i << "]" << " fin";
        ums.ligne(out, outS);
        out << " " << std::string(largeur - 1, '-') << std::endl;
        return out;
    }
};

template <typename TYPE,typename classe_de_dispersion>
class unordered_multiset<TYPE, classe_de_dispersion>::iterator
{
    friend class unordered_multiset<TYPE>;
private:
    typename vector<list<TYPE>*>::iterator m_alv;
    typename list<TYPE>::iterator m_pos;
    void avancer();
    void reculer();
    
    iterator() { }
    iterator(typename vector<list<TYPE>*>::iterator alv, typename list<TYPE>::iterator pos)
    {
        m_alv = alv;
        m_pos = pos;
    }
public:
    const TYPE& operator*() const { return *m_pos; }
    iterator& operator++() { avancer(); return *this; }
    iterator operator++(int) { iterator copie(*this); avancer(); return copie; }
    iterator& operator--() { reculer(); return *this; }
    iterator operator--(int) { iterator copie(*this); reculer(); return copie; }
    bool operator==(const iterator& dr) const
    {
        if (m_alv != dr.m_alv)
            return false;
        return m_pos == dr.m_pos;
    }
    bool operator!=(const iterator& dr) const { return !(*this == dr); }
};

/////////////////////////////////////////////////////////////////////
// fonctions de base (constructeur, copieur, destructeur)
template <typename TYPE,typename classe_de_dispersion>
unordered_multiset<TYPE, classe_de_dispersion>::unordered_multiset(size_t alvmin)
{
    m_facteur_max = 2.0;
    m_facteur_min = 0.75;
    size_t nbalv = 1;
    while (nbalv <= alvmin)
        nbalv += nbalv;
    //nbalv est la puissance de 2 superieure a alvmin
    m_size = 0;
    for (size_t i = 0;i < nbalv;++i)
        m_rep.push_back(nullptr);
    m_rep.back() = new list<TYPE>();
}

template <typename TYPE,typename classe_de_dispersion>
unordered_multiset<TYPE, classe_de_dispersion>::~unordered_multiset()
{
    m_facteur_max = 2.0;
    m_facteur_min = 0.5;
    m_size = 0;
    for (auto& p : m_rep)
        delete p;
}

template <typename TYPE,typename classe_de_dispersion>
unordered_multiset<TYPE, classe_de_dispersion>::unordered_multiset(const unordered_multiset& source)
{
    m_facteur_max = source.m_facteur_max;
    m_facteur_min = source.m_facteur_min;
    m_size = source.size();
    m_rep.resize(source.m_rep.size());
    for (size_t i = 0;i < m_rep.size();++i)
        if (source.m_rep[i] == nullptr)
            m_rep[i] = nullptr;
        else
            m_rep[i] = new list<TYPE>(*source.m_rep[i]);
}

template <typename TYPE,typename classe_de_dispersion>
unordered_multiset<TYPE,classe_de_dispersion>& unordered_multiset<TYPE,classe_de_dispersion>::operator=(const unordered_multiset& source)
{
    if (this != &source)
    {
        unordered_multiset<TYPE, classe_de_dispersion> copie(source);
        swap(copie);
    }
    return *this;
}

/////////////////////////////////////////////////////////////////////
// swap
template <typename TYPE,typename classe_de_dispersion>
void unordered_multiset<TYPE, classe_de_dispersion>::swap(unordered_multiset& deux)
{
    std::swap(m_facteur_min, deux.m_facteur_min);
    std::swap(m_facteur_max, deux.m_facteur_max);
    std::swap(m_size, deux.m_size);
    std::swap(m_rep, deux.m_rep);
}

/////////////////////////////////////////////////////////////////////
// rehash

template <typename TYPE,typename classe_de_dispersion>
void unordered_multiset<TYPE, classe_de_dispersion>::rehash(size_t nbalv)
{
    unordered_multiset<TYPE, classe_de_dispersion> copie(nbalv);
    for (auto& x : *this)
        copie.insert(x);
    swap(copie);
}


/////////////////////////////////////////////////////////////////////
// count
template <typename TYPE,typename classe_de_dispersion>
size_t unordered_multiset<TYPE, classe_de_dispersion>::count(const TYPE& val) const
{
    size_t alv = disperseur(val) % (m_rep.size() - 1);
    if (m_rep[alv] == nullptr)
        return 0;
    return std::count(m_rep[alv]->begin(), m_rep[alv]->end(), val);
}

/////////////////////////////////////////////////////////////////////
// iteration

template <typename TYPE,typename classe_de_dispersion>
typename unordered_multiset<TYPE,classe_de_dispersion>::iterator
unordered_multiset<TYPE, classe_de_dispersion>::begin()
{
    auto i = m_rep.begin();
    while (*i == nullptr)
        ++i;
    return iterator(i, (*i)->begin());
}

template <typename TYPE,typename classe_de_dispersion>
typename unordered_multiset<TYPE,classe_de_dispersion>::iterator unordered_multiset<TYPE, classe_de_dispersion>::end()
{
    return iterator(--m_rep.end(), m_rep.back()->begin());

}

/////////////////////////////////////////////////////////////////////
// mise au point
template <typename TYPE,typename classe_de_dispersion>
void unordered_multiset<TYPE, classe_de_dispersion>::ligne(std::ostream& out, std::stringstream& outS)const
{
    size_t largeur = 60;
    std::string s1 = std::string("| ") + outS.str();
    s1 += std::string(largeur, ' ');
    s1 = s1.substr(0, largeur) + "|";
    outS.str(" ");
    outS.clear();
    out << s1 << std::endl;
}

#include "unordered_multisetImpl.h"

#endif /* unordered_multiset_h */
