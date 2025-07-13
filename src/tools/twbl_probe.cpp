// TODO: windows https://github.com/dlfcn-win32/dlfcn-win32

#include <twbl/teeworlds/base/detect.h>
#include <twbl/teeworlds/collision.h>

#ifdef CONF_FAMILY_WINDOWS

int main() { return 0; }

#else

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <dlfcn.h>

#include <twbl/types.h>

const char *GetString(void *pHandle, const char *pStrFunc)
{
	typedef const char *(*FTwblStr)();
	FTwblStr Info;
	Info = (FTwblStr)dlsym(pHandle, pStrFunc);

	char *pError = dlerror();
	if(pError != NULL)
	{
		fprintf(stderr, "dlsym failed on %s: %s\n", pStrFunc, pError);
		return 0;
	}

	return Info();
}

void ProbeInfo(void *pHandle)
{
	typedef const char *(*FTwblInfo)();
	FTwblInfo Info;
	Info = (FTwblInfo)dlsym(pHandle, "TwblInfo");

	char *pError = dlerror();
	if(pError != NULL)
	{
		fprintf(stderr, "dlsym failed on TwblInfo: %s\n", pError);
		return;
	}

	printf("TwblInfo: %s\n", Info());
}

void ProbeTick(void *pHandle, const char *pTickname)
{
	char aTickfunc[512];
	snprintf(aTickfunc, sizeof(aTickfunc), "Twbl_%sTick", pTickname);

	typedef void (*FTwbl_BotTick)(const CServerBotStateIn *pStateIn, CServerBotStateOut *pStateOut);
	FTwbl_BotTick Twbl_BotTick;
	Twbl_BotTick = (FTwbl_BotTick)dlsym(pHandle, aTickfunc);

	char *pError = dlerror();
	if(pError != NULL)
	{
		fprintf(stderr, "dlsym failed on %s: %s\n", aTickfunc, pError);
		return;
	}

	printf("Found tick '%s'. Calling ...\n", aTickfunc);

	CServerBotStateOut Bot;
	CServerBotStateIn State;
	CCollision Collision;
	State.m_pCollision = &Collision;

	Twbl_BotTick(&State, &Bot);

	printf("Dump state after calling '%s':\n", aTickfunc);
	Bot.DumpStdout();
}

void ProbeLib(const char *pLibPath)
{
	printf("loading file '%s'\n", pLibPath);
	void *pHandle = dlopen(pLibPath, RTLD_NOW | RTLD_GLOBAL);
	if(!pHandle)
	{
		fprintf(stderr, "dlopen error: %s\n", dlerror());
		exit(1);
	}
	dlerror();

	const char *pInfo = GetString(pHandle, "TwblInfo");
	printf("TwblInfo: %s\n", pInfo ? pInfo : "(null)");
	const char *pTicks = GetString(pHandle, "TwblTicks");
	printf("TwblTicks: %s\n", pTicks ? pTicks : "(null)");

	if(pTicks)
	{
		char aTicks[512];
		strncpy(aTicks, pTicks, sizeof(aTicks) - 1);
		char *pSplit = aTicks;
		char *pStart = pSplit;

		while(true)
		{
			pSplit = strstr(pSplit, ";");
			if(!pSplit)
			{
				ProbeTick(pHandle, pStart);
				break;
			}
			*pSplit = 0;
			pSplit += 1;

			ProbeTick(pHandle, pStart);
			pStart = pSplit;
		}
	}
	dlclose(pHandle);
}

void usage()
{
	puts("usage: twbl_proble <TWBL_LIB>");
	puts("description: prints information about twbl shared objects");
}

int main(int argc, char *argv[])
{
	puts("twbl probe tool");
	if(argc < 2)
	{
		usage();
		exit(1);
	}
	char aPath[512];
	strncpy(aPath, argv[1], sizeof(aPath) - 1);
	if(argv[1][0] != '.' && argv[1][0] != '/')
	{
		strncpy(aPath, "./", sizeof(aPath) - 1);
		strncat(aPath, argv[1], sizeof(aPath) - strlen(aPath) - 1);
	}

	ProbeLib(aPath);
}

#endif
