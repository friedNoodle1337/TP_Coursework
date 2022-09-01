#ifndef HELPCOMMAND_HPP
#define HELPCOMMAND_HPP

#include "Command.hpp"

namespace savranenko
{
  class HelpCommand: public Command
  {
  public:
    HelpCommand() = delete;
    HelpCommand(std::vector< std::string >& args, std::map< std::string, command_t >& mapOfCommands):
      args_(args),
      mapOfCommands_(mapOfCommands),
      description_("help - show list of available commands\n")
    {}

    void execute() override
    {
      checkExceptions();

      std::cout << "Available commands:\n";
      for (std::map< std::string, command_t >::const_iterator commandsIt = mapOfCommands_.cbegin();
        commandsIt != mapOfCommands_.cend(); commandsIt++)
      {
        std::cout << commandsIt->second->getDescription();
      }
    }

    std::string getDescription() override
    {
      return description_;
    }

  private:
    std::vector< std::string >& args_;
    std::map< std::string, command_t >& mapOfCommands_;
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
