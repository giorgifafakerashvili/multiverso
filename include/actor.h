#ifndef MULTIVERSO_ACTOR_H_
#define MULTIVERSO_ACTOR_H_


#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

#include "multiverso/message.h"

namespace multiverso {

template<typename T> class MtQueue;



// The basic computation and communication unit in the system 

class Actor {
 public:
 	explicit Actor(const std::string& name);
 	virtual ~Actor();

 	// Start to run the Actor 
 	void Start();

 	// Stop the run the Actor 
 	void Stop();

 	// Accept a message from other actors 
 	void Recieve(MessagePtr&);

 	// Actor name, a unique identified of a actor 
 	const std::string name() const { return name_; }

 protected:
 	// Message response function 
 	using Handler = std::function<void(MessagePtr&)>;
 	// Register message handler function 
 	void RegisterHandler(const MsgType& type, const Handler& task) {
 		handlers_.insert({type, tast});
 	}

 	// Send a message to a dst actor 
 	void SendTo(const std::string& dst_name, MessagePtr& msg);

 	// Main function run in background thread 
 	// The default main is to recieve msg from other actors and process 
 	// message based on registered message handler s
 	virtual void Main();

 	// message queue 
 	std::unique_ptr<MtQueue<MessagePtr>> mailbox_;
 	// message handlers function 
 	std::unordered_map<int, Handler> handlers_;
 	bool is_working_;

 private:
 	std::string name_;
 	std::unique_ptr<std::thread> thread_;

 	Actor(const Actor&)  = delete; 
 	void operator=(const Actor&)  = delete; 
};

namespace actor {

const std::string kCommunicator = "communicator";
const std::string kController = "controller";
const std::string kServer = "server";
const std::string kWorker = "worker";

}


}


#endif