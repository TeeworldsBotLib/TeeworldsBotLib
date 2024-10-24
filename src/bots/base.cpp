#include <cstdio>

#include <bots/base.h>
#include <twbl/types.h>

namespace TWBL {

CCharacter *CBaseBot::Character(int ClientId)
{
	if(ClientId == -1)
		return m_pStateIn->m_pCharacter;

	return GetPlayer(ClientId)->GetCharacter();
}

CPlayer *CBaseBot::GetPlayer(int ClientId)
{
#ifdef TWBL_SHARED_OBJECT
	// keep release mode fast
	// and test/hotreload safe
	if(!m_pStateIn->m_ppPlayers)
		return nullptr;
#endif
	if(ClientId == -1)
		ClientId = m_pStateIn->m_ClientId;
	return m_pStateIn->m_ppPlayers[ClientId];
}

CCharacter *CBaseBot::ClosestCharacter(vec2 Pos, const CCharacter *pNotThis)
{
	float ClosestRange = 0.f;
	CCharacter *pClosest = nullptr;

	for(int i = 0; i < MAX_CLIENTS; i++)
	{
		CPlayer *pPlayer = GetPlayer(i);
		if(!pPlayer)
			continue;
		CCharacter *pChr = pPlayer->GetCharacter();
		if(!pChr)
			continue;
		if(pChr == pNotThis)
			continue;

		float Len = distance(Pos, pChr->GetPos());

		if(Len < ClosestRange || !ClosestRange)
		{
			ClosestRange = Len;
			pClosest = pChr;
		}
	}

	return pClosest;
}

bool CBaseBot::IsFrozen(CCharacter *pChr)
{
	if(!pChr)
		return Character()->m_FreezeTime != 0;
	return pChr->m_FreezeTime != 0;
}

void PushRingStr(const char **ppBuffer, const char *pNew, size_t MaxEntries)
{
	for(int i = MaxEntries - 1; i > 0; i--)
		ppBuffer[i] = ppBuffer[i - 1];
	ppBuffer[0] = pNew;
}

void PushRingInt(int *pBuffer, int New, size_t MaxEntries)
{
	for(int i = MaxEntries - 1; i > 0; i--)
		pBuffer[i] = pBuffer[i - 1];
	pBuffer[0] = New;
}

#define GetStrBufSize(buf) sizeof(buf) / sizeof(const char *)
#define GetIntBufSize(buf) sizeof(buf) / sizeof(int)

void CBaseBot::_DieRaw() const
{
	m_pStateIn->m_pfnCallbackDie(m_pStateIn->m_pCharacter);
}

void CBaseBot::_Die(const char *pComment) const
{
	_DieRaw();
	m_pStateOut->m_pDieComment = pComment;
}

void CBaseBot::_AimRaw(int TargetX, int TargetY) const
{
	m_pStateOut->m_TargetX = TargetX;
	m_pStateOut->m_TargetY = TargetY;
}

void CBaseBot::_Aim(int TargetX, int TargetY, const char *pComment, const char *pFunction, const char *pFile, int Line) const
{
	_AimRaw(TargetX, TargetY);
	PushRingStr(m_pStateOut->m_apAimComments, pComment, GetStrBufSize(m_pStateOut->m_apAimComments));
	PushRingStr(m_pStateOut->m_apAimFunctions, pFunction, GetStrBufSize(m_pStateOut->m_apAimFunctions));
	PushRingStr(m_pStateOut->m_apAimFiles, pFile, GetStrBufSize(m_pStateOut->m_apAimFiles));
	PushRingInt(m_pStateOut->m_aAimLines, Line, GetIntBufSize(m_pStateOut->m_aAimLines));
}

void CBaseBot::_AimPos(int TargetX, int TargetY, const char *pComment, const char *pFunction, const char *pFile, int Line)
{
	_Aim(TargetX - GetPos().x, TargetY - GetPos().y, pComment, pFunction, pFile, Line);
}

void CBaseBot::_SetDirectionRaw(int Dir) const
{
	m_pStateOut->m_Direction = Dir;
}

void CBaseBot::_SetDirection(int Dir, const char *pComment, const char *pFunction, const char *pFile, int Line) const
{
	_SetDirectionRaw(Dir);
	PushRingStr(m_pStateOut->m_apDirComments, pComment, GetStrBufSize(m_pStateOut->m_apDirComments));
	PushRingStr(m_pStateOut->m_apDirFunctions, pFunction, GetStrBufSize(m_pStateOut->m_apDirFunctions));
	PushRingStr(m_pStateOut->m_apDirFiles, pFile, GetStrBufSize(m_pStateOut->m_apDirFiles));
	PushRingInt(m_pStateOut->m_aDirLines, Line, GetIntBufSize(m_pStateOut->m_aDirLines));
}

void CBaseBot::_HookRaw(int Value) const
{
	m_pStateOut->m_Hook = Value;
}

void CBaseBot::_Hook(int Value, const char *pComment, const char *pFunction, const char *pFile, int Line) const
{
	_HookRaw(Value);
	PushRingStr(m_pStateOut->m_apHookComments, pComment, GetStrBufSize(m_pStateOut->m_apHookComments));
	PushRingStr(m_pStateOut->m_apHookFunctions, pFunction, GetStrBufSize(m_pStateOut->m_apHookFunctions));
	PushRingStr(m_pStateOut->m_apHookFiles, pFile, GetStrBufSize(m_pStateOut->m_apHookFiles));
	PushRingInt(m_pStateOut->m_aHookLines, Line, GetIntBufSize(m_pStateOut->m_aHookLines));
}

void CBaseBot::_JumpRaw(int Value) const
{
	m_pStateOut->m_Jump = Value;
}

void CBaseBot::_Jump(int Value, const char *pComment, const char *pFunction, const char *pFile, int Line) const
{
	_JumpRaw(Value);
	PushRingStr(m_pStateOut->m_apJumpComments, pComment, GetStrBufSize(m_pStateOut->m_apJumpComments));
	PushRingStr(m_pStateOut->m_apJumpFunctions, pFunction, GetStrBufSize(m_pStateOut->m_apJumpFunctions));
	PushRingStr(m_pStateOut->m_apJumpFiles, pFile, GetStrBufSize(m_pStateOut->m_apJumpFiles));
	PushRingInt(m_pStateOut->m_aJumpLines, Line, GetIntBufSize(m_pStateOut->m_aJumpLines));
}

void CBaseBot::_FireRaw(int Value) const
{
	m_pStateOut->m_Fire = Value;
}

void CBaseBot::_Fire(int Value, const char *pComment, const char *pFunction, const char *pFile, int Line) const
{
	_FireRaw(Value);
	PushRingStr(m_pStateOut->m_apFireComments, pComment, GetStrBufSize(m_pStateOut->m_apFireComments));
	PushRingStr(m_pStateOut->m_apFireFunctions, pFunction, GetStrBufSize(m_pStateOut->m_apFireFunctions));
	PushRingStr(m_pStateOut->m_apFireFiles, pFile, GetStrBufSize(m_pStateOut->m_apFireFiles));
	PushRingInt(m_pStateOut->m_aFireLines, Line, GetIntBufSize(m_pStateOut->m_aFireLines));
}

void CBaseBot::_SetWeaponRaw(int Value) const
{
	m_pStateOut->m_Weapon = Value;
}

void CBaseBot::_SetWeapon(int Value, const char *pComment, const char *pFunction, const char *pFile, int Line) const
{
	_SetWeaponRaw(Value);
	PushRingStr(m_pStateOut->m_apSetWeaponComments, pComment, GetStrBufSize(m_pStateOut->m_apSetWeaponComments));
	PushRingStr(m_pStateOut->m_apSetWeaponFunctions, pFunction, GetStrBufSize(m_pStateOut->m_apSetWeaponFunctions));
	PushRingStr(m_pStateOut->m_apSetWeaponFiles, pFile, GetStrBufSize(m_pStateOut->m_apSetWeaponFiles));
	PushRingInt(m_pStateOut->m_aSetWeaponLines, Line, GetIntBufSize(m_pStateOut->m_aSetWeaponLines));
}

#undef GetStrBufSize
#undef GetIntBufSize

} // namespace TWBL

extern "C" {

const char *TwblInfo() { return "twbl OK"; }
const char *TwblTicks() { return "Sample;Follow"; }
}
