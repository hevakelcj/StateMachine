#include "StateMachine.h"
#include <boost/bind.hpp>

void State::addTransition(EventType event, State *nextState,
                          GuardFunc guard, ActionFunc action)
{
    transTable.insert(std::pair<EventType, TransItem>(event, TransItem(nextState, guard, action)));
}

void State::addTransition(EventType event, State *nextState)
{
    transTable.insert(std::pair<EventType, TransItem>(event, TransItem(nextState, boost::bind(&State::guard, this),
                                  boost::bind(&State::action, this))));
}

void State::addTransition(EventType event, State *nextState, GuardFunc guard)
{
    transTable.insert(std::pair<EventType, TransItem>(event, TransItem(nextState, guard,
                                  boost::bind(&State::action, this))));
}

void State::addTransition(EventType event, State *nextState, int, ActionFunc action)
{
    transTable.insert(std::pair<EventType, TransItem>(event, TransItem(nextState,
                                  boost::bind(&State::guard, this), action)));
}

State* State::acceptEvent(EventType event)
{
    State *nextState = this;

    std::multimap<EventType, TransItem>::const_iterator c_iter = transTable.begin();
    while (c_iter != transTable.end()) {
        const TransItem* item = & (c_iter->second);
        if (c_iter->first == event && item->guard()) {
            nextState = item->nextState;
            this->exit();
            item->action();
            nextState->enter();
            break;
        }
        ++ c_iter;
    }

    return nextState;
}

/////////////////////////////////////////////////////////////////////////////////////

void StateMachine::setOriginState(State *originState)
{
    assert(originState != NULL);    // what on earth you want set ?
    currentState = originState;
}

StateMachine::Result StateMachine::acceptEvent(EventType event)
{
    assert(currentState != NULL);
    // please set origin state before state translation

    State *next = currentState->acceptEvent(event);
    if (next == NULL) {
        return Error;
    } else if (next == currentState) {
        return NoChange;
    } else {
        currentState = next;
        return Changed;
    }
}
