#ifndef KARTIKAY_ROBOTICS_APPLICATION_H
#define KARTIKAY_ROBOTICS_APPLICATION_H

#include <QApplication>
#include <QIcon>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QSettings>
#include <rl/version.h>

inline void configureDesktopApplication()
{
    QApplication::setApplicationName("Kartikay Srivastava Robotics");
    QApplication::setOrganizationName("Kartikay Srivastava");
    QApplication::setApplicationVersion(RL_VERSION_STRING);
    QApplication::setWindowIcon(QIcon(":/branding/icon.ico"));
}

inline QString desktopBinaryDirectory()
{
    QDir directory(QApplication::applicationDirPath());
#ifdef Q_OS_MAC
    if (directory.dirName() == "MacOS")
        for (int level = 0; level < 3; ++level) directory.cdUp();
#endif
    return directory.absolutePath();
}

inline QString exampleDirectory()
{
    const QStringList candidates = QStringList()
        << QSettings().value("examplesDirectory").toString()
        << QDir(desktopBinaryDirectory()).filePath("../share/rl-" RL_VERSION_STRING "/examples")
        << QString::fromUtf8(RL_DESKTOP_EXAMPLES);
    for (const QString& path : candidates)
        if (!path.isEmpty() && QDir(path).exists("rlsg"))
            return QDir(path).absolutePath();
    return QString();
}

inline QStringList& desktopArguments()
{
    static QStringList arguments = QApplication::arguments();
    return arguments;
}

inline bool prepareRobotArguments(bool legacyKinematics = false)
{
    QStringList& arguments = desktopArguments();
    if (arguments.size() == 1 && !exampleDirectory().isEmpty())
        arguments << QDir(exampleDirectory()).filePath("rlsg/unimation-puma560_boxes.xml")
                  << QDir(exampleDirectory()).filePath(legacyKinematics ? "rlkin/unimation-puma560.xml" : "rlmdl/unimation-puma560.xml");
    if (arguments.size() < 2)
    {
        QString scene = QFileDialog::getOpenFileName(nullptr, "Choose a robot scene", exampleDirectory(), "Robot scenes (*.xml)");
        if (scene.isEmpty()) return false;
        arguments << scene;
    }
    if (arguments.size() < 3)
    {
        QString model = QFileDialog::getOpenFileName(nullptr, "Choose the matching robot model", exampleDirectory(), "Robot models (*.xml)");
        if (model.isEmpty()) return false;
        arguments << model;
    }
    return true;
}

#endif
