#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <stdexcept>

#include "utils.hpp"

namespace savranenko
{
  class Command
  {
  public:
    virtual ~Command() = default;

    virtual void execute() = 0;
    virtual std::string getDescription() = 0;

  private:
    virtual void checkExceptions() = 0;
  };
}

#endif
