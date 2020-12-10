QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    accountcreator.cpp \
    bankomat.cpp \
    cardcreator.cpp \
    creditrequestcreator.cpp \
    database.cpp \
    employee.cpp \
    investcreator.cpp \
    investout.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    manager.cpp \
    manager2.cpp \
    movemoneyfromcardtocard.cpp \
    payforcredit.cpp \
    signup.cpp

HEADERS += \
    accountcreator.h \
    bankomat.h \
    cardcreator.h \
    creditrequestcreator.h \
    database.h \
    employee.h \
    investcreator.h \
    investout.h \
    login.h \
    mainwindow.h \
    manager.h \
    manager2.h \
    movemoneyfromcardtocard.h \
    payforcredit.h \
    signup.h

FORMS += \
    accountcreator.ui \
    bankomat.ui \
    cardcreator.ui \
    creditrequestcreator.ui \
    employee.ui \
    investcreator.ui \
    investout.ui \
    login.ui \
    mainwindow.ui \
    manager.ui \
    manager2.ui \
    movemoneyfromcardtocard.ui \
    payforcredit.ui \
    signup.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
  resource.qrc
