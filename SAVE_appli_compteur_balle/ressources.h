#ifndef RESSOURCES_H
#define RESSOURCES_H

/**
 * \file ressources.h
 * \author Angibaud
 */

#include <LinuxDARwIn.h>
#include "BallFollower.h"
#include "mjpg_streamer.h"
#include "log_file.h"
#include "define.h"

namespace Robot
{
    class ColorFinder;
    class BallTracker;
    class CM730;
    class LinuxCM730;
    class Image;

    /**
      * \brief Classe contenant l'ensemble des ressources systèmes.
      * \author Angibaud
      */
    class ressources
    {
    public:
        ressources();
        ~ressources();
        ColorFinder* get_noir_finder() const;
        ColorFinder* get_blanche_finder() const;
        ColorFinder* get_purple_finder() const;
        ColorFinder* get_ball_finder() const;
        ColorFinder* get_red_finder() const;
        ColorFinder* get_blue_finder() const;
        ColorFinder* get_yellow_finder() const;
        ColorFinder* get_green_finder() const;

        BallTracker& get_tracker();
        BallFollower& get_follower();
        CM730 & get_cm730();
        log_file& get_log_file();

        Image* get_rgb_output() const;
        mjpg_streamer* get_streamer() const;


    private:
        LinuxCM730 m_linux_cm730;
        CM730 m_cm730;

        ColorFinder* m_ball_finder;
        ColorFinder* m_white_finder;
        ColorFinder* m_black_finder;
        ColorFinder* m_purple_finder;
        ColorFinder* m_red_finder;
        ColorFinder* m_blue_finder;
        ColorFinder* m_yellow_finder;
        ColorFinder* m_green_finder;

        BallTracker m_tracker;
        BallFollower m_follower;

        Image* m_rgb_output;
        mjpg_streamer* m_streamer;
        log_file m_log_file;
    }; // end class ressources
} // end namespace Robot

#endif // RESSOURCES_H
