#pragma once

#include <string>
#include <iostream>
/**************mongoose****************/
#include "webserver/mongoose.h"
/************************************/
/**************jsoncpp****************/
#include "jsoncpp/json.h"
/**************mongoose****************/

/**************planner****************/
#include "dynamics/solver/fk_solver_pos_kdl.h"
#include "dynamics/solver/fk_solver_pos_recursive.h"
#include "dynamics/solver/ik_solver_pos_lma.h"
#include "gflags/gflags.h"
#include "planning/planning.h"
#include "protocol/configuration/manipulator.h"
/************************************/

enum STATUS
{
    UNKNOWN = -1,
    JOINT_SPACE = 0,
    TCP_SPACE = 1,
    MOVEL = 2
};

void PrintPoseInfo(arwen::dynamics::common::Pose &pose);

/**
 * @brief 用于处理WebSocket接收的消息，状态机
 * 
 * @param json_str 输入的JSON字符串，即接收到的WebSocket消息
 * 
 * @return 返回WebSocket消息指定的状态，是关节空间的指令，还是笛卡尔空间的指令
*/
enum STATUS WSSpaceParse(const char *json_str);

/**
 * @brief 接收输入的JSON字符串和JSON 键，解析并返回JSON 键所对应的值
 * 
 * @param json_str  输入的JSON字符串
 * @param json_key  输入的要获取的键
 * 
 * @return 成功，返回json_key对应的JSON值
*/
const std::string GetValueFromJSON(const char *json_str, const char *json_key);

/**
 * @brief: 接收Json字符串 http_msg，解析并获取键json_key对应的数组，写入position_array
 * 
 * @param json_str [IN] : Json字符串
 * @param position_array [OUT] : 保存键json_key对应的数组
 * @param json_key [IN] : 要获取的json的键
 * 
 * @return 成功，返回0
*/
int GetArrayFromJsonString(const char *json_str, double *position_array, const char *json_key);

/**
 * @brief 接收一个大小为arr_size的double数据类型的数组和键，构造一个JSON字符串
 * 
 * @param json_key 构造的JSON字符串的键
 * @param arr_num double数据类型的数组，作为所构造的JSON字符串的值
 * @param arr_size 数组的大小
 * 
 * @return 成功，返回一个JSON字符串
*/
const std::string ArrayToJsonString(const char *json_key, double *arr_num, int arr_size);

/**
 * @brief 接收输入的键和值(字符串)，返回JSON字符串
 * 
 * @param json_key 输入的键
 * @param json_value 输入的值
 * 
 * @return 成功，返回构造的JSON字符串
*/
const std::string StringToJsonString(const char *json_key, const char *json_value);

/**
 * @brief 接收输入的键和值(整数)，返回JSON字符串
 * 
 * @param json_key 输入的键
 * @param json_value 输入的值
 * 
 * @return 成功，返回构造的JSON字符串
*/
const std::string NumberToJsonString(const char *json_key, int json_value);

/**
 * @brief 接收多条JSON字符串，和根键，以输入的根键作为键，将多条JSON字符串放到一个JSON字符串中
 * 
 * @param multi 存放多条JSON字符串的容器
 * @param root_json_key 根键
 * 
 * @return 成功，返回一个总的JSON字符串
*/
const std::string MultiJsonStringToSingle(std::vector<std::string>& multi_json_str, const char *root_json_key);