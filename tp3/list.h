/*
*  list.h
*
*  Auteur : Jean Goulet
*
*  Modifie par : Vincent Ducharme
*  Date : Automne 2022
*
*/

#ifndef _LIST_H_
#define _LIST_H_

#include <ostream>
#include <cassert>
#include <initializer_list>
#include <utility>

///////////////////////////////////////////////////////////
/*Description de la representation

Chaine double de cellules
Une cellule supplementaire a la fin,
nommee m_apres en memoire automatique
m_debut pointe sur la premiere cellule
m_size contient le nombre d'elements dans la liste


iterator: pointeur sur la cellule concernee,
la fin est un pointeur sur la cellule de queue

reverse_iterator: pointeur sur la cellule qui
suit la cellule concernee
(rbegin: la queue, rend: la premiere)

Vous pouvez afficher la liste comme ceci :
afficher(std::cout, maListe);

*//////////////////////////////////////////////////////////


template <typename TYPE>
class list
{
private:
    struct cellule {
        TYPE m_contenu;
        cellule *m_suiv, *m_prec;
        cellule(const TYPE& c, cellule*s = nullptr, cellule*p = nullptr)
            :m_contenu(c), m_suiv(s), m_prec(p)
        {
        }
        ~cellule() = default;
    };
    cellule *m_debut;
    cellule m_apres;
    size_t m_size;

    //fonctions generatrices privees
    //inserer avant cette cellule
    cellule* insert(cellule*, const TYPE&);
    //enlever cette cellule
    cellule* erase(cellule*);

public:
    class iterator;
    class reverse_iterator;
    class const_iterator;

    list();
    ~list();
    list(const list&);
    list(std::initializer_list<TYPE>);
    list& operator=(const list&);

    iterator insert(iterator, const TYPE&); // Retourne un iterator sur la position de la valeur ajoutee
    iterator erase(iterator); // Retourne un iterartor sur la position suivant celle supprimee
    reverse_iterator insert(reverse_iterator, const TYPE&);
    reverse_iterator erase(reverse_iterator);

    void push_back(const TYPE&);
    void pop_back();
    void push_front(const TYPE&);
    void pop_front();
    const TYPE& back()const;
    const TYPE& front()const;
    TYPE& back();
    TYPE& front();

    void clear();
    size_t size()const;
    bool empty()const;

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;
    reverse_iterator rbegin();
    reverse_iterator rend();

    //algorithmes
    void reverse(); // Inverse le contenu de la liste
    void splice(iterator, list&); // Transfere le contenu de la liste recue dans la liste courante
    void resize(size_t, const TYPE& = TYPE());

    //fonction de mise au point (code jetable)
    friend void afficher(std::ostream& out, const list<TYPE>& liste)
    {
        typename list<TYPE>::cellule* p = liste.m_debut;
        size_t i = 0, skipde = liste.m_size, skipa = 0;
        if (skipde > 5)
            skipde = 5;
        if (skipa < liste.m_size - 5)
            skipa = liste.m_size - 5;
        out << "-----list " << &liste << " (" << liste.m_size << " elements) -----\n";
        out << "m_debut: " << liste.m_debut << "\n";
        while (p != &(liste.m_apres))
        {
            if (i<skipde || i>skipa)
                out << i << "=> <" << p->m_contenu
                << "," << p->m_suiv << "," << p->m_prec
                << ">\n";
            else if (i == skipde)
                out << "   .....\n";
            i++;
            p = p->m_suiv;
        }
        out << "m_apres: <???," << liste.m_apres.m_suiv << "," << liste.m_apres.m_prec << ">\n";
        out << "-------------------------------------------\n";
    }
};

///////////////////////////////////////////////////////////
//les classes d'iteration

template <typename TYPE>
class list<TYPE>::iterator
{
    friend class list<TYPE>;
private:
    cellule* m_pointeur = nullptr;

    iterator() = default;
    iterator(cellule* c) :m_pointeur(c) {}
public:
    
    TYPE& operator*()const { return m_pointeur->m_contenu; }
    TYPE* operator->()const { return &(m_pointeur->m_contenu); }
    iterator& operator++()
    {
        // ++i
        m_pointeur = m_pointeur->m_suiv;
        return *this;
    }
    iterator operator++(int)
    {   
        // i++
        iterator ret(*this);
        operator++();
        return ret;
    }
    iterator& operator--()
    {
        // --i
        m_pointeur = m_pointeur->m_prec;
        return *this;
    }
    iterator operator--(int)
    {
        // i--
        iterator ret(*this);
        operator--();
        return ret;
    }
    bool operator==(const iterator&droite)const
    {
        return m_pointeur == droite.m_pointeur;
    }
    bool operator!=(const iterator&droite)const
    {
        return !(*this == droite);
    }
};


template <typename TYPE>
class list<TYPE>::const_iterator
{
    friend class list<TYPE>;
private:
    const cellule* m_pointeur = nullptr;

    const_iterator() = default;
    const_iterator(const cellule* c) :m_pointeur(c) {}
public:

    const TYPE& operator*()const { return m_pointeur->m_contenu; }
    const TYPE* operator->()const { return &(m_pointeur->m_contenu); }
    const_iterator& operator++()
    {
        // ++i
        m_pointeur = m_pointeur->m_suiv;
        return *this;
    } 
    const_iterator operator++(int)
    {   
        // i++
        const_iterator ret(*this);
        operator++();
        return ret;
    }
    const_iterator& operator--()
    {
        // --i
        m_pointeur = m_pointeur->m_prec;
        return *this;
    }
    const_iterator operator--(int)
    {
        // i--
        const_iterator ret(*this);
        operator--();
        return ret;
    }
    bool operator==(const const_iterator& droite)const
    {
        return m_pointeur == droite.m_pointeur;
    }
    bool operator!=(const const_iterator& droite)const
    {
        return !(*this == droite);
    }
};


#include "listImpl.h"



///////////////////////////////////////////////////////////
template <typename TYPE>
list<TYPE>::list()
    :m_debut(&m_apres), m_apres(TYPE()), m_size(0)
{
}

template <typename TYPE>
list<TYPE>::~list()
{
    clear();
}

template <typename TYPE>
list<TYPE>::list(const list& droite)
    :list()
{
	// Une meilleure implémentation serait d'utiliser le constructeur de copie
	// dans l'implémentation de l'opérateur= et coder directement le code de copie
	// dans le constructeur de copie. 
    *this = droite;
}

template <typename TYPE>
list<TYPE>::list(std::initializer_list<TYPE> droite) :list()
{
    for (const auto& x : droite)
        push_back(x);
}

template <typename TYPE>
typename list<TYPE>::iterator list<TYPE>::insert(iterator i, const TYPE& x)
{
    return iterator(insert(i.m_pointeur, x));
}

template <typename TYPE>
typename list<TYPE>::iterator list<TYPE>::erase(iterator i)
{
    return iterator(erase(i.m_pointeur));
}

template <typename TYPE>
typename list<TYPE>::reverse_iterator list<TYPE>::insert(reverse_iterator i, const TYPE& x)
{
    insert(i.m_pointeur, x);
    return i;
}

template <typename TYPE>
typename list<TYPE>::reverse_iterator list<TYPE>::erase(reverse_iterator i)
{
    erase(i.m_pointeur->m_prec);
    return i;
}

template <typename TYPE>
void list<TYPE>::push_back(const TYPE& x)
{
    insert(end(), x);
}

template <typename TYPE>
void list<TYPE>::pop_back()
{
    erase(rbegin());
}

template <typename TYPE>
void list<TYPE>::push_front(const TYPE& x)
{
    insert(begin(), x);
}

template <typename TYPE>
void list<TYPE>::pop_front()
{
    erase(begin());
}

template <typename TYPE>
const TYPE& list<TYPE>::back()const
{
    return *rbegin();
}

template <typename TYPE>
const TYPE& list<TYPE>::front()const
{
    return *begin();
}

template <typename TYPE>
TYPE& list<TYPE>::back()
{
    return *rbegin();
}

template <typename TYPE>
TYPE& list<TYPE>::front()
{
    return *begin();
}


template <typename TYPE>
void list<TYPE>::clear()
{
    while (!empty())
    {
        m_debut = erase(m_debut);
    }
}

template <typename TYPE>
size_t list<TYPE>::size()const
{
    return m_size;
}

template <typename TYPE>
bool list<TYPE>::empty()const
{
    return size() == 0;
}


///////////////////////////////////////////////////////////
// gestion de l'iteration
///////////////////////////////////////////////////////////

template <typename TYPE>
typename list<TYPE>::iterator list<TYPE>::begin()
{
    return iterator(m_debut);
}

template <typename TYPE>
typename list<TYPE>::iterator list<TYPE>::end()
{
    return iterator(&m_apres);
}

template <typename TYPE>
typename list<TYPE>::const_iterator list<TYPE>::begin() const
{
    return const_iterator(m_debut);
}

template <typename TYPE>
typename list<TYPE>::const_iterator list<TYPE>::end() const
{
    return const_iterator(&m_apres);
}

template <typename TYPE>
typename list<TYPE>::const_iterator list<TYPE>::cbegin() const
{
    return const_iterator(m_debut);
}

template <typename TYPE>
typename list<TYPE>::const_iterator list<TYPE>::cend() const
{
    return const_iterator(&m_apres);
}

///////////////////////////////////////////////////////////
// algorithmes
///////////////////////////////////////////////////////////


template <typename TYPE>
void list<TYPE>::resize(size_t n, const TYPE& val)
{
    iterator it = begin();
    for (size_t i = 0; i<n; ++i, ++it)
        if (it == end())
            it = insert(it, val);
    while (it != end())
        it = erase(it);
}

template <typename TYPE>
void list<TYPE>::splice(iterator i, list& lst)
{
    if (lst.empty())
        return;
    cellule* ap = i.m_pointeur;
    cellule* av = ap->m_prec;
    cellule* pr = lst.m_debut;
    cellule* de = lst.m_apres.m_prec;
    av->m_suiv = pr;
    pr->m_prec = av;
    ap->m_prec = de;
    de->m_suiv = ap;
    if (ap == m_debut)
        m_debut = pr;
    //rendre L vide
    lst.m_debut = lst.m_apres.m_prec = lst.m_apres.m_suiv = &lst.m_apres;

    m_size += lst.m_size;
    lst.m_size= 0;
}

///////////////////////////////////////////////////////////
//code jetable

/*template <typename TYPE>
void afficher(std::ostream& out, const list<TYPE>& liste)
{
    liste<TYPE>::cellule* p = liste.m_debut;
    size_t i = 0, skipde = liste.m_size, skipa = 0;
    if (skipde>5)
        skipde = 5;
    if (skipa<liste.m_size - 5)
        skipa = liste.m_size - 5;
    out << "-----list " << &liste << " (" << liste.m_size << " elements) -----\n";
    out << "m_debut: " << liste.m_debut << "\n";
    while (p != &(liste.m_apres))
    {
        if (i<skipde || i>skipa)
            out << i << "=> <" << p->m_contenu
            << "," << p->m_suiv << "," << p->m_prec
            << ">\n";
        else if (i == skipde)
            out << "   .....\n";
        i++;
        p = p->m_suiv;
    }
    out << "m_apres: <???," << liste.m_apres.m_suiv << "," << liste.m_apres.m_prec << ">\n";
    out << "-------------------------------------------\n";
}*/

///////////////////////////////////////////////////////////
//algorithme de tri avec des iterateurs generaux

template <typename iter>
void sort(iter deb, iter fin)
{
    size_t nb = 0;
    iter i = deb, j = fin, pivot = deb;
    //choisir l'element du milieu comme pivot
    for (; i != j; ++nb, ++i)
        if (++nb, i == --j)
            break;
    if (nb<2)
        return;  //rien a trier
    std::swap(*deb, *i);
    //separer la liste en deux  {<PIVOT,>=PIVOT}
    ++(i = deb);
    j = fin;
    while (i != j)
        if (*i<*pivot)
            ++i;
        else if (*--j<*pivot)
            std::swap(*i++, *j);
    --i;
    std::swap(*pivot, *i);
    //trier les deux sous-listes
    sort(deb, i);
    sort(j, fin);
}

///////////////////////////////////////////////////////////
#endif
