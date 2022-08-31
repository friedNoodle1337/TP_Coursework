#ifndef HELPCOMMAND_HPP
#define HELPCOMMAND_HPP

#include "Command.hpp"

namespace savranenko
{
  using command_t = std::shared_ptr< Command >;

  class HelpCommand: public Command
  {
  public:
    HelpCommand() = delete;
    HelpCommand(std::vector< std::string >& args, std::map< std::string, command_t >& mapOfCommands):
      args_(args),
      description_("help - show list of available commands\n")
    {
      for (std::map< std::string, command_t >::const_iterator commandsIt = mapOfCommands.cbegin();
        commandsIt != mapOfCommands.cend(); commandsIt++)
      {
        descriptions_.push_back(commandsIt->second->getDescription());
      }
    }

    void execute() override
    {
      checkExceptions();

      std::cout << "Available commands:\n"
                << description_;
      for (std::size_t i = 0; i < descriptions_.size(); i++)
      {
        std::cout << descriptions_[i];
      }
    }

    std::string getDescription() override
    {
      return description_;
    }

  private:
    std::vector< std::string >& args_;
    std::string description_;
    std::vector< std::string > descriptions_;

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
