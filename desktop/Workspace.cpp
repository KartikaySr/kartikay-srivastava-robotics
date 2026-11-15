#include "Application.h"
#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QProcess>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>

struct Tool
{
    const char* title;
    const char* description;
    const char* executable;
    const char* scene;
    const char* model;
    const char* guidance;
};

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    configureDesktopApplication();
    QWidget window;
    window.setWindowTitle("Kartikay Srivastava Robotics");
    window.resize(1000, 850);
    window.setMinimumSize(680, 560);
    window.setStyleSheet(
        "QWidget { background: #f3f6f8; color: #142c3e; font-size: 14px; }"
        "QFrame#card { background: white; border: 1px solid #d4dfe5; border-radius: 12px; }"
        "QFrame#card QLabel { background: transparent; border: none; }"
        "QLabel#heading { font-size: 32px; font-weight: bold; }"
        "QLabel#title { font-size: 20px; font-weight: bold; }"
        "QLabel#secondary { color: #4c6473; }"
        "QPushButton { background: #087e80; color: white; padding: 10px 16px; border: 2px solid transparent; border-radius: 6px; font-weight: bold; }"
        "QPushButton:hover { background: #086769; }"
        "QPushButton:focus { border-color: #142c3e; }"
        "QPushButton:disabled { background: #d4dfe5; color: #4c6473; }"
        "QPushButton#secondary { background: #e8f1f3; color: #15575d; }"
        "QPushButton#secondary:hover { background: #d5e6e9; }");
    auto* outer = new QVBoxLayout(&window);
    outer->setContentsMargins(28, 24, 28, 20);
    outer->setSpacing(16);
    auto* heading = new QLabel("Robotics workspace");
    heading->setObjectName("heading");
    outer->addWidget(heading);
    outer->addWidget(new QLabel("Open a robot, explore its movement, and plan a path."));
    auto* status = new QLabel("Start with an included example, or open your own files.");
    status->setWordWrap(true);
    status->setObjectName("secondary");
    outer->addWidget(status);
    auto* scroll = new QScrollArea;
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);
    auto* content = new QWidget;
    auto* grid = new QGridLayout(content);
    grid->setContentsMargins(0, 0, 8, 0);
    grid->setSpacing(16);
    const Tool tools[] = {
        {"Robot kinematics", "Move the arm's joints and inspect the tool position.", "rlCoachMdl", "rlsg/unimation-puma560_boxes.xml", "rlmdl/unimation-puma560.xml", "Edit Joint positions to move the arm. Tool pose shows its position and orientation."},
        {"Dynamics simulator", "Explore how a robot responds to joint torque commands.", "rlSimulator", "rlsg/unimation-puma560_boxes.xml", "rlmdl/unimation-puma560.xml", "Use Simulation controls to start or pause. Joint positions, velocities and torques show the robot state. A controller can send torque commands on TCP port 11235."},
        {"Motion planner", "Find a path between start and goal positions around obstacles.", "rlPlanDemo", "rlplan/unimation-puma560_boxes_rrtConCon.mdl.xml", "", "The example includes start and goal positions. Use the planner controls to calculate a path. Drag in the 3D view to inspect the scene."},
        {"Collision inspector", "Check robot geometry for contact and separation.", "rlCollisionDemo", "rlsg/unimation-puma560_boxes.xml", "", "Select bodies to inspect collision and distance results. Available queries depend on the collision engine."},
        {"Rotation converter", "Convert between Euler angles, matrices and quaternions.", "rlRotationConverterDemo", "", "", "Edit a value in an Input table. Output tables update to show equivalent rotations."},
        {"3D model viewer", "Open and inspect VRML and Open Inventor geometry.", "wrlview", "", "", "Use File > Open to choose a model. Drag to rotate, and use View to change the camera."}
    };
    for (int index = 0; index < 6; ++index)
    {
        const Tool tool = tools[index];
        auto* card = new QFrame;
        card->setObjectName("card");
        auto* layout = new QVBoxLayout(card);
        layout->setContentsMargins(20, 18, 20, 18);
        layout->setSpacing(12);
        auto* title = new QLabel(tool.title);
        title->setObjectName("title");
        layout->addWidget(title);
        auto* description = new QLabel(tool.description);
        description->setWordWrap(true);
        description->setMinimumHeight(42);
        layout->addWidget(description);
        auto* open = new QPushButton(*tool.scene ? "Open Puma 560 example" : "Open tool");
        open->setAccessibleName(QString("Open %1").arg(tool.title));
        layout->addWidget(open);
        const QString executable = QDir(desktopBinaryDirectory()).filePath(QString(tool.executable)
#ifdef Q_OS_WIN
            + ".exe"
#endif
        );
        auto launch = [&, tool, executable](bool custom) {
            QStringList arguments;
            if (*tool.scene)
            {
                QString scene = custom ? QFileDialog::getOpenFileName(&window,
                    QString("Open %1 file").arg(*tool.model ? "scene" : "scenario"), exampleDirectory(), "Robot files (*.xml)")
                    : QDir(exampleDirectory()).filePath(tool.scene);
                if (custom && scene.isEmpty()) return;
                QString model;
                if (*tool.model)
                {
                    model = custom ? QFileDialog::getOpenFileName(&window, "Open matching robot model", exampleDirectory(), "Robot models (*.xml)")
                                   : QDir(exampleDirectory()).filePath(tool.model);
                    if (custom && model.isEmpty()) return;
                }
                if (!QFileInfo(scene).isFile() || (*tool.model && !QFileInfo(model).isFile()))
                {
                    QMessageBox::warning(&window, "Example files unavailable", "Choose the examples folder below, or use Open your files to select a scene and matching robot model.");
                    return;
                }
                arguments << scene;
                if (*tool.model) arguments << model;
            }
#ifdef RL_DESKTOP_ENGINE
            if (QString(tool.executable) == "rlPlanDemo" || QString(tool.executable) == "rlCollisionDemo")
                arguments.prepend("--engine=" RL_DESKTOP_ENGINE);
#endif
            if (!QProcess::startDetached(executable, arguments))
                QMessageBox::critical(&window, "Could not open tool", "The application could not start. Keep the workspace beside the installed tools in the bin folder and check that runtime dependencies are installed.");
            else
                status->setText(QString("Opened %1. %2").arg(tool.title, tool.guidance));
        };
        QObject::connect(open, &QPushButton::clicked, &window, [launch]() { launch(false); });
        if (*tool.scene)
        {
            auto* custom = new QPushButton("Open your files…");
            custom->setObjectName("secondary");
            custom->setAccessibleName(QString("Open custom files in %1").arg(tool.title));
            layout->addWidget(custom);
            QObject::connect(custom, &QPushButton::clicked, &window, [launch]() { launch(true); });
        }
        layout->addStretch();
        if (!QFileInfo(executable).isExecutable())
        {
            for (QPushButton* button : card->findChildren<QPushButton*>()) button->setEnabled(false);
            layout->addWidget(new QLabel("This tool is unavailable in this installation."));
        }
        grid->addWidget(card, index / 2, index % 2);
    }
    scroll->setWidget(content);
    outer->addWidget(scroll, 1);
    auto* footer = new QHBoxLayout;
    auto* examples = new QPushButton("Choose examples folder…");
    examples->setObjectName("secondary");
    footer->addWidget(examples);
    QObject::connect(examples, &QPushButton::clicked, &window, [&]() {
        QString path = QFileDialog::getExistingDirectory(&window, "Choose the examples folder", exampleDirectory());
        if (path.isEmpty()) return;
        if (!QDir(path).exists("rlsg") || !QDir(path).exists("rlmdl") || !QDir(path).exists("rlplan"))
        {
            QMessageBox::warning(&window, "Choose the examples root", "Select the folder containing rlsg, rlmdl and rlplan.");
            return;
        }
        QSettings().setValue("examplesDirectory", path);
        status->setText("Examples folder updated. You can now open an included robot example.");
    });
    footer->addStretch();
    auto* about = new QPushButton("Help && credits");
    about->setObjectName("secondary");
    footer->addWidget(about);
    QObject::connect(about, &QPushButton::clicked, &window, [&]() {
        QMessageBox::information(&window, "Kartikay Srivastava Robotics",
            "Developed and maintained by Kartikay Srivastava.\n\nStart with Robot kinematics to explore joint movement. Use the mouse to rotate the 3D view and the wheel to zoom. Each tool opens in its own window.\n\nCustom scenes and models must describe the same robot. Simulation controllers can connect over TCP.\n\nBased on Robotics Library. Original contributors include Markus Rickert, Andre Gaschler and Arne Sieverling. See CONTRIBUTORS.md and LICENSE.md for full credits and notices.");
    });
    outer->addLayout(footer);
    window.show();
    return app.exec();
}
