#pragma once
#include "Message.h"
namespace w5{
	const int NOTIFICATIONS_CAPACITY = 10;
	
	class Notifications{
		Message* ptrMessages;
		size_t count;
		public:
			Notifications();
			Notifications(const Notifications& rhs);
			Notifications& operator=(const Notifications& rhs);
			Notifications(Notifications&& rhs);
			Notifications&& operator=(Notifications&& rhs);
			~Notifications();
			void operator+=(const Message& msg);
			void display(std::ostream& os) const;
	};
}