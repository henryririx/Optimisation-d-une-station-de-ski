#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED
class Point
{
    ///
private:
    int m_numeropoint;
    std::string m_nomlieu;
    int m_altitude;
    int m_p; ///pour le constructeur

    std::vector<std::pair<Point*,int>> m_voisins;///listes d'adjacences
public:


    Point(int p)
    {
        m_p = p;
    }
    ~Point()
    {

    }
    std::string  getnomlieu() const
    {
        return m_nomlieu;
    }
    int getaltitude() const
    {
        return m_altitude;
    }

    int getnumeropoint() const
    {
        return m_numeropoint;
    }

    void setnomlieu(std::string nom)
    {
        m_nomlieu=nom;
    }

    void setaltitude(int alti)
    {
        m_altitude=alti;
    }

    void setnumeropoint(int num)
    {
        m_numeropoint=num;
    }
    std::vector <std::pair<Point*,int>> getAdj()const
    {
        return m_voisins;
    }

    void afficher() const
    {

        for(auto const elem:m_voisins)
        {
            std::cout<<elem.first->getnumeropoint()<<" avec duree:";
            std::cout<<elem.second<<" ,";
        }

    }
    void ajouterSucc(Point* s, int pond){
        if(s!= nullptr)
        {
            std::pair<Point*,int>succ;
            succ.first=s;
            succ.second=pond;
            m_voisins.push_back(succ);
        }

    }

};
class Point;
class Arc
{
private:///rajouter le temps de trajet (calcul entre altitude et données du projets)
    Point*m_p1;///a partir de l altitude des 2 points on pourra calculer le temps de trajets
    Point*m_p2;
    int m_numerotrajet;
    std::string m_nomtrajet;
    std::string m_typetrajet;
    int m_depart;
    int m_arrive;
    int m_duree;
    int m_arc; // constructeur

public:


    Arc(int arc)
    {
        m_arc = arc;
    }

    int getnumerotrajet() const
    {
        return m_numerotrajet;
    }

    int getdepart() const
    {
        return m_depart;
    }

    int getarrivee() const
    {
        return m_arrive;
    }

    std::string gettypetrajet() const
    {
        return m_typetrajet;
    }

    std::string getnomtrajet() const
    {
        return m_nomtrajet;
    }

    Point* getp1() const
    {
        return m_p1;
    }

    Point* getp2() const
    {
        return m_p2;
    }

    void setnumerotrajet(int num)
    {
        m_numerotrajet=num;
    }

    void setdepart(int depart)
    {
        m_depart=depart;
    }

    void setarrivee(int arrivee)
    {
        m_arrive=arrivee;
    }

    void settypetrajet(std::string type)
    {
        m_typetrajet =type;
    }

    void setnomtrajet(std::string nom)
    {
        m_nomtrajet=nom;
    }

    void setp1(Point *P1)
    {
        m_p1=P1;
    }

    void setp2(Point *P2)
    {
        m_p2=P2;
    }

    int getduree() const
    {
        return m_duree;
    }

    void setDuree(int duree)
    {
        m_duree=duree;
    }

};
class Grapheski
{private:

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
    Grapheski(std::string fichier) {
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

    }
    void afficherGraphe()const{
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
    {   std::string trajet;
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
    void afficherPoint()
    {
        for(auto const elem:m_point)
        {
            std::cout<<"le point "<<elem->getnumeropoint()<<" a pour adjacent ";
            elem->afficher();
            std::cout<<std::endl;
        }
    }

};

int main() {
    Grapheski g("duree.txt");
    std::cout<<"hello word";
    //g.afficherGraphe();
   // g.tempstrajet();
    //g.afficherPoint();
    //g.fichierecriture("duree.txt");
    //g.afficheTrajet();///4.3 affiche un trajet saisie, le type et la duréee, depart et arrivéé
    //g.afficherEntrantSortant();///4.3 pour un point affiche les trajets partants et entrants

    return 0;
}

#endif // TEST_H_INCLUDED
