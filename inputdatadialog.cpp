#include <fstream>
#include <sstream>
#include <QFileDialog>
#include "inputdatadialog.h"
#include "ui_inputdatadialog.h"

InputDataDialog::InputDataDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputDataDialog)
{
    ui->setupUi(this);
}

InputDataDialog::~InputDataDialog()
{
    delete ui;
}

void InputDataDialog::generateData(int N, double lower_bound, double upper_bound)
{
    data.clear();
    ui->powerEdit->clear();
    ui->frequencyEdit->clear();
    for(int i = 0; i < N; i++)
    {
        signal_data single_data = {lower_bound + i * (upper_bound - lower_bound) / N, rand() % 256 };
        data.push_back(single_data);
        ui->powerEdit->setText(ui->powerEdit->toPlainText() + " " + QString::number(data[i].power_8bit_));
        ui->frequencyEdit->setText(ui->frequencyEdit->toPlainText() + " " + QString::number(data[i].frequency_khz_));
    }
}

void InputDataDialog::on_cancelButton_clicked()
{
    this->reject();
}

void InputDataDialog::on_okButton_clicked()
{
    if (data.size() > 0)
    {
        ((AudioSignalSpectrumWindow*)(this->parent()))->setData(this->data);
        this->accept();
    }
    else this->reject();
}

void InputDataDialog::on_generateButton_clicked()
{
    generateData(10, 10, 100);
}

void InputDataDialog::on_loadButton_clicked()
{
    QString fname = QFileDialog::getOpenFileName(this,
             tr("Открыть файл с описанием спектра"), "", tr("txt Files (*.txt)"));
    if (fname == "")
        return;
    std::ifstream ifs(fname.toStdString());
    data.clear();
    int N;
    ifs >> N;
    std::string tmp;
    std::getline(ifs, tmp);
    data.resize(N);
    std::string powers, frequencies;
    std::getline(ifs, powers);
    std::getline(ifs, frequencies);
    std::istringstream ips(powers);
    std::istringstream ifrs(frequencies);
    for(int i = 0; i < N; i++)
    {
        int tmp_val;
        ips >> tmp_val;
        data[i].power_8bit_ = tmp_val;
        ifrs >> data[i].frequency_khz_;
        ui->powerEdit->setText(ui->powerEdit->toPlainText() + " " + QString::number(data[i].power_8bit_));
        ui->frequencyEdit->setText(ui->frequencyEdit->toPlainText() + " " + QString::number(data[i].frequency_khz_));
    }
}
