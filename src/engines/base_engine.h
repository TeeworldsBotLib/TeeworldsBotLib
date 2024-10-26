#ifndef TWBL_SRC_ENGINES_BASE_ENGINE_H
#define TWBL_SRC_ENGINES_BASE_ENGINE_H

namespace TWBL {

class CBaseBot;

class CBaseEngine
{
	CBaseBot *m_pBaseBot;

protected:
	CBaseBot *Bot();

public:
	CBaseEngine(CBaseBot *pBaseBot);
};

} // namespace TWBL

#endif
