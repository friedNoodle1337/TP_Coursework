#ifndef TOPTHREECOMMAND_HPP
#define TOPTHREECOMMAND_HPP

#include <algorithm>

#include "Command.hpp"

namespace savranenko
{
  class TopThreeCommand: public Command
  {
  public:
    TopThreeCommand() = delete;
    TopThreeCommand(std::vector< std::string >& args, map_of_dicts_t& mapOfDicts):
      args_(args),
      mapOfDicts_(mapOfDicts),
      description_("topThree [dict] - print 3 words with the biggest freqs\n")
    {}

    void execute() override
    {
      checkExceptions();

      std::vector< std::pair< std::size_t, std::string > > tempVect;
      for (std::map< std::string, std::size_t >::const_iterator dictIt = mapOfDicts_[args_[1]].cbegin();
        dictIt != mapOfDicts_[args_[1]].cend(); dictIt++)
      {
        tempVect.push_back(std::make_pair(dictIt->second, dictIt->first));
      }
      std::stable_sort(tempVect.rbegin(), tempVect.rend());

      std::size_t size = tempVect.size() >= 3 ? 3 : tempVect.size();
      for (std::size_t i = 0; i < size; i++)
      {
        std::cout << i + 1 << ". \"" << tempVect[i].second << "\" with freq \"" << tempVect[i].first << "\"\n";
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
