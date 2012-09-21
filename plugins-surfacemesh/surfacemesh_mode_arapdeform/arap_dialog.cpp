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
    mode->connect(ui->anchorModes, SIGNAL(buttonClicked(int)), SLOT(setAcitveAnchorMode(int)));
    mode->connect(ui->distanceSlider, SIGNAL(valueChanged(int)), SLOT(setDistanceAnchors(int)));

    ui->anchorModes->setId(ui->manualAnchor, MANUAL_POINTS);
    ui->anchorModes->setId(ui->distanceAnchor, GEODESIC_DISTANCE);

    connect(ui->anchorModes, SIGNAL(buttonClicked(int)), SLOT(anchorModeChanged(int)));

}

void arap_dialog::anchorModeChanged(int newMode)
{
    switch((ANCHOR_MODE) newMode)
    {
    case MANUAL_POINTS:
        ui->distanceSlider->setEnabled(false);
        ui->anchorButton->setEnabled(true);
        break;

    case GEODESIC_DISTANCE:
        ui->distanceSlider->setEnabled(true);
        ui->anchorButton->setEnabled(false);
        break;
    }
}

arap_dialog::~arap_dialog()
{
    delete ui;
}
