QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    avltree.cpp \
    b_plus_tree.cpp \
    enterpmc.cpp \
    enterpricepoint.cpp \
    finaloutput.cpp \
    finaloutputpmc.cpp \
    hashmap.cpp \
    main.cpp \
    mainwindow.cpp \
    secondwindow.cpp \
    supplycurveeqn.cpp \
    timetaken.cpp \
    treenode.cpp

HEADERS += \
    avltree.h \
    b_plus_tree.h \
    enterpmc.h \
    enterpricepoint.h \
    finaloutput.h \
    finaloutputpmc.h \
    hashmap.h \
    mainwindow.h \
    secondwindow.h \
    supplycurveeqn.h \
    timetaken.h \
    treenode.h

FORMS += \
    enterpmc.ui \
    enterpricepoint.ui \
    finaloutput.ui \
    finaloutputpmc.ui \
    mainwindow.ui \
    secondwindow.ui \
    supplycurveeqn.ui \
    timetaken.ui

OTHER_FILES += \
Resources

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    C:/Users/Bruce Maddux/Desktop/COP3530/Data Sets/Resources

RESOURCES += \
    Resource.qrc
