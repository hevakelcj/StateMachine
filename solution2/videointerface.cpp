#include "videointerface.h"
#include "ui_videointerface.h"

VideoInterface::VideoInterface(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VideoInterface)
{
    ui->setupUi(this);

    connect(&vsm, SIGNAL(stateChangedSignal(VideoState*)), this, SLOT(stateChangedSlot(VideoState*)));
    connect(this, SIGNAL(eventTrigerSignal(Event)), &vsm, SLOT(eventTriger(Event)));
}

VideoInterface::~VideoInterface()
{
    delete ui;
}

void VideoInterface::stateChangedSlot(VideoState *state)
{
    ui->label_State->setText(state->text());
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
