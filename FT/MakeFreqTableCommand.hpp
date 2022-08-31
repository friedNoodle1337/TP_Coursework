#ifndef MAKEFREQTABLECOMMAND_HPP
#define MAKEFREQTABLECOMMAND_HPP

#include "Command.hpp"

namespace savranenko
{
  class MakeFreqTableCommand: public Command
  {
  public:
    MakeFreqTableCommand() = delete;
    MakeFreqTableCommand(std::vector< std::string >& args, map_of_dicts_t& mapOfDicts):
      args_(args),
      mapOfDicts_(mapOfDicts),
      description_("makeFreqTable [file] [name_of_dict] - make freq dict\n")
    {}

    void execute() override
    {
      checkExceptions();

      std::ifstream text(args_[1]);
      if (!text.is_open())
      {
        throw std::logic_error("File is not open!");
      }
      std::string str = "";
      std::getline(text, str);
      text.close();
      std::map< std::string, std::size_t > dict;
      makeFreqDict(dict, splitString(str));
      mapOfDicts_.insert_or_assign(args_[2], dict);
      std::cout << "Created a dict with name \"" << args_[2] << "\" from file \"" << args_[1] << "\"\n";
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
    }
  };
}

#endif
