/*
 * andor_executor.cpp
 *
 *  Created on: Jun 24, 2013
 *      Author: jiyuan.zjy@alibaba-inc.com
 */
#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <typeinfo>
using namespace std;

#include <google/protobuf/descriptor.h>
#include <google/protobuf/service.h>

#include <easy_define.h>

#include "andor_executor.hpp"
#include "rpc.pb.h"
#include "commands.pb.h"
#include "tdh_socket_handler.hpp"

namespace taobao {



int andor_server_io_process(easy_request_t *r) {
	cout<<"Enter andor_server_io_process(...)"<<endl;
	/*
	if (r->retcode == EASY_AGAIN) {
		tdhs_client_wait_t * cond = (tdhs_client_wait_t *) r->args;
		if (cond && cond->is_inited) {
			//对流作处理
			pthread_mutex_lock(&cond->client_wait.mutex);
			if (cond->is_waiting) {
				easy_debug_log("TDHS:wake up for stream!");
				easy_atomic_inc( &r->ms->pool->ref);
				r->ms->c->pool->ref++;
				cond->client_wait.done_count++;
				pthread_cond_signal(&cond->client_wait.cond);
			} else {
				fatal_abort(
						"TDHS:OMG! wait client error,it should not be happed!");
			}
			pthread_mutex_unlock(&cond->client_wait.mutex);
		}
		return EASY_AGAIN;
	}
	*/
	::muduo::RpcMessage *rpcMessage = (::muduo::RpcMessage *) (r->ipacket);
	if (!rpcMessage) {
		return EASY_ERROR;
	}


	Andor_Executor_Service *executor_service = new Andor_Executor_Service;

	const ::google::protobuf::ServiceDescriptor* service = executor_service->GetDescriptor();
	const ::google::protobuf::MethodDescriptor* method = service->FindMethodByName(rpcMessage->method());
    if(method != NULL){
    	::google::protobuf::Message* request = executor_service->GetRequestPrototype(method).New();
    	request->ParseFromString(rpcMessage->request());
    	::google::protobuf::Message* response = executor_service->GetResponsePrototype(method).New();
    	uint64_t id = rpcMessage->id();
    	if(request!=NULL){
    		rpcMessage->Clear();
    		rpcMessage->set_id(id);
    		andor_packet_t* andor_packet = NULL;
    		if ((andor_packet = (andor_packet_t *) easy_pool_calloc(r->ms->pool,
					sizeof(andor_packet_t) )) == NULL) {
				r->ms->status = EASY_ERROR;
				return EASY_ERROR;
			}
    		andor_packet->rpcMessage = rpcMessage;
    		andor_packet->response = (::protobuf::ResultSet*)response;

    		ServerDone *done = new ServerDone(r,andor_packet);
    		executor_service->CallMethod(method,NULL,request,response,done);

    	}
    }
    cout<<"leave andor_server_io_process(...)"<<endl;
	return EASY_OK;
}

void build_tdhs_packet_insert(easy_request_t *r,const ::protobuf::Put& put_insert,tdhs_packet_t* packet){
	cout<<"Enter build_tdhs_packet_insert(...)"<<endl;
	int i,tmp;
	char * str;
	packet->command_id_or_response_code=12;//insert
	packet->pool = r->ms->pool;

	packet->req.status = TDHS_DECODE_DONE;
	packet->req.type = REQUEST_TYPE_INSERT;
	tdhs_request_table_t & table_info = packet->req.table_info;
	table_info.db.len = 5;
	table_info.db.str = "test";
	cout<<"DB name:"<<table_info.db.str<<endl;
	table_info.table.len = put_insert.indexkey().size()+1;
	table_info.table.str = put_insert.indexkey().c_str();
	cout<<"Table name:"<<table_info.table.str<<endl;
	table_info.index.len;
	table_info.index.str;

	tdhs_request_values_t & tdhs_values = packet->req.values;

	const ::google::protobuf::RepeatedPtrField< ::protobuf::Expression >& columns = put_insert.columns();
	const ::google::protobuf::RepeatedPtrField< ::protobuf::Expression >& values = put_insert.updateval();

	table_info.field_num = columns.size();
	tdhs_values.value_num = values.size();
	for(i=0;i<columns.size();i++){
		const ::protobuf::Expression & col = columns.Get(i);
		table_info.fields[i].len = col.column().columnname().size()+1;
		table_info.fields[i].str = col.column().columnname().c_str();
		const ::protobuf::Expression & val = values.Get(i);
		tdhs_values.flag[i]=::taobao::TDHS_UPDATE_SET;

		switch ( col.column().valuetype() ){
		case ::protobuf::Column::LONG_VAL:
		    //mysql bigint 20 numbers
			//cout<<"value("<<i<<")longval : "<<val.value().longval()<<endl;
			str = (char *)easy_pool_calloc(r->ms->pool,sizeof(char)*22);
		    tmp = snprintf (str, 22, "%d",val.value().longval());
		    tdhs_values.value[i].len = tmp+1;
		    tdhs_values.value[i].str = str;
			break;
		case ::protobuf::Column::BOOLEAN_VAL:
			//msyql true 1,false 0
			//cout<<"value("<<i<<")boolval : "<<val.value().boolval()<<endl;
		    str = (char *)easy_pool_calloc(r->ms->pool,2);
		    if(val.value().boolval() == true)
		    	tmp = snprintf (str, 2, "%d",1);
		    else
		    	tmp = snprintf (str, 2, "%d",0);
		    tdhs_values.value[i].len = tmp+1;
		    tdhs_values.value[i].str = str;
			break;
		case ::protobuf::Column::CHAR_VAL:
			//string&
			//cout<<"value("<<i<<")charval : "<<val.value().charval()<<endl;
			tdhs_values.value[i].len = val.value().charval().size()+1;
			tdhs_values.value[i].str = val.value().charval().c_str();
			break;
		case ::protobuf::Column::STRING_VAL:
			//cout<<"value("<<i<<")stringval : "<<val.value().stringval()<<endl;
			tdhs_values.value[i].len = val.value().stringval().size()+1;
		    tdhs_values.value[i].str = val.value().stringval().c_str();
			break;
		case ::protobuf::Column::FLOAT_VAL:
			//cout<<"value("<<i<<")floatval : "<<val.value().floatval()<<endl;
			str = (char *)easy_pool_calloc(r->ms->pool,sizeof(char)*42);
		    tmp = snprintf (str, 42, "%f",val.value().floatval());
		    tdhs_values.value[i].len = tmp+1;
		    tdhs_values.value[i].str = str;
			break;
		case ::protobuf::Column::DOUBLE_VAL:
			//cout<<"value("<<i<<")doubleval : "<<val.value().doubleval()<<endl;
			str = (char *)easy_pool_calloc(r->ms->pool,sizeof(char)*320);
			tmp = snprintf (str, 320, "%f",val.value().doubleval());
			tdhs_values.value[i].len = tmp+1;
			tdhs_values.value[i].str = str;
			break;
		case ::protobuf::Column::INT_VAL:
			//cout<<"value("<<i<<")integerval : "<<val.value().integerval()<<endl;
			str = (char *)easy_pool_calloc(r->ms->pool,sizeof(char)*12);
			tmp = snprintf (str, 12, "%d",val.value().integerval());
			tdhs_values.value[i].len = tmp+1;
			tdhs_values.value[i].str = str;
			break;
		case ::protobuf::Column::BIND_VAL:
			//cout<<"value("<<i<<")bindval : "<<val.value().bindval()<<endl;
			str = (char *)easy_pool_calloc(r->ms->pool,sizeof(char)*12);
			tmp = snprintf (str, 12, "%d",val.value().bindval());
			tdhs_values.value[i].len = tmp+1;
			tdhs_values.value[i].str = str;
			break;
		case ::protobuf::Column::DATE_VAL:
			//cout<<"value("<<i<<")dateval : "<<val.value().dateval()<<endl;
			str = (char *)easy_pool_calloc(r->ms->pool,sizeof(char)*22);
			tmp = snprintf (str, 22, "%d",val.value().dateval());
			tdhs_values.value[i].len = tmp+1;
		    tdhs_values.value[i].str = str;
			break;
		/*
		case ::protobuf::Column::BYTES_VAL:

			break;
		case ::protobuf::Column::TIMESTAMP:

			break;
		*/
		}
		cout<<table_info.fields[i].str<<" : "<<tdhs_values.value[i].str<<endl;

	}

	cout<<"leave build_tdhs_packet_insert(...)"<<endl;
}


void build_tdhs_packet_delete(easy_request_t *r,const ::protobuf::Put& put_delete,tdhs_packet_t* packet){
	cout<<"Enter build_tdhs_packet_delete(...)"<<endl;
	packet->command_id_or_response_code=12;//insert
	packet->pool = r->ms->pool;

	packet->req.status = TDHS_DECODE_DONE;
	packet->req.type = REQUEST_TYPE_DELETE;
	tdhs_request_table_t & table_info = packet->req.table_info;
	table_info.db.len = 5;
	table_info.db.str = "test";
	cout<<"DB name:"<<table_info.db.str<<endl;
	table_info.table.len = put_delete.indexkey().size()+1;
	table_info.table.str = put_delete.indexkey().c_str();
	cout<<"Table name:"<<table_info.table.str<<endl;
	table_info.index.len;
	table_info.index.str;

	cout<<"Leave build_tdhs_packet_delete(...)"<<endl;
}

void Andor_Executor_Service::ping(::google::protobuf::RpcController* controller,
                     const ::protobuf::PingRequest* request,
                     ::protobuf::ResultSet* response,
                     ::google::protobuf::Closure* done){
	cout << "Enter Andor_Executor_Service::ping(...)" << endl;
	ServerDone *server_done = dynamic_cast<ServerDone *>(done);
	easy_request_t *r = server_done->get_easy_request();
	andor_packet_t* andor_packet = server_done->get_andor_packet();
	//response->set_success(true);
	//andor_packet->response = response;
	tdhs_packet_t* packet = NULL;
	if ((packet = (tdhs_packet_t *) easy_pool_calloc(r->ms->pool,
			sizeof(tdhs_packet_t))) == NULL) {
		r->ms->status = EASY_ERROR;
		return;
	}
	packet->args = andor_packet;
	r->opacket = packet;
	packet->command_id_or_response_code=200;
	cout << "leave Andor_Executor_Service::ping(...)" << endl;
	return;
}

void Andor_Executor_Service::login(::google::protobuf::RpcController* controller,
                     const ::protobuf::LoginRequest* request,
                     ::protobuf::ResultSet* response,
                     ::google::protobuf::Closure* done){
	//add db name info and implement user info
	cout << "Enter Andor_Executor_Service::login(...)" << endl;
	cout << request->user() << endl;
	cout << request->password() << endl;

	ServerDone *server_done = dynamic_cast<ServerDone *>(done);
	easy_request_t *r = server_done->get_easy_request();
	andor_packet_t* andor_packet = server_done->get_andor_packet();
	//response->set_success(true);
	//andor_packet->response = response;
	tdhs_packet_t* packet = NULL;
	if ((packet = (tdhs_packet_t *) easy_pool_calloc(r->ms->pool,
			sizeof(tdhs_packet_t))) == NULL) {
		r->ms->status = EASY_ERROR;
		return;
	}
	packet->args = andor_packet;
	r->opacket = packet;
	packet->command_id_or_response_code=200;

	cout << "leave Andor_Executor_Service::login(...)" << endl;
}

void Andor_Executor_Service::execute(::google::protobuf::RpcController* controller,
                     const ::protobuf::CommandRequest* request,
                     ::protobuf::ResultSet* response,
                     ::google::protobuf::Closure* done){

	cout<<"Enter Andor_Executor_Service::execute(...)"<<endl;
	cout<<request->GetTypeName()<<endl;
	cout<<request->fetchsize()<<endl;

	ServerDone *server_done = dynamic_cast<ServerDone *>(done);
	easy_request_t *r = server_done->get_easy_request();
	andor_packet_t* andor_packet = server_done->get_andor_packet();
	//andor_packet->response = response;

	const ::protobuf::CommandNode& command_node = request->cmdnode();
	cout<<typeid(command_node).name()<<endl;
	if(command_node.has_put()){
		tdhs_packet_t* packet = NULL;
		if ((packet = (tdhs_packet_t *) easy_pool_calloc(r->ms->pool,
				sizeof(tdhs_packet_t) )) == NULL) {
			r->ms->status = EASY_ERROR;
			return;
		}
        packet->args = andor_packet;
        r->ipacket = packet;

		switch(command_node.put().puttype()){
		case ::protobuf::Put_PUT_TYPE_INSERT:
		{
			build_tdhs_packet_insert(r,command_node.put(),packet);
			push_to_write_task_thread(r,packet);
			break;
		}
		case ::protobuf::Put_PUT_TYPE_DELETE:
		{
			//build_tdhs_packet_delete(r,command_node.put(),packet);
			//push_to_write_task_thread(r,packet);
			break;
		}
		case ::protobuf::Put_PUT_TYPE_UPDATE:
		{
			break;
		}
		default:

			break;
		}

	}else if(command_node.has_querycommon()){
		//query...

	}else{
		//error
	}

	//response->set_success(true);

	cout<<"leave Andor_Executor_Service::execute(...)"<<endl;

	return;
}

void Andor_Executor_Service::fetchNext(::google::protobuf::RpcController* controller,
                     const ::protobuf::ResultSetRequest* request,
                     ::protobuf::ResultSet* response,
                     ::google::protobuf::Closure* done){
	return;
}

void Andor_Executor_Service::closeResultSet(::google::protobuf::RpcController* controller,
                     const ::protobuf::ResultSetRequest* request,
                     ::protobuf::ResultSet* response,
                     ::google::protobuf::Closure* done){
	return;
}

void Andor_Executor_Service::commit(::google::protobuf::RpcController* controller,
                     const ::protobuf::TransactionRequest* request,
                     ::protobuf::ResultSet* response,
                     ::google::protobuf::Closure* done){
	return;
}

void Andor_Executor_Service::rollback(::google::protobuf::RpcController* controller,
                     const ::protobuf::TransactionRequest* request,
                     ::protobuf::ResultSet* response,
                     ::google::protobuf::Closure* done){
	return;
}

void Andor_Executor_Service::first(::google::protobuf::RpcController* controller,
                     const ::protobuf::ResultSetRequest* request,
                     ::protobuf::ResultSet* response,
                     ::google::protobuf::Closure* done){
	return;
}

void Andor_Executor_Service::beforeFirst(::google::protobuf::RpcController* controller,
                     const ::protobuf::ResultSetRequest* request,
                     ::protobuf::ResultSet* response,
                     ::google::protobuf::Closure* done){
	return;
}


}//namespace taobao


