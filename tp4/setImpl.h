//
//  setImpl.h
//  SkipList
//
//  Jean Goulet 2017
//
//  Devoir fait par
//     Co�quipier 1 : Simon Lalonde - lals2906
//     Co�quipier 2 :
//
#include "set.h"
#ifndef SkipList_set2_h
#define SkipList_set2_h

/////////////////////////////////////////////////////////////////
// copieur et destructeur de liste

template <typename TYPE>
set<TYPE>::set(const set<TYPE>& src)
    : set()
{
}

template <typename TYPE>
set<TYPE>::~set()
{
}

/////////////////////////////////////////////////////////////////
// find
// localise un �l�ment, retourne la fin si absent

template <typename TYPE>
typename set<TYPE>::iterator set<TYPE>::find(const TYPE& x) const
{
}

// lower_bound
// localise la premiere position ou l'element n'est
// pas plus petit que celui recu en parametre

template <typename TYPE>
typename set<TYPE>::iterator set<TYPE>::lower_bound(const TYPE& t) const
{
    cellule *c = m_avant;
    cellule *apres = m_avant->m_prec[0];
	while(c->m_suiv[0] != apres)
		if(*c->m_suiv[0]->m_contenu < t)
			c = c->m_suiv[0];
		else
			break;
	return iterator(c->m_suiv[0]);
}

template <typename TYPE>
typename set<TYPE>::iterator set<TYPE>::upper_bound(const TYPE& x) const
{
}

/////////////////////////////////////////////////////////////////
// erase(VAL)
// elimine VAL de l'ensemble, si present

template <typename TYPE>
size_t set<TYPE>::erase(const TYPE& VAL)
{
}

// erase(it)
// elimine de l'ensemble l'element en position it

template <typename TYPE>
typename set<TYPE>::iterator set<TYPE>::erase(iterator it)
{
}

#endif
