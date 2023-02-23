#include "webserver/webserver_api.h"

// 构建响应头    | webserver_api.h
void GetResponseHeader(std::string &response_header)
{
  response_header =  "Content-Type: application/json\r\n";
  response_header += "Connection: keep-alive\r\n";
  response_header += "Server: armcontrol\r\n";
  response_header += "Cache-control: no-cache, max-age=0, must-revalidate\r\n";
  response_header += "Access-Control-Allow-Origin: *\r\n";
  response_header += "Access-Control-Allow-Methods: *\r\n";
}

// 登录功能，默认密码为 123456    |  webserver_api.h
int api_login(struct mg_http_message *http_msg, struct mg_connection *connect)
{
  std::string response_header;
  GetResponseHeader(response_header);

  std::string passwd_value = GetValueFromJSON(http_msg->body.ptr, "passwd");
  if (strcmp(passwd_value.c_str(), "123456") == 0)
  {
    http_api_reply(connect, 200, "LOGIN", "SUCCESS");
  }
  else
  {
    http_api_reply(connect, 404, "LOGIN", "FAILED");
  }

  return 0;
}

// 快速发送http响应消息   | webserver_api.h
int http_api_reply(struct mg_connection *connect, int status, const char *reply_key, const char *reply_value)
{
  std::string response_header;
  GetResponseHeader(response_header);

  mg_http_reply(connect, status, response_header.c_str(), "{%Q:%Q}\n", reply_key, reply_value);

  return 0;
}