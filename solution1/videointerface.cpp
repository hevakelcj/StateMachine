#include "videointerface.h"
#include "ui_videointerface.h"

VideoInterface::VideoInterface(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VideoInterface)
{
    ui->setupUi(this);

    connect(&vsm, SIGNAL(stateChanged(VideoState)), this, SLOT(stateChangedSlot(VideoState)));
    connect(this, SIGNAL(eventTrigerSignal(Event)), &vsm, SLOT(eventTriger(Event)));
}

VideoInterface::~VideoInterface()
{
    delete ui;
}

void VideoInterface::stateChangedSlot(VideoState state)
{
    QString tmp;
    switch (state) {
    case State_NoDisk:
        tmp = "No Disk";
        break;
    case State_Stop:
        tmp = "Stop";
        break;
    case State_Playing:
        tmp = "Playing";
        break;
    case State_Pause:
        tmp = "Pause";
        break;
    default:;
    }
    ui->label_State->setText(tmp);
}

void VideoInterface::on_pushButton_Open_clicked()
{
    eventTrigerSignal(Event_Open);
}

void VideoInterface::on_pushButton_Stop_clicked()
{
    eventTrigerSignal(Event_Stop);
}

void VideoInterface::on_pushButton_Play_clicked()
{
    eventTrigerSignal(Event_Play);
}

void VideoInterface::on_pushButton_Pause_clicked()
{
    eventTrigerSignal(Event_Pause);
}
