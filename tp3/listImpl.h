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

    // Ajustement en fonction de c tete ou non 
    if (c->m_prec)
    {
        c->m_prec->m_suiv = new_cell;
    }
    else
    {
        m_debut = new_cell;     // m-a-j de la tete de liste
    }
    c->m_prec = new_cell;

    m_size++;
}

template <typename TYPE>
typename list<TYPE>::cellule* list<TYPE>::erase(cellule* c)
{
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
    TYPE& operator*()const;
    TYPE* operator->()const;
    reverse_iterator& operator++(); //++i
    reverse_iterator operator++(int); //i++
    reverse_iterator& operator--(); //--i
    reverse_iterator operator--(int); // i--
    bool operator==(const reverse_iterator&droite)const;
    bool operator!=(const reverse_iterator&droite)const;
};

template <typename TYPE>
typename list<TYPE>::reverse_iterator list<TYPE>::rbegin()
{
}

template <typename TYPE>
typename list<TYPE>::reverse_iterator list<TYPE>::rend()
{
}

///////////////////////////////////////////////////////////
//affectateur
///////////////////////////////////////////////////////////

template <typename TYPE>
list<TYPE>& list<TYPE>::operator=(const list<TYPE>& droite)
{
    return *this;
}


///////////////////////////////////////////////////////////
//algorithme reverse
///////////////////////////////////////////////////////////

template <typename TYPE>
void list<TYPE>::reverse()
{
}


#endif // listImpl_h
