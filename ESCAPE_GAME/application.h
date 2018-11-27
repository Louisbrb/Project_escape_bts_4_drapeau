#ifndef APPLICATION_H
#define APPLICATION_H

/**
 * \file application.h
 *
 * \author Angibaud
 */

#include "ressources.h"

namespace Robot
{
    /**
      * \brief Classe abstraite décrivant une application de base.
      * \author Angibaud
      */
    class application
    {
    public:
        application();
        ~application();

        virtual void run() = 0;

    protected:
        ressources m_ressources;
    }; // end class application
} // end namespace Robot

#endif // APPLICATION_H
