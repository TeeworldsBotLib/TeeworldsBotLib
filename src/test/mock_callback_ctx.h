#ifndef TWBL_SRC_TESTS_MOCK_CALLBACK_CTX_H
#define TWBL_SRC_TESTS_MOCK_CALLBACK_CTX_H

#include <twbl/callback_ctx.h>
#include <twbl/teeworlds/base/system.h>
#include <twbl/teeworlds/character.h>

class CMockCallbackCtx : public TWBL::CCallbackCtx
{
public:
	/*   _
	 *  | |__   __ _ ___  ___
	 *  | '_ \ / _` / __|/ _ \
	 *  | |_) | (_| \__ \  __/
	 *  |_.__/ \__,_|___/\___|
	 */

	void SendChat(int Team, const char *pText) override;
	void Die() override;
	void Emote(int Emoticon) override;

	bool IsFrozen(const CCharacter *pChr = nullptr) override;

	/*                  _
	 *    ___ _   _ ___| |_ ___  _ __ ___
	 *   / __| | | / __| __/ _ \| '_ ` _ \
	 *  | (__| |_| \__ \ || (_) | | | | | |
	 *   \___|\__,_|___/\__\___/|_| |_| |_|
	 */
};

#endif
