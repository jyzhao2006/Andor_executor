/*
 * andor_executor.hpp
 *
 *  Created on: Jun 13, 2013
 *      Author: root
 */

#ifndef ANDOR_EXECUTOR_HPP_
#define ANDOR_EXECUTOR_HPP_

#include <easy_io.h>
#include "commands.pb.h"
#include "rpc.pb.h"

namespace taobao{

struct andor_packet_t{
	::muduo::RpcMessage *rpcMessage;
	::protobuf::ResultSet* response;
};

typedef struct andor_packet_t andor_packet_t;


class ServerDone :public ::google::protobuf::Closure{
public:
	ServerDone(easy_request_t *r,andor_packet_t *packet){
		this->e_request = r;
		this->ar_packet = packet;
	}
	void Run(){
		return;
	}
	easy_request_t * get_easy_request(){
		return this->e_request;
	}
	andor_packet_t * get_andor_packet(){
		return this->ar_packet;
	}
private:
	easy_request_t *e_request;
	andor_packet_t *ar_packet;
};

class Andor_Executor_Service : public ::protobuf::CommandExecutor{
public:
	  void ping(::google::protobuf::RpcController* controller,
	                       const ::protobuf::PingRequest* request,
	                       ::protobuf::ResultSet* response,
	                       ::google::protobuf::Closure* done);
	  void login(::google::protobuf::RpcController* controller,
	                       const ::protobuf::LoginRequest* request,
	                       ::protobuf::ResultSet* response,
	                       ::google::protobuf::Closure* done);
	  void execute(::google::protobuf::RpcController* controller,
	                       const ::protobuf::CommandRequest* request,
	                       ::protobuf::ResultSet* response,
	                       ::google::protobuf::Closure* done);
	  void fetchNext(::google::protobuf::RpcController* controller,
	                       const ::protobuf::ResultSetRequest* request,
	                       ::protobuf::ResultSet* response,
	                       ::google::protobuf::Closure* done);
	  void closeResultSet(::google::protobuf::RpcController* controller,
	                       const ::protobuf::ResultSetRequest* request,
	                       ::protobuf::ResultSet* response,
	                       ::google::protobuf::Closure* done);
	  void commit(::google::protobuf::RpcController* controller,
	                       const ::protobuf::TransactionRequest* request,
	                       ::protobuf::ResultSet* response,
	                       ::google::protobuf::Closure* done);
	  void rollback(::google::protobuf::RpcController* controller,
	                       const ::protobuf::TransactionRequest* request,
	                       ::protobuf::ResultSet* response,
	                       ::google::protobuf::Closure* done);
	  void first(::google::protobuf::RpcController* controller,
	                       const ::protobuf::ResultSetRequest* request,
	                       ::protobuf::ResultSet* response,
	                       ::google::protobuf::Closure* done);
	  void beforeFirst(::google::protobuf::RpcController* controller,
	                       const ::protobuf::ResultSetRequest* request,
	                       ::protobuf::ResultSet* response,
	                       ::google::protobuf::Closure* done);

};

extern int andor_server_io_process(easy_request_t *r);

}//namespace taobao

/*
#include "commands.pb.h"
#include <stdio.h>

#include <iostream>
using namespace std;

namespace taobao{
//class CommandExecutor;

class Andor_Executor_Service : public protobuf::CommandExecutor{
public:
	  void ping(::google::protobuf::RpcController* controller,
	                       const ::protobuf::PingRequest* request,
	                       ::protobuf::ResultSet* response,
	                       ::google::protobuf::Closure* done);
	  void login(::google::protobuf::RpcController* controller,
	                       const ::protobuf::LoginRequest* request,
	                       ::protobuf::ResultSet* response,
	                       ::google::protobuf::Closure* done){

		  cout<<request->user()<<endl;
		  cout<<request->password()<<endl;

		  response->set_success(true);

	  }
	  void execute(::google::protobuf::RpcController* controller,
	                       const ::protobuf::CommandRequest* request,
	                       ::protobuf::ResultSet* response,
	                       ::google::protobuf::Closure* done){
		  cout<<request->fetchsize()<<endl;


	  }
	  void fetchNext(::google::protobuf::RpcController* controller,
	                       const ::protobuf::ResultSetRequest* request,
	                       ::protobuf::ResultSet* response,
	                       ::google::protobuf::Closure* done);
	  void closeResultSet(::google::protobuf::RpcController* controller,
	                       const ::protobuf::ResultSetRequest* request,
	                       ::protobuf::ResultSet* response,
	                       ::google::protobuf::Closure* done);
	  void commit(::google::protobuf::RpcController* controller,
	                       const ::protobuf::TransactionRequest* request,
	                       ::protobuf::ResultSet* response,
	                       ::google::protobuf::Closure* done);
	  void rollback(::google::protobuf::RpcController* controller,
	                       const ::protobuf::TransactionRequest* request,
	                       ::protobuf::ResultSet* response,
	                       ::google::protobuf::Closure* done);
	  void first(::google::protobuf::RpcController* controller,
	                       const ::protobuf::ResultSetRequest* request,
	                       ::protobuf::ResultSet* response,
	                       ::google::protobuf::Closure* done);
	  void beforeFirst(::google::protobuf::RpcController* controller,
	                       const ::protobuf::ResultSetRequest* request,
	                       ::protobuf::ResultSet* response,
	                       ::google::protobuf::Closure* done);

};


}//namespace taobao

*/

#endif /* ANDOR_EXECUTOR_HPP_ */
