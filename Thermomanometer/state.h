#ifndef STATE_H
#define STATE_H

class Context;

class State { 
  public:
    virtual ~State() = default;
    virtual uint32_t handle(Context& context) = 0;
};

#endif
