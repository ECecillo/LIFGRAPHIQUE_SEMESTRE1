
#ifndef VIEWER_ETUDIANT_H
#define VIEWER_ETUDIANT_H

#include "Viewer.h"



class ViewerEtudiant : public Viewer
{
public:
    ViewerEtudiant();

    int init();
    int render();
    int update( const float time, const float delta );

protected:
    /* -----------------------------------------
     Pour creer un nouvel objet vous devez :

     1. declarer ici dans le fichier Viewer_etudiant.h
     le Mesh,
     la texture si besoin,
     une fonction 'init_votreObjet'
     une fonction 'draw_votreObjet(const Transform& T)'

     --- Rq : regarder comment cela est effectue dans le fichier Viewer.h


     2. Appeler la fonction 'init_votreObjet' dans la fonction 'init' du Viewer_etudiant.cpp
     --- Rq : regarder comment cela est effectue dans le fichier Viewer.cpp


     3. Appeler la fonction 'draw_votreObjet' dans la fonction 'render' du Viewer_etudiant.cpp
     --- Rq : regarder comment cela est effectue dans le fichier Viewer.cpp

      ----------------------------------------- */


    /// Declaration des Mesh
    Mesh m_disque;
    Mesh m_disque2;

    Mesh m_Cube;

    Mesh m_cylindre;

    Mesh m_cone;

    Mesh m_sphere;
    /// Declaration des Textures


    /// Declaration des fonction de creation de Mesh du type init_votreObjet()
    void init_disque(int x, int y, int z, Point normale, int nb_mesh, int around, Mesh& m_Disque);
    void init_Cube(int x, int y, int z);
    void init_cylindre(int x, int y, int z, Point normale, int nb_mesh, Mesh& cy);
    void init_cone (int x, int y, int z, Point normale, int nb_mesh, Mesh& co);
    void init_sphere();

    /// Declaration des fonctions draw_votreObjet(const Transform& T)
    void draw_disque(const Transform& T);
    void draw_Cube(const Transform& T, unsigned int tex);
    void draw_Cube(const Transform& T);
    void draw_cylindre(const Transform& T);
};



#endif
