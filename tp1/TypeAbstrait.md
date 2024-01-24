# TP1 IFT-339: Types Abstraits
Créer un type abstrait de données relativement similaire au vecteur de la STL en C++. Il s'agit du premier devoir du cours de Structures de données et algorithmes (IFT-339) à l'Université de Sherbrooke.

## Structure du projet
Creation d'un header file `Array.h` qui contient un template de classe pour le type abstrait `Array`. Ce fichier contient aussi les signatures des fonctions et classes membres de la classe `Array`. Le ficher `main.cpp` n'a pas été fournit, mais les comportements on été testé au préaalable.

## Explication générale du type abstrait `Array`
Le type abstrait `Array` est un tableau dynamique qui peut contenir des éléments de n'importe quel type. Ce type est inspiré de la classe `vector` de la STL C++.

 Il est possible de creer des instances du conteneur `Array`, d'accéder les différents éléments du conteneur et les modifiers graces aux fonctions membres de la classe `Array`. Il est également possible de faire des opérations entre 2 conteneurs `Array` de même type (type des éléments contenus et dimension).

 Une différence principale avec le type `vector` de la STL est que la taille du conteneur `Array` doit être connue à la compilation. Il est donc impossible de modifier la taille du conteneur `Array` une fois qu'il est créé. Cependant, il existe certaines fonctions membres qui peuvent échanger (`swap()`), échantillonner (`subset()`) ou fusionner (`fusion()`) 2 conteneurs `Array` de même type.

### Fonctions membres du type abstrait `Array`
<u>Membres privés:</u>
- `T* ARR`: Pointeur vers le début du tableau contenant les éléments du conteneur `Array`.

<u>Membres publiques</u>

**Constructeurs**
- `Array()`: Constructeur par défaut. Creer un conteneur vide de la dimension spécifiée du template. On alloue l'espace dans le heap et on créer le champ `ARR` qui pointe vers le début de l'espace alloué.

- `Array(T value)`: Constructeur qui prend une valeur de type T et qui initialise tous les éléments du conteneur `Array` à cette valeur.

- `Array(Array& otherArr)`: Constructeur par copie. Creer une copie du conteneur `Array` passé en paramètre. Utilise un `ConstIterator` pour parcourir le conteneur `Array` passé en paramètre et copier les éléments dans le nouveau conteneur `Array`.

**Affectateur de mouvement**
- `Array& operator=(Array&& otherArr)`: Affectateur de mouvement. Réassigne l'adresse du pointeur `ARR` du Array avec celle du Array passé en paramètre en libérant l'espace alloué du conteneur Array au préalable. N'est pas utilisé dans les fonctions membres.

**Destructeur**
- `~Array()`: Destructeur. Libère l'espace alloué dans le heap pour le conteneur `Array` en utilisant l'opérateur `delete[]`.

**Fonctions d'aide facultative**
- `printArr()`: Fonction d'aide qui permet d'afficher les propriétés du conteneur `Array` dans la console. Utilise un `ConstIterator` pour parcourir le conteneur `Array` et afficher les éléments.

**Fonctions membres principales**
- `size()`: Retourne la taille  de type `size_t` du conteneur `Array` sans le modifier.

- `empty()`: Retourne un booléen qui indique si le conteneur `Array` est vide (true == 1 ou false == 0).

- `operator[](size_t index)`: Retourne une référence vers l'élément à l'index de type `size_t` spécifié du conteneur `Array`. Si l'index est invalide, on retourne une référence vers le premier élément du conteneur `Array`. Prend un non-const Array car il peut être modifier puisqu'il retourne une référence en le chainant avec l'opérateur `=`. Ne valide pas si l'index est valide. Il y a également une version qui prends un Array constant s'il n'est pas modifé.

- `at(size_t index)`: Comme l'opérateur `[]`, mais valide si l'index est valide. Si l'index est invalide, on retourne une référence vers la position correspondante à l'index. Il existe autant des versions qui prennent un Array constant que non-constant.

- `front()`: Retourne une référence vers le premier élément du conteneur `Array`. On utilise l'operateur de dereference `*` pour retourner la valeur de `ARR` qui pointe sur le Array (this). En specifiant le type de retour comme `T&`, on retourne une référence vers l'élément et non une copie de l'élément.

- `back()`: Comme `front()`, mais au pointeur `ARR` de type `T` on additionne la taille size_t  de (`size()`) - 1 (puisque la) pour aller chercher l'adresse du dernier élément. Même mécanique C++ qui retourne la référence au lieu de la copie avec le type dans la déclaration de fonction.

**Classes membres d'itérateurs**
On définie un `Iterator` et `ConstIterator` pour naviguer dans le conteneur `Array`. On utilise le `Iterator` pour modifier les éléments du conteneur `Array` et le `ConstIterator` pour parcourir le conteneur `Array` sans le modifier. Il est facile d'instantié un de ces itérateurs en utilisant les fonctions membres `begin()`, `end()`, `cbegin()` et `cend()`. À l'intérieur nous avons surcharger les opérateurs `++`, `*`, `==` et `!=` pour faciliter la navigation dans le conteneur `Array` en plus des constructeurs par défaut et par copie.

**Fonctions de ''modification'' du conteneur `Array`**
- `fill(T value)`: Remplie le conteneur `Array` avec la valeur de type T spécifiée. On utilise un `Iterator` pour parcourir le conteneur `Array` et remplacer les éléments par la valeur spécifiée.

- `swap(Array& otherArr)`: Échange le contenu du conteneur `Array` avec le contenu du conteneur `Array` passé en paramètre. On utilise un `Iterator` pour parcourir les 2 conteneurs `Array` et échanger les éléments. Il s'agit d'un échange en temps constant car nous ne faisons qu'échanger les pointeurs `ARR` des 2 conteneurs `Array`. Aucun retour mais change le contenu des 2 Arrays impliques.

- `subset(size_t index)`: Retourne un nouveau conteneur `Array` qui contient les éléments du conteneur `Array` à partir de l'index spécifié jusqu'à la fin du conteneur `Array`. Ainsi, on doit créer un nouvel Array dans le heap en appelant le constructeur de la dimension finale (Array.size - index). On utilise un `ConstIterator` pour parcourir le conteneur `Array` et copier les éléments dans le nouveau conteneur `Array` en utilisant lui même un `Iterator`. ne modifie pas le Array initital.

- `fusion(const Array& otherArr)`: Retourne un nouveau conteneur `Array` qui contient les éléments du conteneur `Array` et du conteneur `Array` passé en paramètre. Il s'agit d'une fonction template qui nous permet de modifier le type de Array afin d'avoir la bonne taille finale. On passe le otherArr par référence constante car on ne le modifie pas. Utilise 2 `ConstIterator` pour parcourir les 2 conteneurs `Array` et copier les éléments dans le nouveau conteneur `Array` en utilisant lui même un `Iterator` dans le nouvel array fusionnee afin de faire l'équivalent de ''append'' le `Array` avec `otherArr`.
