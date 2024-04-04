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
//     Coéquipier 1 :
//     Coéquipier 2 :

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
    typename unordered_multiset<TYPE,classe_de_dispersion>::iterator p;
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
