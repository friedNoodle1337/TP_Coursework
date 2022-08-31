#ifndef FINDCOMMAND_HPP
#define FINDCOMMAND_HPP

#include "Command.hpp"

namespace savranenko
{
  class FindCommand: public Command
  {
  public:
    FindCommand() = delete;
    FindCommand(std::vector< std::string >& args, map_of_dicts_t& mapOfDicts):
      args_(args),
      mapOfDicts_(mapOfDicts),
      description_("find [word] [dict] - search a word in one dict\n")
    {}

    void execute() override
    {
      checkExceptions();

      if (mapOfDicts_[args_[2]].find(args_[1]) != mapOfDicts_[args_[2]].end())
      {
        std::cout << "\"" << args_[1] << "\" is found.\n";
      }
      else
      {
        std::cout << "No such word in " << args_[2] << "\n";
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
      if (args_.size() != 3)
      {
        throw std::logic_error("Invalid amount of args");
      }

      map_of_dicts_t::iterator foundDict = mapOfDicts_.find(args_[2]);
      bool isDictExists = foundDict != mapOfDicts_.end();
      if (!isDictExists)
      {
        throw std::logic_error("There is not such dict");
      }
    }
  };
}

#endif
