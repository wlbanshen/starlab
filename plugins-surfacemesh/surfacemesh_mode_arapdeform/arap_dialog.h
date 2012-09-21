#pragma once
#include <QDialog>
class surfacemesh_mode_arapdeform;
namespace Ui { class arap_dialog; }

class arap_dialog: public QDialog{
    Q_OBJECT
public:
    explicit arap_dialog(surfacemesh_mode_arapdeform * m = 0, QWidget *parent = 0);
    ~arap_dialog();
private:
    Ui::arap_dialog *ui;
    surfacemesh_mode_arapdeform *mode;
};
