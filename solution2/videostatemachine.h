#ifndef VideoStateMachine_H
#define VideoStateMachine_H

#include <QObject>
#include "StateMachine.h"
#include <QString>

enum Event {
    Event_Play,
    Event_Stop,
    Event_Pause,
    Event_Open
};

class VideoState : public State
{
public:
    VideoState(QString text)
        : m_text(text) {}

    QString text() {return m_text;}

private:
    QString m_text;
};

// We need print information while enter and leave this state
class PlayState : public VideoState
{
public:
    PlayState() : VideoState("Playing") {}
protected:
    virtual void enter();
    virtual void exit();
};

class VideoStateMachine : public QObject
{
    Q_OBJECT
public:
    explicit VideoStateMachine(QObject *parent = 0);
    ~VideoStateMachine();

signals:
    void stateChangedSignal(VideoState *newState);

public slots:
    void eventTriger(Event event);

protected:
    bool gd_hasDisk() { return diskExist; }
    bool gd_hasNoDisk() { return !diskExist; }

    void at_inputDisk() { diskExist = true; }
    void at_outputDisk() { diskExist = false; }

private:
    VideoState *state_noDisk;
    VideoState *state_playing;
    VideoState *state_Stop;
    VideoState *state_Pause;

    StateMachine sm;

    bool diskExist;
};

#endif // VideoStateMachine_H
