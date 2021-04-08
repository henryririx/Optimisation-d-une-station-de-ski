#include <iostream>
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include "Grapheski.h"

int main() {

    std::vector<int> pred;
    int init,fin;
    Grapheski g("duree.txt");
   //g.fichierecriture("duree.txt");
    g.afficherGraphe();
   // g.tempstrajet();
    //g.afficheTrajet();///4.3 affiche un trajet saisie, le type et la duréee, depart et arrivéé
    //g.afficherEntrantSortant();///4.3 pour un point affiche les trajets partants et entrants
   //g.fichierecriture("duree.txt");
   std::cout<<"Depart ?"<<std::endl;
   std::cin>>init;
    std::cout<<"Arrivee ?"<<std::endl;
    std::cin>>fin;
    pred=g.djikstra(init,fin);
    g.affichageDjik( pred ,  init ,  fin);

    return 0;
}
