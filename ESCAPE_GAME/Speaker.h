/**
 * \file speak.h
 *
 * \author Angibaud
 */

#ifndef Speaker_H_
#define Speaker_H_

#include <string>
#include <espeak.h>

namespace Robot
{

    /**
      * \brief Classe décrivant une application de base.
      * \author Angibaud
      */
    class Speaker
    {
    private:
        static Speaker* m_UniqueInstance;
        static bool s_ready;

    public:
        Speaker();
        void Speak(std::string s, std::string voice);
        static Speaker* GetInstance() { return m_UniqueInstance; }
        static int callback(short *wav, int numsamples, espeak_EVENT *events);
        static bool is_ready();
    }; // end class Speaker

} // end namespace Robot

#endif /* Speaker_H_ */
