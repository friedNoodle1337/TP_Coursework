#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

namespace savranenko
{
  void readFiles(std::vector< std::string >& files, std::map< std::string, std::map< std::string, std::size_t > >& dictOfDicts);
  std::vector< std::string > splitString(const std::string& str);
  void makeFreqDict(std::map< std::string, std::size_t >& dict, const std::vector < std::string >& words);

  void help();
  bool find(const std::string& word, const std::map< std::string, std::size_t >& dict);
  void search(const std::string& word, std::map< std::string, std::map< std::string, std::size_t > >& dictOfDicts);
  void deleteFunc(const std::string& word, std::map< std::string, std::size_t >& dict);
  void deleteFunc(std::map< std::string, std::size_t >& dict,
    std::map< std::string, std::map< std::string, std::size_t > >& dictOfDicts);
  void clear(std::map< std::string, std::map< std::string, std::size_t > >& dictOfDicts);
  void print(const std::map< std::string, std::size_t >& dict);
  void list(const std::map< std::string, std::map< std::string, std::size_t > >& dictOfDicts);
  bool compare(const std::string& word, const std::map< std::string, std::size_t >& dict1,
    const std::map< std::string, std::size_t >& dict2);
  std::map< std::string, std::size_t > merge(const std::string& nameOfNewDict, std::map< std::string, std::size_t >& dict1,
    std::map< std::string, std::size_t >& dict2, std::map< std::string, std::map< std::string, std::size_t > >& dictOfDicts);
  void topThree(const std::map< std::string, std::size_t >& dict);
  void showFreq(const std::string& word, const std::map< std::string, std::size_t >& dict);
  void makeFreqTable(const std::string& fileName, const std::string& nameOfDict,
    std::map< std::string, std::map< std::string, std::size_t > >& dictOfDicts);
}

#endif
