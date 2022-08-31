#ifndef DELETECOMMAND_HPP
#define DELETECOMMAND_HPP

#include "Command.hpp"

namespace savranenko
{
  class DeleteCommand: public Command
  {
  public:
    DeleteCommand() = delete;
    DeleteCommand(std::vector< std::string >& args, map_of_dicts_t& mapOfDicts):
      args_(args),
      mapOfDicts_(mapOfDicts),
      description_("delete [word] [dict]- delete a word from a dict\ndelete [dict] - clear a dict\n")
    {}

    void execute() override
    {
      checkExceptions();

      if (args_.size() == 3)
      {
        mapOfDicts_[args_[2]].erase(args_[1]);
        std::cout << "Word \"" << args_[1] << "\" is deleted from dict with name \"" << args_[2] << "\"\n";
      }
      else
      {
        mapOfDicts_.erase(args_[1]);
        std::cout << "Dict with name \"" << args_[1] << "\" is deleted\n";
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
      if (args_.size() < 2 || args_.size() > 3)
      {
        throw std::logic_error("Invalid amount of args");
      }

      map_of_dicts_t::iterator foundDict;
      if (args_.size() == 2)
      {
        foundDict = mapOfDicts_.find(args_[1]);
      }
      else
      {
        foundDict = mapOfDicts_.find(args_[2]);
      }

      bool isDictExists = foundDict != mapOfDicts_.end();
      if (!isDictExists)
      {
        throw std::logic_error("There is not such dict");
      }

      if (args_.size() == 3)
      {
        bool isWordExists = foundDict->second.find(args_[1]) != foundDict->second.end();
        if (!isWordExists)
        {
          throw std::logic_error("There is not such word");
        }
      }
    }
  };
}

#endif
