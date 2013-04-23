#include "videostatemachine.h"

VideoStateMachine::VideoStateMachine(QObject *parent) :
    QObject(parent),
    sm(State_NoDisk)
{
#define BIND_A(func)    boost::bind(&VideoStateMachine::at_##func, this)
#define BIND_G(func)    boost::bind(&VideoStateMachine::gd_##func, this)

    sm.append(State_NoDisk, State_Stop, Event_Open, BIND_G(hasNoDisk), BIND_A(inputDisk));
    sm.append(State_Stop, State_Playing, Event_Play, BIND_G(hasDisk));
    sm.append(State_Stop, State_NoDisk, Event_Open, BIND_G(hasDisk), BIND_A(outputDisk));
    sm.append(State_Playing, State_Stop, Event_Stop);
    sm.append(State_Playing, State_Pause, Event_Pause);
    sm.append(State_Playing, State_NoDisk, Event_Open, 0, BIND_A(outputDisk));
    sm.append(State_Pause, State_Playing, Event_Pause);
    sm.append(State_Pause, State_Stop, Event_Stop);
    sm.append(State_Pause, State_NoDisk, Event_Open, 0, BIND_A(outputDisk));
}

void VideoStateMachine::eventTriger(Event event)
{
    if (sm.eventTriger(event)) {
        emit stateChanged(sm.currentState());
    }
}
