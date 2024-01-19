# include <cstddef>

template <typename T, size_t DIM>
class Array {
    private:
        T* ARR; // pointeur vers array de type T
    public:
        // Constructeur par defaut
        Array() {
            ARR = new T[DIM];
        }

        // Destructeur de base
        ~Array() {
            delete[] ARR;
        }
};