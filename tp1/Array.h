# include <cstddef>

template <typename T, size_t DIM>
class Array {
    private:
        T* ARR; // pointeur vers le debut array de type T

    public:
        // Constructeur par defaut
        Array() {
            ARR = new T[DIM];
        }

        // Destructeur de base
        ~Array() {
            delete[] ARR;
        }

        // Retourne le nombre d’éléments du tableau
        size_t size() const {
            return DIM;
        };

        // Indique si le nombre d’éléments est de zéro
        bool empty() const {
            return DIM == 0;
        };

        // Retourne une référence vers un élément à la position indiquée sans validation
        T& operator[] (size_t index) const {
            return *(ARR + index);
        };

        // Retourne une référence vers un élément, en validant la position
        T& at(size_t index) const {
            if (index >= DIM) {
                throw std::out_of_range("Index est hors-limite du Array");
            };
            return *(ARR + index);
        };

        // front() : Retourne une référence sur le premier élément ;

        // back() : Retourne une référence sur le dernier élément ;

        // fill(T) : Affecte la valeur passée en paramètre à chaque élément du tableau

        // swap(Array<T, N>) : Échange le contenu de deux tableaux, en temps constant

        // fusion(Array<T, M>) : Fusionne le tableau courant avec celui reçu
        // en paramètre et retourne le tableau fusionné

        // subset<M>(size_t) : Retourne, dans un nouveau tableau, M valeurs
        // du tableau courant à partir de la position indiquée en paramètre

        // begin() : Retourne un itérateur au début du tableau ;

        // end() : Retourne un itérateur à la fin du tableau ;

        // cbegin() : Retourne un itérateur constant au début du tableau ;

        // cend() : Retourne un itérateur constant à la fin du tableau.
};