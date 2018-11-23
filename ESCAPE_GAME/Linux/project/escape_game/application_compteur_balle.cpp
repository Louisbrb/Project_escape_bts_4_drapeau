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

/*************************************************************************************/
/**
  * \brief Constructeur.
  */
Robot::application_compteur_balle::application_compteur_balle()
{
}

/*************************************************************************************/
/**
  * \brief Lancement de la démo.
  */
void Robot::application_compteur_balle::run()
{
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
    Point2D red_pos, yellow_pos, blue_pos, green_pos,purple_pos;

    if( StatusCheck::m_cur_mode == READY || StatusCheck::m_cur_mode == VISION || StatusCheck::m_cur_mode == SOCCER || StatusCheck::m_cur_mode == MOTION )
    {
        purple_pos = m_ressources.get_purple_finder()->GetPosition(LinuxCamera::GetInstance()->fbuffer->m_HSVFrame);

        // modification de la sortie vidéo pour un meilleur contrôle de la détection
        unsigned char r, g, b;
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
                if ( Speaker::is_ready() )
        //Speaker::GetInstance()->Speak("ROUGE !.","fr");

                m_tab_pixel_drapeau[ ligne ][ colonne ] = 1;
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

        for(int j=0;j< m_ressources.get_rgb_output()->m_NumberOfPixels;j++)
        {
            if (m_tab_pixel_drapeau == false)
            {
                if(m_ressources.get_white_finder()->m_result->m_ImageData[j] == 1)
                {
                    r = 255;
                    g = 255;
                    b = 255;
                    //                    if(couleur_actuelle != "white")
                    //                    {
                    //                    parcourir_couleur();
                    //                    m_couleur_actuelle = "white";
                    //
                    //}
                }
                if(m_ressources.get_blue_finder()->m_result->m_ImageData[j] == 1)
                {
                    r = 0;
                    g = 72;
                    b = 206;
                }
                if(m_ressources.get_yellow_finder()->m_result->m_ImageData[j] == 1)
                {
                    r = 255;
                    g = 255;
                    b = 0;
                }
                if(m_ressources.get_black_finder()->m_result->m_ImageData[j] == 1)
                {
                    r = 0;
                    g = 0;
                    b = 0;
                }
                if(m_ressources.get_red_finder()->m_result->m_ImageData[j] == 1)
                {
                    r = 244;
                    g = 42;
                    b = 164;
                }
                if(m_ressources.get_green_finder()->m_result->m_ImageData[j] == 1)
                {
                    r = 0;
                    g = 106;
                    b = 78;
                }
                if(r > 0 || g > 0 || b > 0)
                {
                    m_ressources.get_rgb_output()->m_ImageData[j * m_ressources.get_rgb_output()->m_PixelSize + 0] = r;
                    m_ressources.get_rgb_output()->m_ImageData[j * m_ressources.get_rgb_output()->m_PixelSize + 1] = g;
                    m_ressources.get_rgb_output()->m_ImageData[j * m_ressources.get_rgb_output()->m_PixelSize + 2] = b;
                }
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
