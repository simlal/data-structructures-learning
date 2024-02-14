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
    // Resize pour un vecteur de dim 0
    if (m_debut == nullptr) 
    {
        reserve(nDIM);
    }
    // Pour agrandissement du vecteur 
    else if (nDIM > size())
    {
        // Verification si capacite restante adequate
        size_t required_space = nDIM - size();
        size_t spare_space = m_finCap - m_finDim;
        if (spare_space < required_space)
        {
            reserve(std::max(nDIM, 2 * size()));    // Reserve le +grand de nDIM ou 2*CAP precedente
        }
    }
    // M-a-j de la dimension sans probleme de reserve
    m_finDim = m_debut + nDIM;
}


///////////////////////////////////////////////////
//reserve (modifie la capacite)

template <typename T>
void vector<T>::reserve(size_t nCAP)
{
    if (nCAP > m_finCap - m_debut)    // Compare capacite desiree vs existante 
    {
        T* new_debut = new T[nCAP];
        
        // Copie dans le nouvel espace dynamique
        for (size_t i=0; i < size(); i++) {
            new_debut[i] = m_debut[i];
        }
        
        size_t old_size = size();    // Conserver la dimension originale
        clear();    // Nettoyage pour eviter fuite de memoire
        
        // Changement d'adresse vecteur ajustement capacite
        m_debut = new_debut;
        m_finDim = m_debut + old_size;
        m_finCap = m_debut + nCAP;
    }   
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
    // Augmente la capacite de 1 au besoin
    size_t new_size = size() + 1;
    if (m_finDim == m_finCap)
    {
        reserve(new_size);
    }
    // Ajustement dimension et ajout x en dernier
    m_finDim = m_debut + new_size;
    m_debut[new_size - 1] = x;
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
