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
// Fonctions de rotations inspirees des notes de  cours IFT-339 v.10.2
// tel que mentionne dans l'enonce

//effectuer une rotation simple de la gauche vers la droite
template <typename Tclef, typename Tvaleur>
void map<Tclef, Tvaleur>::rotation_gauche_droite(noeud*& p)
{
    // Chercher les indices pre-rotations
    noeud *temp = p->m_gauche;    // noeud-enfant ("A") de gauche avec noeud parent p ("B") debalance
    int ia = temp->m_indice;
    int ib = p->m_indice;

    // Calculs et affectation des nouveaux indices post-rotations
    int nib = -ia - std::max(0, -ia) - 1 + ib;
    int nia = ia - std::max(0, -nib) - 1;
    temp->m_indice = nia;
    p->m_indice = nib;

    // Rotation enfant-g vers parent avec changements de ss-arbres
    p->m_gauche = temp->m_droite;
    temp->m_droite = p;
    p = temp;    
}

//effectuer une rotation simple de la droite vers la gauche
/*
Considerant A comme noeud enfant droite et B parent debalance
Pour nib:
ia = h2 - h3
h2 = h3 + ia
ha = max(h2, h3) + 1
   = max (h3 + ia, h3) + 1
   = h3 + max(0, ia) + 1

ib = h1 - ha
h1 = ha + ib = h3 + max(0, ia) + 1 + ib
Donc
nib = h1 - h2
    = (h3 + max(0, ia) + 1 + ib) - (h3 + ia)
    = -ia + max(0, ia) + 1 + ib


Pour nia:
nib = h1 - h2
h1 = nib + h2
nhb = max(h1, h2) + 1
    = max(nib + h2, h2) + 1
    = h2 + max(0, nib) + 1
    = h3 + ia + max(0, nib) + 1
Donc
nia = nhb - h3 = (h3 + ia + max(0, nib) + 1) - h3
nia = ia - max(0, nib) + 1
*/

template <typename Tclef, typename Tvaleur>
void map<Tclef, Tvaleur>::rotation_droite_gauche(noeud*& p)
{
    // Chercher les indices pre-rotations
    noeud *temp = p->m_droite;    // noeud-enfant ("A") de droite avec noeud parent p ("B") debalance
    int ia = temp->m_indice;
    int ib = p->m_indice;
    
    // Calculs et affectation des nouveaux indices post-rotations
    int nib = -ia + std::max(0, ia) + 1 + ib;
    int nia = ia - std::max(0, nib) + 1;
    temp->m_indice = nia;
    p->m_indice = nib;

    // Rotation enfant-d vers parent avec changement ss-arbres
    p->m_droite = temp->m_gauche;
    temp->m_gauche = p;
    p = temp;
}


#endif /* mapImpl_h */
