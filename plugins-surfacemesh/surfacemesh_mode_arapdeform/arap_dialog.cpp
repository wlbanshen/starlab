#include "arap_dialog.h"
#include "ui_arap_dialog.h"
#include "surfacemesh_mode_arapdeform.h"

arap_dialog::arap_dialog(surfacemesh_mode_arapdeform * m, QWidget *parent) : QDialog(parent), ui(new Ui::arap_dialog)
{
    ui->setupUi(this);

    /// Stay on top
    setWindowFlags(Qt::WindowStaysOnTopHint);

    this->mode = m;

    mode->connect(ui->controlButton, SIGNAL(clicked()), SLOT(setControlMode()));
    mode->connect(ui->anchorButton, SIGNAL(clicked()), SLOT(setAnchorMode()));
    mode->connect(ui->deformButton, SIGNAL(clicked()), SLOT(setDeformMode()));
    mode->connect(ui->numIterations, SIGNAL(valueChanged(int)), SLOT(setNumIterations(int)));
}

arap_dialog::~arap_dialog()
{
    delete ui;
}
