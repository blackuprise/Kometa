/*
 * SoundEventReceiver.h
 *
 *  Created on: Dec 27, 2010
 *      Author: miroslav
 */

#ifndef SOUNDEVENTRECEIVER_H_
#define SOUNDEVENTRECEIVER_H_

#include <QMessageBox>
#include "MediaPlayer.h"

class SoundEventReceiver : public irrklang::ISoundStopEventReceiver{
public:

	virtual void OnSoundStopped(irrklang::ISound* sound,
			irrklang::E_STOP_EVENT_CAUSE reason, void* userData)
	{
		if (reason == irrklang::ESEC_SOUND_FINISHED_PLAYING)
		{
			//MediaPlayer* mediaPlayer = static_cast<MediaPlayer*> (userData);
			//mediaPlayer->next();
		}
	}
};

#endif /* SOUNDEVENTRECEIVER_H_ */
