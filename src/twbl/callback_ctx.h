#ifndef TWBL_SRC_TWBL_CALLBACK_CTX_H
#define TWBL_SRC_TWBL_CALLBACK_CTX_H

namespace TWBL {

class CCallbackCtx {
public:
	virtual ~CCallbackCtx() = default;
	virtual void SendChat(int ClientId, int Team, const char *pText) = 0;
	virtual void Die(int ClientId) = 0;
};

}; // namespace TWBL

#endif
