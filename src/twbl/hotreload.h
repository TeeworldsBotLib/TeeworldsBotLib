#ifndef TWBL_SRC_SHARED_HOTRELOAD_H
#define TWBL_SRC_SHARED_HOTRELOAD_H

#include <cstddef>
#include <cstring>
#include <ctime>

#include <twbl/state.h>
#include <twbl/types.h>

#if defined(__GNUC__) && __GNUC__ >= 4
#define TWBL_HOT __attribute__((visibility("hidden")))
#elif defined(__SUNPRO_C) && (__SUNPRO_C >= 0x590)
#define TWBL_HOT __attribute__((visibility("hidden")))
#else
#define TWBL_HOT
#endif

typedef void (*FTwbl_BotTick)(const CServerBotStateIn *pStateIn, CServerBotStateOut *pStateOut, CTwblPersistentState *pState, size_t SizeOfState);

namespace TWBL {

class CHotreloader
{
	char m_aTickname[512];

	void *m_pHandle = nullptr;
	FTwbl_BotTick m_pfnBotTick = nullptr;
	time_t m_LastReload = -1;

	bool NeedRefresh();

	int CloseHandle(void *pHandle);
	int UnloadTick();

public:
	char m_aFilename[512];
	CHotreloader();
	~CHotreloader();

	/**
	 * @param pFilename the full path to the shared object file of the twbl bot
	 * @param pTickname pretty name of the tick (example: "Sample", "Foo") will expand to Twbl_TicknameTick
	 */
	void Init(const char *pFilename, const char *pTickname);

	/**
	 * You have to call Init() first
	 * otherwise hot loading will not work
	 *
	 * @param ppfnBotTick a pointer where the found callback will be stored in
	 * @returns NULL on error and a file handle you should close with dlclose() otherwise
	 */
	void *LoadTick(FTwbl_BotTick *ppfnBotTick);
};

} // namespace TWBL

#endif
