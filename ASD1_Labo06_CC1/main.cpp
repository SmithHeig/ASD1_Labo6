//HIDE
// PROGRAMME DE TEST. NE RIEN CHANGER

#include <iostream>
#include <algorithm>
#include "abr.cpp"
using namespace std;

void visitor(int a) { cout << a << " "; }

int main() {

    try {

        vector<int> values = { 10, 12, 16, 15, 7, 1, 12, 5, 11, 11, 4, 2, 6, 0, 13 };

        BinarySearchTree<int> abr;

        // **** INSERT ****

        cout << "Insertion de " << values.size() << " éléments\n";
        for(int i : values) {
            cout << i << " ";
            abr.insert(i);
        }
        cout << "\n\n";
        cout << "Etat de l'arbre: \n";
        abr.displayKeys();
        cout << "\n";

        // ***** CONTAINS ****

        const int M = *max_element(values.begin(), values.end());
        cout << "Recherche des valeurs de 0 à " << M << "\n";
        cout << "Trouves: ";
        for(int i = 0; i < M; ++i) {
            if(abr.contains(i))
                cout << i << " ";
        }
        cout << "\nAbsents: ";
        for(int i = 0; i < M; ++i) {
            if(not abr.contains(i))
                cout << i << " ";
        }
        cout << "\n\n";

        // ***** MIN ****

        cout << "Recherche du minimum: " << abr.min() << "\n\n";

        // ***** DELETE_MIN ****

        cout << "Suppression du minimum (2x) \n";
        for(int i = 0; i < 2; i++) {
            abr.deleteMin();
            cout << "Etat de l'arbre: \n";
            abr.displayKeys();
            cout << "\n";
        }

        // ***** DELETE ****

        vector<int> toDelete = { 10, 16, 7, 10 };

        for(int i : toDelete ) {
            if(abr.deleteElement(i)) {
                cout << "Suppression de " << i << "\n";
                cout << "Etat de l'arbre: \n";
                abr.displayKeys();
                cout << "\n";
            } else {
                cout << "Absence de " << i << ". Pas de suppression \n";
            }
        }

        // **** VISITES *****

        cout << "\nTest des parcours ... \n";
        cout << "Pre-ordonne : ";
        abr.visitPre(visitor);
        cout << "\n";

        cout << "Symetrique  : ";
        abr.visitSym(visitor);
        cout << "\n";

        cout << "Post-ordonne: ";
        abr.visitPost(visitor);
        cout << "\n\n";


        cout << "Fin des tests CC1 \n";

    } catch (...) {
        cout << "\nErreur - une exception imprévue a été capturée \n";
    }
    return 0;
}
