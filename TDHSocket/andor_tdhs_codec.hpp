/*
 * andor_tdhs_codec.hpp
 *
 *  Created on: Jun 13, 2013
 *      Author: root
 */

#ifndef ANDOR_TDHS_CODEC_HPP_
#define ANDOR_TDHS_CODEC_HPP_

#include <easy_define.h>
#include <easy_io_struct.h>

namespace taobao{

extern void* test_decode(easy_message_t *m);
extern int test_encode(easy_request_t *r, void *data);
extern int test_server_io_process(easy_request_t *r);

extern void *andor_tdhs_decode(easy_message_t *m);
extern int andor_tdhs_encode(easy_request_t *r, void *data);
//extern int andor_server_io_process(easy_request_t *r);

}

#endif /* ANDOR_TDHS_CODEC_HPP_ */
