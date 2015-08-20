; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTestSocketDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "TestSocket.h"

ClassCount=3
Class1=CTestSocketApp
Class2=CTestSocketDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_TESTSOCKET_DIALOG

[CLS:CTestSocketApp]
Type=0
HeaderFile=TestSocket.h
ImplementationFile=TestSocket.cpp
Filter=N

[CLS:CTestSocketDlg]
Type=0
HeaderFile=TestSocketDlg.h
ImplementationFile=TestSocketDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_SENDNUM

[CLS:CAboutDlg]
Type=0
HeaderFile=TestSocketDlg.h
ImplementationFile=TestSocketDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_TESTSOCKET_DIALOG]
Type=1
Class=CTestSocketDlg
ControlCount=21
Control1=IDCANCEL,button,1342242816
Control2=IDC_DATARECV,edit,1352728580
Control3=IDC_CLEANUP,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATE,edit,1350633600
Control6=IDC_DATASEND,edit,1350631552
Control7=IDC_SEND,button,1342242816
Control8=IDC_STATIC,static,1342308352
Control9=IDC_SERVERINFO,edit,1350633600
Control10=IDC_RECVNUM,edit,1350633600
Control11=IDC_STATIC,static,1342308352
Control12=IDC_RN,edit,1350631552
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_FREQUENCY,edit,1350631552
Control16=IDC_SFREQUENCY,edit,1350631552
Control17=IDC_STATIC,button,1342177287
Control18=IDC_APPLY,button,1342242816
Control19=IDC_SENDNUM,edit,1350631552
Control20=IDC_AUTOSEND,button,1342242816
Control21=IDC_STOP,button,1342242816

