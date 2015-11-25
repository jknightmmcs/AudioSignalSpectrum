#include "audiosignalspectrumwindow.h"
#include <QPainter>
#include <QMessageBox>
#include <vector>

AudioSignalSpectrumWindow::AudioSignalSpectrumWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ui.setupUi(this);    
}

void AudioSignalSpectrumWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //Moved from 0, 0 by the height of the menu bar
    painter.drawPixmap(0, ui.menuBar->height(), pixmap_);
}

void AudioSignalSpectrumWindow::generateData(int N, double lower_bound, double upper_bound, std::vector<signal_data>* data)
{
    data -> clear();
    for(int i = 0; i < N; i++)
    {
        signal_data single_data = {lower_bound + i * (upper_bound - lower_bound) / N, rand() % 256 };
        data->push_back(single_data);
    }
}

void AudioSignalSpectrumWindow::drawColumn(QPainter& painter, signal_data data, int position, int count, int w, int h)
{
    QTransform transform;
    transform.translate(0, h);
    transform.scale(1, -1);
    painter.setWorldTransform(transform);
        
    int values_per_block = 8;
    int block_count = 256 / values_per_block;
    int actual_h = h - ui.menuBar->height();
            
    int height_shift = 30;
    
    int block_space_height = actual_h / block_count;
    int block_space_shift = block_space_height * 0.3;    
    int block_height = block_space_height - block_space_shift / 2;
            
    int space_width = w / (double)count;
    int space_shift = space_width * 0.1;
    int width = space_width - space_shift;    
    int draw_x = space_width * position + space_shift / 2;        
    
    int block = data.power_8bit_ / values_per_block;        
    for(int i = 0; i < block_count; i++)
    {            
        Qt::GlobalColor colorFill = Qt::red;
        if (i < block_count - 3) colorFill = Qt::green;
        Qt::GlobalColor colorEmpty = Qt::darkRed;
        if (i < block_count - 3) colorEmpty = Qt::darkGreen;

        if (i <= block && data.power_8bit_ != 0)
        {            
                painter.fillRect(draw_x, height_shift + block_space_height * i, width, block_height, colorFill);
        }
        else
        {            
                painter.fillRect(draw_x, height_shift + block_space_height * i, width, block_height, colorEmpty);
        }
    }        
    
    transform.reset();
    painter.setWorldTransform(transform);
    QRect rect = QRect(draw_x,  h - height_shift, space_width, height_shift);    
    painter.drawText(rect, Qt::AlignCenter, QString::number(data.frequency_khz_, 'f', 2) + " kHz ");
}

void AudioSignalSpectrumWindow::drawData(QPainter& painter, std::vector<signal_data>& data, int w, int h)
{
    for(int i = 0; i < data.size(); i++)
        drawColumn(painter, data[i], i, data.size(), w, h);
}

void AudioSignalSpectrumWindow::on_input_data_action_triggered()
{    
    pixmap_ = QPixmap(ui.centralWidget->width(), ui.centralWidget->height());    
    pixmap_.fill(/*white*/);
    QPainter painter(&pixmap_);
    
    std::vector<signal_data> data;
    generateData(15, 10, 100, &data);
    std::sort(data.begin(), data.end(), [](signal_data& a, signal_data& b) 
        { return a.frequency_khz_ < b.frequency_khz_; });    
    drawData(painter, data, pixmap_.width(), pixmap_.height());
    
    repaint();
}

void AudioSignalSpectrumWindow::on_quit_action_triggered()
{
    qApp->exit(0);
}

void AudioSignalSpectrumWindow::on_about_action_triggered()
{
    QMessageBox box;
    box.setWindowTitle("О программе");
    box.setText("Демонстрация спектра звукового сигнала.\nАвтор: Леонтьев Георгий, группа КН, 2 год магистратуры");    
    box.setIcon(QMessageBox::Icon::Information);
    box.exec();
}
