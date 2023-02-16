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

const std::string setFlag(bool is_connect = false);

const std::string parse_loginPasswd(const char *passwd_data);

/**
 * @brief: 接收Json字符串 http_msg，解析并获取键json_key对应的数组，写入position_array
 * 
 * @param json_str [IN] : Json字符串
 * @param position_array [OUT] : 保存键json_key对应的数组
 * @param json_key [IN] : 要获取的json的键
 * 
*/
int GetArrayFromJsonString(const char *json_str, double *position_array, const char *json_key);

enum STATUS WSSpaceParse(const char *json_str);