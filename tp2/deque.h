//
//  Nom du fichier : deque.h
//  Description : deque-circulaire
//
//  Auteur : Jean Goulet
//  Date :   2016-12-27
//  Copyleft 2016 UdeS
//
//  Modifié par Vincent Ducharme, Septembre 2022
//

#ifndef _deque_h
#define _deque_h

#include <ostream>
#include <utility>
#include <stdexcept>

template <typename T>
class deque
{
private:
    T**  m_debut;
    size_t m_cap,m_size,m_zero;
    void reserve(size_t);//augmente la capacite
public:
    deque(size_t=0);
    ~deque();
    deque(const deque&);
    deque& operator=(const deque&);
    void swap(deque&);
    
    //selecteurs
    size_t size()const;
    bool empty()const;
    
    //gestion de la memoire
    void resize(size_t); //change la dimension
    void clear();        //vide la memoire
    
    //acces aux elements individuels
    T& operator[](size_t);
    T& at(size_t);
    const T& operator[](size_t)const;
    const T& at(size_t)const;
    void push_back(const T&);
    void pop_back();
    void push_front(const T&);
    void pop_front();
    
    //code de mise au point
    void afficher(std::ostream&)const;
};

template <typename T>
deque<T>::deque(size_t dim)
{
    m_size=dim;
    if(dim==0)
	{
        m_cap=0;
        m_debut=nullptr;
    }
    else
	{
        m_cap=dim+1;
        m_debut=new T*[m_cap];
		m_debut[m_cap-1] = nullptr;
    }
    m_zero=0;
    for(size_t i=0;i<dim;++i)
	{
        m_debut[i]=new T();
	}
}

template <typename T>
deque<T>::~deque()
{
    clear();
}

template <typename T>
deque<T>& deque<T>::operator=(const deque& source)
{
	deque copie(source);
    swap(copie);
    return *this;
}

template <typename T>
void deque<T>::swap(deque& source)
{
    std::swap(m_debut,source.m_debut);
    std::swap(m_cap,source.m_cap);
    std::swap(m_size,source.m_size);
    std::swap(m_zero,source.m_zero);
}

template <typename T>
size_t deque<T>::size()const
{
    return m_size;
}

template <typename T>
bool deque<T>::empty()const
{
    return m_size==0;
}

template <typename T>
void deque<T>::clear(){
    for(size_t i=0;i<m_size;++i)
        delete m_debut[(i+m_zero)%m_cap];
    delete[] m_debut;
    m_debut=nullptr;
    m_zero=0;
    m_cap=m_size=0;
}


/////////////////////////////////////////////////////////////////
//code de mise au point

template <typename T>
void deque<T>::afficher(std::ostream& out)const
{
    out<<"\n"<<"Etat du deque a l'adresse: "<<this<<"\n";
    out<<"m_debut:"<<m_debut<<"\n";
    out<<"m_cap:  "<<m_cap<<"\n";
    out<<"m_size: "<<m_size<<"\n";
    out<<"m_zero: "<<m_zero<<"\n";
    out<<"---------------------------\n";
    size_t i,j;
    for(i=0;i<m_cap;++i)
    {
        j=(m_cap+i-m_zero)%m_cap;
        if(j>=m_size)
            out<<i<<"(-)"<<"\n";
        else 
            out<<i<<"("<<j<<"): "<<*m_debut[i]<<"\n";
    }
    if(m_cap>0)
        out<<"---------------------------\n";
}

template <typename T>
std::ostream& operator<<(std::ostream& out,const deque<T>& d)
{
    char delim='[';
    size_t s=d.size();
    if(s==0)
        out<<delim;
    if(s>40)
        s=40;
    for(size_t i=0;i<s;++i)
    {
        out<<delim<<d[i];
        delim=',';
    }
    out<<"]";
    return out;
}

#include "dequeImpl.h"


#endif // deque_h
