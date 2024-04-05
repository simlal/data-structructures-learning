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


///////////////////////////////////////////
// avancer et reculer un iterateur

template <typename TYPE,typename classe_de_dispersion>
void unordered_multiset<TYPE, classe_de_dispersion>::iterator::avancer()
{
}

template <typename TYPE,typename classe_de_dispersion>
void unordered_multiset<TYPE, classe_de_dispersion>::iterator::reculer()
{
}

/////////////////////////////////////////////////////////////////////
// fonctions generatrices

template <typename TYPE,typename classe_de_dispersion>
typename unordered_multiset<TYPE,classe_de_dispersion>::iterator
unordered_multiset<TYPE, classe_de_dispersion>::insert(const TYPE& val)
{
    // Faire le hachage de la nouvelle val et localiser l'alveole
    size_t valHachage = disperseur(val);
    size_t alv = valHachage % m_rep.size();
    
    // Creer une nouvelle alveole au besoin en fct du hachage
    if (m_rep[alv] == nullptr)
    {
        std::list<TYPE>* pList = new std::list<TYPE>();
        pList->push_back(val);
        m_rep[alv] = pList;
    }
    else
    {
        m_rep[alv]->push_back(val);     // 
    }

    // Mise a jour de la taille
    m_size++;

    // Augmentation nb alveoles en fct du facteur de charge
    float facteurCharge = static_cast<float>(m_size) / m_rep.size();       // moy nb ele par alveole
    if (facteurCharge > m_facteur_max)
    {
        m_rep.resize(m_rep.size() * 2 + 1);
    }
    // Iterator sur alveole d'insertion
    typename std::vector<std::list<TYPE>*>::iterator itAlv = m_rep.begin() + alv;
    
    // Iterator sur l'element insere dans la liste 
    typename list<TYPE>::iterator itPos = m_rep[alv]->end();
    itPos--;       // Chercher le dernier ele
    
    // Retour de l'iterator ums
    typename unordered_multiset<TYPE,classe_de_dispersion>::iterator p;
    p.m_alv = itAlv;
    p.m_pos = itPos;
    return p;
}

template <typename TYPE,typename classe_de_dispersion>
size_t unordered_multiset<TYPE, classe_de_dispersion>::erase(const TYPE& val)
{
    size_t nb=0;
    return nb;
}

template <typename TYPE,typename classe_de_dispersion>
typename unordered_multiset<TYPE,classe_de_dispersion>::iterator
unordered_multiset<TYPE, classe_de_dispersion>::erase(typename unordered_multiset<TYPE, classe_de_dispersion>::iterator i)
{
    return i;
}

#endif // unordered_multisetImpl_h
