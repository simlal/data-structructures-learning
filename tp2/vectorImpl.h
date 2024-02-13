//
//  Nom du fichier : vectorImpl.h
//
//  Auteur : Jean Goulet
//  Date :   2016-01-05
//
//  Modifié par : Vincent Ducharme, Septembre 2022
//
// =============================================
//
//  Nom de l'étudiant : Simon Lalonde (lals2906)
//
// =============================================

#ifndef _vectorImpl_h
#define _vectorImpl_h


///////////////////////////////////////////////////
//clear (vide la memoire dynamique)

template <typename T>
void vector<T>::clear()
{
    delete[] m_debut;
    m_debut = nullptr;
    m_finDim = nullptr;
    m_finCap = nullptr;

}

///////////////////////////////////////////////////
//resize (modifie la dimension)

template <typename T>
void vector<T>::resize(size_t nDIM)
{
    // Vecteur null size=0
    if (m_debut == nullptr) 
    {

    }
}


///////////////////////////////////////////////////
//reserve (modifie la capacite)

template <typename T>
void vector<T>::reserve(size_t nCAP)
{
    std::cout<<"reserve A VENIR"<<std::endl;
}

///////////////////////////////////////////////////
//fonctions d'acces a un element sauf front et back
//push_back
//pop_back
//operator[]
//operator[]const
//at
//at const

template <typename T>
void vector<T>::push_back(const T& x)
{
    std::cout<<"push_back A VENIR"<<std::endl;
}

template <typename T>
void vector<T>::pop_back()
{
    // Cas limite vecteur vide
    if (empty()) 
    {
        throw std::out_of_range("Impossible d'enlever dernier element liste vide");
    }
    --m_finDim;    // Diminue la taille par la fin sans affecter capacite
}

template <typename T>
T& vector<T>::operator[](size_t i)
{
    return *(m_debut + i);
}

template <typename T>
const T& vector<T>::operator[](size_t i)const
{
    return *(m_debut + i);
}

template <typename T>
T& vector<T>::at(size_t i)
{
    if (i >= size() || i < 0) 
    {
        throw std::out_of_range("L'index est hors de la plage possible");
    }
    return *(m_debut + i);
}
template <typename T>
const T& vector<T>::at(size_t i)const
{
    if (size() >= i || i < 0) 
    {
        throw std::out_of_range("L'index est hors de la plage possible");
    }
    return *(m_debut + i);
}


#endif // vectorImpl_h
