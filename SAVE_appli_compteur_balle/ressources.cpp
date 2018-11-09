/**
 * \file ressources.cpp
 * \brief Implémentation de la classe ressources.
 * \author Angibaud
 */

#include "ressources.h"

#include "Image.h"
#include "mjpg_streamer.h"
#include "utils.h"
#include "define.h"

/*************************************************************************************/
/**
  * \brief Constructor.
  */
Robot::ressources::ressources()
 : m_linux_cm730(U2D_DEV_NAME0),
   m_cm730(&m_linux_cm730),
   m_tracker(BallTracker()),
   m_log_file(LOG_FILE_PATH)
 {
    utils::change_current_dir();

    minIni* ini = new minIni(INI_FILE_PATH);
    m_rgb_output = new Image(Camera::WIDTH, Camera::HEIGHT, Image::RGB_PIXEL_SIZE);

    LinuxCamera::GetInstance()->Initialize(0);
    LinuxCamera::GetInstance()->SetCameraSettings(CameraSettings());    // set default
    LinuxCamera::GetInstance()->LoadINISettings(ini);                   // load from ini

    m_streamer = new mjpg_streamer(Camera::WIDTH, Camera::HEIGHT);

    m_ball_finder = new ColorFinder();
    m_ball_finder->LoadINISettings(ini);
    httpd::ball_finder = m_ball_finder;

    m_follower = BallFollower();

    m_red_finder = new ColorFinder(0, 15, 45, 30, 0.3, 50.0);
    httpd::red_finder = m_red_finder;

    m_yellow_finder = new ColorFinder(80, 45, 40, 50, 0.3, 50.0);
    httpd::yellow_finder = m_yellow_finder;

    m_blue_finder = new ColorFinder(200, 45, 25, 20, 0.3, 50.0);
    httpd::blue_finder = m_blue_finder;

    m_green_finder = new ColorFinder(160, 15, 20, 50, 0.3, 50.0);
    httpd::green_finder = m_green_finder;

    httpd::ini = ini;

    //////////////////// Framework Initialize ////////////////////////////
    if(MotionManager::GetInstance()->Initialize(&m_cm730) == false)
    {
        m_linux_cm730.SetPortName(U2D_DEV_NAME1);
        if(MotionManager::GetInstance()->Initialize(&m_cm730) == false)
        {
            printf("Fail to initialize Motion Manager!\n");
            //return 0;
        }
    }

    Walking::GetInstance()->LoadINISettings(ini);

    MotionManager::GetInstance()->AddModule((MotionModule*)Action::GetInstance());
    MotionManager::GetInstance()->AddModule((MotionModule*)Head::GetInstance());
    MotionManager::GetInstance()->AddModule((MotionModule*)Walking::GetInstance());

    LinuxMotionTimer *motion_timer = new LinuxMotionTimer(MotionManager::GetInstance());
    motion_timer->Start();
    /////////////////////////////////////////////////////////////////////

    MotionManager::GetInstance()->LoadINISettings(ini);

    int firm_ver = 0;
    if(m_cm730.ReadByte(JointData::ID_HEAD_PAN, MX28::P_VERSION, &firm_ver, 0)  != CM730::SUCCESS)
    {
        fprintf(stderr, "Can't read firmware version from Dynamixel ID %d!! \n\n", JointData::ID_HEAD_PAN);
        exit(0);
    }

    if(0 < firm_ver && firm_ver < 27)
    {
#ifdef MX28_1024
        Action::GetInstance()->LoadFile(MOTION_FILE_PATH);
#else
        fprintf(stderr, "MX-28's firmware is not support 4096 resolution!! \n");
        fprintf(stderr, "Upgrade MX-28's firmware to version 27(0x1B) or higher.\n\n");
        exit(0);
#endif
    }
    else if(27 <= firm_ver)
    {
#ifdef MX28_1024
        fprintf(stderr, "MX-28's firmware is not support 1024 resolution!! \n");
        fprintf(stderr, "Remove '#define MX28_1024' from 'MX28.h' file and rebuild.\n\n");
        exit(0);
#else
        Action::GetInstance()->LoadFile((char*)MOTION_FILE_PATH);
#endif
    }
    else
        exit(0);
} // end constructor

/*************************************************************************************/
/**
  * \brief Destructor.
  */
Robot::ressources::~ressources()
{

} // end destructor

/*************************************************************************************/
/**
  * \brief Retourne le composant ColorFinder sur la balle.
  */
Robot::ColorFinder* Robot::ressources::get_ball_finder() const
{
    return m_ball_finder;
} // end get_ball_finder()
/*************************************************************************************/
/**
  * \brief Retourne le composant ColorFinder sur la couleur noire.
  */
Robot::ColorFinder* Robot::ressources::get_black_finder() const
{
    return m_black_finder;
} // end get_black_finder()

/*************************************************************************************/
/**
  * \brief Retourne le composant ColorFinder sur la couleur blanche.
  */
Robot::ColorFinder* Robot::ressources::get_white_finder() const
{
    return m_white_finder;
} // end get_purple_finder()

/*************************************************************************************/
/**
  * \brief Retourne le composant ColorFinder sur la couleur violette.
  */
Robot::ColorFinder* Robot::ressources::get_purple_finder() const
{
    return m_purple_finder;
} // end get_purple_finder()

/*************************************************************************************/
/**
  * \brief Retourne le composant ColorFinder sur la couleur rouge.
  */
Robot::ColorFinder* Robot::ressources::get_red_finder() const
{
    return m_red_finder;
} // end get_red_finder()

/*************************************************************************************/
/**
  * \brief Retourne le composant ColorFinder sur la couleur bleu.
  */
Robot::ColorFinder* Robot::ressources::get_blue_finder() const
{
    return m_blue_finder;
} // end get_blue_finder()

/*************************************************************************************/
/**
  * \brief Retourne le composant ColorFinder sur la couleur jaune.
  */
Robot::ColorFinder* Robot::ressources::get_yellow_finder() const
{
    return m_yellow_finder;
} // end get_yellow_finder()


/*************************************************************************************/
/**
  * \brief Retourne le composant ColorFinder sur la couleur verte.
  */
Robot::ColorFinder* Robot::ressources::get_green_finder() const
{
    return m_green_finder;
} // end get_green_finder()

/*************************************************************************************/
/**
  * \brief Retourne le composant BallTracker sur la balle.
  */
Robot::BallTracker& Robot::ressources::get_tracker()
{
    return m_tracker;
} // end get_tracker()

/*************************************************************************************/
/**
  * \brief Retourne le composant BallFollower sur la balle.
  */
Robot::BallFollower& Robot::ressources::get_follower()
{
    return m_follower;
} // end get_follower()

/*************************************************************************************/
/**
  * \brief Retourne le composant cm730.
  */
Robot::CM730 & Robot::ressources::get_cm730()
{
    return m_cm730;
}

/*************************************************************************************/
/**
  * \brief Retourne le fichier de log.
  */
Robot::log_file & Robot::ressources::get_log_file()
{
    return m_log_file;
}

/*************************************************************************************/
/**
  * \brief Retourne le composant rgb_output.
  */
Robot::Image* Robot::ressources::get_rgb_output() const
{
    return m_rgb_output;
} // end get_rgb_output()

/*************************************************************************************/
/**
  * \brief Retourne le composant mjpg_streamer.
  */
mjpg_streamer* Robot::ressources::get_streamer() const
{
    return m_streamer;
} // end get_streamer()
