
#include "Messenger.h"

namespace ent
{
	// global messager object for all
	CMessenger Messenger;

	// send receive
	void CMessenger::SendMessage(TEntityUID to, const SMessage& msg)
	{
		m_Messages.insert(UIDMsgPair(to, msg));
	}

	// fetch
	bool CMessenger::FetchMessage(TEntityUID to, SMessage* msg)
	{
		// find first instance of message for given UID
		TMessageIter itMessage = m_Messages.find(to);

		// no messages found
		if (itMessage == m_Messages.end())
		{
			return false;
		}

		*msg = itMessage->second;
		m_Messages.erase(itMessage);
		return true;
	}

}