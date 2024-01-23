# include <cstddef>
# include <iostream>

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
            ARR = new T[DIM];    // Alloc sur heap type/dim
            fill(value);
        }
        // Constructeur de copie
        Array(Array& otherArr) {
            ARR = new T[DIM];    // Alloc sur heap type/dim
            
            // Copie les valeurs de otherArr dans this par dereference
            ConstIterator otherArrIter = otherArr.cbegin();
            for (Iterator iter = begin(); iter != end(); ++iter) {
                *iter = *otherArrIter;
                ++otherArrIter;
            }
        }

        // Destructeur de base
        ~Array() {
            delete[] ARR;
        }

        // Affichage de Array pour debug
        void printArr() const {
            // Base properties
            std::cout << "### Array info ###"<< std::endl;
            std::cout << "pARR (T*): " << ARR << std::endl;
            std::cout << "*pARR (1st ele value): " << *ARR << std::endl;
            std::cout << "DIM (size_t): " << DIM << std::endl;
            std::cout << "size (size_t): " << size() << std::endl;
            std::cout << "empty?: " << std::boolalpha << empty() << std::endl;
            std::cout << "front (T&): " << front() << std::endl;
            std::cout << "back (T&): " << back() << std::endl;
            
            // Affiche le contenu avec ConstIterator
            std::cout << "Contenu du Array: "<< std::endl;
            for (ConstIterator iter = cbegin(); iter != cend(); ++iter) {
                std::cout << "  ARR[" << iter.getCounter() << "]: ";
                std:: cout << *iter << std::endl;
            }
        }

        // Getter pour membre ARR (debug)
        T* getARR() const {
            return ARR;
        }

        // Retourne le nombre d’éléments du tableau
        size_t size() const {
            return DIM;
        }

        // Indique si le nombre d’éléments est de zéro
        bool empty() const {
            return size() == 0;
        }

        // Retourne une référence vers un élément à la position indiquée sans validation
        // Prend un const Array donc pas de modif
        T& operator[] (size_t index) const {
            return *(ARR + index);
        }
        
        // Retourne une référence vers un élément à la position indiquée sans validation
        // Prend un non-const Array donc peut modifier le Array
        T& operator[] (size_t index) {
            return *(ARR + index);
        }

        // Retourne une référence vers un élément, en validant la position
        // Prend un const Array donc pas de modif
        T& at(size_t index) const {
            if (index >= size()) {
                throw std::out_of_range("Index est hors-limite du Array");
            };
            return *(ARR + index);
        }
        // Retourne une référence vers un élément, en validant la position
        // Prend un non-const Array donc peut modifier le Array
        T& at(size_t index) {
            if (index >= size()) {
                throw std::out_of_range("Index est hors-limite du Array");
            };
            return *(ARR + index);
        }

        // Retourne une référence sur le premier élément ;
        T& front() const {
            return *ARR;
        }

        // Retourne une référence sur le dernier élément ;
        T& back() const {
            return *(ARR + size() - 1); // 0-based indexing
        }

        // Iterateur de Array pour fonctions qui necessitent de traverser le conteneur
        class Iterator {
            private:
                T* arrElement;
                size_t counter;    // Pour debug
            public:
                // Constructeur de base qui prend un pointeur T en param
                Iterator(T* arrElement) {counter++;
                    this->arrElement = arrElement;
                    this->counter = 0;
                }

                // Constructeur de copie
                Iterator(Iterator& otherIter) {

                }
                // Pas de destructeur car instance creer sur la pile et conserver
                // dans la portee uniquement

                // Affichage iterator pour debug
                void printIterator() const {
                    std::cout << "Iterator info" << std::endl;
                    std::cout << "arrElement (T*): " << arrElement << std::endl;
                    std::cout << "*arrElement: " << *arrElement << std::endl;

                }

                // getter pour arrElement (debug)
                T* getArrElement() const {
                    return arrElement;
                }
                // Getter pour counter (debug)
                size_t getCounter() const {
                    return counter;
                }

                // Operateur dereference *
                T& operator*() const {
                    return *arrElement;
                }
                // Operateur ++ prefixe retourne une reference a l'iterateur
                Iterator& operator++() {
                    arrElement = arrElement + 1;
                    counter++;
                    return *this;    // reference a l'iterateur incremente
                }
                // Operateur ++ postfixe retourne la valeur de l'iterateur avant incrementation
                // Incremente l'iterateur
                Iterator operator++(int) {
                    Iterator temp = *this;
                    arrElement = arrElement + 1;
                    counter++;
                    return temp;    // copie de l'etat actuel avant incrementation
                }
                // Operateur == si 2e iterateur pointe a meme position que this
                bool operator==(const Iterator& otherIter) const {
                    return arrElement == otherIter.arrElement;
                }
                // Operateur != si 2e iterateur pointe a diff position que this
                bool operator!=(const Iterator& otherIter) const {
                    return arrElement != otherIter.arrElement;
                }
        };


        // Retourne un itérateur au début du tableau ;
        Iterator begin() const {
            return Iterator(&front());
        }

        // Retourne un itérateur à la fin du tableau ;
        Iterator end() const {
            return Iterator(&back() + 1);
        }

        // Affecte la valeur passée en paramètre à chaque élément du tableau
        // Utilise ++ prefixe pour eviter la copie et incrementer directement iter
        void fill(T value) {
            for (Iterator iter = begin(); iter != end(); ++iter) {
                *iter = value;
            }
        }

        // ConstIterateur pour lecture du conteneur Array sans modification
        class ConstIterator {
            private:
                const T* arrElement;    // ptr vers element const non-mutable
                size_t counter;    // Pour debug

            public:
                // Constructeur de base
                ConstIterator(const T* arrElement) {
                    this->arrElement = arrElement;
                    this->counter = 0;
                }

                // Constructeur par copie d'un iterator constant
                ConstIterator(const ConstIterator* otherIter) {
                    this->arrElement = otherIter->arrElement;
                }

                // getter pour arrElement (debug)
                const T* getArrElement() const {
                    return arrElement;
                }
                // Getter pour counter (debug)
                size_t getCounter() const {
                    return counter;
                }

                // Operateur dereference * qui ne permet pas la modification de la reference
                const T& operator*() const {
                    return *arrElement;
                }
                // Operateur ++ prefixe retourne une reference a l'iterateur
                ConstIterator& operator++() {
                    arrElement = arrElement + 1;
                    counter++;
                    return *this;    // reference a l'iterateur incremente
                }
                // Operateur ++ postfixe retourne la valeur de l'iterateur avant incrementation
                // Incremente l'iterateur
                ConstIterator operator++(int) {
                    Iterator temp = *this;
                    arrElement = arrElement + 1;
                    counter++;
                    return temp;    // copie de l'etat actuel avant incrementation
                }
                // Operateur == si 2e iterateur pointe a meme position que this
                bool operator==(const ConstIterator& otherIter) const {
                    return arrElement == otherIter.arrElement;
                }
                // Operateur != si 2e iterateur pointe a diff position que this
                bool operator!=(const ConstIterator& otherIter) const {
                    return arrElement != otherIter.arrElement;
                }
        };

        // cbegin() : Retourne un itérateur constant au début du tableau ;
        ConstIterator cbegin() const {
            return ConstIterator(&front());
        }

        // cend() : Retourne un itérateur constant à la fin du tableau.
        ConstIterator cend() const {
            return ConstIterator(&back() + 1);
        }

        // Échange le contenu de deux tableaux, en temps constant
        // Peut seulement echanger 2 array de taille identique 
        void swap(Array& otherArr) {
            T* tempArr = ARR;
            ARR = otherArr.ARR;
            otherArr.ARR = tempArr;
        }

        // Fusionne le tableau courant avec celui reçu
        // en paramètre et retourne le tableau fusionné
        template<size_t M>
        Array<T, DIM + M> fusion(Array<T, M>& otherArr) const {
            // Alloc de l'espace (DIM + M) dans heap
            Array<T, DIM + M> fusedArr;
            typename Array<T, DIM + M>::Iterator fusedArrIter = fusedArr.begin();    // non-const iter pour remplir le array fusionne
            
            // Debut par copie de this
            for (ConstIterator iter = cbegin(); iter != cend(); ++iter) {
                *fusedArrIter = *iter;
                ++fusedArrIter;
            }
            
            // Creer const-iter de type Array avec une DIM differente
            typename Array<T, M>::ConstIterator otherIter = otherArr.cbegin(); 
            typename Array<T, M>::ConstIterator otherIterEnd = otherArr.cend(); 
            
            // Append otherArr dans le fusedArr
            for (otherIter; otherIter != otherIterEnd; ++otherIter) {
                *fusedArrIter = *otherIter;
                ++fusedArrIter;
            }
            
            return fusedArr;
        }

        // subset<M>(size_t) : Retourne, dans un nouveau tableau, M valeurs
        // du tableau courant à partir de la position indiquée en paramètre
};