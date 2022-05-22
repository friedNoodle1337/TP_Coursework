#include "utils.hpp"

namespace savranenko
{
  void readFiles(std::vector< std::string >& files, std::map< std::string, std::map< std::string, std::size_t > >& dictOfDicts)
  {
    std::vector< std::string > dictNames;
    dictNames.push_back("first");
    dictNames.push_back("second");
    dictNames.push_back("third");

    for (std::size_t i = 0; i < files.size(); i++)
    {
      std::ifstream text(files[i]);
      std::string str = "";
      std::getline(text, str);
      text.close();
      std::map< std::string, std::size_t > dict;
      makeFreqDict(dict, splitString(str));
      dictOfDicts.insert_or_assign(dictNames[i], dict);
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
      if (dict.contains(words[i]) == false)
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

  void help()
  {
    std::cout << "Available commands:\n";
    std::cout << "help\nfind [word] [dict] - search a word in one dict\nsearch [word] - search a word in all dicts\n";
    std::cout << "delete [word] [dict]- delete a word from a dict\ndelete [dict] - clear a dict\n";
    std::cout << "clear - clear all dicts\n";
    std::cout << "print [dict] - print a dict\nlist - print a list of dicts\n";
    std::cout << "compare [word] [dict1] [dict2] - compare freq of a word in two dicts\n";
    std::cout << "merge [name_of_new_dict] [dict1] [dict2] - merge two dicts in one but without repeats\n";
  }

  bool find(const std::string& word, const std::map< std::string, std::size_t >& dict)
  {
    return dict.contains(word);
  }

  void search(const std::string& word, std::map< std::string, std::map< std::string, std::size_t > >& dictOfDicts)
  {
    std::map< std::string, std::size_t > tempDict;
    bool check = false;
    for (std::map< std::string, std::map< std::string, std::size_t > >::const_iterator dictsIterator = dictOfDicts.cbegin();
      dictsIterator != dictOfDicts.cend(); dictsIterator++)
    {
      tempDict = dictsIterator->second;
      if (find(word, tempDict))
      {
        if (check == false)
        {
          std::cout << "\"" << word << "\" is found in " << dictsIterator->first;
          check = true;
        }
        else
        {
          std::cout << ", " << dictsIterator->first;
        }
      }
    }
    if (check == false)
    {
      std::cout << "No such word in all dicts\n";
    }
    else
    {
      std::cout << ".\n";
    }
  }

  void deleteFunc(const std::string& word, std::map< std::string, std::size_t >& dict)
  {
    dict.erase(word);
  }

  void deleteFunc(std::map< std::string, std::size_t >& dict, std::map< std::string,
    std::map< std::string, std::size_t > >& dictOfDicts)
  {
    for (std::map< std::string, std::map< std::string, std::size_t > >::const_iterator dictsIterator = dictOfDicts.cbegin();
      dictsIterator != dictOfDicts.cend(); dictsIterator++)
    {
      if (dictsIterator->second == dict)
      {
        dictOfDicts.erase(dictsIterator->first);
        break;
      }
    }
  }

  void clear(std::map< std::string, std::map< std::string, std::size_t > >& dictOfDicts)
  {
    dictOfDicts.clear();
  }

  void print(const std::map< std::string, std::size_t >& dict)
  {
    bool check = false;
    for (std::map< std::string, std::size_t >::const_iterator it = dict.cbegin();
      it != dict.cend(); it++)
    {
      if (check == false)
      {
        std::cout << it->first << " " << it->second;
        check = true;
      }
      else
      {
        std::cout << " " << it->first << " " << it->second;
      }
    }
    std::cout << "\n";
  }

  void list(const std::map< std::string, std::map< std::string, std::size_t > >& dictOfDicts)
  {
    bool check = false;
    for (std::map< std::string, std::map< std::string, std::size_t > >::const_iterator dictsIterator = dictOfDicts.cbegin();
      dictsIterator != dictOfDicts.cend(); dictsIterator++)
    {
      print(dictsIterator->second);
    }
    if (check == false)
    {
      std::cout << "There is not any dict\n";
    }
  }

  bool compare(const std::string& word, const std::map< std::string, std::size_t >& dict1,
    const std::map< std::string, std::size_t >& dict2)
  {
    if (dict1.find(word)->second >= dict2.find(word)->second)
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  std::map< std::string, std::size_t > merge(const std::string& nameOfNewDict, std::map< std::string, std::size_t >& dict1,
    std::map< std::string, std::size_t >& dict2, std::map< std::string, std::map< std::string, std::size_t > >& dictOfDicts)
  {
    std::map< std::string, std::size_t > newDict;
    newDict.merge(dict2);
    newDict.merge(dict1);
    deleteFunc(dict1, dictOfDicts);

    dictOfDicts.insert_or_assign(nameOfNewDict, newDict);

    return newDict;
  }
}
