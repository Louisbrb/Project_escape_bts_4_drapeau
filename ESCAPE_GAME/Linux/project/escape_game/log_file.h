#ifndef LOG_FILE_H
#define LOG_FILE_H

#include <fstream>
#include <string>
#include "time.h"

namespace Robot
{
    class log_file
    {
        public:

            log_file(const std::string & filename);
            ~log_file();

            void ajouter(std::string texte);
            void ajouter(std::string texte, int nb);

        private:
            void init_time();

        private:
            struct tm * time_info;
            time_t current_time;
            std::ofstream m_ofs;
    };
} // end namespace Robot

#endif // LOG_FILE_H
