#ifndef PRINTCOMMAND_HPP
#define PRINTCOMMAND_HPP

#include "Command.hpp"

namespace savranenko
{
  class PrintCommand: public Command
  {
  public:
    PrintCommand() = delete;
    PrintCommand(std::vector< std::string >& args, map_of_dicts_t& mapOfDicts):
      args_(args),
      mapOfDicts_(mapOfDicts),
      description_("print [dict] - print a dict\n")
    {}

    void execute() override
    {
      checkExceptions();

      bool check = false;
      for (std::map< std::string, std::size_t >::const_iterator dictIt = mapOfDicts_[args_[1]].cbegin();
        dictIt != mapOfDicts_[args_[1]].cend(); dictIt++)
      {
        if (check == false)
        {
          std::cout << dictIt->first << " " << dictIt->second;
          check = true;
        }
        else
        {
          std::cout << " " << dictIt->first << " " << dictIt->second;
        }
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

      map_of_dicts_t::iterator foundDict = mapOfDicts_.find(args_[1]);
      bool isDictExists = foundDict != mapOfDicts_.end();
      if (!isDictExists)
      {
        throw std::logic_error("There is not such dict");
      }
    }
  };
}

#endif
