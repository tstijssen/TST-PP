#pragma once

#include <map>

using namespace std;

#include "GenericDefines.h"
#undef SendMessage

namespace ent
{
	enum EMessageType
	{
		Msg_Die,
		Msg_Spawn,
	};

	struct SMessage
	{
		SMessage() {};

		SMessage(const SMessage& o)
		{
			memcpy(this, &o, sizeof(SMessage));
		}

		SMessage& operator=(const SMessage& o)
		{
			memcpy(this, &o, sizeof(SMessage));
			return *this;
		}

		EMessageType type;
		TEntityUID from;

		union
		{

		};

	};

	class CMessenger
	{
	public:
		CMessenger();

		// interface
		void SendMessage(TEntityUID to, const SMessage& msg);

		bool FetchMessage(TEntityUID to, SMessage* msg);

	private:
		CMessenger(const CMessenger&);
		CMessenger& operator=(const CMessenger&);

		//interface
		typedef multimap<TEntityUID, SMessage> TMessages;
		typedef TMessage::iterator TMessageIter;
		typedef pair<TEntityUID, SMessage> UIDMsgPair;

		TMessages m_Messages;
	};

}