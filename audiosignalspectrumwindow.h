#ifndef AUDIOSIGNALSPECTRUMWINDOW_H
#define AUDIOSIGNALSPECTRUMWINDOW_H

#include <QGraphicsScene>
#include "ui_audiosignalspectrumwindow.h"
#include <QPixmap>


struct signal_data
{
    double frequency_khz_;
    u_int8_t power_8bit_;
};

class AudioSignalSpectrumWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit AudioSignalSpectrumWindow(QWidget *parent = 0);
    
private slots:
    void on_input_data_action_triggered();
    
    void on_quit_action_triggered();
    
    void on_about_action_triggered();
    
private:
    void paintEvent(QPaintEvent *);
    QPixmap pixmap_;    
    Ui::AudioSignalSpectrumWindow ui;    
    void generateData(int N, double lower_bound, double upper_bound, std::vector<signal_data> *data);
    void drawColumn(QPainter &painter, signal_data data, int position, int count, int w, int h);
    void drawData(QPainter &painter, std::vector<signal_data> &data, int w, int h);
};

#endif // AUDIOSIGNALSPECTRUMWINDOW_H
