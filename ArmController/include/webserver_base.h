#pragma once

#include <string>
#include <iostream>
/**************mongoose****************/
#include "webserver/mongoose.h"
/************************************/
/**************planner****************/
#include "dynamics/solver/fk_solver_pos_kdl.h"
#include "dynamics/solver/fk_solver_pos_recursive.h"
#include "dynamics/solver/ik_solver_pos_lma.h"
#include "gflags/gflags.h"
#include "planning/planning.h"
#include "protocol/configuration/manipulator.h"
/************************************/

void PrintPoseInfo(arwen::dynamics::common::Pose &pose);
