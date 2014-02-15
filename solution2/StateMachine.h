#ifndef STATEMACHINEEX_H
#define STATEMACHINEEX_H

#include <boost/function.hpp>
#include <map>

typedef boost::function<bool()> GuardFunc;
typedef boost::function<void()> ActionFunc;
typedef int EventType;

class State
{
public:
    virtual ~State() {}

    void addTransition(EventType event, State *nextState);
    void addTransition(EventType event, State *nextState, GuardFunc guard);
    void addTransition(EventType event, State *nextState, int, ActionFunc action);
    void addTransition(EventType event, State *nextState, GuardFunc guard, ActionFunc action);

    State* acceptEvent(EventType event);

protected:
    virtual void enter() {}
    virtual void exit() {}

    virtual bool guard() {return true;}
    virtual void action() {}

private:
    struct TransItem {
        State *nextState;
        GuardFunc guard;
        ActionFunc action;

        TransItem(State* state, GuardFunc g, ActionFunc a)
            : nextState(state), guard(g), action(a) {}
        TransItem() : nextState(NULL), guard(boost::function<bool()>(NULL))
          , action(boost::function<void()>(NULL)) {}
    };

    std::multimap<EventType, TransItem> transTable;
};


//////////////////////////////////////////////////////////////////////////////////////////

class StateMachine
{
public:
    enum Result{
        Changed,
        NoChange,
        Error
    };

    StateMachine(State* originState = NULL)
        : currentState(originState) {}

    void   setOriginState(State* originState);
    State* getCurrentState() { return currentState; }

    Result acceptEvent(EventType event);

private:
    State* currentState;
};

#endif // STATEMACHINEEX_H
