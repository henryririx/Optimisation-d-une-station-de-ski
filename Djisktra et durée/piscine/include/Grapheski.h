#ifndef GRAPHESKI_H
#define GRAPHESKI_H
#include <algorithm>
#include <iostream>
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include "Arc.h"
#include "Point.h"

class Grapheski
{
private:

    ///pour le graphe
    std::vector<Point*>m_point;    ///vecteur de pointeurs sur point
    std::vector<Arc*>m_trajet;  ///vecteur de trajet
    int ordre;  /// nombre de points
    int taille;   ///nombre de trajets

public:
    std::vector<Point*> getpoint() const
    {
        return m_point;
    }

    void setpoint(std::vector<Point*>point)
    {
        m_point=point;
    }

    std::vector<Arc*> gettrajet() const
    {
        return m_trajet;
    }

    void settrajet(std::vector<Arc*>trajet)
    {
        m_trajet=trajet;
    }

    int getnbpoint() const
    {
        return ordre;
    }
    int getnbtrajet() const
    {
        return taille;
    }
    Grapheski(std::string fichier)
    {
        std::ifstream ifs{fichier};
        if (ifs.fail())
            throw std::runtime_error("Probleme lecture orientation du graphe");
        ifs >> ordre;
        if (ifs.fail())
            throw std::runtime_error("Probleme lecture ordre du graphe");
        for (int i = 0; i < ordre; ++i)
            m_point.push_back(new Point{i});

        std::string nom;
        int num;
        int alt;
        for (int i = 0; i < ordre; i++) {
            ifs >> num >> nom >> alt;
            m_point[i]->setnomlieu(nom);
            m_point[i]->setaltitude(alt);
            m_point[i]->setnumeropoint(num);

        }
        if (ifs.fail())
            throw std::runtime_error("Probleme lecture taille du graphe");
        ifs >> taille;
        if(fichier=="data_arcs.txt")
        {
            int num1, arriv, depart;
            std::string moy, nom2;
            for (int i = 0; i < taille; i++) {
                ifs>>num1>>nom2>>moy>>depart>>arriv;
                m_trajet.push_back(new Arc(i));
                m_trajet[i]->setdepart(depart);
                m_trajet[i]->setp1(m_point[depart - 1]);
                m_trajet[i]->setarrivee(arriv);
                m_trajet[i]->setp2(m_point[arriv - 1]);
                m_trajet[i]->setnomtrajet(nom2);
                m_trajet[i]->setnumerotrajet(num1);
                m_trajet[i]->settypetrajet(moy);

                m_point[depart-1]->ajouterSucc(m_point[arriv-1],0);

            }
        }
        if(fichier=="duree.txt")
        {
            int num1, arriv, depart,duree;
            std::string moy, nom2;
            for (int i = 0; i < taille; i++) {
                ifs>>num1>>nom2>>moy>>depart>>arriv>>duree;
                m_trajet.push_back(new Arc(i));
                m_trajet[i]->setdepart(depart);
                m_trajet[i]->setp1(m_point[depart - 1]);
                m_trajet[i]->setarrivee(arriv);
                m_trajet[i]->setp2(m_point[arriv - 1]);
                m_trajet[i]->setnomtrajet(nom2);
                m_trajet[i]->setnumerotrajet(num1);
                m_trajet[i]->settypetrajet(moy);

                m_point[depart-1]->ajouterSucc(m_point[arriv-1],duree);

            }
        }


        /*
        std::ifstream ifs{fichier};
        if (ifs.fail())
            throw std::runtime_error("Probleme lecture orientation du graphe");
        ifs >> ordre;
        if (ifs.fail())
            throw std::runtime_error("Probleme lecture ordre du graphe");
        for (int i = 0; i < ordre; ++i)
            m_point.push_back(new Point{i});

        std::string nom;
        int num;
        int alt;
        for (int i = 0; i < ordre; i++)
        {
            ifs >> num >> nom >> alt;
            m_point[i]->setnomlieu(nom);
            m_point[i]->setaltitude(alt);
            m_point[i]->setnumeropoint(num);

        }
        if (ifs.fail())
            throw std::runtime_error("Probleme lecture taille du graphe");
        ifs >> taille;
        int num1, arriv, depart;
        std::string moy, nom2;
        for (int i = 0; i < taille; i++)
        {
            ifs>>num1>>nom2>>moy>>depart>>arriv;
            m_trajet.push_back(new Arc(i));
            m_trajet[i]->setdepart(depart);
            m_trajet[i]->setp1(m_point[depart - 1]);
            m_trajet[i]->setarrivee(arriv);
            m_trajet[i]->setp2(m_point[arriv - 1]);
            m_trajet[i]->setnomtrajet(nom2);
            m_trajet[i]->setnumerotrajet(num1);
            m_trajet[i]->settypetrajet(moy);
*/
          /*if(m_point[m_trajet[i]->getp1()->getnumeropoint()-1]->verification(m_trajet[i]->getp2()->getnumeropoint())==false)
            m_point[depart-1]->ajouterSucc(m_point[arriv-1],0);*/

        }

    void afficherGraphe()const
    {
         std::cout << std::endl << "graphe ";
        std::cout << "ordre = " << ordre<< std::endl << "  ";
        std::cout << "listes d'adjacence :" << std::endl;
        for (auto s : m_point) {
            std::cout<<" le point "<<s->getnumeropoint()<<" a pour adjacent: ";
            s->afficher();
            std::cout << std::endl;
        }
    }

    void tempstrajet()
    {
        int d; //distance entre 2 points
        for (int i =0; i< m_trajet.size(); i++)
        {   if(m_trajet[i]->getp1()->getaltitude()>m_trajet[i]->getp2()->getaltitude()) {
                d = m_trajet[i]->getp1()->getaltitude() -
                    m_trajet[i]->getp2()->getaltitude(); // calcul distance entre les deux points}
            }
            else{
                d = m_trajet[i]->getp2()->getaltitude()-m_trajet[i]->getp1()->getaltitude(); // calcul distance entre les deux points}
            }

            //pour la descente

            if ( m_trajet[i]->gettypetrajet() == "V")   /// si la piste est verte
            {
                m_trajet[i]->setDuree(((60*5)*d)/100);     /// donne le temps en SECONDEs
            }



            if ( m_trajet[i]->gettypetrajet() == "R" )  /// si la piste est rouge
            {
                m_trajet[i]->setDuree(((60*3)*d)/100);
            }



            if ( m_trajet[i]->gettypetrajet() == "B" ) /// si la piste est bleue
            {
                m_trajet[i]->setDuree(((60*4)*d)/100);
            }



            if ( m_trajet[i]->gettypetrajet() == "N" ) /// si la piste est noire
            {
                m_trajet[i]->setDuree(((60*2)*d)/100);
            }



            if ( m_trajet[i]->gettypetrajet() == "KL" )
            {
                m_trajet[i]->setDuree((10*d)/100);// le temps est deja en secondes
            }




            if (m_trajet[i]->gettypetrajet() == "SURF" )
            {
                m_trajet[i]->setDuree(((60*10)*d)/100);
            }
// pour les remontees



            if (m_trajet[i]->gettypetrajet() == "TPH" )
            {
                m_trajet[i]->setDuree( (4*60 + (((60*2)*d))/100));
            }



            if ( m_trajet[i]->gettypetrajet() == "TC" )
            {
                m_trajet[i]->setDuree((2*60 + (((60*3)*d))/100));
            }



            if (m_trajet[i]->gettypetrajet() == "TSD" )
            {
                m_trajet[i]->setDuree((60 +( ((60*3)*d))/100));
            }
            if ( m_trajet[i]->gettypetrajet() == "TS" )
            {



                m_trajet[i]->setDuree((60 + (((60*4)*d))/100));
            }
            if ( m_trajet[i]->gettypetrajet() == "TK" )
            {
                m_trajet[i]->setDuree( (60 + (((60*4)*d))/100));
            }
/// BUS ?????



            if ( m_trajet[i]->gettypetrajet() == "BUS"  )
            {
                if ( (m_trajet[i]->getnomtrajet() == "navette2000-1600")|| m_trajet[i]->getnomtrajet() == "navette1600-2000")
                {m_trajet[i]->setDuree(40*60);
                }



                else if ( (m_trajet[i]->getnomtrajet() == "navette1600-1800")|| m_trajet[i]->getnomtrajet() == "navette1800-1600")
                {
                    m_trajet[i]->setDuree(30*60);
                }
            }

        }
        /*int d; //distance entre 2 points
        for (int i =0; i< m_trajet.size(); i++)
        {
            if(m_trajet[i]->getp1()->getaltitude()>m_trajet[i]->getp2()->getaltitude())
            {
                d = m_trajet[i]->getp1()->getaltitude() -
                    m_trajet[i]->getp2()->getaltitude(); // calcul distance entre les deux points}
            }
            else
            {
                d = m_trajet[i]->getp2()->getaltitude()-m_trajet[i]->getp1()->getaltitude(); // calcul distance entre les deux points}
            }

            //pour la descente

            if ( m_trajet[i]->gettypetrajet() == "V")   /// si la piste est verte
            {
                m_trajet[i]->setDuree(((60*5)*d)/100);     /// donne le temps en SECONDEs
            }



            if ( m_trajet[i]->gettypetrajet() == "R" )  /// si la piste est rouge
            {
                m_trajet[i]->setDuree(((60*3)*d)/100);
            }



            if ( m_trajet[i]->gettypetrajet() == "B" ) /// si la piste est bleue
            {
                m_trajet[i]->setDuree(((60*4)*d)/100);
            }



            if ( m_trajet[i]->gettypetrajet() == "N" ) /// si la piste est noire
            {
                m_trajet[i]->setDuree(((60*2)*d)/100);
            }



            if ( m_trajet[i]->gettypetrajet() == "KL" )
            {
                m_trajet[i]->setDuree((10*d)/100);// le temps est deja en secondes
            }




            if (m_trajet[i]->gettypetrajet() == "SURF" )
            {
                m_trajet[i]->setDuree(((60*10)*d)/100);
            }
// pour les remontees



            if (m_trajet[i]->gettypetrajet() == "TPH" )
            {
                m_trajet[i]->setDuree( (4*60 + (((60*2)*d))/100));
            }



            if ( m_trajet[i]->gettypetrajet() == "TC" )
            {
                m_trajet[i]->setDuree((2*60 + (((60*3)*d))/100));
            }



            if (m_trajet[i]->gettypetrajet() == "TSD" )
            {
                m_trajet[i]->setDuree((60 +( ((60*3)*d))/100));
            }
            if ( m_trajet[i]->gettypetrajet() == "TS" )
            {



                m_trajet[i]->setDuree((60 + (((60*4)*d))/100));
            }
            if ( m_trajet[i]->gettypetrajet() == "TK" )
            {
                m_trajet[i]->setDuree( (60 + (((60*4)*d))/100));
            }

            if ( m_trajet[i]->gettypetrajet() == "BUS"  )
            {
                if ( (m_trajet[i]->getnomtrajet() == "navette2000-1600")|| m_trajet[i]->getnomtrajet() == "navette1600-2000")
                {
                    m_trajet[i]->setDuree(40*60);
                }



                else if ( (m_trajet[i]->getnomtrajet() == "navette1600-1800")|| m_trajet[i]->getnomtrajet() == "navette1800-1600")
                {
                    m_trajet[i]->setDuree(30*60);
                }
            }

        }*/


    }
    void fichierecriture(std::string fichier)/// fichier d'écriture pour les durées

    {
        std::string const nomFichier(fichier);

        std::ofstream monFlux(nomFichier.c_str());//Déclaration d'un flux permettant d'écrire dans un fichier
        //std::ofstream monFlux(nomFichier.c_str(), std::ios::app); // si il existe deja ? peut on faire ca pr rajouter les durées
        if(monFlux)  //On teste si tout est OK
        {  monFlux<<ordre<<std::endl;
            //Tout est OK, on peut utiliser le fichier
            for (int i = 0; i < ordre; i++) {




                monFlux << m_point[i]->getnumeropoint() << "\t" << m_point[i]->getnomlieu() << "\t" << m_point[i]->getaltitude() << std::endl;



            }
            monFlux<<taille<<std::endl;
            for (int i = 0; i < taille; i++) {



                monFlux << m_trajet[i]->getnumerotrajet() << "\t" << m_trajet[i]->getnomtrajet() << "\t" << m_trajet[i]->gettypetrajet() << "\t" << m_trajet[i]->getp1()->getnumeropoint()
                        << "\t" << m_trajet[i]->getp2()->getnumeropoint() << "\t" << m_trajet[i]->getduree() << std::endl;




            }
        }
        else
        {
            std::cout << "ERREUR: Impossible d'ouvrir le fichier." <<std:: endl;
        }
        monFlux.close();
        /*
        std::string const nomFichier(fichier);



        std::ofstream monFlux(nomFichier.c_str());//Déclaration d'un flux permettant d'écrire dans un fichier
        //std::ofstream monFlux(nomFichier.c_str(), std::ios::app); // si il existe deja ? peut on faire ca pr rajouter les durées
        if(monFlux)  //On teste si tout est OK
        {
            for (int i = 0; i < ordre; i++)
            {
                monFlux << m_point[i]->getnumeropoint() << "\t" << m_point[i]->getnomlieu() << "\t" << m_point[i]->getaltitude() << std::endl;
            }

            for (int i = 0; i < taille; i++)
            {

                monFlux << m_trajet[i]->getnumerotrajet() << "\t" << m_trajet[i]->getnomtrajet() << "\t" << m_trajet[i]->gettypetrajet() << "\t" << m_trajet[i]->getp1()->getnumeropoint()
                        << "\t" << m_trajet[i]->getp2()->getnumeropoint() << "\t" << m_trajet[i]->getduree() << std::endl;

if(m_point[m_trajet[i]->getp1()->getnumeropoint()-1]->verification(m_trajet[i]->getp2()->getnumeropoint())==false)
{
            m_point[m_trajet[i]->getp1()->getnumeropoint()-1]->ajouterSucc(m_point[m_trajet[i]->getp2()->getnumeropoint()-1],m_trajet[i]->getduree());
}

            }
        }
        else
        {
            std::cout << "ERREUR: Impossible d'ouvrir le fichier." <<std:: endl;
        }
        monFlux.close();*/
    }

    void afficherEntrantSortant()
    {
        int saisie;
        std::cout<<" saisir un point pour avoir les trajets sortants et entrants "<<std::endl;
        std::cin>>saisie;
        std::cout<<" les trajets sortants sont : ";
        for(auto const elem:m_trajet)
        {
            if(elem->getdepart()==saisie)
            {
                std::cout<<elem->getnomtrajet()<<" ";
            }
        }
        std::cout<<std::endl;
        std::cout<<" les trajets entrants sont : ";
        for(auto const elem:m_trajet)
        {
            if(elem->getarrivee()==saisie)
            {
                std::cout<<elem->getnomtrajet()<<" ";
            }
        }
        std::cout<<std::endl;
    }




    void afficheTrajet()
    {
        std::string trajet;
        std::cout<<" saisir le nom d'un trajet"<<std::endl;
        std::cin>>trajet;
        for(auto const elem:m_trajet)
        {
            if(elem->getnomtrajet()==trajet)
            {
                std::cout<<" le trajet est de type "<<elem->gettypetrajet()<<" ,le point de depart est "<<elem->getdepart()<<" , l'arrivée est "<<elem->getarrivee()<<" avec une duree :"<<elem->getduree()<<" secondes "<<std::endl;
            }
        }
    }
    std::vector<int> djikstra(int init,int fin)
    {  if(init==29)
       {
        std::cout<<"pas de chemin partant de 29"<<std::endl;
       }

        std::vector<int>marquage(ordre,0);
        std::vector<int>pred(ordre,-1);///pour avoir le plus court chemin
        std::vector<Point*> djik;///ou on stocke les sommets a parcourir apres (les adjacents du sommet etudie)
        marquage[init-1 ]=1;/// premier sommet visite est le sommet initial
        m_point[init-1]->setdistance(0);///le sommet init a une distance 0 de lui même
        Point*tmp=m_point[init-1];///sommet qu'on "etudie" (ses adjacents, leur poid)
        while(marquage[fin-1]!=1)///tant qu'on est pas arrivé au sommet final
        {
            /// on regarde la distance init-voisins
            for(auto elem:tmp->getAdj())
            {
                if(marquage[elem.first->getnumeropoint()-1]!=1) /// on verifie si les adjacents sont visités
                {
                    djik.push_back(elem.first);///on stocke le sommet adjacent dans le vecteur pour l'etudier apres

                    if(elem.first->getdistance()==10000)/// si pas encore de distance
                    {
                        elem.first->setdistance(elem.second+ tmp->getdistance());///on attribut a chaque sommet voisin sa distance au sommet initial
                        pred[elem.first->getnumeropoint()-1




                        ]=tmp->getnumeropoint();///on leur donne leur predecesseur
                    }
                    else///s'il a deja une distance
                    {
                        if( elem.first->getdistance() > elem.second + tmp->getdistance())///on verifie si c la plus petite
                        {
                            elem.first->setdistance(elem.second+  tmp->getdistance());///si c pas le cas on la change
                            pred[elem.first->getnumeropoint()-1]=tmp->getnumeropoint();///et on lui "refresh son predecesseur"
                        }
                    }
                }
            }

            ///trie avec sort le djik par rapport au distance du+ petit au+grand
            std::sort(djik.begin(),djik.end(),[](Point* p1,Point* p2) //tri du tableau
            {
                return p1->getdistance() < p2->getdistance();
            });

            tmp=djik[0];///pour enlever le tmp du vecteur
            marquage[tmp->getnumeropoint()-1]=1;
            std::vector<Point*> nouveau = djik;
            djik.clear();
            for(int i=0; i<nouveau.size(); i++)
            {
                if(nouveau[i]->getnumeropoint() != tmp->getnumeropoint())
                {
                    djik.push_back(nouveau[i]);
                }
            }
        }
        std::cout<<"La distance totale est de : "<<tmp->getdistance();
        return pred;
    }

    void affichageDjik (std::vector<int> pred, int init, int fin)
    {
        std::cout<<std::endl;
        std::cout<<"affichage du chemin le plus court entre le sommet "<<init<<"et le sommet "<<fin<<" : "<<std::endl;
        int predecesseur = fin;
        std::cout<<fin<<"<--";
        while(predecesseur != init)///tant qu'on arrive pas au sommet uinitiale on remonte la chaine de predecesseur
        {
            std::cout<<pred[predecesseur-1];
            if(pred[predecesseur-1]!=init)
            {
                std::cout<<"<--";
            }

            predecesseur = pred[predecesseur-1];
        }
    }

    void resetD()
    {
        for(int i=0; i<37; i++)
        {
            m_point[i]->reset();
        }
    }

};

#endif // GRAPHESKI_H
