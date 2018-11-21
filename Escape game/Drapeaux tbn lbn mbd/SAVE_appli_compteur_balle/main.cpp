/**
 * \file main.cpp
 *
 *  \author Angibaud
 */
#include "application_compteur_balle.h"

#include <iostream>
#include <signal.h>
#include "Speaker.h"

/**
  \brief Procédure de sortie.
  */
void sighandler(int sig)
{
    exit(0);
}

/**
  \brief Programme principal.
  */
int main(int argc, char *argv[])
{
    // Ajout des signaux de sortie
    signal(SIGABRT, & sighandler);
    signal(SIGTERM, & sighandler);
    signal(SIGQUIT, & sighandler);
    signal(SIGINT, & sighandler);

    Robot::application_compteur_balle app;
    app.run();

    return 0;
}

