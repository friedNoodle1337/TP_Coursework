#ifndef COMPARECOMMAND_HPP
#define COMPARECOMMAND_HPP

#include "Command.hpp"

namespace savranenko
{
  class CompareCommand: public Command
  {
  public:
    CompareCommand() = delete;
    CompareCommand(std::vector< std::string >& args, map_of_dicts_t& mapOfDicts):
      args_(args),
      mapOfDicts_(mapOfDicts),
      description_("compare [word] [dict1] [dict2] - compare freq of a word in two dicts\n")
    {}

    void execute() override
    {
      checkExceptions();

      if (mapOfDicts_[args_[2]][args_[1]] > mapOfDicts_[args_[3]][args_[1]])
      {
        std::cout << "Freq of word \"" << args_[1] << "\" in \"" << args_[2] << "\" is bigger than in \"" << args_[3] << "\"\n";
      }
      else if (mapOfDicts_[args_[2]][args_[1]] < mapOfDicts_[args_[3]][args_[1]])
      {
        std::cout << "Freq of word \"" << args_[1] << "\" in \"" << args_[2] << "\" is smaller than in \"" << args_[3] << "\"\n";
      }
      else
      {
        std::cout << "Freq of word \"" << args_[1] << "\" in \"" << args_[2] << "\" and in \"" << args_[3] << "\" is equal\n";
      }
    }

    std::string getDescription() override
    {
      return description_;
    }

  private:
    std::vector< std::string >& args_;
    map_of_dicts_t& mapOfDicts_;
    std::string description_;

    void checkExceptions() override
    {
      if (args_.size() != 4)
      {
        throw std::logic_error("Invalid amount of args");
      }

      map_of_dicts_t::iterator foundDict1 = mapOfDicts_.find(args_[2]);
      bool isDict1Exists = foundDict1 != mapOfDicts_.end();
      if (!isDict1Exists)
      {
        throw std::logic_error("There is not dict on first place");
      }
      bool isWordExists1 = foundDict1->second.find(args_[1]) != foundDict1->second.end();
      if (!isWordExists1)
      {
        throw std::logic_error("There is not such word in dict on first place");
      }

      map_of_dicts_t::iterator foundDict2 = mapOfDicts_.find(args_[3]);
      bool isDict2Exists = foundDict2 != mapOfDicts_.end();
      if (!isDict2Exists)
      {
        throw std::logic_error("There is not dict on second place");
      }
      bool isWordExists2 = foundDict2->second.find(args_[1]) != foundDict2->second.end();
      if (!isWordExists2)
      {
        throw std::logic_error("There is not such word in dict on second place");
      }
    }
  };
}

#endif
