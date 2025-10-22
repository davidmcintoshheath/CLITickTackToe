#ifndef SAVECSVFILE_HPP
#define SAVECSVFILE_HPP

#include <vector>
#include <string>

int saveCSVFile(const std::string &fileName, const std::vector<std::string> &inputHeaderStrings, const std::vector<std::vector<double>> &inputData);

#endif
