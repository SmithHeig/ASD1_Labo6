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
    abr.display();
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
      abr.display();
      cout << "\n";
    }
    
    // ***** DELETE ****
    
    vector<int> toDelete = { 10, 16, 7, 10 };
    
    for(int i : toDelete ) {
      if(abr.deleteElement(i)) {
        cout << "Suppression de " << i << "\n";
        cout << "Etat de l'arbre: \n";
        abr.display();
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
    
    // **** SIZE ****
    
    cout << "Nombre d'éléments : " << abr.size() << "\n\n";
    
    // **** NTH_ELEMENT ****
    
    cout << "Test de nth_element \n";
    for(int i = 0; i < abr.size(); ++i) {
      cout << abr.nth_element(i) << " ";
    }
    cout << "\n\n";
    
    // **** RANK ****
    
    cout << "Test de rank: \n";
    for(int i = M; i >= 0; --i) {
      size_t r = abr.rank(i);
      if ( r != -1 )
        cout << r << " ";
    }
    cout << "\n\n";
    
    // **** CONSTRUCTEURS ET AFFECTATION ****
    
    /**cout << "Test du move constructor - abr2(move(abr)) \n";
    {
      BinarySearchTree<int> abr2 ( move(abr) );
      cout << "abr2: \n"; abr2.display();
      cout << "\n";
      cout << "abr: \n"; abr.display();
      cout << "\n";
      
      {
        cout << "Test du copy constructor - abr3(abr2)\n";
        BinarySearchTree<int> abr3 ( abr2 );
        cout << "\n";
        cout << "abr3: \n"; abr3.display();
        cout << "\n";
        
        {
          cout << "Test du move operator= - abr4 = move(abr2)\n";
          BinarySearchTree<int> abr4;
          abr4 = move(abr2);
          cout << "abr4: \n"; abr4.display();
          cout << "\n";
          cout << "abr2: \n"; abr2.display();
          cout << "\n";
          cout << "Destruction abr4 \n";
        }
        cout << "\n\n";
        cout << "Test du copy operator= - abr2 = abr3 \n";
        abr2 = abr3;
        cout << "\n";
        cout << "abr2: \n"; abr2.display();
        cout << "\n";
        cout << "abr3: \n"; abr3.display();
        cout << "\n";
        
        cout << "Destruction abr3 \n";
        
      }
      cout << "\n\n";

      cout << "Test du swap - abr.swap(abr2) \n\n";
      
      abr.swap(abr2);
      cout << "abr: \n"; abr.display();
      cout << "\n";
      cout << "abr2: \n"; abr2.display();
      cout << "\n";
      
      cout << "Destruction abr2 \n";
    }*/
    cout << "\n";
    cout << "Destruction abr \n";

  } catch (...) {
    cout << "\nErreur - une exception imprévue a été capturée \n";
  }
  return 0;
}
