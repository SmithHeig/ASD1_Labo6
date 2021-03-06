//
//  Binary Search Tree
//
//  Copyright (c) 2017 Olivier Cuisenaire. All rights reserved.
//

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <queue>
#include <cassert>
#include <stdexcept>
#include <stack>

using namespace std;

template < typename T >
class BinarySearchTree {
public:

    using value_type = T;
    using reference = T&;
    using const_reference = const T&;

private:
    /**
     *  @brief Noeud de l'arbre.
     *
     * contient une cle et les liens vers les sous-arbres droit et gauche.
     */
    struct Node {
        const value_type key; // clé non modifiable
        Node* right;          // sous arbre avec des cles plus grandes
        Node* left;           // sous arbre avec des cles plus petites
        size_t nbElements;    // nombre de noeuds dans le sous arbre dont
        // ce noeud est la racine

        Node(const_reference key)  // seul constructeur disponible. key est obligatoire
                : key(key), right(nullptr), left(nullptr), nbElements(1)
        {
            cout << "(C" << key << ") ";
        }
        ~Node()               // destructeur
        {
            cout << "(D" << key << ") ";
        }
        Node() = delete;             // pas de construction par défaut
        Node(const Node&) = delete;  // pas de construction par copie
        Node(Node&&) = delete;       // pas de construction par déplacement
    };

    /**
     *  @brief Copie le noeud
     *
     *  @param Node* r, le noeud à copier
     *
     *  Complexité: O(n)
     */    
    static Node* copyNode(Node* r){
        Node *node = nullptr;
        try {
            if (r != nullptr) {
                node = new Node(r->key);
                node->nbElements = r->nbElements;
                node->left = copyNode(r->left);
                node->right = copyNode(r->right);
                return node;
            }
            return r;
        } catch(...){
            if(node != nullptr){
                deleteSubTree(node);
            }
            throw;
        }
    }

    /**
     *  @brief  Racine de l'arbre. nullptr si l'arbre est vide
     */
    Node* _root;

public:
    /**
     *  @brief Constructeur par défaut. Construit un arbre vide
     *
     *  Complexité: O(1)
     */
    BinarySearchTree() : _root(nullptr) {
    }

    /**
     *  @brief Constucteur de copie.
     *
     *  @param other le BinarySearchTree à copier
     *
     *  Complexité: O(n)
     */
    BinarySearchTree(const BinarySearchTree& other ) {
        _root = copyNode(other._root);
    }

    /**
     *  @brief Opérateur d'affectation par copie.
     *
     *  @param other le BinarySearchTree à copier
     *
     *  Complexité: O(n)
     */
    BinarySearchTree& operator = (const BinarySearchTree& other ) {
        BinarySearchTree tmp = other;
        swap(tmp);
        return *this;
    }

    /**
     *  @brief Echange le contenu avec un autre BST
     *
     *  @param other le BST avec lequel on echange le contenu
     *
     *  Complexité: O(n)
     */
    void swap(BinarySearchTree& other ) noexcept {
        std::swap(_root, other._root);
    }

    /**
     *  @brief constructeur de copie par déplacement
     *
     *  @param other le BST dont on vole le contenu
     *
     *  Complexité: O(n)
     */
    BinarySearchTree( BinarySearchTree&& other ) noexcept
            : _root(nullptr){
        swap(other);
    }

    /**
     *  @brief Opérateur d'affectation par déplacement.
     *
     *  @param other le BST dont on vole le contenu
     *
     *  Complexité: O(1)
     */
    BinarySearchTree& operator = ( BinarySearchTree&& other ) noexcept {
        _root = nullptr;
        swap(other);
        return *this;
    }

    //
    // @brief Destructeur
    //
    // Ne pas modifier mais écrire la fonction
    // récursive privée deleteSubTree(Node*)
    //
    //  Complexité O(n)
    //
    ~BinarySearchTree() {
        if(_root != nullptr)
            deleteSubTree( _root );
    }

private:
    //
    // @brief Fonction détruisant (delete) un sous arbre
    //
    // @param r la racine du sous arbre à détruire.
    //          peut éventuellement valoir nullptr
    //
    //  Complexité: moy(n))
    //
    static void deleteSubTree(Node* r) noexcept {
        if(r != nullptr) {
            if (r->left != nullptr) {
                deleteSubTree(r->left);
            }
            if (r->right != nullptr) {
                deleteSubTree(r->right);
            }
            delete (r);
            r = nullptr;
        }
    }

public:
    //
    // @brief Insertion d'une cle dans l'arbre
    //
    // @param key la clé à insérer.
    //
    // Ne pas modifier mais écrire la fonction
    // récursive privée insert(Node*&,const_reference)
    //
    //  Complexité: moy(log(n))
    //
    void insert( const_reference key) {
        insert(_root,key);
    }

private:
    //
    // @brief Insertion d'une cle dans un sous-arbre
    //
    // @param r la racine du sous-arbre dans lequel
    //          insérer la cle.
    // @param key la clé à insérer.
    //
    // @return vrai si la cle est inseree. faux si elle etait deja presente.
    //
    // Si la cle est deja presente, cette fonction ne fait rien.
    // x peut éventuellement valoir nullptr en entrée.
    // la fonction peut modifier x, reçu par référence, si nécessaire
    //
    //  Complexité: moy(log(n))
    //
    static bool insert(Node*& r, const_reference key) {

        if(r == nullptr) {
            r = new Node(key);
            return true;
        }

        else if (key < r->key) {
            bool inserted = insert(r->left, key);
            //addition du nombre d'éléments des deux enfants
            r->nbElements = 1 + (r->left ? r->left->nbElements : 0) + (r->right ? r->right->nbElements : 0);
            return inserted;
        }

        else if (key > r->key) {
            bool inserted = insert(r->right, key);
            //addition du nombre d'éléments des deux enfants
            r->nbElements = 1 +  (r->left ? r->left->nbElements : 0) + (r->right ? r->right->nbElements : 0);
            return inserted;
        }

        else
            return false;

    }

public:
    //
    // @brief Recherche d'une cle.
    //
    // @param key la cle a rechercher
    //
    // @return vrai si la cle trouvee, faux sinon.
    //
    // Ne pas modifier mais écrire la fonction
    // récursive privée contains(Node*,const_reference)
    //
    //  Complexité moy(log(n))
    //
    bool contains( const_reference key ) const noexcept {
        return contains(_root,key);
    }

private:
    //
    // @brief Recherche d'une cle dans un sous-arbre
    //
    // @param key la cle a rechercher
    // @param r   la racine du sous-arbre
    //
    // @return vrai si la cle trouvee, faux sinon.
    //
    //  Complexité moy(log(n))
    //
    static bool contains(Node* r, const_reference key) noexcept {

        if(r == nullptr)
            return false;

        else if(key < r->key)
            return contains(r->left, key);

        else if(key > r->key)
            return contains(r->right, key);

        else
            return true;
    }

public:
    //
    // @brief Recherche de la cle minimale.
    //
    // @return une const reference a la cle minimale
    //
    // @exception std::logic_error si necessaire
    //
    // vous pouvez mettre en oeuvre de manière iterative ou recursive a choix
    //
    const_reference min() const {

        if(_root == nullptr)
            throw logic_error("empty tree");

        Node* min = _root;

        while(min->left != nullptr){
            min = min->left;
        }

        return min->key;
    }

    //
    // @brief Supprime le plus petit element de l'arbre.
    //
    // @exception std::logic_error si necessaire
    //
    // vous pouvez mettre en oeuvre de manière iterative ou recursive a choix
    //

    void deleteMin() {
        delete deleteMinAndReturnIt(_root);
    }


    //
    // @brief Supprime l'element de cle key de l'arbre.
    //
    // @param key l'element a supprimer
    //
    // si l'element n'est pas present, la fonction ne modifie pas
    // l'arbre mais retourne false. Si l'element est present, elle
    // retourne vrai
    //
    // Ne pas modifier mais écrire la fonction
    // récursive privée deleteElement(Node*&,const_reference)
    //
    bool deleteElement( const_reference key) noexcept {
        return deleteElement( _root, key );
    }

private:
    //
    // @brief Supprime l'element de cle key du sous arbre.
    //
    // @param r la racine du sous arbre
    // @param key l'element a supprimer
    //
    // si l'element n'est pas present, la fonction ne modifie pas
    // l'arbre mais retourne false. Si l'element est present, elle
    // retourne vrai
    //
    //  Complexité : O(log(n))  
    //
    static Node* minEl(Node *r){
        if(r == nullptr)
            throw logic_error("tree empty");

        if(r->left == nullptr)
            return r;

        return minEl(r->left);
    }

   /**
    * @brief Enleve et retourne le plus petit élément de l'arbre
    * 
    * @param r la racine du sous arbre
    * @return l'element minimum supprimé
    * 
    * Complexité : O(log(n))
    */    
    static Node* deleteMinAndReturnIt(Node* r) {
        if(r == nullptr)
            throw logic_error("empty tree");

        Node* min = r;
        Node* tmp = nullptr;

        r->nbElements--;
        //le minimum est la racine
        if(min->left == nullptr){
            tmp = min;
            return tmp;
        }

        // minEl est l'avant plus petit
        while(min->left->left != nullptr){
            min = min->left;
            min->nbElements--;
        }

        tmp = min->left;
        min->left = min->left->right;
        if (tmp->right != nullptr) {
            min->left = tmp->right;
        } else {
            tmp->left = nullptr;
        }

        return tmp;
    }


   /**
    * @brief Mise du nombre d'éléments de chaque nooeuds selon les enfants
    * 
    * @param r la racine du sous arbre
    * 
    * Complexité : O(n)
    */  
    static void updateNbElem(Node* r){
        if(r != nullptr){
            updateNbElem(r->left);
            updateNbElem(r->right);
            r->nbElements = 1 + (r->left ? r->left->nbElements : 0) + (r->right ? r->right->nbElements : 0);
        }
    }

   /**
    * @brief Supprime le noeud contenant la valeur key
    * 
    * @param r la racine du sous arbre
    * @param key valeur à supprimer 
    * @return true si la suppression s'est effectuée correctement
    * 
    * Complexité : O(log(n))
    */      
    static bool deleteElement( Node*& r, const_reference key) noexcept {

        if(r == nullptr)
            return false;

        if(r->key > key) {
            bool deleted = deleteElement(r->left, key);
            if (deleted) {
                r->nbElements--;
            }
            return deleted;
        }

        else if(r->key < key) {
            bool deleted = deleteElement(r->right, key);
            if(deleted){
                r->nbElements--;
            }
            return deleted;
        }
        else{ // key found
            Node* tmp = r;
            if(r->right == nullptr) {
                tmp = r->left;
                delete r;
                r = tmp;
            }
            else if(r->left == nullptr){
                tmp = r->right;
                delete r;
                r = tmp;
            } // use Hibbard
            else {
                Node* min = deleteMinAndReturnIt(r->right);
                min->nbElements = tmp->nbElements -1;
                r = min;
                tmp->right->left = min->right;
                min->right = tmp->right;
                min->left = tmp->left;
                delete tmp;
                tmp = nullptr;
            }
            return true;
        }
    }

public:
    //
    // @brief taille de l'arbre
    //
    // @return le nombre d'elements de l'arbre
    //
    //  Complexité: O(n)
    //
    size_t size() const noexcept {
        if(_root == nullptr){
            return 0;
        }
        return _root->nbElements;
    }

    // @brief cle en position n
    //
    // @return une reference a la cle en position n par ordre croissant des
    // elements
    //
    // @exception std::logic_error si nécessaire
    //
    // ajoutez le code de gestion des exceptions, puis mettez en oeuvre
    // la fonction recursive nth_element(Node*, n)
    //
    // Complexité: O(n)
    //
    const_reference nth_element(size_t n) const {
        if(_root == nullptr){
            throw logic_error("Erreur: l'arbre est vide");
        } else if(n > size()){
            throw logic_error("Erreur: La position est en dehors du tableau.");
        }
        return nth_element(_root,n);
    }

private:
    //
    // @brief cle en position n dans un sous arbre
    //
    // @param r la racine du sous arbre. ne peut pas etre nullptr
    // @param n la position n
    //
    // @return une reference a la cle en position n par ordre croissant des
    // elements
    //
    //  Complexité: O(n)
    //
    static const_reference nth_element(Node* r, size_t n) noexcept {
        size_t s;
        if(r->left == nullptr){
            s = 0;
        } else {
            s = r->left->nbElements;
        }
        if(n < s){
            return nth_element(r->left,n);
        } else if(n > s){
            return nth_element(r->right,n-s-1);
        } else {
            return r->key;
        }
    }

public:
    //
    // @brief position d'une cle dans l'ordre croissant des elements de l'arbre
    //
    // @param key la cle dont on cherche le rang
    //
    // @return la position entre 0 et size()-1, size_t(-1) si la cle est absente
    //
    // Ne pas modifier mais écrire la fonction
    // récursive privée rank(Node*,const_reference)
    //
    //  Compléxité moy O(log(n))
    //      
    size_t rank(const_reference key) const noexcept {
        return rank(_root,key);
    }

private:
    //
    // @brief position d'une cle dans l'ordre croissant des elements du sous-arbre
    //
    // @param key la cle dont on cherche le rang
    // @param r la racine du sous arbre
    //
    // @return la position entre 0 et size()-1, size_t(-1) si la cle est absente
    //
    //  Complexité moy O(log(n))
    //  
    static size_t rank(Node* r, const_reference key) noexcept {
        if(r == nullptr)
            return -1;
        else if(key < r->key)
            return rank(r->left, key);
        else if(key > r->key) {
            size_t rank_l = 0;
            size_t rank_r = rank(r->right, key);
            if(rank_r == -1)
                return -1;
            if(r->left != nullptr)
                rank_l = r->left->nbElements;
            return rank_l + rank_r + 1;
        }
        else{
            if(r->left != nullptr)
                return r->left->nbElements;
            return 0;
        }
    }

public:
    //
    // @brief linearise l'arbre
    //
    // transforme l'arbre en une liste simplement chainee composee des memes
    // noeuds que precedemment, mais dont les pointeurs left sont tous egaux
    // a nullptr. Cette liste doit toujours respecter les conditions d'un
    // arbre binaire de recherche
    //
    // Ne pas modifier cette fonction qui sert essentiellement a tester la
    // fonction recursive linearize(Node*, Node*&, size_t&) utilisée par
    // la methode publique arborize
    //
    //  Complexité: O(n)
    //
    void linearize() noexcept {
        size_t cnt = 0;
        Node* list = nullptr;
        linearize(_root,list,cnt);
        _root = list;
    }

private:
    //
    // @brief linearise une sous arbre tree en une liste
    //
    // @param tree pointe vers la racine de l'arbre a lineariser
    // @param list reference a la tete de la liste a creer. sera modifiee
    //             par la fonction pour que list pointe vers le plus petit
    //             element de tree
    // @param cnt  calcule au fure et a mesure le nombre d'elements de la liste
    //             cree. l'effet de la fonction doit etre d'ajouter le nombre
    //             d'elements du sous-arbre de racine tree. Cependant, vous
    //             avez uniquement le droit d'utiliser l'opérateur ++.
    //
    //  Complexité: O(n)
    //
    static void linearize(Node* tree, Node*& list, size_t& cnt) noexcept {
        if(tree == nullptr){
            return;
        }

        linearize(tree->right,list, cnt);

        Node* temp = list;
        list = tree;
        tree->right = temp;
        list->nbElements = ++cnt;

        linearize(tree->left, list,cnt);

        tree->left = nullptr;

    }

public:
    //
    // @brief equilibre l'arbre
    //
    // applique l'algorithme d'equilibrage de l'arbre par linearisation et
    // arborisation
    //
    // Ne pas modifier cette fonction.
    //
    //  Complexité: O(n)
    //  
    void balance() noexcept {
        size_t cnt = 0;
        Node* list = nullptr;
        linearize(_root,list,cnt);
        arborize(_root,list,cnt);
    }

private:
    //
    // @brief arborise les cnt premiers elements d'une liste en un arbre
    //
    // @param tree reference dans laquelle il faut ecrire la racine de l'arbre
    //             arborise par la fonction
    // @param list IN - reference a la tete de la liste a parcourir. La liste
    //                  est composee de Node dont le pointer left est nullptr
    //             OUT - debut de la suite de la liste dont on a utilise cnt
    //                   elements
    // @param cnt  nombre d'elements de la liste que l'on doit utiliser pour
    //             arboriser le sous arbre
    //
    //  Complexité: O(n)
    //
    static void arborize(Node*& tree, Node*& list, size_t cnt) noexcept {
        if(list == nullptr || cnt == 0){
            tree = nullptr;
            return;
        }

        Node* middleNode = list;
        size_t midCnt = (cnt-1)/2;

        while(midCnt != 0){
            middleNode = middleNode->right;
            --midCnt;
        }

        tree = middleNode;
        tree->nbElements = cnt;
        arborize(tree->left, list, (cnt-1)/2);
        list = middleNode->right;
        arborize(tree->right, list, cnt/2);

    }

public:
    //
    // @brief Parcours pre-ordonne de l'arbre
    //
    // @param f une fonction capable d'être appelée en recevant une cle
    //          en parametre. Pour le noeud n courrant, l'appel sera
    //          f(n->key);
    //
    //  Complexité: O(n)
    //
    template < typename Fn>
    void visitPre(Node* r, Fn f){
        if(r != nullptr){
            f(r->key);
            visitPre(r->left, f);
            visitPre(r->right, f);
        }
    }

    template < typename Fn >
    void visitPre (Fn f) {
        visitPre(_root, f);
    }

    //
    // @brief Parcours symétrique de l'arbre
    //
    // @param f une fonction capable d'être appelée en recevant une cle
    //          en parametre. Pour le noeud n courrant, l'appel sera
    //          f(n->key);
    //
    //  Complexité: O(n)	
    //
    template < typename Fn>
    void visitsym(Node* r, Fn f){
        if(r != nullptr){
            visitsym(r->left, f);
            f(r->key);
            visitsym(r->right, f);
        }
    }

    template < typename Fn >
    void visitSym (Fn f) {
        visitsym(_root, f);
    }

    //
    // @brief Parcours post-ordonne de l'arbre
    //
    // @param f une fonction capable d'être appelée en recevant une cle
    //          en parametre. Pour le noeud n courrant, l'appel sera
    //          f(n->key);
    //
    // Complexité: O(n)
    //
    template < typename Fn>
    void visitPost(Node* r, Fn f){
        if(r != nullptr){
            visitPost(r->left, f);
            visitPost(r->right, f);
            f(r->key);
        }
    }
    template < typename Fn >
    void visitPost (Fn f) {
        visitPost(_root, f);
    }

    //
    // Les fonctions suivantes sont fournies pour permettre de tester votre classe
    // Merci de ne rien modifier au dela de cette ligne
    //
    void display() const {
        stringstream ss1, ss2, ss3;
        displayKeys(ss1);
        displayKeys(ss3);
        displayCounts(ss2);
        string l1, l2;

        size_t W = 11;
        while( getline(ss3,l1) )
            if (l1.length() > W) W = l1.length();

        displayKeys(ss1);

        cout << "\n";
        cout << "+-" << left << setfill('-') << setw(W) << "-" << "+-" << setw(W) << "-" << setfill(' ') << "+" << endl;
        cout << "| "<< left << setw(W) << "key" << "| " << setw(W) << "nbElements" << "|" << endl;
        cout << "+-" << left << setfill('-') << setw(W) << "-" << "+-" << setw(W) << "-" << setfill(' ') << "+" << endl;
        while( getline(ss1,l1) and getline(ss2, l2) ) {
            cout << "| "<< left << setw(W) << l1 << "| " << setw(W) << l2 << "|" << endl;
        }
        cout << "+-" << left << setfill('-') << setw(W) << "-" << "+-" << setw(W) << "-" << setfill(' ') << "+" << endl;

    }

    void displayKeys(ostream& os = cout) const {
        display([](Node* n) -> const_reference { return n->key; }, os);
    }

    void displayCounts(ostream& os = cout) const {
        display([](Node* n) -> size_t { return n->nbElements; }, os);
    }

    //
    // utilise un parcours de l'arbre en largeur avec
    // un noeud sentinelle newLevel qui traque les
    // changements de niveaux
    //
    template <typename Fn>
    void display (Fn func, ostream& os = cout ) const {
        Node* newLevel = (Node*) -1;
        // addresse non nulle dont on est sur qu'elle ne contient pas
        // vraiment un Node. Utilisée comme sentinelle.

        queue<Node*> Q;
        Q.push(_root);
        Q.push(newLevel);

        while(!Q.empty()) {
            Node* cur = Q.front();
            Q.pop();

            if(cur == newLevel) {
                os << endl;
                if(!Q.empty())
                    Q.push(newLevel);
            } else if(cur == nullptr) {
                os << "- ";
            } else {
                os << func(cur) << " ";
                Q.push(cur->left);
                Q.push(cur->right);
            }
        }
    }
};