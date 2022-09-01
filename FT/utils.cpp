#include "utils.hpp"

namespace savranenko
{
  void readFiles(std::vector< std::string >& files, map_of_dicts_t& mapOfDicts)
  {
    std::vector< std::string > dictNames{"first", "second", "third"};
    for (std::size_t i = 0; i < files.size(); i++)
    {
      std::ifstream text(files[i]);
      if (!text.is_open())
      {
        std::cerr << "File with name " << files[i] << " is not open!\n";
        continue;
      }
      std::string str = "";
      std::getline(text, str);
      text.close();
      std::map< std::string, std::size_t > dict;
      makeFreqDict(dict, splitString(str));
      mapOfDicts.insert_or_assign(dictNames[i], dict);
    }
  }

  std::vector< std::string > splitString(const std::string& str)
  {
    std::vector< std::string > words;

    std::size_t begin = 0;
    std::size_t end = str.find(' ', begin);
    while (end != -1)
    {
      words.push_back(str.substr(begin, end - begin));

      begin = end + 1;
      end = str.find(' ', begin);
    }
    words.push_back(str.substr(begin));

    return words;
  }

  void makeFreqDict(std::map< std::string, std::size_t >& dict, const std::vector < std::string >& words)
  {
    std::size_t freq = 1;
    for (std::size_t i = 0; i < words.size(); i++)
    {
      if (dict.find(words[i]) == dict.end())
      {
        for (std::size_t j = i + 1; j < words.size(); j++)
        {
          if (words[i] == words[j])
          {
            freq += 1;
          }
        }
        dict.insert_or_assign(words[i], freq);
        freq = 1;
      }
    }
  }
}
