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
        for (size_t i = 0; i < srcCell->m_suiv.size(); i++)
        {
            copieCell->m_suiv[i] = srcVersCopie[srcCell->m_suiv[i]];
        }
        for (size_t i = 0; i < srcCell->m_prec.size(); i++)
        {
            copieCell->m_prec[i] = srcVersCopie[srcCell->m_prec[i]];
        }
    }
    // Redimensionnement des vecteurs pointeurs de la cellule frontiere
    m_avant->m_suiv.resize(src.m_avant->m_suiv.size());
    apresCopie->m_prec.resize(apresSrc->m_prec.size());
    
    // M-a-j des vecteurs pointeurs m_suiv de cell frontiere avant
    for (size_t i = 0; i < src.m_avant->m_suiv.size(); i++)
    {
        m_avant->m_suiv[i] = srcVersCopie[src.m_avant->m_suiv[i]];
    }
    // M-a-j des vecteurs pointeurs m_prec de cell frontiere apres
    for (size_t i = 0; i < apresSrc->m_prec.size(); i++)
    {
        apresCopie->m_prec[i] = srcVersCopie[apresSrc->m_prec[i]];
    }

    m_size = src.m_size;    // M-a-j de la taille

}

template <typename TYPE>
set<TYPE>::~set()
{
    // Revenir au set vide
    clear();

    // Nettoyage des cellules frontieres
    m_avant->m_suiv[0] = nullptr;
    m_avant->m_prec[0]->m_prec[0] = nullptr;
    delete m_avant->m_prec[0];    // libere apres
    
    m_avant->m_prec[0] = nullptr;
    delete m_avant;
    m_avant = nullptr;
}

/////////////////////////////////////////////////////////////////
// find
// localise un �l�ment, retourne la fin si absent

template <typename TYPE>
typename set<TYPE>::iterator set<TYPE>::find(const TYPE& x) const
{
    int niveau = m_avant->m_suiv.size() - 1;
    cellule* c = m_avant;

    while (niveau >= 0)
    {
        // if imbrique dans while car != dereference nullptr possible
        while (c->m_suiv[niveau]->m_contenu != nullptr)
        {
            // Allez vers droite si la valeur est plus petite
            if (*(c->m_suiv[niveau]->m_contenu) < x)
            {
                c = c->m_suiv[niveau];
            }
            else
            {
                break;
            }
        }
        niveau--;
    // element en sortie de portee est le precedent de l'element recherche
    }    
    // Suivant == fin ou plus grand, on retourne la fin car introuvable
    if (c->m_suiv[0]->m_contenu == nullptr || x < *(c->m_suiv[0]->m_contenu))
    {
        return end();
    }
    return iterator(c->m_suiv[0]);
}

// lower_bound
// localise la premiere position ou l'element n'est
// pas plus petit que celui recu en parametre

// template <typename TYPE>
// typename set<TYPE>::iterator set<TYPE>::lower_bound(const TYPE& t) const
// {
//     cellule *c = m_avant;
//     cellule *apres = m_avant->m_prec[0];
// 	while(c->m_suiv[0] != apres)
// 		if(*c->m_suiv[0]->m_contenu < t)
// 			c = c->m_suiv[0];
// 		else
// 			break;
// 	return iterator(c->m_suiv[0]);
// }

// lower_bound en temps log n
// localise la premiere position ou l'element n'est
// pas plus petit que celui recu en parametre
template <typename TYPE>
typename set<TYPE>::iterator set<TYPE>::lower_bound(const TYPE& t) const
{
    int niveau = m_avant->m_suiv.size() - 1;
    cellule* c = m_avant;

    while (niveau >= 0)
    {
        while (c->m_suiv[niveau]->m_contenu != nullptr)
        {
            if (*(c->m_suiv[niveau]->m_contenu) < t)
            {
                c = c->m_suiv[niveau];
            }
            else
            {
                break;
            }
        }
        niveau--;
    }    
    return iterator(c->m_suiv[0]);    // retourne tjrs suivant comparativement a find
}

template <typename TYPE>
typename set<TYPE>::iterator set<TYPE>::upper_bound(const TYPE& x) const
{
    int niveau = m_avant->m_suiv.size() - 1;
    cellule* c = m_avant;

    while (niveau >= 0)
    {
        while (c->m_suiv[niveau]->m_contenu != nullptr)
        {
            if (*(c->m_suiv[niveau]->m_contenu) < x)
            {
                c = c->m_suiv[niveau];
            }
            else
            {
                break;
            }
        }
        niveau--;
    }
    // Suivant == fin ou plus grand on retourne le suivant
    if (c->m_suiv[0]->m_contenu == nullptr || x < *(c->m_suiv[0]->m_contenu))
    {
        return iterator(c->m_suiv[0]);
    }
    // Suivant est necessairement x
    return iterator(c->m_suiv[0]->m_suiv[0]);
}

/////////////////////////////////////////////////////////////////
// erase(VAL)
// elimine VAL de l'ensemble, si present

template <typename TYPE>
size_t set<TYPE>::erase(const TYPE& VAL)
{
    iterator it = find(VAL);
    if (it == end())
    {
        return 0;
    
    }
    else
    {
        erase(it);
        return 1;
    }

}

// erase(it)
// elimine de l'ensemble l'element en position it

template <typename TYPE>
typename set<TYPE>::iterator set<TYPE>::erase(iterator it)
{
    // Cas limite set vide
    if (m_size == 0)
    {
        return end();
    }

    cellule* toDelete = it.m_pointeur;
    cellule* next = toDelete->m_suiv[0];
    int niveau = toDelete->m_suiv.size() - 1;

    for (int i = niveau; i >= 0; i--)
    {
        // Diminution de la taille des cellules frontieres
        if (toDelete->m_prec[i] ==  m_avant && toDelete->m_suiv[i] == m_avant->m_prec[0])
        {
            m_avant->m_suiv.pop_back();
            m_avant->m_prec[0]->m_prec.pop_back();
        }
        // M-a-j des vecteurs pointeurs des cellules voisines
        else
        {
            toDelete->m_prec[i]->m_suiv[i] = toDelete->m_suiv[i];
            toDelete->m_suiv[i]->m_prec[i] = toDelete->m_prec[i];
        }
    }
    --m_size;
    delete toDelete;
    return iterator(next);
}

#endif
