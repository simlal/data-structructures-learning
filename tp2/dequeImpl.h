//
//  Nom du fichier dequeImpl.h
//  Description : deque-circulaire
//
//  Auteur : Jean Goulet 
//  Date :   2016-12-27
//  Copyleft 2016 UdeS
//
//  Modifié par : Vincent Ducharme, Septembre 2022
//
// =============================================
//
//  Nom de l'étudiant : Simon Lalonde (lals2906)
//
// =============================================

#ifndef _dequeImpl_h
#define _dequeImpl_h

/////////////////////////////////////////////////////////////////
//code a completer pour le devoir

template <typename T>
deque<T>::deque(const deque& source)
{
}

template <typename T>
void deque<T>::resize(size_t nSize)
{
}

template <typename T>
void deque<T>::reserve(size_t nCap)
{
}

template <typename T>
T& deque<T>::operator[](size_t i)
{
    return *m_debut[m_zero + i];
}

template <typename T>
T& deque<T>::at(size_t i)
{
    if (i >= size())
    {
        throw std::out_of_range("L'index est hors de la plage possible");
    }
    return *m_debut[m_zero + i];
}

template <typename T>
const T& deque<T>::operator[](size_t i)const
{
    return *m_debut[m_zero + i];
}

template <typename T>
const T& deque<T>::at(size_t i)const
{
    if (i >= size())
    {
        throw std::out_of_range("L'index est hors de la plage possible");
    }
    return *m_debut[m_zero + i];
}

template <typename T>
void deque<T>::push_back(const T& val)
{
}

template <typename T>
void deque<T>::pop_back()
{
}

template <typename T>
void deque<T>::push_front(const T& val)
{
}

template <typename T>
void deque<T>::pop_front()
{
}


#endif // dequeImpl_h
