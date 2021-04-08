#ifndef POINT_H
#define POINT_H

#include <iostream>
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
class Point
{
private:
    int m_numeropoint;
    std::string m_nomlieu;
    int m_altitude;
    int m_p; ///pour le constructeur
    int distance=10000; ///distance a l'infini pour le di
    std::vector<std::pair<Point*,int>> m_voisins;///listes d'adjacences
public:
  int getdistance()
    {
        return distance;
    }
     void setdistance(int d)
    {
        distance=d;
    }

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
                void reset()
                {
                    distance=10000;
                }
                bool verification(int num)
                {
                    for(int i=0;i<m_voisins.size();i++)
                    {
                        if(m_voisins[i].first->getnumeropoint()==num);
                        {

                            return true;
                        }
                    }
                    return false;
                }

};

#endif // POINT_H
