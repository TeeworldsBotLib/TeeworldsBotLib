#include <cstdio>
#include <cstdlib>

#include <twbl/teeworlds/base/detect.h>

#ifdef CONF_FAMILY_WINDOWS
// TODO: windows api
#else
#include <dlfcn.h>
#include <sys/stat.h>
#endif

#include <twbl/hotreload.h>
#include <twbl/teeworlds/base/system.h>

namespace TWBL {

CHotreloader::CHotreloader()
{
	m_aFilename[0] = '\0';
	m_aTickname[0] = '\0';
}

void CHotreloader::Init(const char *pFilename, const char *pTickname)
{
	strncpy(m_aFilename, pFilename, sizeof(m_aFilename) - 1);
	strncpy(m_aTickname, pTickname, sizeof(m_aTickname) - 1);
}

bool CHotreloader::NeedRefresh()
{
	time_t Created, Updated;
	// returns 1 if the file does not exist
	if(fs_file_time(m_aFilename, &Created, &Updated))
		return false;

	// wait for the newly created file to become ready
	// we expect "file too short" to be caused while
	// the file is being written
	if(!m_pHandle && fs_is_file(m_aFilename))
		return true;

	if(Updated > m_LastReload)
	{
		m_LastReload = Updated;
		return true;
	}

	return false;
}

void *CHotreloader::LoadTick(FTwbl_BotTick *ppfnBotTick)
{
	const char *pFilename = m_aFilename;
	const char *pTickname = m_aTickname;

	*ppfnBotTick = m_pfnBotTick;

	if(!NeedRefresh())
		return m_pHandle;

	UnloadTick();

#ifdef CONF_FAMILY_WINDOWS
	return nullptr;
#else
	char aTickfunc[512];
	snprintf(aTickfunc, sizeof(aTickfunc), "Twbl_%sTickHot", pTickname);

	if(m_pHandle)
	{
		int Error = CloseHandle(m_pHandle);
		if(Error)
		{
			fprintf(stderr, "dlclose error: %d\n", Error);
		}
	}
	// else
	// {
	// 	fprintf(stderr, "[twbl] Error: ignore this error if it is only printed once.\n");
	// 	fprintf(stderr, "[twbl] Error: twbl no privious handle found for %s\n", pFilename);
	// 	fprintf(stderr, "[twbl] Error: make sure to not recreate the hotreload object. Use static or member variables.\n");
	// }

	dlerror();
	m_pHandle = dlopen(pFilename, RTLD_NOW | RTLD_GLOBAL);
	if(!m_pHandle)
	{
		fprintf(stderr, "dlopen error: %s\n", dlerror());
		return NULL;
	}
	dlerror();

	m_pfnBotTick = (FTwbl_BotTick)dlsym(m_pHandle, aTickfunc);

	char *pError = dlerror();
	if(pError != NULL)
	{
		fprintf(stderr, "dlsym failed on %s: %s\n", aTickfunc, pError);
		return NULL;
	}

	*ppfnBotTick = m_pfnBotTick;

	return m_pHandle;
#endif
}

int CHotreloader::CloseHandle(void *pHandle)
{
#ifdef CONF_FAMILY_WINDOWS
	return 0;
#else
	return dlclose(pHandle);
#endif
}

int CHotreloader::UnloadTick()
{
	int Error = 0;
	if(m_pHandle)
		Error = CloseHandle(m_pHandle);
	m_pHandle = nullptr;
	m_pfnBotTick = nullptr;
	m_LastReload = -1;
	return Error;
}

CHotreloader::~CHotreloader()
{
	UnloadTick();
}

} // namespace TWBL
