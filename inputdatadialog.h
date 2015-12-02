#ifndef INPUTDATADIALOG_H
#define INPUTDATADIALOG_H

#include <QDialog>
#include <vector>
#include "audiosignalspectrumwindow.h"

namespace Ui {
class InputDataDialog;
}

class InputDataDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InputDataDialog(QWidget *parent = 0);
    ~InputDataDialog();

    void generateData(int N, double lower_bound, double upper_bound);
private slots:
    void on_cancelButton_clicked();

    void on_okButton_clicked();

    void on_generateButton_clicked();

    void on_loadButton_clicked();

private:
    std::vector<signal_data> data;
    Ui::InputDataDialog *ui;
};

#endif // INPUTDATADIALOG_H
