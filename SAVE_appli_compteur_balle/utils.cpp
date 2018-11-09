/**
 * \file utils.cpp
 * \brief Implémentation de la classe utils.
 * \author Angibaud
 */

#include "utils.h"

#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <libgen.h>

/*************************************************************************************/
/**
  * \brief Modifie le dossier courant.
  */
void Robot::utils::change_current_dir()
{
    char exepath[1024] = {0};
    if(readlink("/proc/self/exe", exepath, sizeof(exepath)) != -1)
    {
        if(chdir(dirname(exepath)))
            fprintf(stderr, "chdir error!! \n");
    }
}
