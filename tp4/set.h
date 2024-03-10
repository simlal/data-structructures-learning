/*
*  SkipList
*
*  Auteur : Jean Goulet 2016
*  Cette version integre la rustine
*  set<TYPE>::to_string pour remplacer std::to_string
*
*  Modifi� par : Vincent Ducharme, Automne 2022
*/

#pragma once

#include <ostream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <random>
#include <chrono>

/////////////////////////////////////////////////
// affichage
// n'est fonctionnel que pour les types primitifs
// et les string (max 4 caracteres par element)

template <typename T> 
std::string to_string(const T& n) {
    std::ostringstream stm;
    stm << n;
    return stm.str();
}

//conversion d'une valeur en string
//cas generique
template <typename TYPE>
std::string vers_string(TYPE val)
{
    return to_string<TYPE>(val);
}

//cas specialise double
template <>
std::string vers_string<double>(double val)
{
    std::string retour = to_string<double>(val);
    if (retour.find('.') == std::string::npos)
        return retour;
    for (auto i = retour.rbegin(); i != retour.rend(); ++i)
        if (*i == '0')
            retour.pop_back();
        else
            break;
    if (retour.back() == '.')
        retour.pop_back();
    return retour;
}

//cas specialise float
template <>
std::string vers_string<float>(float val)
{
    return vers_string(double(val));
}

//cas specialise string
template <>
std::string vers_string<std::string>(std::string val)
{
    return val;
}


template <typename TYPE>
class set
{
private:
    struct cellule
    {
        TYPE* m_contenu = nullptr;
        std::vector<cellule*> m_prec, m_suiv;
        cellule() = default;
        cellule(TYPE* v) :m_contenu(v) {};
        ~cellule();
    };
    size_t m_size;
    cellule* m_avant;

    static size_t tirer_couches_au_hasard();
    cellule* insert(cellule*, const TYPE&);
public:
    class iterator;

    set();
    ~set();
    set(const set&);
    set& operator=(const set&);
    void swap(set&);

    size_t size()const;
    bool empty()const;

    size_t count(const TYPE&) const;
    iterator find(const TYPE&) const;
    iterator lower_bound(const TYPE&) const;
    iterator upper_bound(const TYPE&) const;

    std::pair<iterator, bool> insert(const TYPE&);
    iterator insert(iterator, const TYPE&);
    size_t erase(const TYPE&);
    iterator erase(iterator);
    void clear();

    iterator begin()const;
    iterator end()const;

    friend void afficher(std::ostream& out, const set<TYPE>& s)
    {
        out << "------------------------------------------\n";
        if (s.m_avant == nullptr)
        {
            out << "le set a ete detruit\n";
            return;
        }
        size_t nbniv = s.m_avant->m_suiv.size();
        std::string une_clef, lignes, clefs;
        TYPE elem;
        cellule* p;
        lignes = to_string(s.size()) + " elements";
        for (size_t nb = nbniv; nb > 0;)
        {
            std::string clefs = " ";
            nb--;
            //afficher toute la couche nb
            out << lignes << "\n";
            lignes = "|";
            for (auto it = s.begin(); it != s.end(); ++it)
            {
                if (it.m_pointeur->m_suiv.size() > nb)
                {
                    p = it.m_pointeur;
                    elem = *p->m_contenu;
                    une_clef = "-----" + vers_string(elem);
                    clefs += une_clef.substr(une_clef.size() - 6, 6);
                    lignes += "     |";
                }
                else
                {
                    clefs += "------";
                    lignes += "      ";
                }
            }
            clefs += "--";
            out << clefs << "\n";
            lignes += "  |";
        }
        out << "\n\n";
    }
};

/////////////////////////////////////////////////
// destructeur de cellule

template <typename TYPE>
set<TYPE>::cellule::~cellule()
{
    delete m_contenu;
    for (auto& x : m_prec)
        x = nullptr;
    for (auto& x : m_suiv)
        x = nullptr;
}

/////////////////////////////////////////////////
// iterator

template <typename TYPE>
class set<TYPE>::iterator
{
private:
    cellule* m_pointeur;
    friend class set<TYPE>;
    friend void afficher(std::ostream& out, const set<TYPE>& s);
    iterator(cellule* p = nullptr) :m_pointeur(p) {}
public:
    
    const TYPE& operator*()const { return *m_pointeur->m_contenu; }
    iterator operator++();     //++i
    iterator operator++(int);  //i++
    iterator operator--();     //--i
    iterator operator--(int);  //i--
    bool operator==(const iterator&i2)const { return m_pointeur == i2.m_pointeur; }
    bool operator!=(const iterator&i2)const { return !(*this == i2); }
};


template <typename TYPE>
typename set<TYPE>::iterator set<TYPE>::iterator::operator++()
{   //++i
    m_pointeur = m_pointeur->m_suiv[0];
    return *this;
}

template <typename TYPE>
typename set<TYPE>::iterator set<TYPE>::iterator::operator++(int)
{
    //i++
    iterator r(m_pointeur);
    operator++();
    return r;
}

template <typename TYPE>
typename set<TYPE>::iterator set<TYPE>::iterator::operator--()
{
    //--i
    m_pointeur = m_pointeur->m_prec[0];
    return *this;
}

template <typename TYPE>
typename set<TYPE>::iterator set<TYPE>::iterator::operator--(int)
{ 
    //i--
    iterator r(m_pointeur);
    operator--();
    return r;
}

/////////////////////////////////////////////////
// set
// fonctions privees

template <typename TYPE>
size_t set<TYPE>::tirer_couches_au_hasard()
{
    //tirer au hasard le nombre de couches
    //prob 1/2 d'avoir 1
    //prob 1/4 d'avoir 2
    //prob 1/8 d'avoir 3 etc.
    //
    // Si vous voulez g�n�rer la m�me s�quence pour vos tests, vous pouvez modifier la valeur de seed pour qu'elle soit �gale � 0
    static auto seed = 0;
    // static auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::minstd_rand0 generator(static_cast<unsigned int>(seed));
    size_t i = 1;
    auto g = generator();
    for (; g % 2 != 0; ++i)
        g /= 2;
    return i;
}


/////////////////////////////////////////////////
// set
// fonctions publiques

template <typename TYPE>
set<TYPE>::set()
{
    m_size = 0;
    m_avant = new cellule(nullptr);
    cellule* apres = new cellule(nullptr);
    m_avant->m_prec.push_back(apres);
    m_avant->m_suiv.push_back(apres);
    apres->m_prec.push_back(m_avant);
    apres->m_suiv.push_back(nullptr);
}

template <typename TYPE>
set<TYPE>& set<TYPE>::operator=(const set<TYPE>& source)
{
    if (this != &source)
    {
        set copie(source);
        swap(copie);
    }
    return *this;
}

template <typename TYPE>
void set<TYPE>::swap(set<TYPE>& src)
{
    std::swap(m_size, src.m_size);
    std::swap(m_avant, src.m_avant);
}

template <typename TYPE>
size_t set<TYPE>::size()const
{
    return m_size;
}

template <typename TYPE>
bool set<TYPE>::empty()const
{
    return size() == 0;
}

template <typename TYPE>
size_t set<TYPE>::count(const TYPE& t)const
{
    auto it = find(t);
    if (it == end())
        return 0;
    else
        return 1;
}

/////////////////////////////////////////////////
// les trois fonctions d'insertion
// deux fonctions publiques et une fonction priv�e

template <typename TYPE>
std::pair<typename set<TYPE>::iterator, bool> set<TYPE>::insert(const TYPE& val)
{
    //insertion par valeur seulement
    iterator it = lower_bound(val);
    TYPE* p = it.m_pointeur->m_contenu;
    if (p == nullptr || val<*p)
        return std::make_pair(iterator(insert(it.m_pointeur, val)), true);
    else
        return std::make_pair(it, false);
}

template <typename TYPE>
typename set<TYPE>::iterator set<TYPE>::insert(iterator it, const TYPE& val)
{
    //insertion avec indice a verifier
    //verifier que l'on est a la bonne place
    cellule* ap = it.m_pointeur;
    cellule* av = ap->m_prec[0];
    TYPE* ava = av->m_contenu;
    if (ap->m_contenu != nullptr && (*ap->m_contenu<val))
        return insert(val).first;
    else if (ava == nullptr)
        return iterator(insert(ap, val));
    else if (*ava<val)
        return iterator(insert(ap, val));
    else
        return insert(val).first;
}

template <typename TYPE>
typename set<TYPE>::cellule* set<TYPE>::insert(typename set<TYPE>::cellule* ap, const TYPE& val)
{
    size_t nbniv_orig = m_avant->m_suiv.size();
    cellule* fin = m_avant->m_prec[0];
    cellule* av = ap->m_prec[0];
    cellule* nouv = new cellule(new TYPE(val));
    size_t nbniv = tirer_couches_au_hasard();
/*
    for (size_t i = 0;;)
    {
        nouv->m_prec.push_back(av);
        nouv->m_suiv.push_back(ap);
        av->m_suiv[i] = nouv;
        ap->m_prec[i] = nouv;
        if (++i == nbniv)
            break; //on a insere le bon nombre de couches
        if (i == nbniv_orig)
        {  //ajouter une couche vide
            m_avant->m_suiv.push_back(ap = fin);
            fin->m_prec.push_back(av = m_avant);
            ++nbniv_orig;
        }
        else
        {
            while (av->m_suiv.size() == i)
                av = av->m_prec.back();
            ap = av->m_suiv[i];
        }
    }
    ++m_size;
 */
    for (size_t i = 0; i<nbniv;)
    {
        nouv->m_prec.push_back(av);
        nouv->m_suiv.push_back(ap);
        av->m_suiv[i] = nouv;
        ap->m_prec[i] = nouv;
        ++i;
        if (i<nbniv){
            if (i == nbniv_orig)
            {  //ajouter une couche vide
                m_avant->m_suiv.push_back(ap = fin);
                fin->m_prec.push_back(av = m_avant);
                ++nbniv_orig;
            }
            else
            {
                while (av->m_suiv.size() == i)
                    av = av->m_prec.back();
                ap = av->m_suiv[i];
            }
        }
    }
    ++m_size;
    return nouv;
}

/////////////////////////////////////////////////////////////////
// clear
// vide la liste en temps O(n)

template <typename TYPE>
void set<TYPE>::clear()
{
    cellule* p = m_avant->m_suiv[0], *prochain;
    while (size() != 0)
    {
        --m_size;
        prochain = p->m_suiv[0];
        delete p;
        p = prochain;
    }

    m_avant->m_suiv.clear();
    m_avant->m_suiv.push_back(m_avant->m_prec[0]);
    m_avant->m_prec[0]->m_prec.clear();
    m_avant->m_prec[0]->m_prec.push_back(m_avant);
}



/////////////////////////////////////////////////
// iteration

template <typename TYPE>
typename set<TYPE>::iterator set<TYPE>::begin()const
{
    return iterator(m_avant->m_suiv[0]);
}

template <typename TYPE>
typename set<TYPE>::iterator set<TYPE>::end()const
{
    return iterator(m_avant->m_prec[0]);
}



////////////////////////////////////////////////////////////

#include "setImpl.h"
