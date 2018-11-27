/*
 * Speak.cpp
 *
 *  Created on: 2014. 11. 21.
 *      Author: angibaud
 */
#include "Speaker.h"

#include <unistd.h>
#include <string.h>
#include <malloc.h>
#include <iostream>


Robot::Speaker* Robot::Speaker::m_UniqueInstance = new Robot::Speaker();
bool Robot::Speaker::s_ready = true;

/*************************************************************************************/
/**
  * \brief Constructeur
  */
Robot::Speaker::Speaker()
{
    int Buflength = 500, Options=0;
    char *path=NULL;
    espeak_AUDIO_OUTPUT output;

    output  = AUDIO_OUTPUT_PLAYBACK;

    espeak_Initialize(output, Buflength, path, Options );
}


/*************************************************************************************/
/**
  * \brief Envoi au haut parleur la phrase donnée en paramètre.
  * \param s : Le texte à lire.
  * \param voice : La voix à utiliser. Par exemple "fr", "en"...
  */
void Robot::Speaker::Speak(std::string s, std::string voice)
{
    s_ready = false;
    s = s + " . . ";

    espeak_POSITION_TYPE position_type;
    void* user_data;

    unsigned int position=0, end_position=0, flags=espeakCHARS_AUTO, *unique_identifier;

    unique_identifier = NULL;
    user_data = NULL;
    position_type = POS_CHARACTER;

    espeak_SetSynthCallback(callback);
    espeak_SetVoiceByName(voice.c_str());
    espeak_SetParameter(espeakRATE, 130, 0);
    espeak_SetParameter(espeakVOLUME, 100, 0); // 100 par défaut
    printf("Saying  '%s(%u)'\n",s.c_str(), s.size() + 1);
    espeak_Synth( s.c_str(), s.size() + 1, position, position_type, end_position, flags,
            unique_identifier, user_data );
    espeak_Synchronize( );
} // end speaker::Speak()

/*************************************************************************************/
/**
  * \brief Function used for callback.
  */
int Robot::Speaker::callback(short *wav, int numsamples, espeak_EVENT *events)
{
    espeak_EVENT_TYPE type = events->type;

    if ( type == 6 )
        s_ready = true;

    return 0;
}

/*************************************************************************************/
/**
  * \brief Returns if the speaker is ready.
  */
bool Robot::Speaker::is_ready()
{
    return s_ready;
}
