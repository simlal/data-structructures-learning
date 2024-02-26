//
//  listImpl.h
//
//  Auteur : Jean Goulet
//  Copyleft  2017 UdeS
//
//  Modifie par : Vincent Ducharme, Automne 2022
//
//  Devoir fait par
//     Co�quipier 1 : Simon Lalonde (lals2906)
//     Co�quipier 2 :

#ifndef listImpl_h
#define listImpl_h

//////////////////////////////////////////////////////////////
//fonctions generatrices privees
//////////////////////////////////////////////////////////////

template <typename TYPE>
typename list<TYPE>::cellule* list<TYPE>::insert(cellule* c, const TYPE& VAL)
{
    cellule* new_cell = new cellule(VAL, c, c->m_prec);     // pointeurs suiv-prec OK pour new_cell

    if (c->m_prec)    // Cas general
    {
        c->m_prec->m_suiv = new_cell;    // lien avant 'c'
    }
    else    // 'c' en debut de liste non-vide ou liste vide
    {
        m_debut = new_cell;
    }
    c->m_prec = new_cell;

    m_size++;
    return new_cell;
}

template <typename TYPE>
typename list<TYPE>::cellule* list<TYPE>::erase(cellule* c)
{
    // Tout sauf debut
    if (c->m_prec)
    {
        c->m_prec->m_suiv = c->m_suiv;    // pont entre prec et suiv
    }
    else    // Efface tete et ajustement
    {
        m_debut = c->m_suiv;
    }
    // Tout sauf la fin
    if (c->m_suiv)
    {
        c->m_suiv->m_prec = c->m_prec;
    }

    // Nettoyage memoire et maj taille
    cellule* next_cell = c->m_suiv;
    delete c;
    m_size--;
    return next_cell;
}


//////////////////////////////////////////////////////////////
//reverse_iterator
//////////////////////////////////////////////////////////////


template <typename TYPE>
class list<TYPE>::reverse_iterator
{
    friend class list<TYPE>;
    cellule* m_pointeur = nullptr;
    reverse_iterator() = default;
    reverse_iterator(cellule *c) :m_pointeur(c) {}
public:
    TYPE& operator*()const { return m_pointeur->m_prec->m_contenu; }
    TYPE* operator->()const { return &(m_pointeur->m_prec->m_contenu); }
    reverse_iterator& operator++(); //++i
    reverse_iterator operator++(int); //i++
    reverse_iterator& operator--(); //--i
    reverse_iterator operator--(int); // i--
    bool operator==(const reverse_iterator&droite)const;
    bool operator!=(const reverse_iterator&droite)const;
};

template <typename TYPE>
typename list<TYPE>::reverse_iterator& list<TYPE>::reverse_iterator::operator++()
{ 
    // ++i
    m_pointeur = m_pointeur->m_prec;
    return *this;
}

template <typename TYPE>
typename list<TYPE>::reverse_iterator list<TYPE>::reverse_iterator::operator++(int)
{ 
    // i++
    list<TYPE>::reverse_iterator copy_iter = *this;    // copie de this
    operator++();
    return copy_iter;
}

template <typename TYPE>
typename list<TYPE>::reverse_iterator& list<TYPE>::reverse_iterator::operator--()
{ 
    // --i
    m_pointeur = m_pointeur->m_suiv;
    return *this;
}

template <typename TYPE>
typename list<TYPE>::reverse_iterator list<TYPE>::reverse_iterator::operator--(int)
{ 
    // i--
    list<TYPE>::reverse_iterator copy_iter = *this;    // copie de this
    operator--();
    return copy_iter;
}

template <typename TYPE>
bool list<TYPE>::reverse_iterator::operator==(const list<TYPE>::reverse_iterator& droite) const
{
    return m_pointeur == droite.m_pointeur;
}

template <typename TYPE>
bool list<TYPE>::reverse_iterator::operator!=(const list<TYPE>::reverse_iterator& droite) const
{
    return !(*this == droite);
}

template <typename TYPE>
typename list<TYPE>::reverse_iterator list<TYPE>::rbegin()
{
    return reverse_iterator(&m_apres);    // la cellule de queue
}

template <typename TYPE>
typename list<TYPE>::reverse_iterator list<TYPE>::rend()
{
    return reverse_iterator(m_debut);    // la tete de la liste
}

///////////////////////////////////////////////////////////
//affectateur
///////////////////////////////////////////////////////////

template <typename TYPE>
list<TYPE>& list<TYPE>::operator=(const list<TYPE>& droite)
{
    if (this != &droite)    // Prevention re-assignation de sois
    {
        // Nettoyage memoire des cellules
        for (list<TYPE>::iterator i = begin(); i != end();)
        {
            cellule* to_delete = i.m_pointeur;    // Sauvegarde position actuelle avant incrementation
            ++i;
            delete to_delete;
        }
        // Reset liste vide
        m_debut = nullptr;
        m_size = 0;

        // Copie et re-assignation
        for (list<TYPE>::const_iterator i = droite.begin(); i != droite.end(); ++i)
        {
            push_back(*i);    // S'occupe d'ajuster m_debut et m_size
        }
    }
    return *this;
}


///////////////////////////////////////////////////////////
//algorithme reverse
///////////////////////////////////////////////////////////

template <typename TYPE>
void list<TYPE>::reverse()
{
    if (m_debut == nullptr || m_size <= 1) // Pas d'inversion pour liste vide ou 1 ele
    {
        return;
    }

    cellule* temp = nullptr;
    cellule* current_c = nullptr;
    list<TYPE>::iterator i_end = end();
    
    for (list<TYPE>::iterator i = begin(); i != i_end;)
    {
        // Echange des pointeurs suiv/prec en utilisant temp
        current_c = i.m_pointeur;
        temp = current_c->m_prec;
        current_c->m_prec = current_c->m_suiv;
        current_c->m_suiv = temp;

        i = current_c->m_prec; // Bouge iterateur en fonction de liste dans ordre original
    }

    // Copie debut et ajustement de tete
    temp = m_debut;
    m_debut = m_apres.m_prec;
    m_debut->m_prec = nullptr;

    // Ajustement de la queue
    m_apres.m_prec = temp;    // l'ancienne tete maintenant fin
    m_apres.m_prec->m_suiv = &m_apres;    // Ajustement de m_suiv pour dernier ele
    m_apres.m_suiv = nullptr;
}

#endif // listImpl_h
