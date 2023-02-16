#include "webserver/webserver_base.h"

//  打印笛卡尔空间坐标信息  | webserver_base.h
void PrintPoseInfo(arwen::dynamics::common::Pose &pose)
{
  std::cout << '\n';
  std::cout << __DATE__ << __TIME__ << __FILE__ << __LINE__ << " : " << "pose_info.p.data.x: " << pose.p.X() << std::endl;
  std::cout << __DATE__ << __TIME__ << __FILE__ << __LINE__ << " : " << "pose_info.p.data.y: " << pose.p.Y() << std::endl;
  std::cout << __DATE__ << __TIME__ << __FILE__ << __LINE__ << " : " << "pose_info.p.data.z: " << pose.p.Z() << std::endl;
  std::cout << __DATE__ << __TIME__ << __FILE__ << __LINE__ << " : " << "pose_info.rot.data.x: " << pose.rot.X() * 180 / M_PI << std::endl;
  std::cout << __DATE__ << __TIME__ << __FILE__ << __LINE__ << " : " << "pose_info.rot.data.y: " << pose.rot.Y() * 180 / M_PI << std::endl;
  std::cout << __DATE__ << __TIME__ << __FILE__ << __LINE__ << " : " << "pose_info.rot.data.z: " << pose.rot.Z() * 180 / M_PI << std::endl;
  std::cout << '\n';
}

const std::string setFlag(bool is_connect)
{
  Json::Value ws_conn_flag;
  Json::StreamWriterBuilder builder;

  if (is_connect) 
  {
    ws_conn_flag["flag"] = 1;
  }
  else
  {
    ws_conn_flag["flag"] = 0;
  }
  
  const std::string flag_str = Json::writeString(builder, ws_conn_flag);

  return flag_str.c_str();
}

const std::string parse_loginPasswd(const char *passwd_data)
{
  const std::string passwd_str = passwd_data;
  const auto passwd_str_len = static_cast<int>(passwd_str.length());
  Json::Value root;
  JSONCPP_STRING err;
  bool result = false;

  Json::CharReaderBuilder builder;
  const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
  result = reader->parse(passwd_str.c_str(), passwd_str.c_str() + passwd_str_len, &root, &err);
  if (!result)
  {
    std::cout << "error" << std::endl;
    return nullptr;
  }
  const std::string passwd_value = root["passwd"].asString();

  return passwd_value;
}

int GetArrayFromJsonString(const char *json_str, double *position_array, const char *json_key)
{
  Json::Value root;
  JSONCPP_STRING err;
  std::string json_obj;
  Json::CharReaderBuilder char_builder;

  json_obj = json_str;
  const std::unique_ptr<Json::CharReader> char_reader(char_builder.newCharReader());
  bool result = char_reader->parse(json_obj.c_str(), json_obj.c_str() + json_obj.size(), &root, &err);
  if (!result)
  {
    std::cout << "error" << std::endl;
    return EXIT_FAILURE;
  }
  if (root.isMember(json_key))
  {
    const Json::Value arrayNum = root[json_key];
    for (unsigned int i = 0; i < arrayNum.size(); i++)
    {
      position_array[i] = arrayNum[i].asDouble();
    }
  }
  else
  {
    std::cout << "The key [" << json_key << "] not exists!" << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

enum STATUS WSSpaceParse(const char *json_str)
{
  STATUS status = UNKNOWN;
  Json::Value root;
  JSONCPP_STRING err;
  std::string json_obj;
  Json::Value::Members key_members;
  Json::CharReaderBuilder char_builder;

  json_obj = json_str;
  const std::unique_ptr<Json::CharReader> char_reader(char_builder.newCharReader());
  bool result = char_reader->parse(json_obj.c_str(), json_obj.c_str() + json_obj.size(), &root, &err);
  if (!result)
  {
    std::cout << "error" << std::endl;
    return status;
  }

  key_members = root.getMemberNames();
  std::string first_key = key_members.front();
  if (strcmp(first_key.c_str(), "jointSpace") == 0)
  {
    status = JOINT_SPACE;
  } else if (strcmp(first_key.c_str(), "tcpSpace") == 0) {
    status = TCP_SPACE;
  } else if (strcmp(first_key.c_str(), "moveL") == 0) {
    status = MOVEL;
  } else {
    status = UNKNOWN;
  }

  return status;
}