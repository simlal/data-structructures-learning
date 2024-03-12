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
#include <unordered_map>
#ifndef SkipList_set2_h
#define SkipList_set2_h

/////////////////////////////////////////////////////////////////
// copieur et destructeur de liste

template <typename TYPE>
set<TYPE>::set(const set<TYPE>& src)
    : set()
{
    // Utilisation map pour correspondance src/this
    std::unordered_map<cellule*, cellule*> srcVersCopie;

    // M-a-j des pointeurs de debut et fin initialisee a null deja
    srcVersCopie[src.m_avant] = m_avant;
    cellule* apresSrc = src.m_avant->m_prec[0];
    cellule* apresCopie = m_avant->m_prec[0];
    srcVersCopie[apresSrc] = apresCopie;    // ptr vers cellule frontiere apres

    // Copie profonde des elements du set src
    for (auto sit = src.begin(); sit != src.end(); ++sit)
    {
        cellule *srcCell = sit.m_pointeur;
        cellule *copieCell = new cellule(new TYPE(*sit));
        // Conserve la taille des vecteurs pointeurs
        copieCell->m_suiv.resize(srcCell->m_suiv.size());
        copieCell->m_prec.resize(srcCell->m_prec.size());
        srcVersCopie[srcCell] = copieCell;
    }

    // M-a-j des vecteurs pointeurs de chaque cellule du set
    for (auto sit = src.begin(); sit != src.end(); ++sit)
    {
        cellule *srcCell = sit.m_pointeur;
        cellule *copieCell = srcVersCopie[srcCell];
        for (int i = 0; i < srcCell->m_suiv.size(); i++)
        {
            copieCell->m_suiv[i] = srcVersCopie[srcCell->m_suiv[i]];
        }
        for (int i = 0; i < srcCell->m_prec.size(); i++)
        {
            copieCell->m_prec[i] = srcVersCopie[srcCell->m_prec[i]];
        }
    }
    // Redimensionnement des vecteurs pointeurs de la cellule frontiere
    m_avant->m_suiv.resize(src.m_avant->m_suiv.size());
    apresCopie->m_prec.resize(apresSrc->m_prec.size());
    
    // M-a-j des vecteurs pointeurs m_suiv de cell frontiere avant
    for (int i = 0; i < src.m_avant->m_suiv.size(); i++)
    {
        m_avant->m_suiv[i] = srcVersCopie[src.m_avant->m_suiv[i]];
    }
    // M-a-j des vecteurs pointeurs m_prec de cell frontiere apres
    for (int i = 0; i < apresSrc->m_prec.size(); i++)
    {
        apresCopie->m_prec[i] = srcVersCopie[apresSrc->m_prec[i]];
    }

    m_size = src.m_size;    // M-a-j de la taille

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
