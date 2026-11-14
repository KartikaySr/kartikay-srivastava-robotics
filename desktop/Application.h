#ifndef KARTIKAY_ROBOTICS_APPLICATION_H
#define KARTIKAY_ROBOTICS_APPLICATION_H

#include <QApplication>
#include <QIcon>
#include <rl/version.h>

inline void configureDesktopApplication()
{
    QApplication::setApplicationName("Kartikay Srivastava Robotics");
    QApplication::setOrganizationName("Kartikay Srivastava");
    QApplication::setApplicationVersion(RL_VERSION_STRING);
    QApplication::setWindowIcon(QIcon(":/branding/icon.ico"));
}

#endif
