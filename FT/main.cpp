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
using command_t = std::shared_ptr< Command >;

int main()
{
  std::vector< std::string > files{"Test-First.txt", "Test-Second.txt", "Test-Third.txt"};
  map_of_dicts_t dictOfDicts;
  readFiles(files, dictOfDicts);

  std::vector< std::string > args;
  std::map< std::string, command_t > mapOfCommands(
  {
    {"find", command_t(new FindCommand(std::ref(args), std::ref(dictOfDicts)))},
    {"search", command_t(new SearchCommand(std::ref(args), std::ref(dictOfDicts)))},
    {"delete", command_t(new DeleteCommand(std::ref(args), std::ref(dictOfDicts)))},
    {"clear", command_t(new ClearCommand(std::ref(args), std::ref(dictOfDicts)))},
    {"print", command_t(new PrintCommand(std::ref(args), std::ref(dictOfDicts)))},
    {"list", command_t(new ListCommand(std::ref(args), std::ref(dictOfDicts)))},
    {"compare", command_t(new CompareCommand(std::ref(args), std::ref(dictOfDicts)))},
    {"merge", command_t(new MergeCommand(std::ref(args), std::ref(dictOfDicts)))},
    {"topThree", command_t(new TopThreeCommand(std::ref(args), std::ref(dictOfDicts)))},
    {"showFreq", command_t(new ShowFreqCommand(std::ref(args), std::ref(dictOfDicts)))},
    {"makeFreqTable", command_t(new MakeFreqTableCommand(std::ref(args), std::ref(dictOfDicts)))}
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
