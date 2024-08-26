#ifndef CONTEXT_H
#define CONTEXT_H

#include "data_visualizer.h"
#include "morser.h"

#include "wait_for_warm_state.h"
#include "press_temp_state.h"
#include "message_state.h"

class Context {
  private:
    State* previousState;
    State* currentState;
    
    DataVisualizer dv;
    Morser morser;
  
  public:
    explicit Context() 
    : previousState(nullptr), currentState(new PressTempState()) {}

    ~Context() {
      delete previousState;
      delete currentState;
    }

    DataVisualizer& getDV() { return dv; }
    Morser& getMorser() { return morser; }

    void setState(State* state)
    {
      delete previousState;
      previousState = currentState;
      currentState = state;
    }

    void update() {
      uint32_t time = currentState->handle(*this);
      delay(time);
    }
};

#endif
