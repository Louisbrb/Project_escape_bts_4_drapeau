#include "log_file.h"
#include "define.h"

/*************************************************************************************/
/**
  * \brief Constructeur.
  */
Robot::log_file::log_file(const std::string & filename)
{
    m_ofs.open(filename.c_str(), std::ofstream::out | std::ofstream::app );
}

/*************************************************************************************/
/**
  * \brief Destructeur.
  */
Robot::log_file::~log_file()
{
    m_ofs.close();
}

/*************************************************************************************/
/**
  * \brief Ajoute un texte au fichier de log.
  */
void Robot::log_file::ajouter(std::string texte)
{
    init_time();

    m_ofs << asctime(time_info) << "\t" << texte << std::endl;
}

/*************************************************************************************/
/**
  * \brief Ajoute un texte puis un entier au fichier de log.
  */
void Robot::log_file::ajouter(std::string texte, int nb)
{
    init_time();

    m_ofs << asctime(time_info) << "\t" << texte << " " << nb << std::endl;
}

/*************************************************************************************/
/**
  * \brief Initialise la date actuelle.
  */
void Robot::log_file::init_time()
{
    time( & current_time );
    time_info = localtime( & current_time );
}

