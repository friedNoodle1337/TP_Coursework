#include "utils.hpp"
#include "Command.hpp"
#include "FindCommand.hpp"
#include "SearchCommand.hpp"
#include "DeleteCommand.hpp"
#include "ClearCommand.hpp"
#include "PrintCommand.hpp"
#include "ListCommand.hpp"
#include "CompareCommand.hpp"
#include "MergeCommand.hpp"
#include "TopThreeCommand.hpp"
#include "ShowFreqCommand.hpp"
#include "MakeFreqTableCommand.hpp"
#include "HelpCommand.hpp"

using namespace savranenko;

int main()
{
  std::vector< std::string > files{"Test-First.txt", "Test-Second.txt", "Test-Third.txt"};
  map_of_dicts_t mapOfDicts;
  readFiles(files, mapOfDicts);

  std::vector< std::string > args;
  std::map< std::string, command_t > mapOfCommands(
  {
    {"find", command_t(new FindCommand(std::ref(args), std::ref(mapOfDicts)))},
    {"search", command_t(new SearchCommand(std::ref(args), std::ref(mapOfDicts)))},
    {"delete", command_t(new DeleteCommand(std::ref(args), std::ref(mapOfDicts)))},
    {"clear", command_t(new ClearCommand(std::ref(args), std::ref(mapOfDicts)))},
    {"print", command_t(new PrintCommand(std::ref(args), std::ref(mapOfDicts)))},
    {"list", command_t(new ListCommand(std::ref(args), std::ref(mapOfDicts)))},
    {"compare", command_t(new CompareCommand(std::ref(args), std::ref(mapOfDicts)))},
    {"merge", command_t(new MergeCommand(std::ref(args), std::ref(mapOfDicts)))},
    {"topThree", command_t(new TopThreeCommand(std::ref(args), std::ref(mapOfDicts)))},
    {"showFreq", command_t(new ShowFreqCommand(std::ref(args), std::ref(mapOfDicts)))},
    {"makeFreqTable", command_t(new MakeFreqTableCommand(std::ref(args), std::ref(mapOfDicts)))}
  });
  mapOfCommands["help"] = command_t(new HelpCommand(std::ref(args), std::ref(mapOfCommands)));

  std::string strOfArgs = "";
  while (std::getline(std::cin, strOfArgs))
  {
    args = splitString(strOfArgs);
    try
    {
      if (mapOfCommands.find(args[0]) != mapOfCommands.end())
      {
        mapOfCommands[args[0]]->execute();
      }
      else
      {
        throw std::logic_error("There is not such command");
      }
    }
    catch (const std::exception& exc)
    {
      std::cerr << exc.what() << "\n";
    }
  }

  return 0;
}
