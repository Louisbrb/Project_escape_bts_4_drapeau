/**
 * \file application_compteur_balle.cpp
 * \brief Implémentation de la classe application_compteur_balle.
 * \author Angibaud
 */

#include "application_compteur_balle.h"

#include "StatusCheck.h"
#include "VisionMode.h"
#include "mjpg_streamer.h"
#include "Action.h"
#include "define.h"
#include "Speaker.h"
#include "string"
/*************************************************************************************/
/**
  * \brief Constructeur.
  */
Robot::application_compteur_balle::application_compteur_balle()
{
}
   int compteur = 0;
/*************************************************************************************/
/**
  * \brief Lancement de la démo.
  */
void Robot::application_compteur_balle::run()
{

    QString m_couleur_actuelle = "debut";
    init();
    // attente
    while(Action::GetInstance()->IsRunning()) usleep(8*1000);
    
    if ( Speaker::is_ready() )
        //Speaker::GetInstance()->Speak("Compteur de balles. Sélectionner le mode Interactive Mochionne Mode.","fr");
        Speaker::GetInstance()->Speak("Montrer drapeau.","fr");


    
    while(1)
    {
        StatusCheck::Check(m_ressources.get_cm730());
        
        if(StatusCheck::m_is_started == 0)
            continue;
        
        switch(StatusCheck::m_cur_mode)
        {
        case READY:
            break;
            // on lance le mode horloge parlante quelque soit le mode lancé sous condition d'être prêt à parler
        case SOCCER:
        case MOTION:
        case VISION:
            // if ( Speaker::is_ready() )
            mode_compteur_balle();
            break;
        }
    }
} // end run()

/*************************************************************************************/
/**
  * \brief Lancement de l'application.
  */
void Robot::application_compteur_balle::init()
{
    Action::GetInstance()->m_Joint.SetEnableBody(true, true);
    MotionManager::GetInstance()->SetEnable(true);
    
    m_ressources.get_cm730().WriteByte(CM730::P_LED_PANNEL, 0x01|0x02|0x04, NULL);
    
    LinuxActionScript::PlayMP3("/darwin/Data/mp3/Demonstration ready mode.mp3");
    Action::GetInstance()->Start(15);
    
    while(Action::GetInstance()->IsRunning())
        usleep(8*1000);
}

/*************************************************************************************/
/**
  * \brief Mode Compter_balle.
  */
void Robot::application_compteur_balle::mode_compteur_balle()
{
    traitement_camera();

    //    affiche_nombre_de_pixels_bleus();
    //    affiche_nombre_de_balles_bleues();
}

/*************************************************************************************/
/**
  * \brief Affiche le nombre de pixels bleues.
  */
//void Robot::application_compteur_balle::affiche_nombre_de_pixels_bleus()
//{
//    int nb_pixels_bleu = 0;
//    for ( int ligne = 0; ligne != HEIGHT; ++ligne )
//        for ( int colonne = 0; colonne != WIDTH; ++colonne )
//            if ( m_tab_pixel_bleu[ligne][colonne] )
//                ++nb_pixels_bleu;
//
//    std::cout << "Il y a " << nb_pixels_bleu << " pixels bleus." << std::endl;
//}

/*************************************************************************************/
/**
  * \brief Affiche le nombre de balles bleues.
  */
//void Robot::application_compteur_balle::affiche_nombre_de_balles_bleues()
//{
//    int nb_balles = 0;
//
//    // A FAIRE
//    // ...
//
//    std::cout << "Il y a " << nb_balles << " balles bleues" << std::endl;
//}

/*************************************************************************************/
/**
  * \brief Détection des éléments via la caméra.
  */
void Robot::application_compteur_balle::traitement_camera()
{
    LinuxCamera::GetInstance()->CaptureFrame();
    memcpy(m_ressources.get_rgb_output()->m_ImageData, LinuxCamera::GetInstance()->fbuffer->m_RGBFrame->m_ImageData,
           LinuxCamera::GetInstance()->fbuffer->m_RGBFrame->m_ImageSize);
    Point2D red_pos, yellow_pos, blue_pos, green_pos,purple_pos,black_pos,white_pos;

    if( StatusCheck::m_cur_mode == READY || StatusCheck::m_cur_mode == VISION || StatusCheck::m_cur_mode == SOCCER || StatusCheck::m_cur_mode == MOTION )
    {
        purple_pos = m_ressources.get_purple_finder()->GetPosition(LinuxCamera::GetInstance()->fbuffer->m_HSVFrame);
        red_pos = m_ressources.get_red_finder()->GetPosition(LinuxCamera::GetInstance()->fbuffer->m_HSVFrame);
        yellow_pos = m_ressources.get_yellow_finder()->GetPosition(LinuxCamera::GetInstance()->fbuffer->m_HSVFrame);
        blue_pos = m_ressources.get_blue_finder()->GetPosition(LinuxCamera::GetInstance()->fbuffer->m_HSVFrame);
        green_pos = m_ressources.get_green_finder()->GetPosition(LinuxCamera::GetInstance()->fbuffer->m_HSVFrame);
        white_pos = m_ressources.get_white_finder()->GetPosition(LinuxCamera::GetInstance()->fbuffer->m_HSVFrame);
        black_pos = m_ressources.get_black_finder()->GetPosition(LinuxCamera::GetInstance()->fbuffer->m_HSVFrame);
        // modification de la sortie vidéo pour un meilleur contrôle de la détection
        unsigned char r, g, b;
        int nb_pixel_bleu = 0;
        int nb_pixel_jaune = 0;
        int nb_pixel_violet = 0;


        for(int i = 0; i < m_ressources.get_rgb_output()->m_NumberOfPixels; i++)
        {


            r = 0; g = 0; b = 0;

            int ligne = i / WIDTH;
            int colonne = i % WIDTH;
            m_tab_pixel_drapeau[ ligne ][ colonne ] = 0; // par défaut, le pixel n'est pas violet

            // violet
            if(m_ressources.get_purple_finder()->m_result->m_ImageData[i] == 1)
            {
                r = 204;
                g = 0;
                b = 255;
                m_tab_pixel_drapeau[ ligne ][ colonne ] = 1;
                nb_pixel_violet = nb_pixel_violet+1;
            }

            // rouge
            if(m_ressources.get_red_finder()->m_result->m_ImageData[i] == 1)
            {
                r = 255;
                g = 0;
                b = 0;
            }

            // jaune
            if(m_ressources.get_yellow_finder()->m_result->m_ImageData[i] == 1)
            {
                r = 255;
                g = 255;
                b = 0;
                nb_pixel_jaune = nb_pixel_jaune+1;
            }

            // blue
            if(m_ressources.get_blue_finder()->m_result->m_ImageData[i] == 1)
            {
                r = 0;
                g = 0;
                b = 255;
                nb_pixel_bleu = nb_pixel_bleu+1;
            }
            if(nb_pixel_bleu > 0 && nb_pixel_jaune > 0 && nb_pixel_violet > 0)
            {
                if(compteur == 0)
                {
                    std::cout << "laos" << std::endl;
                    if ( Speaker::is_ready() )
                        Speaker::GetInstance()->Speak("laos","fr");
                }


            }
            compteur ++;
            if(compteur == 1000)
            {
                compteur = 0;
            }

            if(r > 0 || g > 0 || b > 0)
            {
                m_ressources.get_rgb_output()->m_ImageData[i * m_ressources.get_rgb_output()->m_PixelSize + 0] = r;
                m_ressources.get_rgb_output()->m_ImageData[i * m_ressources.get_rgb_output()->m_PixelSize + 1] = g;
                m_ressources.get_rgb_output()->m_ImageData[i * m_ressources.get_rgb_output()->m_PixelSize + 2] = b;
                m_ressources.get_streamer()->send_image(m_ressources.get_rgb_output());
            }
        }

        supprimerPixel(0,0);
        r = 0; g = 0; b = 0;

        for(int j = 0; j < m_ressources.get_rgb_output()->m_NumberOfPixels; j++)
        {
            int ligne = j / WIDTH;
            int colonne = j % WIDTH;
            if (m_tab_pixel_drapeau[ligne][colonne] == 0)
            {
                if(m_ressources.get_white_finder()->m_result->m_ImageData[j] == 1)
                {
                    r = 255;
                    g = 255;
                    b = 255;
                    if(m_couleur_actuelle != "white" && m_couleur_actuelle != "debut")
                    {
                        //parcourir_couleur(1, j);
                        m_couleur_actuelle = "white";

                    }
                    else if (m_couleur_actuelle == "debut")
                    {
                        m_couleur_actuelle = "white";
                    }
                }
                if(m_ressources.get_blue_finder()->m_result->m_ImageData[j] == 1)
                {
                    r = 0;
                    g = 72;
                    b = 206;
                    if(m_couleur_actuelle != "blue" && m_couleur_actuelle != "debut")
                    {
                        //parcourir_couleur(2, j);
                        m_couleur_actuelle = "blue";

                    }
                    else if (m_couleur_actuelle == "debut")
                    {
                        m_couleur_actuelle = "blue";
                    }
                }

                if(m_ressources.get_yellow_finder()->m_result->m_ImageData[j] == 1)
                {
                    r = 255;
                    g = 255;
                    b = 0;
                    if(m_couleur_actuelle != "yellow" && m_couleur_actuelle != "debut")
                    {
                        //parcourir_couleur(3, j);
                        m_couleur_actuelle = "yellow";

                    }
                    else if (m_couleur_actuelle == "debut")
                    {
                        m_couleur_actuelle = "yellow";
                        m_description_drapeau = "yellow";
                    }
                }
                if(m_ressources.get_black_finder()->m_result->m_ImageData[j] == 1)
                {
                    r = 0;
                    g = 0;
                    b = 0;
                    if(m_couleur_actuelle != "black" && m_couleur_actuelle != "debut")
                    {
                        //parcourir_couleur(4, j);
                        m_couleur_actuelle = "black";

                    }
                    else if (m_couleur_actuelle == "debut")
                    {
                        m_couleur_actuelle = "black";
                    }

                }

                if(m_ressources.get_red_finder()->m_result->m_ImageData[j] == 1)
                {
                    r = 244;
                    g = 42;
                    b = 164;
                    if(m_couleur_actuelle != "red" && m_couleur_actuelle != "debut")
                    {
                        //parcourir_couleur(5, j);
                        m_couleur_actuelle = "red";

                    }
                    else if (m_couleur_actuelle == "debut")
                    {
                        m_couleur_actuelle = "red";
                    }
                }

                if(m_ressources.get_green_finder()->m_result->m_ImageData[j] == 1)
                {
                    r = 0;
                    g = 106;
                    b = 78;
                    if(m_couleur_actuelle != "green" && m_couleur_actuelle != "debut")
                    {
                        //parcourir_couleur(6, j);
                        m_couleur_actuelle = "green";

                    }
                    else if (m_couleur_actuelle == "debut")
                    {
                        m_couleur_actuelle = "green";
                    }
                }
            }

            if(r > 0 || g > 0 || b > 0)
            {
                m_ressources.get_rgb_output()->m_ImageData[j * m_ressources.get_rgb_output()->m_PixelSize + 0] = r;
                m_ressources.get_rgb_output()->m_ImageData[j * m_ressources.get_rgb_output()->m_PixelSize + 1] = g;
                m_ressources.get_rgb_output()->m_ImageData[j * m_ressources.get_rgb_output()->m_PixelSize + 2] = b;

            }
        }

    }

    m_ressources.get_streamer()->send_image(m_ressources.get_rgb_output());
}



void application_compteur_balle::supprimerPixel(int i,int j)
{
    //std::cout <<"début" << std::endl;
    if(m_tab_pixel_drapeau[i][j] == 0)
    {
        //std::cout <<"1" << std::endl;
        m_tab_pixel_drapeau[i][j] = 2;
    }
    if(i>0)
    {
        //std::cout <<"2" << std::endl;
        if (m_tab_pixel_drapeau[i-1][j] == 0)
            supprimerPixel(i-1,j);
    }
    if(i<HEIGHT-1)
    {
        //std::cout <<"3" << std::endl;
        if(m_tab_pixel_drapeau[i+1][j] == 0 )
            supprimerPixel(i+1,j);
    }
    if( j<WIDTH-1)
    {
        //std::cout <<"4" << std::endl;
        if(m_tab_pixel_drapeau[i][j+1] == 0 )
            supprimerPixel(i,j+1);
    }
    if(j>0)
    {
        //std::cout <<"5" << std::endl;
        if(m_tab_pixel_drapeau[i][j-1] == 0 )
            supprimerPixel(i,j-1);
    }
}
QString application_compteur_balle::parcourir_couleur(int i,int j)
{
    std::cout <<"8" << std::endl;
    switch (i) {
    case 1:
        if(m_ressources.get_purple_finder()->m_result->m_ImageData[j+1] == 1)
        {
            return m_description_drapeau + " and white";
        }
        if(m_ressources.get_purple_finder()->m_result->m_ImageData[j-1] == 1)
        {
            return m_description_drapeau + " and white";
        }
        if(m_ressources.get_white_finder()->m_result->m_ImageData[j-1] == 1)
        {
            parcourir_couleur(1,j-1);
        }

        if(m_ressources.get_white_finder()->m_result->m_ImageData[j+1] == 1)
        {
            parcourir_couleur(1,j+1);
        }



        break;
    case 2:
        if(m_ressources.get_purple_finder()->m_result->m_ImageData[j+1] == 1)
        {
            return m_description_drapeau + " and blue";
        }
        if(m_ressources.get_purple_finder()->m_result->m_ImageData[j-1] == 1)
        {
            return m_description_drapeau + " and blue";
        }
        if(m_ressources.get_white_finder()->m_result->m_ImageData[j-1] == 1)
        {
            parcourir_couleur(2,j-1);
        }

        if(m_ressources.get_white_finder()->m_result->m_ImageData[j+1] == 1)
        {
            parcourir_couleur(2,j+1);
        }

        break;
    case 5:
        if(m_ressources.get_purple_finder()->m_result->m_ImageData[j+1] == 1)
        {
            return m_description_drapeau + " and red";
        }
        if(m_ressources.get_purple_finder()->m_result->m_ImageData[j-1] == 1)
        {
            return m_description_drapeau + " and red";
        }
        if(m_ressources.get_white_finder()->m_result->m_ImageData[j-1] == 1)
        {
            parcourir_couleur(5,j-1);
        }

        if(m_ressources.get_white_finder()->m_result->m_ImageData[j+1] == 1)
        {
            parcourir_couleur(5,j+1);
        }

        break;
    case 4:
        if(m_ressources.get_purple_finder()->m_result->m_ImageData[j+1] == 1)
        {
            return m_description_drapeau + " and black";
        }
        if(m_ressources.get_purple_finder()->m_result->m_ImageData[j-1] == 1)
        {
            return m_description_drapeau + " and black";
        }
        if(m_ressources.get_white_finder()->m_result->m_ImageData[j-1] == 1)
        {
            parcourir_couleur(4,j-1);
        }

        if(m_ressources.get_white_finder()->m_result->m_ImageData[j+1] == 1)
        {
            parcourir_couleur(4,j+1);
        }

        break;
    case 3:
        if(m_ressources.get_purple_finder()->m_result->m_ImageData[j+1] == 1)
        {
            return m_description_drapeau + " and yellow";
        }
        if(m_ressources.get_purple_finder()->m_result->m_ImageData[j-1] == 1)
        {
            return m_description_drapeau + " and yellow";
        }
        if(m_ressources.get_white_finder()->m_result->m_ImageData[j-1] == 1)
        {
            parcourir_couleur(3,j-1);
        }

        if(m_ressources.get_white_finder()->m_result->m_ImageData[j+1] == 1)
        {
            parcourir_couleur(3,j+1);
        }

        break;
    case 6:
        if(m_ressources.get_purple_finder()->m_result->m_ImageData[j+1] == 1)
        {
            return m_description_drapeau + " and green";
        }
        if(m_ressources.get_purple_finder()->m_result->m_ImageData[j-1] == 1)
        {
            return m_description_drapeau + " and green";
        }
        if(m_ressources.get_white_finder()->m_result->m_ImageData[j-1] == 1)
        {
            parcourir_couleur(6,j-1);
        }

        if(m_ressources.get_white_finder()->m_result->m_ImageData[j+1] == 1)
        {
            parcourir_couleur(6,j+1);
        }

        break;
    default:
        break;
    }
}
