/*
 * andor_tdhs_codec.cpp
 *
 *  Created on: Jun 13, 2013
 *      Author: root
 */
#include "andor_tdhs_codec.hpp"

#include "string.h"
#include <netinet/in.h>
#include <stdio.h>
#include <iostream>
using namespace std;

//#include "zlib/zlib.h"
#include "easy_io.h"


#include "rpc.pb.h"

#include "andor_executor.hpp"
#include "commands.pb.h"
#include "tdh_socket_protocol.hpp"


#include <google/protobuf/descriptor.h>
#include <google/protobuf/service.h>
#include <easy_define.h>

typedef unsigned int   uInt;  /* 16 bits or more */
typedef unsigned long  uLong; /* 32 bits or more */
typedef unsigned char  Bytef;  /* 8 bits */


#define BASE 65521UL    /* largest prime smaller than 65536 */
#define NMAX 5552
/* NMAX is the largest n such that 255n(n+1)/2 + (n+1)(BASE-1) <= 2^32-1 */

#define DO1(buf,i)  {adler += (buf)[i]; sum2 += adler;}
#define DO2(buf,i)  DO1(buf,i); DO1(buf,i+1);
#define DO4(buf,i)  DO2(buf,i); DO2(buf,i+2);
#define DO8(buf,i)  DO4(buf,i); DO4(buf,i+4);
#define DO16(buf)   DO8(buf,0); DO8(buf,8);

/* use NO_DIVIDE if your processor does not do division in hardware */
#ifdef NO_DIVIDE
#  define MOD(a) \
    do { \
        if (a >= (BASE << 16)) a -= (BASE << 16); \
        if (a >= (BASE << 15)) a -= (BASE << 15); \
        if (a >= (BASE << 14)) a -= (BASE << 14); \
        if (a >= (BASE << 13)) a -= (BASE << 13); \
        if (a >= (BASE << 12)) a -= (BASE << 12); \
        if (a >= (BASE << 11)) a -= (BASE << 11); \
        if (a >= (BASE << 10)) a -= (BASE << 10); \
        if (a >= (BASE << 9)) a -= (BASE << 9); \
        if (a >= (BASE << 8)) a -= (BASE << 8); \
        if (a >= (BASE << 7)) a -= (BASE << 7); \
        if (a >= (BASE << 6)) a -= (BASE << 6); \
        if (a >= (BASE << 5)) a -= (BASE << 5); \
        if (a >= (BASE << 4)) a -= (BASE << 4); \
        if (a >= (BASE << 3)) a -= (BASE << 3); \
        if (a >= (BASE << 2)) a -= (BASE << 2); \
        if (a >= (BASE << 1)) a -= (BASE << 1); \
        if (a >= BASE) a -= BASE; \
    } while (0)
#  define MOD4(a) \
    do { \
        if (a >= (BASE << 4)) a -= (BASE << 4); \
        if (a >= (BASE << 3)) a -= (BASE << 3); \
        if (a >= (BASE << 2)) a -= (BASE << 2); \
        if (a >= (BASE << 1)) a -= (BASE << 1); \
        if (a >= BASE) a -= BASE; \
    } while (0)
#else
#  define MOD(a) a %= BASE
#  define MOD4(a) a %= BASE
#endif

/* ========================================================================= */
uLong  adler32(uLong adler,const Bytef *buf,uInt len)
{
	unsigned long sum2;
	unsigned n;

	/* split Adler-32 into component sums */
	sum2 = (adler >> 16) & 0xffff;
	adler &= 0xffff;

	/* in case user likes doing a byte at a time, keep it fast */
	if (len == 1) {
		adler += buf[0];
		if (adler >= BASE)
			adler -= BASE;
		sum2 += adler;
		if (sum2 >= BASE)
			sum2 -= BASE;
		return adler | (sum2 << 16);
	}

	/* initial Adler-32 value (deferred check for len == 1 speed) */
	if (buf == NULL)
		return 1L;

	/* in case short lengths are provided, keep it somewhat fast */
	if (len < 16) {
		while (len--) {
			adler += *buf++;
			sum2 += adler;
		}
		if (adler >= BASE)
			adler -= BASE;
		MOD4(sum2);
		/* only added so many BASE's */
		return adler | (sum2 << 16);
	}

	/* do length NMAX blocks -- requires just one modulo operation */
	while (len >= NMAX) {
		len -= NMAX;
		n = NMAX / 16; /* NMAX is divisible by 16 */
		do {
			DO16(buf);
			/* 16 sums unrolled */
			buf += 16;
		} while (--n);
		MOD(adler);
		MOD(sum2);
	}

	/* do remaining bytes (less than NMAX, still just one modulo) */
	if (len) { /* avoid modulos if none remaining */
		while (len >= 16) {
			len -= 16;
			DO16(buf);
			buf += 16;
		}
		while (len--) {
			adler += *buf++;
			sum2 += adler;
		}
		MOD(adler);
		MOD(sum2);
	}

	/* return recombined sums */
	return adler | (sum2 << 16);
}

namespace taobao {



void* andor_tdhs_decode(easy_message_t *m) {
	cout<<"enter decode: andor_tdhs_decode(...)"<<endl;

	::muduo::RpcMessage* rpcMessage;

	uint32_t len,data_len;

	if ((len = m->input->last - m->input->pos) < 4)
		return NULL;
    data_len = ntohl(*((uint32_t *) (m->input->pos)));

    cout<<"Length: "<<data_len<<endl;

    len = len - 4;
	if (len < data_len) {
		m->next_read_len = data_len - len;
		return NULL;
	}

	m->input->pos += 4;
	//RPCMessage prefix
	len = len -4;
	m->input->pos += 4;
	//RPCMessage
	/*
	if ((rpcMessage = (muduo::RpcMessage*) easy_pool_calloc(m->pool,
			sizeof(muduo::RpcMessage))) == NULL) {
		m->status = EASY_ERROR;
		return NULL;
	}
	*/
	rpcMessage = new ::muduo::RpcMessage();
	rpcMessage->ParseFromArray(m->input->pos,len-4);
	m->input->pos += len-4;

	//checksum
	//to do...
	m->input->pos +=4;
	cout<<"leave decode: andor_tdhs_decode(...)"<<endl;
    return rpcMessage;
}

int andor_tdhs_encode(easy_request_t *r, void *data){
	cout<<"enter encode: andor_tdhs_encode(...)"<<endl;
	easy_buf_t *b;
	//String str = "RPC0";
	char ch[4]={'R','P','C','0'};

	tdhs_packet_t* packet = (tdhs_packet_t*)data;
	andor_packet_t* andor_packet = (andor_packet_t*)packet->args;

    ::muduo::RpcMessage* rpcMessage = andor_packet->rpcMessage;
    ::protobuf::ResultSet* response=andor_packet->response;

    if(packet->command_id_or_response_code == 200||packet->command_id_or_response_code == 202
    		||packet->command_id_or_response_code == 207){
    	response->set_success(true);
    	rpcMessage->set_type(::muduo::RESPONSE);
        rpcMessage->set_response(response->SerializeAsString());

        cout<<"successful------"<<endl;
        cout<<"ID   : "<<rpcMessage->id()<<endl;
        cout<<"Type : "<<rpcMessage->GetTypeName()<<endl;
    }
    else{
    	//response->set_success(false);
    	rpcMessage->set_type(::muduo::ERROR);
    	rpcMessage->set_error(::muduo::INVALID_REQUEST);

        cout<<"Error------"<<endl;
        cout<<"ID   : "<<rpcMessage->id()<<endl;
        cout<<"Type : "<<rpcMessage->GetTypeName()<<endl;
    }

    uint32_t rpc_message_len = rpcMessage->ByteSize();
    cout<<"RpcMessage size:"<<rpc_message_len<<endl;
	b = easy_buf_create(r->ms->pool,4+4+rpc_message_len+4);

    //length
	*((uint32_t *) (b->last)) = htonl(4+rpc_message_len+4);
	b->last += 4;
    //"RPC0"
	memcpy(b->last,ch,4);
	b->last += 4;
    //RpcMessage
	rpcMessage->SerializeToArray(b->last,rpc_message_len);
	b->last += rpc_message_len;
	//checksum
	uint32_t adler = adler32(0L,NULL,0);
	adler = adler32(adler,(unsigned char*)b->pos,b->last-b->pos);
	cout<<"checksum adler:"<<adler<<endl;
	*((uint32_t *) (b->last)) = htonl(adler);
	b->last +=4;

	easy_request_addbuf(r, b);

	delete rpcMessage;
	cout<<"leave encode: andor_tdhs_encode(...)"<<endl;
	return EASY_OK;
}


}//namespace taobao

