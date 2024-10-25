#ifndef TWBL_SRC_TESTS_MOCK_CALLBACK_CTX_H
#define TWBL_SRC_TESTS_MOCK_CALLBACK_CTX_H

#include <twbl/teeworlds/base/system.h>
#include <twbl/callback_ctx.h>

class CMockCallbackCtx : public TWBL::CCallbackCtx
{
public:
	void SendChat(int ClientId, int Team, const char *pText) override;
	void Die(int ClientId) override;
};


#endif
