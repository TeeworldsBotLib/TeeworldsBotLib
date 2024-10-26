#ifndef TWBL_SRC_TWBL_CALLBACK_CTX_H
#define TWBL_SRC_TWBL_CALLBACK_CTX_H

#include <twbl/teeworlds/base/vmath.h>
#include <twbl/teeworlds/character.h>

namespace TWBL {

class CCallbackCtx
{
public:
	/*   _
	 *  | |__   __ _ ___  ___
	 *  | '_ \ / _` / __|/ _ \
	 *  | |_) | (_| \__ \  __/
	 *  |_.__/ \__,_|___/\___|
	 */

	virtual ~CCallbackCtx() = default;

	// actions
	virtual void SendChat(int Team, const char *pText) = 0;
	virtual void Die() = 0;
	virtual void Emote(int Emoticon) = 0;

	// checks
	virtual bool IsFrozen(const CCharacter *pChr = nullptr) = 0;

	// getters
	int m_ClientId = 0;
	int GetCid() { return m_ClientId; }

	/*                  _
	 *    ___ _   _ ___| |_ ___  _ __ ___
	 *   / __| | | / __| __/ _ \| '_ ` _ \
	 *  | (__| |_| \__ \ || (_) | | | | | |
	 *   \___|\__,_|___/\__\___/|_| |_| |_|
	 */
};

}; // namespace TWBL

#endif
