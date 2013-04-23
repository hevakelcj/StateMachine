#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <vector>

template <typename StateType, typename EventType>
class StateMachine
{
public:
    typedef boost::function<bool()> GuardFun;
    typedef boost::function<void()> ActionFun;

    struct Item {
        StateType currState, nextState;
        EventType triger;
        GuardFun  guard;
        ActionFun action;

        Item(StateType cs, StateType ns, EventType t, GuardFun gf, ActionFun af)
            : currState(cs), nextState(ns), triger(t), guard(gf), action(af) {}
    };

    StateMachine(StateType startState) : m_currState(startState) {}

    void append(StateType cs, StateType ns, EventType t, GuardFun gf, ActionFun af) {
        m_stateTable.push_back(Item(cs, ns, t, gf, af));
    }
    void append(StateType cs, StateType ns, EventType t, GuardFun gf) {
        m_stateTable.push_back(Item(cs, ns, t, gf, boost::bind(&StateMachine::default_action, this)));
    }
    void append(StateType cs, StateType ns, EventType t, int, ActionFun af) {
        m_stateTable.push_back(Item(cs, ns, t, boost::bind(&StateMachine::default_guard, this), af));
    }
    void append(StateType cs, StateType ns, EventType t) {
        m_stateTable.push_back(Item(cs, ns, t, boost::bind(&StateMachine::default_guard, this),
                                    boost::bind(&StateMachine::default_action, this)));
    }

    StateType currentState() { return m_currState; }

    bool eventTriger(EventType triger)
    {
        bool isStateChanged = false;

        typename std::vector<Item>::iterator iter = m_stateTable.begin();
        for ( ; iter != m_stateTable.end(); ++iter) {
            if (iter->currState == m_currState && iter->triger == triger) {
                if (iter->guard()) {
                    m_currState = iter->nextState;
                    iter->action();
                    isStateChanged = true;
                }
                break;
            }
        }

        return isStateChanged;
    }

protected:
    bool default_guard() { return true; }
    void default_action() {}

private:
    std::vector<Item> m_stateTable;
    StateType m_currState;
};

#endif // STATEMACHINE_H
