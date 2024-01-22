# include <cstddef>

template <typename T, size_t DIM>
class Array {
    private:
        T* ARR; // pointeur vers le debut array de type T

    public:
        // Constructeur par defaut avec Array vide
        Array() {
            ARR = new T[DIM];
        }

        // Constructeur qui remplit le array avec la valeur de type T
        Array(T value) {
            // TODO use iterator
        }

        // Destructeur de base
        ~Array() {
            delete[] ARR;
        }

        // Getter pour membre ARR (debug)
        T* getARR() const {
            return ARR;
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

        // Retourne une référence sur le premier élément ;
        T& front() const {
            return *ARR;
        };

        // Retourne une référence sur le dernier élément ;
        T& back() const {
            return *(ARR + DIM - 1); // 0-based indexing
        };

        // Iterateur de Array pour fonctions qui necessitent de traverser le conteneur
        class Iterator {
            private:
                T* iter;    // 
            public:
                // Constructeur de base qui prend un pointeur T en param
                Iterator(T* iter) {
                    this->iter = iter;
                }
                // Pas de destructeur car instance creer sur la pile et conserver
                // dans la portee uniquement

                // Operateur ++ postfix
                Iterator& operator++() {
                    
                }
                // Operateur ++ prefix
                Iterator operator++(int) {

                }
                // Operateur == si 2e iterateur pointe a meme position que this
                bool operator==(const Iterator& otherIter) const {
                    return iter == otherIter.iter;
                }
                // Operateur != si 2e iterateur pointe a diff position que this
                bool operator!=(const Iterator& otherIter) const {
                    return iter != otherIter.iter;
                }
                // Operateur dereference *
                T& operator*() {
                    return *iter;
                }
        };


        // fill(T) : Affecte la valeur passée en paramètre à chaque élément du tableau
        // void fill(T value) {
        //     for (size_t i = 0; i < DIM; i++)
        // }

        // begin() : Retourne un itérateur au début du tableau ;

        // end() : Retourne un itérateur à la fin du tableau ;

        // cbegin() : Retourne un itérateur constant au début du tableau ;

        // cend() : Retourne un itérateur constant à la fin du tableau.


        // swap(Array<T, N>) : Échange le contenu de deux tableaux, en temps constant

        // fusion(Array<T, M>) : Fusionne le tableau courant avec celui reçu
        // en paramètre et retourne le tableau fusionné

        // subset<M>(size_t) : Retourne, dans un nouveau tableau, M valeurs
        // du tableau courant à partir de la position indiquée en paramètre
};