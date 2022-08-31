#ifndef SHOWFREQCOMMAND_HPP
#define SHOWFREQCOMMAND_HPP

#include "Command.hpp"

namespace savranenko
{
  class ShowFreqCommand: public Command
  {
  public:
    ShowFreqCommand() = delete;
    ShowFreqCommand(std::vector< std::string >& args, map_of_dicts_t& mapOfDicts):
      args_(args),
      mapOfDicts_(mapOfDicts),
      description_("showFreq [word] [dict] - show freq of the word in the dict\n")
    {}

    void execute() override
    {
      checkExceptions();
      std::cout << args_[1] << ": Its frequency is " << mapOfDicts_[args_[2]][args_[1]] << "\n";
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
      bool isWordExists = foundDict->second.find(args_[1]) != foundDict->second.end();
      if (!isWordExists)
      {
        throw std::logic_error("There is not such word");
      }
    }
  };
}

#endif
