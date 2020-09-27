
#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>

#include "draw.h"        // pour dessiner du point de vue d'une camera
#include "Viewer_etudiant.h"

using namespace std;

/*
 * Exemple de definition de fonction permettant la creation du Mesh de votre Objet.
 */
//void ViewerEtudiant::init_votreObjet()
//{
//}

// Initialise un disque
// int x : coo. en X qu'il faut ajouter.
// int y : coo. en Y qu'il faut ajouter.
// int z : coordo en Z qu'il faut ajouter.
// Point normale : Définit la normale aux coo. (x,y,z).
// Mesh m_Disque : Nom du disque pour la génération du Mesh.
void ViewerEtudiant::init_disque(int x, int y, int z, Point normale, int nb_mesh, int around, Mesh& m_Disque) {

    ///Variation de l'angle de 0 à 2pi.
    const int div = nb_mesh; /// Plus on augmente plus on aura de maillage.
    float alpha;
    float step = 2.0 * M_PI / (div);

    /// Choix primitive OpenGL
    m_Disque = Mesh(GL_TRIANGLE_FAN);

    m_Disque.normal(Vector (normale)); /// Normale à la surface
    m_Disque.vertex(Point (0 + x,0 + y,0 + z)); /// Point du centre du disque

    /// Variation de l'angle de 0 à 2PI
    for (int i = 0; i <= div; i++) {

        alpha = i * step;
        m_Disque.normal(Vector (0,1,0));
        //m_Disque.color(0,0,0);
        m_Disque.vertex(Point(cos(alpha),0 + around,sin(alpha)));
    }

    m_Disque.restart_strip(); /// Réinitialise les coordo pour pouvoir redefinir un mesh.s

}

void ViewerEtudiant::init_Cube(int x, int y, int z)
{
    //on définit le type de triangles
    m_Cube = Mesh(GL_TRIANGLE_STRIP);

    //Ici on définit les sommet du cube
    vec3 s[8];
    s[0] = vec3(0 + x, 0 + y, 0 + z);//
    s[1] = vec3(0 + x, 1 + y, 0 + z);//
    s[2] = vec3(1 + x, 1 + y, 0 + z);// 6 -- 5
    s[3] = vec3(1 + x, 0 + y, 0 + z);// /   /|
    s[4] = vec3(1 + x, 0 + y, 1 + z);//1- -2 |
    s[5] = vec3(1 + x, 1 + y, 1 + z);//|   | |
    s[6] = vec3(0 + x, 1 + y, 1 + z);//|   | 4
    s[7] = vec3(0 + x, 0 + y, 1 + z);//0- -3/

    //La on definit un tableau qui va stocker les faces
    vec3 Vertex[6][4];

    Vertex[0][0] = s[1]; // AVANT
    Vertex[0][1] = s[2];
    Vertex[0][2] = s[0];
    Vertex[0][3] = s[3];

    Vertex[1][0] = s[6]; // ARRIERE
    Vertex[1][1] = s[7];
    Vertex[1][2] = s[5];
    Vertex[1][3] = s[4];

    Vertex[2][0] = s[7]; // DESSOUS
    Vertex[2][1] = s[0];
    Vertex[2][2] = s[4];
    Vertex[2][3] = s[3];

    Vertex[3][0] = s[6]; // DESSUS
    Vertex[3][1] = s[5];
    Vertex[3][2] = s[1];
    Vertex[3][3] = s[2];

    Vertex[4][0] = s[6]; // GAUCHE
    Vertex[4][1] = s[1];
    Vertex[4][2] = s[7];
    Vertex[4][3] = s[0];

    Vertex[5][0] = s[5]; // DROITE
    Vertex[5][1] = s[4];
    Vertex[5][2] = s[2];
    Vertex[5][3] = s[3];

    //La on va remplir la meshe avec ses boucles (i  = face, j = sommet)
for(int i = 0; i < 6; i++)
    {

            for(int j = 0; j < 4; j++)
            {
                //On intervertit les sommets pour la texture suivant s'ils sont afficher a la cam ou pas
                int n = j;
                if(i == 1 || i == 2 || i == 5)
                {
                     if(j == 0)
                    {
                        n = 1;
                    }
                    else if (j == 1)
                    {
                        n = 3;
                    }
                    else if (j == 2)
                    {
                        n = 0;
                    }
                    else
                    {
                        n = 2;
                    }
                }
                //on remplit la couleur
                m_Cube.color(1, 0, 0);

                //on remplit le sommet
                m_Cube.normal(Vertex[i][j]);
                m_Cube.vertex(Vertex[i][j]);
            }
            //on recommence le strippage pour eviter les interpolation digoulasse
            m_Cube.restart_strip();


    }

}

// Initialise un cylindre
// int x : coo. en X qu'il faut ajouter.
// int y : coo. en Y qu'il faut ajouter.
// int z : coordo en Z qu'il faut ajouter.
// Point normale : Définit la normale aux coo. (x,y,z).
// Mesh m_Disque : Nom du disque pour la génération du Mesh.
void ViewerEtudiant::init_cylindre(int x, int y, int z, Point normale, int nb_mesh, Mesh& cy) {

    ///Variation de l'angle de 0 à 2pi.
    const int div = nb_mesh; /// Plus on augmente plus on aura de maillage.
    float alpha;
    float step = 2.0 * M_PI / (div);

    /// Choix primitive OpenGL
    cy = Mesh(GL_TRIANGLE_STRIP);

    for (int i = 0; i<=div;i++)
    {
        /// Variation de l'angle de 0 à 2PI
        alpha = i * step;
        m_cylindre.normal( Vector(cos(alpha), 0, sin(alpha)));
        m_cylindre.vertex( Point(cos(alpha) + x, -1 + y, sin(alpha) + z));

        /// On met un point en haut et un point en bas et on fais varié les deux.

        m_cylindre.normal( Vector(cos(alpha), 0, sin(alpha)));
        m_cylindre.vertex( Point(cos(alpha) + x, 1 + y, sin(alpha) + z));
    }
    init_disque(x,y,z,normale,nb_mesh,0,m_disque);
}

// Initialise un disque
// int x : coo. en X qu'il faut ajouter.
// int y : coo. en Y qu'il faut ajouter.
// int z : coordo en Z qu'il faut ajouter.
// Point normale : Définit la normale aux coo. (x,y,z).
// Mesh m_Disque : Nom du disque pour la génération du Mesh.
 void ViewerEtudiant::init_cone (int x, int y, int z, Point normale, int nb_mesh, Mesh& co) {
    ///Variation de l'angle de 0 à 2PI
    const int div = nb_mesh; /// Plus on augmente plus on aura de maillage.
    float alpha;
    float step = 2.0 * M_PI / (div);

    /// Choix primitive OpenGL
    co = Mesh(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= div; i++)
    {
        alpha = i * step; /// Angle varie de 0 à 2PI

        co.normal(Vector (cos(alpha)/ sqrtf(2.f),
                    1.f/sqrtf(2.f),
                sin(alpha)/sqrtf(2.f) ));

        co.vertex(Point(cos(alpha), 0, sin(alpha))); /// Point du disque du bas.

        co.normal(Vector (cos(alpha)/ sqrtf(2.f),
                    1.f/sqrtf(2.f),
                sin(alpha)/sqrtf(2.f) ));

        co.vertex(Point(0, 1, 0)); /// Sommet, et on alterne entre les points du bas et du sommet.
    }

    //init_disque(0,0,0,(0,0,0),25, 0, m_disque2);

 }


void ViewerEtudiant::init_sphere()
{
    /// Variation des angles alpha et beta de 0 à 2PI
    const int divBeta = 100;
    ;
    const int divAlpha = divBeta/2;
    int i,j;

    float beta, alpha, alpha2;

    /// Choix de la primitive OpenGL
    m_sphere = Mesh(GL_TRIANGLE_STRIP);

    /// Variation des angles alpha et beta
    for (int i = 0; i<divAlpha ; i++) /// Variations de l'angle Alpha.
    {
        /// On a 1 rayon et 1 positionement, on considère 2 cercles car on va utiliser des gl triangles strip pour les relier entre eux.
        alpha = -0.5f * M_PI + float(i) * M_PI / divAlpha; /// On fait varié l'angle de -PI/2 à PI/2
        alpha2 = -0.5f * M_PI + float(i+1) * M_PI / divAlpha;

        for (int j = 0; j <= divBeta; j++) /// Variation de l'angle Beta.
        {
            /// On dessine un cercle.
            beta = float(j) * 2.f * M_PI / (divBeta); /// On va de 0 à 2PI

            /// On définit un cercle avec l'angle alpha (cercle du bas).
            m_sphere.normal(Vector(cos(alpha)*cos(beta), sin(alpha), cos(alpha)* sin(beta)));
            m_sphere.vertex(Point(cos(alpha)*cos(beta), sin(alpha), cos(alpha)* sin(beta)));

            /// On définit un autre cercle avec l'angle alpha2 (cercle du haut) et on va mettre des triangle entre les deux pour lier les cercles et avoir une sphere compact.
            m_sphere.normal(Vector(cos(alpha2)*cos(beta), sin(alpha2), cos(alpha2)* sin(beta)));
            m_sphere.vertex(Point(cos(alpha2)*cos(beta), sin(alpha2), cos(alpha2)* sin(beta)));

        }
        m_sphere.restart_strip(); /// Demande un nouveau strip.
    }
}



int ViewerEtudiant::init()
{
    Viewer::init();

    m_camera.lookat( Point(0,0,0), 150 );


    /// Appel des fonctions init_votreObjet pour creer les Mesh
    init_axe();
    //init_disque(0,3,0,(0,1,0),25, 1, m_disque);
    //init_disque(0,3,0,(0,0,0),25, 1, m_disque2);


    //init_cone(0,1,0,(0,1,0),100, m_cone);
    //init_Cube(0,0,0);
    init_cylindre(0,0,0, (0,0,0), 50, m_cylindre);

    //init_sphere();
	/// Chargement des textures


    return 0;
}



/*
 * Exemple de definition de fonction permettant l affichage
 * de 'votreObjet' subissant la Transform T
 */
//void ViewerEtudiant::draw_votreObjet(const Transform& T)
//{
// gl.texture(....);
// gl.model( T );
// gl.draw( m_votreObjet );
//}

//void ViewerEtudiant::draw_disque(const Transform& T)
//{
// gl.texture(....);
// gl.model( T );
// gl.draw(m_disque);
//}


void ViewerEtudiant::draw_cylindre(const Transform& T)
{
    /// Corps du cylindre
    //  gl.texture(....);
    gl.model( T );
    gl.draw( m_cylindre);

    /// Disque du haut
    Transform Tch = T * Translation(0,1,0)
                    * Rotation(Vector(1,0,0), 180) ;
    gl.model(Tch);
    gl.draw(m_disque);

    /// Disque du haut
    Transform Tcb = T * Translation(0,-1,0);
    gl.model(Tcb);
    gl.draw(m_disque);
}

/*
 * Fonction dans laquelle les appels pour les affichages sont effectues.
 */
int ViewerEtudiant::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    manageCameraLight();

    gl.camera(m_camera);


    /// Appel de la fonction render() de la class Viewer
    /// pour que vous voyez apparaitre un premier objet
    /// a supprimer ensuite
    Viewer::render();

    /// Transformation géométrique appliquée au Mesh

        // On spécifie la transformation géométrique avant de faire l'affichage !
    Transform T = Translation(2,0,0);
    /// Cas où pas de transformation géométrique
    Transform T_init = Identity(); // Matrice identité.

    /// Appel des fonctions du type 'draw_votreObjet'

    //gl.draw(m_cone);
//    gl.draw(m_disque);
    //gl.draw(m_disque2);
    //gl.draw(m_cylindre);
    draw_cylindre(T);
//    gl.draw(m_Cube);
//    gl.draw(m_sphere);
	return 1;

}


/*
 * Fonction dans laquelle les mises a jours sont effectuees.
 */
int ViewerEtudiant::update( const float time, const float delta )
{
    // time est le temps ecoule depuis le demarrage de l'application, en millisecondes,
    // delta est le temps ecoule depuis l'affichage de la derniere image / le dernier appel a draw(), en millisecondes.



    return 0;
}


/*
 * Constructeur.
 */

ViewerEtudiant::ViewerEtudiant() : Viewer()
{
}


/*
 * Programme principal.
 */
int main( int argc, char **argv )
{
    ViewerEtudiant v;
    v.run();
    return 0;
}
