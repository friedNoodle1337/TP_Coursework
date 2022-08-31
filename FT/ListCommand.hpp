#ifndef LISTCOMMAND_HPP
#define LISTCOMMAND_HPP

#include "Command.hpp"

namespace savranenko
{
  class ListCommand: public Command
  {
  public:
    ListCommand() = delete;
    ListCommand(std::vector< std::string >& args, map_of_dicts_t& mapOfDicts):
      args_(args),
      mapOfDicts_(mapOfDicts),
      description_("list - print a list of dicts\n")
    {}

    void execute() override
    {
      checkExceptions();

      for (map_of_dicts_t::const_iterator dictsIt = mapOfDicts_.cbegin(); dictsIt != mapOfDicts_.cend(); dictsIt++)
      {
        bool check = false;
        std::cout << dictsIt->first << ": ";
        for (std::map< std::string, std::size_t >::const_iterator dictIt = mapOfDicts_[dictsIt->first].cbegin();
          dictIt != mapOfDicts_[dictsIt->first].cend(); dictIt++)
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
      if (mapOfDicts_.size() == 0)
      {
        throw std::logic_error("There is not any dict");
      }
    }
  };
}

#endif
