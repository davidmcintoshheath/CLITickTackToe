#ifndef VELOCITYUPDATE_HPP
#define VELOCITYUPDATE_HPP
#include <vector>

std::vector<std::vector<double>> velocityUpdate(const std::vector<std::vector<double>> &inputCurrentVelocityVector, const std::vector<std::vector<double>> &inputCurrentPositionVector, const std::vector<double> &dragProperties, const std::vector<double> &areaProperties);

#endif
