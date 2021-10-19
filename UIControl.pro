#-------------------------------------------------
#
# Project created by QtCreator 2019-07-09T13:25:36
#
#-------------------------------------------------

QT       += core gui\
            network\
            sql\
            multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UIControl
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    BaseControl/cbmpbutton.cpp \
    BaseControl/cbmpstate.cpp \
    SecondWindow/csecondwindowdlg.cpp \
    SecondWindow/csecondwindowaimdlg.cpp \
    DataManager/cdatamanager.cpp \
    Comm/ccomtcpclient.cpp \
    Comm/ccomtcpserver.cpp \
    Database/cdatabase.cpp \
    Porotocol/cporotocol.cpp \
    BaseControl/cbmppointer.cpp \
    BaseControl/cbmpmovebutton.cpp \
    uicontroldefine.cpp \
    Comm/ccomcan.cpp \
    Comm/ccomudp.cpp \
    BaseControl/cimgcannon.cpp \
    BaseControl/cimgpointer.cpp \
    BaseControl/cimgstatearea.cpp \
    BaseControl/ccurveshow.cpp \
    BaseControl/cinputedit.cpp

HEADERS  += mainwindow.h \
    BaseControl/cbmpbutton.h \
    BaseControl/cbmpstate.h \
    SecondWindow/csecondwindowdlg.h \
    SecondWindow/csecondwindowaimdlg.h \
    DataManager/cdatamanager.h \
    UIControldefine.h \
    Comm/ccomtcpclient.h \
    Comm/ccomtcpserver.h \
    Database/cdatabase.h \
    Porotocol/cporotocol.h \
    BaseControl/cbmppointer.h \
    BaseControl/cbmpmovebutton.h \
    Comm/ccomcan.h \
    Comm/ccomudp.h \
    BaseControl/cimgcannon.h \
    BaseControl/cimgpointer.h \
    BaseControl/cimgstatearea.h \
    BaseControl/ccurveshow.h \
    BaseControl/cinputedit.h

FORMS    += mainwindow.ui \
    SecondWindow/csecondwindowdlg.ui \
    SecondWindow/csecondwindowaimdlg.ui
