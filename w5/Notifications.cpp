#include "Notifications.h"
namespace w5{
      Notifications::Notifications() : count(0),ptrMessages(new Message[NOTIFICATIONS_CAPACITY]){}
			Notifications::Notifications(const Notifications& rhs)
				:count(0), ptrMessages(new Message[NOTIFICATIONS_CAPACITY]){
				//copy constructor
				count = rhs.count;
				for(int i = 0; i < count; i++)
					ptrMessages[i] = rhs.ptrMessages[i]; 
			}
			Notifications& Notifications::operator=(const Notifications& rhs){
				//copy assignment operator
				if(this != &rhs){
					if(ptrMessages == nullptr)
						ptrMessages = new Message[NOTIFICATIONS_CAPACITY];
					count = rhs.count;
					for(int i = 0; i < count; i++)
						ptrMessages[i] = rhs.ptrMessages[i]; 
				}
				return *this;
			}
			Notifications::Notifications(Notifications&& rhs) : count(0),ptrMessages(rhs.ptrMessages){
				//move construct
				rhs.count = 0;
				rhs.ptrMessages = nullptr;
			}
			Notifications&& Notifications::operator=(Notifications&& rhs){
				if(this != &rhs){
					delete [] ptrMessages;
					
					count = rhs.count;
					ptrMessages = rhs.ptrMessages;
					
					rhs.count = 0;
					rhs.ptrMessages = nullptr;
				}
				return std::move(*this);
			}
			Notifications::~Notifications(){
				delete [] ptrMessages;
			}
			void Notifications::operator+=(const Message& msg){
				if(count < NOTIFICATIONS_CAPACITY){
					ptrMessages[count] = msg;
					count++;
				}
			}
			void Notifications::display(std::ostream& os) const{
				for(int i = 0; i < count; i++){
					ptrMessages[i].display(os);
				}
			}
}