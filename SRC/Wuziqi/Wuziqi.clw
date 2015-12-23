; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CWuziqiDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Wuziqi.h"

ClassCount=3
Class1=CWuziqiApp
Class2=CWuziqiDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_WUZIQI_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Resource4=IDR_MENU1

[CLS:CWuziqiApp]
Type=0
HeaderFile=Wuziqi.h
ImplementationFile=Wuziqi.cpp
Filter=N

[CLS:CWuziqiDlg]
Type=0
HeaderFile=gameui\wuziqidlg.h
ImplementationFile=gameui\wuziqidlg.cpp
BaseClass=CDialog
LastObject=CWuziqiDlg
Filter=D
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=WuziqiDlg.h
ImplementationFile=WuziqiDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_WUZIQI_DIALOG]
Type=1
Class=CWuziqiDlg
ControlCount=4
Control1=IDC_BUTTON_TAKEBACK,button,1342242944
Control2=IDC_BUTTON_RESTART,button,1342242944
Control3=IDC_BUTTON_COMPUTERHELP,button,1342242944
Control4=IDC_BUTTON_LOST,button,1342242944

[MNU:IDR_MENU1]
Type=1
Class=CWuziqiDlg
Command1=ID_MENU_START
Command2=ID_MENU_TAKEBACK
Command3=ID_MENU_HELP
Command4=ID_MENU_LOST
Command5=ID_MENU_SAVE
Command6=ID_MENU_OPEN
Command7=ID_MENU_EXIT
Command8=ID_MENU_1
Command9=ID_MENU_2
Command10=ID_MENU_3
Command11=ID_MENU_BK4
Command12=ID_MENU_PLAYER
Command13=ID_MENU_PLAYERFIRST
Command14=ID_MENU_COMPUTERFIRST
Command15=IDC_MUSIC_1
Command16=IDC_MUSIC_2
Command17=IDC_MUSIC_3
Command18=IDC_MUSIC_CLOSE
Command19=IDC_HELP
Command20=ID_MENU_AB
CommandCount=20

