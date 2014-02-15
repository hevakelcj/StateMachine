#include "videostatemachine.h"
#include <boost/bind.hpp>
#include <iostream>

void PlayState::enter()
{
    std::cout << "Start playing" << std::endl;
}

void PlayState::exit()
{
    std::cout << "Stop play" << std::endl;
}

VideoStateMachine::VideoStateMachine(QObject *parent) :
    QObject(parent)
{
    state_noDisk    = new VideoState("No Disk");
    state_playing   = new PlayState;
    state_Stop      = new VideoState("Stop");
    state_Pause     = new VideoState("Pause");

    sm.setOriginState(state_noDisk);

#define BIND_A(func)    boost::bind(&VideoStateMachine::at_##func, this)
#define BIND_G(func)    boost::bind(&VideoStateMachine::gd_##func, this)

    state_noDisk->addTransition(Event_Open, state_Stop, BIND_G(hasNoDisk), BIND_A(inputDisk));
    state_Stop->addTransition(Event_Play, state_playing, BIND_G(hasDisk));
    state_Stop->addTransition(Event_Open, state_noDisk, BIND_G(hasDisk), BIND_A(outputDisk));
    state_playing->addTransition(Event_Stop, state_Stop);
    state_playing->addTransition(Event_Pause, state_Pause);
    state_playing->addTransition(Event_Open, state_noDisk, 0, BIND_A(outputDisk));
    state_Pause->addTransition(Event_Pause, state_playing);
    state_Pause->addTransition(Event_Stop, state_Stop);
    state_Pause->addTransition(Event_Open, state_noDisk, 0, BIND_A(outputDisk));
}

VideoStateMachine::~VideoStateMachine()
{
    delete state_noDisk;
    delete state_Stop;
    delete state_playing;
    delete state_Pause;
}

void VideoStateMachine::eventTriger(Event event)
{
    if (sm.acceptEvent(event) == StateMachine::Changed) {
        emit stateChangedSignal(static_cast<VideoState*>(sm.getCurrentState()));
    }
}
