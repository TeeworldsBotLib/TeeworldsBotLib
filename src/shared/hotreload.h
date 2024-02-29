#ifndef TWBL_SRC_SHARED_HOTRELOAD_H
#define TWBL_SRC_SHARED_HOTRELOAD_H

#include <cstring>
#include <ctime>

#include "shared/types.h"

typedef void (*FTwbl_BotTick)(const CServerBotStateIn *pStateIn, CServerBotStateOut *pStateOut);

namespace TWBL {

class CHotreloader
{
public:
	char m_aFilename[512];
	char m_aTickname[512];

	void *m_pHandle = nullptr;
	FTwbl_BotTick m_pfnBotTick = nullptr;
	time_t m_LastReload = -1;

	/**
	 * @param pFilename the full path to the shared object file of the twbl bot
	 * @param pTickname pretty name of the tick (example: "Sample", "Foo") will expand to Twbl_TicknameTick
	 */
	CHotreloader(const char *pFilename, const char *pTickname)
	{
		strncpy(m_aFilename, pFilename, sizeof(m_aFilename) - 1);
		strncpy(m_aTickname, pTickname, sizeof(m_aTickname) - 1);
	}

	~CHotreloader();

	/**
	 * Do not forget to call UnloadTick() after calling the tick function
	 * otherwise hot reloading will not work
	 *
	 * @param ppfnBotTick a pointer where the found callback will be stored in
	 * @returns NULL on error and a file handle you should close with dlclose() otherwise
	 */
	void *LoadTick(FTwbl_BotTick *ppfnBotTick);

	bool NeedRefresh();

	int CloseHandle(void *pHandle);
	int UnloadTick();
};

} // namespace TWBL

#endif
