#ifndef ARC_H
#define ARC_H

#include <iostream>
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include "Point.h"
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
#endif // ARC_H
