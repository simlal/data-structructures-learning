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
    m_size = source.size();    // Conserve la meme taille
    if(m_size == 0)
	{
        m_cap = 0;
        m_debut = nullptr;
    }
    else
	{
        m_cap = m_size + 1;
        m_debut = new T*[m_cap];    // Allocation array de pointeurs incluant cap
        for(size_t i = 0; i < m_size; ++i) 
        {
            m_debut[i] = new T(source[i]);    // Copie valeur dans nouvel espace pointe par m_debut[i]
        }
		m_debut[m_size] = nullptr;    // element apres dernier
    }

    m_zero = 0;    // Reset debut a premier pos
}

template <typename T>
void deque<T>::resize(size_t nSize)
{
    // Clear pour resize de dim 0
    if (nSize == 0)
    {
        reserve(nSize);
    }
    
    // Agrandissement du deque
    else if (nSize > m_size)
    {
        size_t required_space = nSize - m_size;
        size_t spare_space = m_cap - m_size;
        if (spare_space <= required_space)
        {
            reserve(nSize + 1);    // Conserver tampon de +1
        }
    }

    // Reduction de la taille du deque
    else if (nSize < m_size)
    {   
        for (size_t i = nSize; i < m_size; ++i)
        {
            delete[] m_debut[(m_zero + i) % m_cap];
            m_debut[(m_zero + i) % m_cap] = nullptr;
        }
    }
    
    // M-a-j de la dimension sans probleme de capacite
    m_size = nSize;
}

template <typename T>
void deque<T>::reserve(size_t nCap)
{
    // Reset capacite a zero et liberation memoire
    if (nCap == 0)
    {
        clear();
        return;
    }
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
