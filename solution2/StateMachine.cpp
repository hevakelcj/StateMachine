#include "StateMachine.h"
#include <boost/bind.hpp>

void State::addTransition(EventType event, State *nextState,
                          GuardFunc guard, ActionFunc action)
{
    transTable[event] = TransItem(nextState, guard, action);
}

void State::addTransition(EventType event, State *nextState)
{
    transTable[event] = TransItem(nextState, boost::bind(&State::guard, this),
                                  boost::bind(&State::action, this));
}

void State::addTransition(EventType event, State *nextState, GuardFunc guard)
{
    transTable[event] = TransItem(nextState, guard,
                                  boost::bind(&State::action, this));
}

void State::addTransition(EventType event, State *nextState, int, ActionFunc action)
{
    transTable[event] = TransItem(nextState, boost::bind(&State::guard, this), action);
}

State* State::translate(EventType event)
{
    State *nextState = NULL;

    std::map<EventType, TransItem>::const_iterator c_iter = transTable.find(event);
    if ( c_iter != transTable.end()) {
        const TransItem* item = & (c_iter->second);
        if (item->guard()) {
            nextState = item->nextState;
            this->exit();
            item->action();
            nextState->enter();
        } else {
            nextState = this;
        }
    }
    return nextState;
}

/////////////////////////////////////////////////////////////////////////////////////

void StateMachine::setOriginState(State *originState)
{
    assert(originState != NULL);    // what on earth you want set ?
    currentState = originState;
}

StateMachine::Result StateMachine::translate(EventType event)
{
    assert(currentState != NULL);
    // please set origin state before state translation

    State *next = currentState->translate(event);
    if (next == NULL) {
        return Error;
    } else if (next == currentState) {
        return NoChange;
    } else {
        currentState = next;
        return Changed;
    }
}
