#ifndef MERGECOMMAND_HPP
#define MERGECOMMAND_HPP

#include "Command.hpp"

namespace savranenko
{
  class MergeCommand: public Command
  {
  public:
    MergeCommand() = delete;
    MergeCommand(std::vector< std::string >& args, map_of_dicts_t& mapOfDicts):
      args_(args),
      mapOfDicts_(mapOfDicts),
      description_("merge [name_of_new_dict] [dict1] [dict2] - merge two dicts in one but without repeats\n")
    {}

    void execute() override
    {
      checkExceptions();

      std::map< std::string, std::size_t > newDict;
      newDict.insert(mapOfDicts_[args_[2]].begin(), mapOfDicts_[args_[2]].end());
      newDict.insert(mapOfDicts_[args_[3]].begin(), mapOfDicts_[args_[3]].end());
      mapOfDicts_.erase(args_[2]);
      mapOfDicts_.erase(args_[3]);

      mapOfDicts_.insert_or_assign(args_[1], newDict);

      std::cout << "Dict \"" << args_[2] << "\" and dict \"" << args_[3] << "\" were merged in dict \"" << args_[1] << "\"\n";
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
      if (args_.size() != 4)
      {
        throw std::logic_error("Invalid amount of args");
      }

      map_of_dicts_t::iterator foundDict1 = mapOfDicts_.find(args_[2]);
      bool isDict1Exists = foundDict1 != mapOfDicts_.end();
      if (!isDict1Exists)
      {
        throw std::logic_error("There is not dict on first place");
      }

      map_of_dicts_t::iterator foundDict2 = mapOfDicts_.find(args_[3]);
      bool isDict2Exists = foundDict2 != mapOfDicts_.end();
      if (!isDict2Exists)
      {
        throw std::logic_error("There is not dict on second place");
      }
    }
  };
}

#endif
