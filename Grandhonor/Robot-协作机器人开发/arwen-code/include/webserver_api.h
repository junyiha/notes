#pragma once

#include <string>
#include <iostream>
/**************mongoose****************/
#include "webserver/mongoose.h"
/************************************/
#include "webserver/webserver_base.h"

void GetResponseHeader(std::string &response_header);

int api_login(struct mg_http_message *http_msg, struct mg_connection *connect);

int http_api_reply(struct mg_connection *connect, int status, const char *reply_key, const char *reply_value);
