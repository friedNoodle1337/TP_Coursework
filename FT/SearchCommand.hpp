#ifndef SEARCHCOMMAND_HPP
#define SEARCHCOMMAND_HPP

#include "Command.hpp"

namespace savranenko
{
  class SearchCommand: public Command
  {
  public:
    SearchCommand() = delete;
    SearchCommand(std::vector< std::string >& args, map_of_dicts_t& mapOfDicts):
      args_(args),
      mapOfDicts_(mapOfDicts),
      description_("search [word] - search a word in all dicts\n")
    {}

    void execute() override
    {
      checkExceptions();

      std::map< std::string, std::size_t > tempDict;
      bool check = false;
      for (map_of_dicts_t::const_iterator dictsIt = mapOfDicts_.cbegin(); dictsIt != mapOfDicts_.cend(); dictsIt++)
      {
        tempDict = dictsIt->second;
        if (tempDict.find(args_[1]) != tempDict.end())
        {
          if (check == false)
          {
            std::cout << "\"" << args_[1] << "\" is found in " << dictsIt->first;
            check = true;
          }
          else
          {
            std::cout << ", " << dictsIt->first;
          }
        }
      }
      if (check == false)
      {
        std::cout << "No such word in all dicts";
      }
      std::cout << "\n";
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
      if (args_.size() != 2)
      {
        throw std::logic_error("Invalid amount of args");
      }
    }
  };
}

#endif
