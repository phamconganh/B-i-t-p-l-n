
#include "music.h"
#include "check and init.h"

int Music::sound(const std::string& nameSound,const int& t)
{
	//Sound Effect
	Mix_Chunk* chunk = NULL;

	//Init SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
	    logError(std::cout," ",Mix_GetError(),false);
		return -1;
	}

	//Load Sound Effect
	chunk = Mix_LoadWAV(nameSound.c_str());
	if (chunk == NULL)
	{
		std::cout << nameSound <<" " << Mix_GetError() << std:: endl;
		return -1;
	}
        Mix_PlayChannel(-1, chunk, t);

	//Mix_CloseAudio();
	Mix_Quit();
	return 0;
}
