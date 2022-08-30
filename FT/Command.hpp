#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <functional>
#include <vector>
#include <string>
#include <stdexcept>

namespace savranenko
{
  class Command
  {
  public:
    virtual ~Command() = default;

    virtual void execute() = 0;

  private:
    virtual void checkExceptions() = 0;
  };
}

#endif
