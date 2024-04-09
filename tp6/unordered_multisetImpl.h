//
//  unordered_setImpl.h
//  unordered_multiset
//
//  AUteur : Jean Goulet
//  Copyleft 2017
//
//  Modifie par : Vincent Ducharme, Automne 2022
//
//  Devoir fait par
//     Co�quipier 1 : Simon Lalonde - lals2906
//     Co�quipier 2 : Adrien Levert - leva3132

#ifndef unordered_multisetImpl_h
#define unordered_multisetImpl_h
#include "unordered_multiset.h"

///////////////////////////////////////////
// avancer et reculer un iterateur

template <typename TYPE,typename classe_de_dispersion>
void unordered_multiset<TYPE, classe_de_dispersion>::iterator::avancer()
{
    
    // Iterateur sur liste vide donc derniere alveole
    if ((*m_alv)->empty())
    {
        return;
    }
    // Avancer a la prochaine position
    if (++m_pos == (*m_alv)->end())
    {
        // Avancer au moins de 1 alv avant de valider si elle est vide
        do
        {
            ++m_alv;
        }
        while (*m_alv == nullptr);
        m_pos = (*m_alv)->begin();
    }
}

template <typename TYPE,typename classe_de_dispersion>
void unordered_multiset<TYPE, classe_de_dispersion>::iterator::reculer()
{
    // Impossible de verifier si on est sur la premiere alveole sans m_rep
    
    // On recule d'une alveole si on est au debut de la liste
    if (m_pos == (*m_alv)->begin())
    {
        do
        {
            --m_alv;
        } 
        while (*m_alv == nullptr);
        m_pos = --(*m_alv)->end();
    }
    // Recule simplement d'une position
    else
    {
        --m_pos;
    }
}

/////////////////////////////////////////////////////////////////////
// fonctions generatrices

template <typename TYPE,typename classe_de_dispersion>
typename unordered_multiset<TYPE,classe_de_dispersion>::iterator
unordered_multiset<TYPE, classe_de_dispersion>::insert(const TYPE& val)
{
    // Faire le hachage de la nouvelle val et localiser l'alveole
    size_t valHachage = disperseur(val);
    size_t nbAlv = m_rep.size() - 1;
    size_t indexAlv = valHachage % nbAlv;
    
    // Creer une nouvelle alveole au besoin en fct du hachage
    if (m_rep[indexAlv] == nullptr)
    {
        std::list<TYPE>* pList = new std::list<TYPE>();
        pList->push_back(val);
        m_rep[indexAlv] = pList;
    }
    else
    {
        m_rep[indexAlv]->push_back(val);
    }

    // Mise a jour de la taille
    m_size++;
    
    // Augmentation nb alveoles car surpasse facteur de charge a max
    float facteurCharge = static_cast<float>(m_size) / nbAlv;
    if (facteurCharge > m_facteur_max)
    {
        // Constructeur avec plus grande puissance de 2 du nbAlv prec
        unordered_multiset<TYPE, classe_de_dispersion> nouveauSet(nbAlv * 2);
        for (iterator it = begin(); it != end(); ++it)
        {
            size_t nouveauIndexAlv = disperseur(*it) % (nouveauSet.m_rep.size() - 1);
            if (nouveauSet.m_rep[nouveauIndexAlv] == nullptr)
            {
                nouveauSet.m_rep[nouveauIndexAlv] = new list<TYPE>();
            }
            nouveauSet.m_rep[nouveauIndexAlv]->push_back(*it);
            nouveauSet.m_size++;
        }
        // Echange du ptr original et reaffectation pour valeur inseree
        this->swap(nouveauSet);
        nbAlv = m_rep.size() - 1;
        indexAlv = valHachage % nbAlv;
    }

    // Chercher alveole de val avec iterateur 'random access'
    typename std::vector<std::list<TYPE>*>::iterator itAlv = m_rep.begin() + indexAlv;
    
    // Iterator sur l'element insere dans la liste 
    typename list<TYPE>::iterator itPos = m_rep[indexAlv]->end();
    itPos--;       // Chercher le dernier ele
    return iterator(itAlv, itPos);
}

template <typename TYPE,typename classe_de_dispersion>
size_t unordered_multiset<TYPE, classe_de_dispersion>::erase(const TYPE& val)
{
    // Faire le hachage de la nouvelle val et localiser l'alveole
    size_t nbEffacer = 0;
    size_t valHachage = disperseur(val);
    size_t nbAlv = m_rep.size() - 1;
    size_t indexAlv = valHachage % nbAlv;

    typename list<TYPE>::iterator it = m_rep[indexAlv]->begin();
    typename list<TYPE>::iterator fin = m_rep[indexAlv]->end();
    while (it != fin)
    {
        // Efface tous les exmaplaires
        if (*it == val)
        {
            it = m_rep[indexAlv]->erase(it);    // Retourne le prochain donc pas besoin ++it;
            nbEffacer++;
            m_size--;
            // Mettre nullptr si liste vide
            if (m_rep[indexAlv]->empty())
            {
                delete m_rep[indexAlv];
                m_rep[indexAlv] = nullptr;
            }
        }
        else
        {
            it++;       // Avance au prochain car non-trouve
        }
    }   
    
    // Diminution nb alveoles car facteur charge inferieur a min
    float facteurCharge = static_cast<float>(m_size) / nbAlv;
    if (facteurCharge < m_facteur_min)
    {
        // Constructeur avec nbAlvMin
        unordered_multiset<TYPE, classe_de_dispersion> nouveauSet(nbAlv / 2);
        for (iterator it = begin(); it != end(); it++)
        {
            size_t nouveauIndexAlv = disperseur(*it) % (nouveauSet.m_rep.size() - 1);
            if (nouveauSet.m_rep[nouveauIndexAlv] == nullptr)
            {
                nouveauSet.m_rep[nouveauIndexAlv] = new list<TYPE>();
            }
            nouveauSet.m_rep[nouveauIndexAlv]->push_back(*it);
            nouveauSet.m_size++;
        }
        // Echange du ptr original et reaffectation pour valeur inseree
        this->swap(nouveauSet);
    }
    return nbEffacer;
}

template <typename TYPE,typename classe_de_dispersion>
typename unordered_multiset<TYPE,classe_de_dispersion>::iterator
unordered_multiset<TYPE, classe_de_dispersion>::erase(typename unordered_multiset<TYPE, classe_de_dispersion>::iterator i)
{
    // Iterateur sur liste vide donc derniere alveole
    if (i == end())
    {
        return i;
    }
    // Faire le hachage de la nouvelle val et localiser l'alveole
    size_t valHachage = disperseur(*i);
    size_t nbAlv = m_rep.size() - 1;
    size_t indexAlv = valHachage % nbAlv;
    
    // Effacer l'element
    typename list<TYPE>::iterator itEfface = i.m_pos;
    ++i; 
    m_rep[indexAlv]->erase(itEfface);
    m_size--;
    // Mettre nullptr si liste vide
    if (m_rep[indexAlv]->empty())
    {
        delete m_rep[indexAlv];
        m_rep[indexAlv] = nullptr;
    }
    // Diminution nb alveoles car facteur charge inferieur a min
    float facteurCharge = static_cast<float>(m_size) / nbAlv;
    if (facteurCharge < m_facteur_min)
    {
        // Constructeur avec nbAlvMin
        unordered_multiset<TYPE, classe_de_dispersion> nouveauSet(nbAlv / 2);
        for (iterator it = begin(); it != end(); it++)
        {
            size_t nouveauIndexAlv = disperseur(*it) % (nouveauSet.m_rep.size() - 1);
            if (nouveauSet.m_rep[nouveauIndexAlv] == nullptr)
            {
                nouveauSet.m_rep[nouveauIndexAlv] = new list<TYPE>();
            }
            nouveauSet.m_rep[nouveauIndexAlv]->push_back(*it);
            nouveauSet.m_size++;
        }
        // Echange du ptr original et reaffectation pour valeur inseree
        this->swap(nouveauSet);
    }
    return i;
}
#endif // unordered_multisetImpl_h
