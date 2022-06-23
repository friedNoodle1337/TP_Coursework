#include "utils.hpp"

using namespace savranenko;

int main()
{
  std::vector< std::string > files;
  files.push_back("Test-First.txt");
  files.push_back("Test-Second.txt");
  files.push_back("Test-Third.txt");
  std::map< std::string, std::map< std::string, std::size_t > > dictOfDicts;
  readFiles(files, dictOfDicts);

  std::string cmd = "";
  std::string strOfArgs = "";
  std::vector< std::string > args;
  std::string word = "";
  std::string nameOfDict1 = "";
  std::string nameOfDict2 = "";

  while (std::getline(std::cin, strOfArgs))
  {
    args = splitString(strOfArgs);
    cmd = args[0];

    if (cmd == "help")
    {
      if (args.size() != 1)
      {
        continue;
      }
      help();
    }
    else if (cmd == "find")
    {
      if (args.size() != 3)
      {
        continue;
      }
      word = args[1];
      nameOfDict1 = args[2];
      if (find(word, dictOfDicts.find(nameOfDict1)->second))
      {
        std::cout << "\"" << word << "\" is found. ";
      }
      else
      {
        std::cout << "No such word in " << nameOfDict1 << "\n";
      }
    }
    else if (cmd == "search")
    {
      if (args.size() != 2)
      {
        continue;
      }
      word = args[1];
      search(word, dictOfDicts);
    }
    else if (cmd == "delete")
    {
      if (args.size() == 3)
      {
        word = args[1];
        nameOfDict1 = args[2];
        if (dictOfDicts.find(nameOfDict1) != dictOfDicts.end())
        {
          if (find(word, dictOfDicts.find(nameOfDict1)->second))
          {
            deleteFunc(word, dictOfDicts.find(nameOfDict1)->second);
            std::cout << "Word was deleted\n";
          }
          else
          {
            std::cerr << "Nothing to delete\n";
          }
        }
        else
        {
          std::cerr << "There is not such dict\n";
        }
      }
      else if (args.size() == 2)
      {
        nameOfDict1 = args[1];
        if (dictOfDicts.find(nameOfDict1) != dictOfDicts.end())
        {
          deleteFunc(dictOfDicts.find(nameOfDict1)->second, dictOfDicts);
          std::cout << nameOfDict1 << " dict was deleted\n";
        }
        else
        {
          std::cerr << "There is not such dict\n";
        }
      }
      else
      {
        continue;
      }
    }
    else if (cmd == "clear")
    {
      if (args.size() != 1)
      {
        continue;
      }
      clear(dictOfDicts);
      std::cout << "All dicts were deleted\n";
    }
    else if (cmd == "print")
    {
      if (args.size() != 2)
      {
        continue;
      }
      nameOfDict1 = args[1];
      if (dictOfDicts.find(nameOfDict1) != dictOfDicts.end())
      {
        print(dictOfDicts.find(nameOfDict1)->second);
      }
      else
      {
        std::cerr << "There is not such dict\n";
      }
    }
    else if (cmd == "list")
    {
      if (args.size() != 1)
      {
        continue;
      }
      list(dictOfDicts);
    }
    else if (cmd == "compare")
    {
      if (args.size() != 4)
      {
        continue;
      }
      word = args[1];
      nameOfDict1 = args[2];
      nameOfDict2 = args[3];
      if (dictOfDicts.find(nameOfDict1) != dictOfDicts.end() &&
        dictOfDicts.find(nameOfDict1)->second.find(word) != dictOfDicts.find(nameOfDict1)->second.end())
      {
        if (dictOfDicts.find(nameOfDict2) != dictOfDicts.end() &&
          dictOfDicts.find(nameOfDict2)->second.find(word) != dictOfDicts.find(nameOfDict2)->second.end())
        {
          if (compare(word, dictOfDicts.find(nameOfDict1)->second, dictOfDicts.find(nameOfDict2)->second))
          {
            if (compare(word, dictOfDicts.find(nameOfDict2)->second, dictOfDicts.find(nameOfDict1)->second))
            {
              std::cout << "Freq of word in " << nameOfDict1 << " and in " << nameOfDict2 << " is equal\n";
            }
            else
            {
              std::cout << "Freq of word in " << nameOfDict1 << " is bigger than in " << nameOfDict2 << "\n";
            }
          }
          else
          {
            std::cout << "Freq of word in " << nameOfDict1 << " is smaller than in " << nameOfDict2 << "\n";
          }
        }
        else
        {
          std::cerr << "There is not dict with name " << nameOfDict2 << " or there is not such word in that dict\n";
        }
      }
      else
      {
        std::cerr << "There is not dict with name " << nameOfDict1 << " or there is not such word in that dict\n";
      }
    }
    else if (cmd == "merge")
    {
      if (args.size() != 4)
      {
        continue;
      }
      nameOfDict1 = args[2];
      nameOfDict2 = args[3];
      if (dictOfDicts.find(nameOfDict1) != dictOfDicts.end())
      {
        if (dictOfDicts.find(nameOfDict2) != dictOfDicts.end())
        {
          std::string nameOfNewDict = args[1];
          std::map< std::string, std::size_t > newDict = merge(nameOfNewDict, dictOfDicts.find(nameOfDict1)->second,
            dictOfDicts.find(nameOfDict2)->second, dictOfDicts);
          std::cout << nameOfDict1 << " and " << nameOfDict2 << " were merged\n";
        }
        else
        {
          std::cerr << "There is not dict with name " << nameOfDict2 << "\n";
        }
      }
      else
      {
        std::cerr << "There is not dict with name " << nameOfDict1 << "\n";
      }
    }
    else if (cmd == "topThree")
    {
      if (args.size() != 2)
      {
        continue;
      }
      nameOfDict1 = args[1];
      if (dictOfDicts.find(nameOfDict1) != dictOfDicts.end())
      {
        topThree(dictOfDicts.find(nameOfDict1)->second);
      }
      else
      {
        std::cerr << "There is not dict with name " << nameOfDict1 << "\n";
      }
    }
    else if (cmd == "showFreq")
    {
      if (args.size() != 3)
      {
        continue;
      }
      word = args[1];
      nameOfDict1 = args[2];
      if (dictOfDicts.find(nameOfDict1) != dictOfDicts.end() &&
        dictOfDicts.find(nameOfDict1)->second.find(word) != dictOfDicts.find(nameOfDict1)->second.end())
      {
        showFreq(word, dictOfDicts.find(nameOfDict1)->second);
      }
      else
      {
        std::cerr << "There is not dict with name " << nameOfDict1 << " or there is not such word\n";
      }
    }
    else if (cmd == "makeFreqTable")
    {
      if (args.size() != 3)
      {
        continue;
      }
      makeFreqTable(args[1], args[2], dictOfDicts);
    }
  }

  return 0;
}
