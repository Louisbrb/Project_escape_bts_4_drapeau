#ifndef application_compteur_balle_H
#define application_compteur_balle_H

/**
 * \file application_compteur_balle.h
 *
 * \author Angibaud
 */

#include "application.h"
#include <QString>

const int WIDTH  = 320;
const int HEIGHT = 240;

namespace Robot
{
    /**
      * \brief Classe décrivant une application de base.
      * \author Angibaud
      */
    class application_compteur_balle : public application
    {
        public:
            application_compteur_balle();

            void run();

        private:
            void supprimerPixel(int i,int j);
            QString parcourircouleur(QString couleur,int j);
            void init();
            void mode_compteur_balle();
            void affiche_nombre_de_pixels_bleus();
            void affiche_nombre_de_balles_bleues();
            void traitement_camera();


        private:
            QString m_couleur_actuelle = "debut";
            QString m_description_drapeau = "";
            int m_tab_pixel_drapeau[ HEIGHT ][ WIDTH ];
            bool m_tab_pixel_vu[ HEIGHT ][ WIDTH ];
    }; // end class application_compteur_balle
} // end namespace Robot

#endif // application_compteur_balle_H
