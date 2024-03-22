//
//  mapImpl.h
//
//  Auteur : Jean Goulet
//  Copyleft  2017 UdeS
//
//  Modifie par : Vincent Ducharme, Hiver 2018
//
//  Devoir fait par
//     Co�quipier 1 : Simon Lalonde lals2906
//     Co�quipier 2 :

#ifndef mapImpl_h
#define mapImpl_h

#include <algorithm>

///////////////////////////////////////////////////////////////////////////
// lower_bound O(log n)

template <typename Tclef, typename Tvaleur>
typename map<Tclef, Tvaleur>::iterator map<Tclef, Tvaleur>::lower_bound(const Tclef& c) const
{
    // Commencer la recherche a partir de la racine
    noeud* currentNode = m_apres->m_gauche;
    noeud* lowerBoundNode = nullptr;
    
    while (currentNode != nullptr)
    {
        // Descend vers la gauche car cle inferieure a position actuelle
        if (c < currentNode->m_contenu->first)
        {
            lowerBoundNode = currentNode;    // Conserve l'identite du plus haut parent ou feuille en fin de parcours
            currentNode = currentNode->m_gauche;
        }
        // Descend vers la droite car cle superieure a position actuelle
        else if (c > currentNode->m_contenu->first)
        {
            currentNode = currentNode->m_droite;
        }
        // La cle existe, on retourne le noeud courant
        else
        {
            return iterator(currentNode);
        }
    }
    // Navigation que vers la droite seulement donc derniere feuille a droite
    if (lowerBoundNode == nullptr)
    {
        return iterator(m_apres);    // Incompatible d'utiliser end() sur fonction-membre const avec retour iterator non-const
    }
    else
    {
        return iterator(lowerBoundNode);    
    }
}

///////////////////////////////////////////////////////////////////////////
//erase a partir d'une position

template <typename Tclef, typename Tvaleur>
typename map<Tclef, Tvaleur>::iterator map<Tclef, Tvaleur>::erase(iterator i)
{
    assert(i!=end());
    erase(i++->first);
    return i;
}

///////////////////////////////////////////////////////////////////////////
//insert avec indice

template <typename Tclef, typename Tvaleur>
typename map<Tclef, Tvaleur>::iterator map<Tclef, Tvaleur>::insert(iterator j, const Tclef& c, const Tvaleur& val)
{
    return insert(c).first;
}

///////////////////////////////////////////////////////////////////////////
// gestion de l'equilibre de l'arbre


//effectuer une rotation simple de la gauche vers la droite
template <typename Tclef, typename Tvaleur>
void map<Tclef, Tvaleur>::rotation_gauche_droite(noeud*& p)
{
}

//effectuer une rotation simple de la droite vers la gauche
template <typename Tclef, typename Tvaleur>
void map<Tclef, Tvaleur>::rotation_droite_gauche(noeud*& p)
{
}


#endif /* mapImpl_h */
