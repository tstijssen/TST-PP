#include "Sound.h"

using namespace snd;

string cSound::m_SoundFolder;

cSound::cSound(string fileName)
{
	bool loadSuccess;

	// create filepath for sound file
	loadSuccess = m_Buffer.loadFromFile(m_SoundFolder + fileName);

	if (loadSuccess)
	{
		m_Sound.setBuffer(m_Buffer);
	}
}



cSound::~cSound()
{

}