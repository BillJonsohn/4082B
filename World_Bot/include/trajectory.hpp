#pragma once
#include "main.h"
#include<vector>

struct TrajectoryPoint{
  double leftVelocity, rightVelocity;
};

using Trajectory = std::vector<TrajectoryPoint>;