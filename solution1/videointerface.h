#ifndef VIDEOINTERFACE_H
#define VIDEOINTERFACE_H

#include <QDialog>
#include "videostatemachine.h"

namespace Ui {
class VideoInterface;
}

class VideoInterface : public QDialog
{
    Q_OBJECT
    
public:
    explicit VideoInterface(QWidget *parent = 0);
    ~VideoInterface();
    
signals:
    void eventTrigerSignal(Event);

protected slots:
    void stateChangedSlot(VideoState state);

    void on_pushButton_Open_clicked();
    void on_pushButton_Stop_clicked();
    void on_pushButton_Play_clicked();
    void on_pushButton_Pause_clicked();

private:
    Ui::VideoInterface *ui;
    VideoStateMachine vsm;
};

#endif // VIDEOINTERFACE_H
