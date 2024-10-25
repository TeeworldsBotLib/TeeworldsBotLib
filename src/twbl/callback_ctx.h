#ifndef TWBL_SRC_TWBL_CALLBACK_CTX_H
#define TWBL_SRC_TWBL_CALLBACK_CTX_H

namespace TWBL {

class CCallbackCtx
{
public:
	virtual ~CCallbackCtx() = default;
	virtual void SendChat(int Team, const char *pText) = 0;
	virtual void Die() = 0;
	virtual void Emote(int Emoticon) = 0;

	int m_ClientId = 0;
	int GetCid() { return m_ClientId; }
};

}; // namespace TWBL

#endif
