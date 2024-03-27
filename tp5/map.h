//
//  map.h
//  MAP-AVL
//
//  Jean Goulet 17-03-17.
//  Copyleft 2017 UdeS
//

#ifndef map_h
#define map_h

#include <vector>
#include <string>
#include <cassert>
#include <cmath>
#include <ostream>
#include <stdexcept>

template <typename Tclef, typename Tvaleur>
class map
{
public:
    class iterator;
    class const_iterator;
    friend class iterator;
    friend class const_iterator;
    typedef std::pair<const Tclef, Tvaleur> paire_t;
private:
    struct noeud
    {
        paire_t* m_contenu;
        noeud *m_parent, *m_gauche, *m_droite;
        int m_indice;
        noeud(const Tclef& c, const Tvaleur& val, noeud* parent, noeud* gauche = nullptr, noeud* droite = nullptr)
            : m_parent(parent)
            , m_gauche(gauche)
            , m_droite(droite)
            , m_indice(0)
        {
            m_contenu = new paire_t(c, val);
        }

        noeud()
            :m_contenu(nullptr)
            , m_parent(nullptr)
            , m_gauche(nullptr)
            , m_droite(nullptr)
            , m_indice(0)
        {
        }

        ~noeud()
        {
            delete m_contenu;
            m_contenu = nullptr;
            m_parent = m_gauche = m_droite = nullptr;
        }
    };

    static void avancer(noeud*&);
    static void reculer(noeud*&);

    noeud *m_apres;
    int m_size;
    noeud*& reference(noeud*);

    //fonctions privees
    void vider(noeud*&);
    void copier(noeud*, noeud*&, noeud*);

    bool insert(const Tclef&, const Tvaleur&, noeud*&, iterator&);
    bool ajouter_gauche(const Tclef&, const Tvaleur&, noeud*&, iterator&);
    bool ajouter_droite(const Tclef&, const Tvaleur&, noeud*&, iterator&);

    bool erase(const Tclef&, noeud*&, noeud*&);
    bool enlever_gauche(const Tclef&, noeud*&, noeud*&);
    bool enlever_droite(const Tclef&, noeud*&, noeud*&);
    bool eliminer(noeud*&, noeud*&);

    void allonger_a_gauche(noeud*&);
    void allonger_a_droite(noeud*&);
    void rotation_gauche_droite(noeud*&);
    void rotation_droite_gauche(noeud*&);

    void afficher(std::ostream&, noeud*, size_t, std::vector<std::string>&, double&, size_t&) const;
    void afficher_barres(std::ostream& out, const std::vector<std::string>&, size_t)const;
public:
    map();
    ~map();
    map(const map&);
    map& operator=(const map&);
    void swap(map&);

    size_t size()const { return m_size; }
    bool empty()const { return size() == 0; }
    void clear();

    iterator find(const Tclef&)const;
    iterator lower_bound(const Tclef&)const;

    Tvaleur& operator[](const Tclef&);
    Tvaleur& at(const Tclef&);
    std::pair<iterator, bool> insert(const Tclef&, const Tvaleur&);
    iterator insert(iterator, const Tclef&, const Tvaleur&);

    size_t erase(const Tclef&);
    iterator erase(iterator);

    //fonction d'iteration
    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;

    //fonction de mise au point
    int verifier_hauteurs(std::ostream&, noeud* = nullptr)const;
    void afficher(std::ostream&)const;
};

template <typename Tclef, typename Tvaleur>
class map<Tclef,Tvaleur>::iterator
{
private:
    noeud* m_courant = nullptr;

    friend class map<Tclef,Tvaleur>;

    explicit iterator() = default;

    explicit iterator(noeud* p)
        : m_courant(p)
    {
    }
public:
    iterator(const iterator&) = default;
    iterator& operator=(const iterator&) = default;
    paire_t& operator*() { return *(m_courant->m_contenu); }
    paire_t* operator->() { return m_courant->m_contenu; }
    iterator& operator++() { map<Tclef, Tvaleur>::avancer(m_courant); return *this; }                          //++i
    iterator operator++(int) { iterator copie(*this); map<Tclef, Tvaleur>::avancer(m_courant); return copie; } //i++
    iterator& operator--() { map<Tclef, Tvaleur>::reculer(m_courant); return *this; }                          //--i
    iterator operator--(int) { iterator copie(*this); map<Tclef, Tvaleur>::reculer(m_courant); return copie; } //i--
    bool operator==(const iterator& dr) const { return m_courant ==dr.m_courant; }
    bool operator!=(const iterator& dr) const { return !(*this == dr); }
};

template <typename Tclef, typename Tvaleur>
class map<Tclef, Tvaleur>::const_iterator
{
private:
    noeud* m_courant = nullptr;
    friend class map<Tclef, Tvaleur>;

    explicit const_iterator() = default;

    explicit const_iterator(noeud* p)
        : m_courant(p)
    {
    }
public:
    const_iterator(const const_iterator&) = default;
    const_iterator& operator=(const const_iterator&) = default;
    const paire_t& operator*() const { return *(m_courant->m_contenu); }
    const paire_t* operator->() const { return m_courant->m_contenu; }
    const_iterator& operator++() { map<Tclef, Tvaleur>::avancer(m_courant); return *this; }                          //++i
    const_iterator operator++(int) { const_iterator copie(*this); map<Tclef, Tvaleur>::avancer(m_courant); return copie; } //i++
    const_iterator& operator--() { map<Tclef, Tvaleur>::reculer(m_courant); return *this; }                          //--i
    const_iterator operator--(int) { const_iterator copie(*this); map<Tclef, Tvaleur>::reculer(m_courant); return copie; } //i--
    bool operator==(const const_iterator& dr) const { return m_courant == dr.m_courant; }
    bool operator!=(const const_iterator& dr) const { return !(*this == dr); }
};

///////////////////////////////////////////////////////////////////////////
// fonctions d'iteration

template <typename Tclef, typename Tvaleur>
typename map<Tclef, Tvaleur>::iterator map<Tclef, Tvaleur>::begin()
{
    noeud* p = m_apres;
    while(p->m_gauche != nullptr)
        p = p->m_gauche;
    return iterator(p);
}

template <typename Tclef, typename Tvaleur>
typename map<Tclef, Tvaleur>::iterator map<Tclef, Tvaleur>::end()
{
    return iterator(m_apres);
}

template <typename Tclef, typename Tvaleur>
typename map<Tclef, Tvaleur>::const_iterator map<Tclef, Tvaleur>::begin() const
{
    noeud* p = m_apres;
    while (p->m_gauche != nullptr)
        p = p->m_gauche;
    return const_iterator(p);
}

template <typename Tclef, typename Tvaleur>
typename map<Tclef, Tvaleur>::const_iterator map<Tclef, Tvaleur>::end() const
{
    return const_iterator(m_apres);
}

///////////////////////////////////////////////////////////////////////////
// fonctions supplementaires de la class map
// ce sont des fonctions statiques, qui n'ont pas de paramètre imlicite

template <typename Tclef, typename Tvaleur>
void map<Tclef, Tvaleur>::avancer(noeud*& p)
{
    //AVANCER le pointeur p vers le prochain noeud en inordre
    //cette fonction fait automatiquement exception
    //si on avance au-dela de la fin
    if (p->m_droite != nullptr)
        for (p = p->m_droite;p->m_gauche != nullptr;p = p->m_gauche);
    else
    {
        noeud* pa;
        for (pa = p->m_parent;pa->m_gauche != p;p = pa, pa = p->m_parent);
        p = pa;
    }
}

template <typename Tclef, typename Tvaleur>
void map<Tclef, Tvaleur>::reculer(noeud*& p)
{
    //RECULER le pointeur p vers le noeud precedent en inordre
    //p sera nullptr si on recule au-dela du debut
    //cas limite: reculer de la fin
    if (p->m_gauche != nullptr)
        for (p = p->m_gauche;p->m_droite != nullptr;p = p->m_droite);
    else
    {
        noeud* pa;
        for (pa = p->m_parent;pa->m_droite != p;p = pa, pa = p->m_parent);
        p = pa;
    }
}

///////////////////////////////////////////////////////////////////////////
// fonctions privees

template <typename Tclef, typename Tvaleur>
typename map<Tclef, Tvaleur>::noeud*& map<Tclef, Tvaleur>::reference(noeud*p)
{
    if (p == m_apres)
        return m_apres;
    else if (p->m_parent->m_gauche == p)
        return p->m_parent->m_gauche;
    else
        return p->m_parent->m_droite;
}


template <typename Tclef, typename Tvaleur>
void map<Tclef, Tvaleur>::vider(noeud*& p)
{
    if (p == nullptr)
        return;
    vider(p->m_gauche);
    vider(p->m_droite);
    delete p;
    p = nullptr;
}

template <typename Tclef, typename Tvaleur>
void map<Tclef, Tvaleur>::copier(noeud* source, noeud*& dest, noeud* parent)
{
    if (source == nullptr)
        return;
    dest = new noeud(*source);
    dest->m_parent = parent;
    dest->m_indice = source->m_indice;
    copier(source->m_droite, dest->m_droite, dest);
    copier(source->m_gauche, dest->m_gauche, dest);
}

///////////////////////////////////////////////////////////////////////////
// fonctions privees d'insertion

template <typename Tclef, typename Tvaleur>
bool map<Tclef, Tvaleur>::insert(const Tclef& c, const Tvaleur& val, noeud*& p, iterator& r)
{
    if (c < p->m_contenu->first)
        return ajouter_gauche(c, val, p, r);
    else if (p->m_contenu->first < c)
        return ajouter_droite(c, val, p, r);
    else
        r = iterator(p);
    return false;
}

template <typename Tclef, typename Tvaleur>
bool map<Tclef, Tvaleur>::ajouter_gauche(const Tclef& c, const Tvaleur& val, noeud*& p, iterator& r)
{
    if (p->m_gauche == nullptr)
    {
        //nouvelle feuille
        p->m_gauche = new noeud(c, val, p);
        r = iterator(p->m_gauche);
        ++m_size;
        return(++(p->m_indice) == 1);
    }
    else if (insert(c, val, p->m_gauche, r))
    { //ajout general a gauche
        allonger_a_gauche(p);
        return p->m_indice != 0;
    }
    else
        return false;
}

template <typename Tclef, typename Tvaleur>
bool map<Tclef, Tvaleur>::ajouter_droite(const Tclef& c, const Tvaleur& val, noeud*& p, iterator& r)
{
    if (p->m_droite == nullptr)
    {         
        //nouvelle feuille
        p->m_droite = new noeud(c, val, p);
        r = iterator(p->m_droite);
        ++m_size;
        return(--(p->m_indice) == -1);
    }
    else if (insert(c, val, p->m_droite, r))
    { //ajout general a droite
        allonger_a_droite(p);
        return p->m_indice != 0;
    }
    else
        return false;
}

///////////////////////////////////////////////////////////////////////////
// fonctions privees d'elimination

template <typename Tclef, typename Tvaleur>
bool map<Tclef, Tvaleur>::erase(const Tclef& c, noeud*& p, noeud*& aRemplacer)
{
    if (c < p->m_contenu->first)
        return enlever_gauche(c, p, aRemplacer);
    else if (p->m_contenu->first < c)
        return enlever_droite(c, p, aRemplacer);
    else
    {
        aRemplacer = p;
        return enlever_gauche(c, p, aRemplacer);
    }
}

template <typename Tclef, typename Tvaleur>
bool map<Tclef, Tvaleur>::enlever_gauche(const Tclef& c, noeud*& p, noeud*& aRemplacer)
{
    if (p->m_gauche == nullptr)
        return eliminer(p, aRemplacer);
    else if (erase(c, p->m_gauche, aRemplacer))
    {
        allonger_a_droite(p);
        return p->m_indice == 0;
    }
    else
        return false;
}

template <typename Tclef, typename Tvaleur>
bool map<Tclef, Tvaleur>::enlever_droite(const Tclef& c, noeud*& p, noeud*& aRemplacer)
{
    if (p->m_droite == nullptr)
        return eliminer(p, aRemplacer);
    else if (erase(c, p->m_droite, aRemplacer))
    {
        allonger_a_gauche(p);
        return p->m_indice == 0;
    }
    else
        return false;
}

template <typename Tclef, typename Tvaleur>
bool map<Tclef, Tvaleur>::eliminer(noeud*& p, noeud*& aRemplacer)
{
    if (aRemplacer != nullptr)
    {
        delete aRemplacer->m_contenu;
        aRemplacer->m_contenu = p->m_contenu;
        p->m_contenu = nullptr;
        aRemplacer = p;
        if (p->m_gauche == nullptr)
            p = p->m_droite;
        else 
            p = p->m_gauche;
        if (p != nullptr)
            p->m_parent = aRemplacer->m_parent;
        --m_size;
        return true;
    }
    else
        return false;
}

///////////////////////////////////////////////////////////////////////////
// fonctions publiques

template <typename Tclef, typename Tvaleur>
map<Tclef, Tvaleur>::map()
    : m_apres(new noeud)
    , m_size(0)
{ }

template <typename Tclef, typename Tvaleur>
map<Tclef, Tvaleur>::~map()
{
    clear();
    delete m_apres;
    m_apres = nullptr;
}

template <typename Tclef, typename Tvaleur>
map<Tclef, Tvaleur>::map(const map& source) :map()
{
    copier(source.m_apres->m_gauche, m_apres->m_gauche, nullptr);
    m_size = source.size();
}

template <typename Tclef, typename Tvaleur>
map<Tclef, Tvaleur>& map<Tclef, Tvaleur>::operator=(const map& source)
{
    if (this != &source)
    {
        map<Tclef, Tvaleur> copie(source);
        this->swap(copie);
    }
    return *this;
}

template <typename Tclef, typename Tvaleur>
void map<Tclef, Tvaleur>::swap(map& source)
{
    std::swap(m_apres, source.m_apres);
    std::swap(m_size, source.m_size);

}

template <typename Tclef, typename Tvaleur>
void map<Tclef, Tvaleur>::clear()
{
    vider(m_apres->m_gauche);
    m_size = 0;
}

template <typename Tclef, typename Tvaleur>
Tvaleur& map<Tclef, Tvaleur>::at(const Tclef& c)
{
    auto p = lower_bound(c);
    if (p == end() || c < p->first)
        throw std::out_of_range("valeur absente du map");
    return p->second;
}


template <typename Tclef, typename Tvaleur>
typename map<Tclef, Tvaleur>::iterator map<Tclef, Tvaleur>::find(const Tclef& c)const
{
    iterator retour = lower_bound(c);
    if (retour == end() || c < retour->first)
        return end();
    return retour;
}

template <typename Tclef, typename Tvaleur>
Tvaleur& map<Tclef, Tvaleur>::operator[](const Tclef& c)
{
    auto r = this->insert(c);
    auto i = r.first;
    paire_t* pa = i.m_courant->m_contenu;
    return pa->second;
}

template <typename Tclef, typename Tvaleur>
std::pair<typename map<Tclef, Tvaleur>::iterator, bool> map<Tclef, Tvaleur>::insert(const Tclef& c, const Tvaleur& val)
{
    iterator retour;
    if (m_size == 0)
    {  //arbre vide
        m_apres->m_gauche = new noeud(c, val, m_apres);
        m_size = 1;
        return std::make_pair(begin(), true);
    }
    bool valeur = insert(c, val, m_apres->m_gauche, retour);
    return std::make_pair(retour, valeur);
}

template <typename Tclef, typename Tvaleur>
size_t map<Tclef, Tvaleur>::erase(const Tclef& c)
{
    size_t avant = size();
    if (size() != 0)
    {
        noeud* aRemplacer = nullptr;
        erase(c, m_apres->m_gauche, aRemplacer);
    }
    return avant - size();
}

///////////////////////////////////////////////////////////////////////////
// gestion de l'equilibre de l'arbre

//incrementer l'indice et verifier
//si on doit transferer des elements et le faire
template <typename Tclef, typename Tvaleur>
void map<Tclef, Tvaleur>::allonger_a_gauche(noeud*& p)
{
    //si le neoud *p est trop haut a gauche
    //faire les rotations necessaires
    //std::cout<<"vers la droite de "<<p->m_contenu->first<<" ("<<p->m_indice<<")"<<std::endl;
    ++(p->m_indice);
    if (p->m_indice != 2)
        return;
    if (p->m_gauche->m_indice == -1)
        rotation_droite_gauche(p->m_gauche);
    rotation_gauche_droite(p);

}

//decrementer l'indice et verifier
//si on doit transferer des elements et le faire
template <typename Tclef, typename Tvaleur>
void map<Tclef, Tvaleur>::allonger_a_droite(noeud*& p)
{
    //si le neoud *p est trop haut a droite
    //faire les rotations necessaires
    //std::cout<<"vers la gauche de "<<p->m_contenu->first<<" ("<<p->m_indice<<")"<<std::endl;
    --(p->m_indice);
    if (p->m_indice != -2)
        return;
    if (p->m_droite->m_indice == 1)
        rotation_gauche_droite(p->m_droite);
    rotation_droite_gauche(p);
}



///////////////////////////////////////////////////////////////////////////
// fonctions de mise au point

template <typename Tclef, typename Tvaleur>
int map<Tclef, Tvaleur>::verifier_hauteurs(std::ostream& out, noeud* p)const
{
    if (p == nullptr)
    { //pour l'appel initial sans parametres
        if (m_apres->m_gauche == nullptr)
            return true;
        else
            p = m_apres->m_gauche;
    }
    int hg = 0, hd = 0;
    if (p->m_gauche != nullptr)
        hg = verifier_hauteurs(out, p->m_gauche);
    if (hg == -1)
        return -1;
    if (p->m_droite != nullptr)
        hd = verifier_hauteurs(out, p->m_droite);
    if (hd == -1)
        return -1;
    int ind = hg - hd;
    if (ind > 1 || ind < -1)
    {
        out << "le noeud " << p->m_contenu->first;
        out << " n'est pas en equilibre: gauche=" << hg;
        out << ", droite=" << hd << std::endl;
        return -1;
    }
    else
        return 1 + std::max(hg, hd);
}


template <typename Tclef, typename Tvaleur>
void map<Tclef, Tvaleur>::afficher(std::ostream& out)const
{
    double total = 0.;
    size_t max = 0;
    out << "-------------------------------\n";
    std::vector<std::string> barres;
    barres.push_back("    ");
    afficher(out, m_apres->m_gauche, 1, barres, total, max);
    total = total / size();
    out << size() << " element";
    if (size() > 1)
        out << "s";
    out << "\n";
    out << "log(" << size() << "): " << log2(double(size())) << "\n";
    out << "hauteur moyenne: " << total << "\n";
    out << "hauteur maximale: " << max << "\n";
    out << "-------------------------------" << std::endl;
}


template <typename Tclef, typename Tvaleur>
void map<Tclef, Tvaleur>::afficher(std::ostream& out, typename map<Tclef, Tvaleur>::noeud* p, size_t niveau, std::vector<std::string>& barres, double& total, size_t& max) const
{
    if (p == 0)
        return;
    total += niveau;
    if (niveau > max)
        max = niveau;
    if (niveau >= barres.size())
        barres.push_back("    ");

    afficher(out, p->m_droite, niveau + 1, barres, total, max);

    //si on est un enfant de gauche arreter les barres a ce niveau
    if (p->m_parent != 0 && p->m_parent->m_gauche == p)
        barres[niveau - 1] = "    ";

    //cout<<niveau;
    afficher_barres(out, barres, niveau);
    out << "---> [";
    out << p->m_contenu->first << "," << p->m_contenu->second << "] (" << p->m_indice;
    //out<<", "<<p;
    //out<<", par="<<p->m_parent;
    //out<<", gau="<<p->m_gauche;;
    //out<<", dro="<<p->m_droite;
    out << ")\n";

    //si on est un enfant de droite barre a mon niveau
    if (p->m_parent->m_droite == p)
        barres[niveau - 1] = "   |";

    //si on a un enfant a gauche mettre des barres apres
    if (p->m_gauche != 0)
        barres[niveau] = "   |";
    else
        barres[niveau] = "    ";

    //cout<<niveau;
    afficher_barres(out, barres, niveau + 1);
    out << "\n";

    afficher(out, p->m_gauche, niveau + 1, barres, total, max);
}

template <typename Tclef, typename Tvaleur>
void map<Tclef, Tvaleur>::afficher_barres(std::ostream& out, const std::vector<std::string>& barres, size_t n) const
{
    for (size_t i = 0; i < n; ++i)
        out << barres[i];
}

#include "mapImpl.h"



#endif /* map_h */
