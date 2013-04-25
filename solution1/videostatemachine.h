#ifndef VideoStateMachine_H
#define VideoStateMachine_H

#include <QObject>
#include "statemachine.hpp"

enum VideoState {
    State_NoDisk,
    State_Playing,
    State_Stop,
    State_Pause
};

enum Event {
    Event_Play,
    Event_Stop,
    Event_Pause,
    Event_Open
};

class VideoStateMachine : public QObject
{
    Q_OBJECT
public:
    explicit VideoStateMachine(QObject *parent = 0);
    
signals:
    void stateChanged(VideoState newState);

public slots:
    void eventTriger(Event event);

protected:
    bool gd_hasDisk() { return diskExist; }
    bool gd_hasNoDisk() { return !diskExist; }

    void at_inputDisk() { diskExist = true; }
    void at_outputDisk() { diskExist = false; }

private:
    StateMachine<VideoState, Event> sm;
    bool diskExist;
};

#endif // VideoStateMachine_H
