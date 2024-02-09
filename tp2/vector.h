//
//  Nom du fichier : vector.h
//  Auteur : Jean Goulet
//  Date :   Septembre 2016
//
//  Modifié par : Vincent Ducharme, Septembre 2022
//
//

#ifndef _vector_h
#define _vector_h

#include <ostream>
#include <stdexcept> // Pour les exceptions standards dans vectorImpl.h
#include <utility> // Pour std::swap

template <typename T>
class vector
{
private:
    T *m_debut,*m_finDim,*m_finCap;
    
public:
    vector();
    vector(size_t);
    ~vector();
    vector(const vector&);
    vector& operator=(const vector&);
    
    class iterator;
    class const_iterator;
    class reverse_iterator;
    
    void resize(size_t);
    void reserve(size_t);
    size_t size()const;
    bool empty()const;
    void clear();
    void swap(vector&);
    
    T& back();
    const T& back()const;
    T& front();
    const T& front()const;
    void push_back(const T&);
    void pop_back();
    T& operator[](size_t);
    const T& operator[](size_t)const;
    T& at(size_t);
    const T& at(size_t)const;
    
    //fonctions d'iteration du vector
    iterator begin();
    iterator end();
	const_iterator begin() const;
    const_iterator end() const;
	const_iterator cbegin() const;
    const_iterator cend() const;
    reverse_iterator rbegin();
    reverse_iterator rend();

    //code jetable
    void afficher(std::ostream&)const;
};

template <typename T>
std::ostream& operator<<(std::ostream&,const vector<T>& V);

////////////////////////////////////////////////////////////////
//class iterator et reverse_iterator

template<typename T>
class vector<T>::iterator
{
friend class vector<T>;

private:
    T *m_pointeur;
    iterator(T *p=nullptr):m_pointeur(p){}
public:    
    T& operator*();
    iterator operator++(){return iterator(++m_pointeur);}    //++i
    iterator operator++(int){return iterator(m_pointeur++);} //i++
    iterator operator--(){return iterator(--m_pointeur);}    //--i
    iterator operator--(int){return iterator(m_pointeur--);} //i--
    bool operator==(const iterator& droite) const {return m_pointeur==droite.m_pointeur;}
    bool operator!=(const iterator& droite) const {return m_pointeur!=droite.m_pointeur;}
};

template<typename T>
class vector<T>::const_iterator
{
friend class vector<T>;

private:
    T *m_pointeur;
    const_iterator(T *p=nullptr):m_pointeur(p){}
public:    
    const T& operator*() const;
    const_iterator operator++(){return const_iterator(++m_pointeur);}    //++i
    const_iterator operator++(int){return const_iterator(m_pointeur++);} //i++
    const_iterator operator--(){return const_iterator(--m_pointeur);}    //--i
    const_iterator operator--(int){return const_iterator(m_pointeur--);} //i--
    bool operator==(const const_iterator& droite) const {return m_pointeur==droite.m_pointeur;}
    bool operator!=(const const_iterator& droite) const {return m_pointeur!=droite.m_pointeur;}
};

template<typename T>
class vector<T>::reverse_iterator
{
friend class vector<T>;

private:
    T *m_pointeur;
    reverse_iterator(T *p=nullptr):m_pointeur(p){}
public:    
    T& operator*();
    reverse_iterator operator++(){return reverse_iterator(--m_pointeur);}    //++i
    reverse_iterator operator++(int){return reverse_iterator(m_pointeur--);} //i++
    reverse_iterator operator--(){return reverse_iterator(++m_pointeur);}    //--i
    reverse_iterator operator--(int){return reverse_iterator(m_pointeur++);} //i--
    bool operator==(const reverse_iterator& droite) const {return m_pointeur==droite.m_pointeur;}
    bool operator!=(const reverse_iterator& droite) const {return m_pointeur!=droite.m_pointeur;}
};


template <typename T>
T& vector<T>::iterator::operator*()
{
    return *m_pointeur;
}

template <typename T>
const T& vector<T>::const_iterator::operator*() const
{
    return *m_pointeur;
}

template <typename T>
T& vector<T>::reverse_iterator::operator*()
{
    return *(m_pointeur-1);
}

////////////////////////////////////////////////////////////////
// constructeurs, affectateur et destructeur

template <typename T>
vector<T>::vector()
    :vector(0)
{
}

template <typename T>
vector<T>::vector(size_t dim)
{
    if(dim>0)
	{
        m_debut=new T[dim];
	}
    else 
	{
        m_debut=nullptr;
	}
    
    m_finDim=m_finCap=m_debut+dim;
}

template <typename T>
vector<T>::vector(const vector& source):vector(source.size())
{
    for(size_t i=0;i<source.size();++i)
	{
        m_debut[i]=source[i];
	}
}

template <typename T>
vector<T>& vector<T>::operator=(const vector& source)
{
	vector copie(source);
	swap(copie);
    return *this;
}

template <typename T>
vector<T>::~vector()
{
    clear();
}

////////////////////////////////////////////////////////////////
// selecteurs et mutateurs

template <typename T>
size_t vector<T>::size()const
{
    return m_finDim-m_debut;
}

template <typename T>
bool vector<T>::empty()const
{
    return m_debut==m_finDim;
}

template <typename T>
void vector<T>::swap(vector<T>& v)
{
    std::swap(m_debut,v.m_debut);
    std::swap(m_finDim,v.m_finDim);
    std::swap(m_finCap,v.m_finCap);
}

template <typename T>
T& vector<T>::back()
{
    return *(m_finDim-1);
}

template <typename T>
const T& vector<T>::back()const
{
    return *(m_finDim-1);
}

template <typename T>
T& vector<T>::front()
{
    return *m_debut;
}

template <typename T>
const T& vector<T>::front()const
{
    return *m_debut;
}



////////////////////////////////////////////////////////////////
//fonctions d'iteration de la class vector

template <typename T>
typename vector<T>::iterator vector<T>::begin()
{
    return iterator(m_debut);
}

template <typename T>
typename vector<T>::iterator vector<T>::end()
{
    return iterator(m_finDim);
}

template <typename T>
typename vector<T>::const_iterator vector<T>::begin() const
{
    return const_iterator(m_debut);
}

template <typename T>
typename vector<T>::const_iterator vector<T>::end() const
{
    return const_iterator(m_finDim);
}

template <typename T>
typename vector<T>::const_iterator vector<T>::cbegin() const
{
    return const_iterator(m_debut);
}

template <typename T>
typename vector<T>::const_iterator vector<T>::cend() const
{
    return const_iterator(m_finDim);
}

template <typename T>
typename vector<T>::reverse_iterator vector<T>::rbegin()
{
    return reverse_iterator(m_finDim);
}

template <typename T>
typename vector<T>::reverse_iterator vector<T>::rend()
{
    return reverse_iterator(m_debut);
}


////////////////////////////////////////////////////////////////
// code jetable
// Attention! cette fonction d'affichage ne fonctionne qu'avec
// de elements qui possedent l'operateur << des ostreams.

template <typename T>
void vector<T>::afficher(std::ostream& out)const
{
    out<<"\n"<<"Etat du vector a l'adresse: "<<this<<"\n";
    size_t i;
	out<<" m_debut:   "<<m_debut<<"\n";
	out<<" m_finDim: "<<m_finDim<<" (+"<<(m_finDim-m_debut)<<")\n";
	out<<" m_finCap: "<<m_finCap<<" (+"<<(m_finCap-m_debut)<<")\n";
    size_t dim=m_finDim-m_debut;
    size_t vide=dim;
    if(vide>11)
        vide=dim-11;
    else 
        vide=0;
    size_t cap=m_finCap-m_debut;
	for(i=0;i<dim;++i)
		if(i<10 || i>vide)
            out<<" "<<i<<": "<<m_debut[i]<<"\n";
        else
        {
            out<<" ..."<<"\n";
			i=vide;
        }
    
    if(cap>dim)
    {
        out<<" "<<i;
        if(cap-dim>1)
            out<<" a "<<cap-1;
        out<<": (--en reserve--)\n";
    }
}

template <typename T>
std::ostream& operator<<(std::ostream& out,const vector<T>& v)
{
    char delim='[';
    size_t s=v.size();
    if(s==0)
        out<<delim;
    if(s>40)
        s=40;
    for(size_t i=0;i<s;++i)
    {
        out<<delim<<v[i];
        delim=',';
    }
    out<<"]";
    return out;
}

///////////////////////////////////////////////////
//inclusion ici de vectorImpl.h des fonctions a modifier
#include "vectorImpl.h"

#endif
