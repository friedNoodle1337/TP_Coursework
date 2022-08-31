#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

namespace savranenko
{
  using map_of_dicts_t = std::map< std::string, std::map< std::string, std::size_t > >;

  void readFiles(std::vector< std::string >& files, map_of_dicts_t& dictOfDicts);
  std::vector< std::string > splitString(const std::string& str);
  void makeFreqDict(std::map< std::string, std::size_t >& dict, const std::vector < std::string >& words);
}

#endif
