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