#ifndef TWBL_SRC_TWBL_STATE_H
#define TWBL_SRC_TWBL_STATE_H

#include <cstddef>

class CTwblPersistentState
{
public:
	/*   _
	 *  | |__   __ _ ___  ___
	 *  | '_ \ / _` / __|/ _ \
	 *  | |_) | (_| \__ \  __/
	 *  |_.__/ \__,_|___/\___|
	 */

	// how many times the twbl tick method has been called
	int m_TwblTicks = 0;

	// used to track fire state to increment it every tick
	int m_Fire = 0;

	/*                  _
	 *    ___ _   _ ___| |_ ___  _ __ ___
	 *   / __| | | / __| __/ _ \| '_ ` _ \
	 *  | (__| |_| \__ \ || (_) | | | | | |
	 *   \___|\__,_|___/\__\___/|_| |_| |_|
	 */
};

static const constexpr size_t MIN_TWBL_STATE_SIZE = sizeof(CTwblPersistentState);

#endif
