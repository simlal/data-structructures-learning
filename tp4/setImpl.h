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
#include <map>
#ifndef SkipList_set2_h
#define SkipList_set2_h

/////////////////////////////////////////////////////////////////
// copieur et destructeur de liste

template <typename TYPE>
set<TYPE>::set(const set<TYPE>& src)
    : set()
{
    // Cas limite avec src liste vide
    if (src.empty())
    {
        return;
    }

    // Utilisation d'un map pour correspondance entre nouvelle copie et src
    std::map<cellule*, cellule*> srcVersCopie;

    // Creation nouvelles cellules et copie de la valeur
    for (set::iterator sit = src.begin(); sit!= src.end(); sit++)
    {
        cellule* srcCell = sit.m_pointeur;
        cellule* copieCell = new cellule(*sit);
        srcVersCopie[srcCell] = copieCell;    // liens entre ptr src et this
    }

    // M-a-j des vecteurs de ptrs m_suiv/prec dans la copie
    for (set::iterator sit = src.begin(); sit!= src.end(); sit++)
    {
        cellule* srcCell = sit.m_pointeur;
        cellule* copieCell = srcVersCopie[srcCell];    // Cree la correspondance src-copy
        
        // Copie des pointeurs correspondants pour les vecteurs m_suiv/prec
        for (vector<cellule*>::iterator vit = srcCell->m_suiv.begin(); vit != srcCell->m_suiv.end(); vit++)
        {
            copieCell->m_suiv.push_back(srcVersCopie[*vit]);
        }
        for (vector<cellule*>::iterator vit = srcCell->m_prec.begin(); vit != srcCell->m_prec.end(); vit++)
        {
            copieCell->m_prec.push_back(srcVersCopie[*vit]);
        }
    }
    
    // Chercher les cellules frontieres apres
    cellule* apresSrc = src.m_avant->m_prec;
    cellule* apresCopie = m_avant->m_prec;

    // Ajout des pointeurs de cellules frontieres dans la map
    srcVersCopie[src.m_avant] = m_avant;
    srcVersCopie[apresSrc] = apresCopie;

    // Pas besoin d'iterer vec de 1 ele: m_avant->m_prec et apres->m_suiv (deja nullptr)
    m_avant->m_prec = srcVersCopie[apresSrc];

    // M-a-j des vec de ptrs suiv/prec pour cell frontiere m_avant
    for (vector<cellule*>::iterator vit = src.m_avant->m_suiv.begin(); vit != src.m_avant->m_suiv.end(); vit++)
    {
        cellule* suivCopie = srcVersCopie[*vit];
        m_avant->m_suiv.push_back(suivCopie);
    }
    for (vector<cellule*>::iterator vit = apresSrc->m_prec.begin(); vit != apresSrc->m_prec.end(); vit++)
    {
        cellule* precCopie = srcVersCopie[*vit];
        apresCopie->m_prec.push_back(precCopie);
    }

    // Ajustement de la taille
    m_size = src.size();
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
