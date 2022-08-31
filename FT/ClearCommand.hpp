#ifndef CLEARCOMMAND_HPP
#define CLEARCOMMAND_HPP

#include "Command.hpp"

namespace savranenko
{
  class ClearCommand: public Command
  {
  public:
    ClearCommand() = delete;
    ClearCommand(std::vector< std::string >& args, map_of_dicts_t& mapOfDicts):
      args_(args),
      mapOfDicts_(mapOfDicts),
      description_("clear - clear all dicts\n")
    {}

    void execute() override
    {
      checkExceptions();

      mapOfDicts_.clear();
      std::cout << "All dicts were deleted\n";
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
      if (args_.size() != 1)
      {
        throw std::logic_error("Invalid amount of args");
      }
    }
  };
}

#endif
