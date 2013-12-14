; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSimpleWall
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "arch.h"
LastPage=0

ClassCount=22
Class1=CArchApp
Class2=CAboutDlg
Class3=CArchDoc
Class4=CArchGL
Class5=CArchView
Class6=Cchair_type
Class7=Cchairtype
Class8=CCurvedWallDlg
Class9=FixtureDialog
Class10=GL3dView
Class11=CMainFrame
Class12=CPillarDlg
Class13=Csofatype
Class14=CStairDlg
Class15=CStraightWallDlg
Class16=Ctabletype
Class17=ViewFloorDialog

ResourceCount=18
Resource1=IDR_TBOBJECT
Resource2=IDD_DIALOG_TABLE
Resource3=IDR_TBRAPPMODE
Resource4=IDD_DIALOG_PILLAR
Resource5=IDD_DIALOG4
Resource6=IDD_DIALOG5
Resource7=IDD_WALL
Resource8=IDR_MAINFRAME
Resource9=IDD_FIXTURE
Resource10=IDD_DIALOG_STAIR
Resource11=IDD_DIALOG_CURVED_WALL
Resource12=IDD_DIALOG2
Resource13=IDR_TBRELEMENT
Class18=CCeilingdlg
Resource14=IDD_FLOOR_VIEW
Class19=CSimpleWall
Resource15=IDD_ABOUTBOX
Class20=CTabledlg
Resource16=IDD_DIALOG_STRAIGHT_WALL
Class21=CSpiralDlg
Resource17=IDD_DIALOG_CEILING
Class22=CSofadlg
Resource18=IDD_DIALOG_SOFA

[CLS:CArchApp]
Type=0
BaseClass=CWinApp
HeaderFile=Arch.h
ImplementationFile=Arch.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=Arch.cpp
ImplementationFile=Arch.cpp
LastObject=CAboutDlg

[CLS:CArchDoc]
Type=0
BaseClass=CDocument
HeaderFile=ArchDoc.h
ImplementationFile=ArchDoc.cpp
Filter=N
VirtualFilter=DC

[CLS:CArchGL]
Type=0
BaseClass=CDialog
HeaderFile=ArchGL.h
ImplementationFile=ArchGL.cpp

[CLS:CArchView]
Type=0
BaseClass=CScrollView
HeaderFile=ArchView.h
ImplementationFile=ArchView.cpp
Filter=C
VirtualFilter=VWC

[CLS:Cchair_type]
Type=0
BaseClass=CDialog
HeaderFile=chair_type.h
ImplementationFile=chair_type.cpp

[CLS:Cchairtype]
Type=0
BaseClass=CDialog
HeaderFile=chairtype.h
ImplementationFile=chairtype.cpp

[CLS:CCurvedWallDlg]
Type=0
BaseClass=CDialog
HeaderFile=CurvedWallDlg.h
ImplementationFile=CurvedWallDlg.cpp

[CLS:FixtureDialog]
Type=0
BaseClass=CDialog
HeaderFile=FixtureDialog.h
ImplementationFile=FixtureDialog.cpp

[CLS:GL3dView]
Type=0
BaseClass=CView
HeaderFile=GL3dView.h
ImplementationFile=GL3dView.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CPillarDlg]
Type=0
BaseClass=CDialog
HeaderFile=pillardlg.h
ImplementationFile=pillardlg.cpp

[CLS:Csofatype]
Type=0
BaseClass=CDialog
HeaderFile=sofatype.h
ImplementationFile=sofatype.cpp

[CLS:CStairDlg]
Type=0
BaseClass=CDialog
HeaderFile=StairDlg.h
ImplementationFile=StairDlg.cpp

[CLS:CStraightWallDlg]
Type=0
BaseClass=CDialog
HeaderFile=StraightWallDlg.h
ImplementationFile=StraightWallDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=CStraightWallDlg

[CLS:Ctabletype]
Type=0
BaseClass=CDialog
HeaderFile=tabletype.h
ImplementationFile=tabletype.cpp

[CLS:ViewFloorDialog]
Type=0
BaseClass=CDialog
HeaderFile=vfd.h
ImplementationFile=vfd.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=6
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308481
Control3=IDC_STATIC,static,1342308353
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308353

[DLG:IDD_ARCHGL_DIALOG]
Type=1
Class=CArchGL

[DLG:IDD_DIALOG4]
Type=1
Class=Cchair_type
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_CHAIR1,button,1342308361
Control4=IDC_CHAIR2,button,1342177289
Control5=IDC_CHAIR3,button,1342177289
Control6=IDC_CHAIR4,button,1342177289
Control7=IDC_CHAIR5,button,1342177289

[DLG:IDD_DIALOG3]
Type=1
Class=Cchairtype

[DLG:IDD_DIALOG_CURVED_WALL]
Type=1
Class=CCurvedWallDlg
ControlCount=18
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC_Preview,button,1073742727
Control4=IDC_STATIC,button,1342178055
Control5=IDC_STATIC,button,1342178055
Control6=IDC_STATIC,button,1342178055
Control7=IDC_RADIO_WALL_4,button,1342406665
Control8=IDC_RADIO_WALL_9,button,1342210057
Control9=IDC_RADIO_WALL_13,button,1342210057
Control10=IDC_RADIO_COL1,button,1342341129
Control11=IDC_RADIO_TEXTURE1,button,1342210057
Control12=IDC_RADIO_COL2,button,1342341129
Control13=IDC_RADIO_TEXTURE2,button,1342210057
Control14=IDC_STATIC_S1,button,1342177287
Control15=IDC_STATIC_S2,button,1342177287
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,button,1342178055

[DLG:IDD_FIXTURE]
Type=1
Class=FixtureDialog
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_PREVIEW,button,1342178055
Control4=IDC_BtnCHK,button,1342242816
Control5=IDC_LISTFIXTURE,listbox,1352728835

[DLG:IDD_DIALOG_PILLAR]
Type=1
Class=CPillarDlg
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC_PILLAR_PREVIEW,button,1342178055
Control4=IDC_BUTTON_COLOR,button,1342242816
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,button,1342177287
Control7=IDC_RADIO_TYPE_CYLINDER,button,1342308361
Control8=IDC_RADIO_TYPE_CUBIC,button,1342177289
Control9=IDC_RADIO_WIDTH_1,button,1342308361
Control10=IDC_RADIO_WIDTH_1andHalf,button,1342177289
Control11=IDC_RADIO_WIDTH_2,button,1342177289

[DLG:IDD_DIALOG2]
Type=1
Class=Csofatype
ControlCount=4
Control1=IDOK,button,1342275585
Control2=IDCANCEL,button,1342275584
Control3=IDC_stypeSTATIC,static,1342308352
Control4=IDC_stypeCOMBO1,combobox,1344340226

[DLG:IDD_DIALOG_STAIR]
Type=1
Class=CStairDlg
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC_Preview,button,1342178183
Control4=IDC_RADIO_WIDTH_2,button,1342406665
Control5=IDC_RADIO_WIDTH_3,button,1342210057
Control6=IDC_RADIO_WIDTH_4,button,1342210057
Control7=IDC_STATIC,button,1342178055
Control8=IDC_BUTTON_COLOR,button,1342242816

[DLG:IDD_DIALOG_STRAIGHT_WALL]
Type=1
Class=CStraightWallDlg
ControlCount=38
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC_Preview,button,1342178183
Control4=IDC_STATIC,button,1342178055
Control5=IDC_STATIC,button,1342178055
Control6=IDC_STATIC,button,1342178055
Control7=IDC_STATIC,button,1342178055
Control8=IDC_RADIO_WALL_4,button,1342406665
Control9=IDC_RADIO_WALL_9,button,1342210057
Control10=IDC_RADIO_WALL_13,button,1342210057
Control11=IDC_STATIC_DOOR,button,1342178055
Control12=IDC_STATIC_WINDOW,button,1342178055
Control13=IDC_RADIO_DOOR_2x7,button,1342406665
Control14=IDC_RADIO_DOOR_3x7,button,1342210057
Control15=IDC_RADIO_DOOR_4x7,button,1342210057
Control16=IDC_RADIO_WINDOW_2x3,button,1342406665
Control17=IDC_RADIO_WINDOW_3x3,button,1342210057
Control18=IDC_RADIO_WINDOW_3x4,button,1342210057
Control19=IDC_RADIO_WINDOW_4x4,button,1342210057
Control20=IDC_RADIO_COL1,button,1342341129
Control21=IDC_RADIO_TEXTURE1,button,1342210057
Control22=IDC_RADIO_COL2,button,1342341129
Control23=IDC_RADIO_TEXTURE2,button,1342210057
Control24=IDC_STATIC_S1,button,1342177287
Control25=IDC_STATIC_S2,button,1342177287
Control26=IDC_BTN_WINDOW_CLR,button,1342242816
Control27=IDC_CHECK_DOOR,button,1342242819
Control28=IDC_CHECK_WINDOW,button,1342242819
Control29=IDC_BTN_DOOR_CLR,button,1342242816
Control30=IDC_BTN_MOVE_LEFT,button,1342242816
Control31=IDC_BTN_MOVE_RIGHT,button,1342242816
Control32=IDC_SELECT_DOOR,button,1342312457
Control33=IDC_SELECT_WINDOW,button,1342181385
Control34=IDC_STATIC,button,1342178055
Control35=IDC_STATIC,static,1342308352
Control36=IDC_BASE_POINT,edit,1350631552
Control37=IDC_STATIC,static,1342308352
Control38=IDC_TOP_POINT,edit,1350631552

[DLG:IDD_DIALOG1]
Type=1
Class=Ctabletype

[DLG:IDD_FLOOR_VIEW]
Type=1
Class=ViewFloorDialog
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_FLOORNUM,edit,1350631426

[DLG:IDD_DIALOG_CEILING]
Type=1
Class=CCeilingdlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_CEILING_POINT,edit,1350631552
Control5=IDC_CEIL_COLOR,button,1342242816

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[TB:IDR_TBRAPPMODE]
Type=1
Class=?
Command1=ID_EDIT_SELECTELEMENT
Command2=ID_EDIT_DELETEELEMENT
Command3=ID_EDIT_MOVEELEMENT
Command4=ID_EDIT_ROTATEELEMENT
Command5=ID_EDIT_RESIZEELEMENT
Command6=ID_VIEW_2DVIEW
Command7=ID_VIEW_3DVIEW
Command8=ID_VIEW_VIEWFLOOR
Command9=ID_VIEW_NEWFLOOR
CommandCount=9

[TB:IDR_TBRELEMENT]
Type=1
Class=?
Command1=ID_BUILD_WALL
Command2=ID_BUILD_CURVEDWALL
Command3=ID_BUILD_PILLAR
Command4=ID_BUILD_STAIRS
Command5=ID_BUILD_CEIL
Command6=ID_BBUILD_SPIRALSTAIR
Command7=ID_BUILD_FIXTURE
CommandCount=7

[TB:IDR_TBOBJECT]
Type=1
Class=?
Command1=ID_OBJECT_TABLE
Command2=ID_OBJECT_CHAIR
Command3=ID_OBJECT_SOFA
CommandCount=3

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_SELECTELEMENT
Command11=ID_EDIT_MOVEELEMENT
Command12=ID_EDIT_ROTATEELEMENT
Command13=ID_EDIT_RESIZEELEMENT
Command14=ID_EDIT_DELETEELEMENT
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_VIEW_FLOOR
Command18=ID_VIEW_3DVIEW
Command19=ID_VIEW_2DVIEW
Command20=ID_BUILD_WALL
Command21=ID_BUILD_CURVEDWALL
Command22=ID_BUILD_PILLAR
Command23=ID_BUILD_STAIRS
Command24=ID_BUILD_BASEPLANE
Command25=ID_BUILD_CEILLING
Command26=ID_BUILD_FLOOR
Command27=ID_APP_ABOUT
CommandCount=27

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_PRINT
Command5=ID_FILE_SAVE
Command6=ID_EDIT_PASTE
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_DELETEELEMENT
Command9=ID_EDIT_CUT
Command10=ID_VIEW_2DVIEW
Command11=ID_VIEW_3DVIEW
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
Command14=ID_EDIT_COPY
Command15=ID_EDIT_PASTE
Command16=ID_EDIT_CUT
Command17=ID_EDIT_UNDO
CommandCount=17

[CLS:CCeilingdlg]
Type=0
HeaderFile=Ceilingdlg.h
ImplementationFile=Ceilingdlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CCeilingdlg

[DLG:IDD_WALL]
Type=1
Class=CSimpleWall
ControlCount=18
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_Base,edit,1350631552
Control4=IDC_Top,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_RADIO_Width,button,1342308361
Control8=IDC_RADIO6,button,1342177289
Control9=IDC_RADIO7,button,1342177289
Control10=IDC_STATIC,button,1342177287
Control11=IDC_STATIC,button,1342177287
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC_Preview1,button,1342178183
Control14=IDC_SideA,button,1342308361
Control15=IDC_T1,button,1342177289
Control16=IDC_SideB,button,1342308361
Control17=IDC_T2,button,1342177289
Control18=IDC_WallPreB,button,1342178183

[CLS:CSimpleWall]
Type=0
HeaderFile=SimpleWall.h
ImplementationFile=SimpleWall.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CSimpleWall

[DLG:IDD_DIALOG_TABLE]
Type=1
Class=CTabledlg
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_RADIO_table,button,1342308361
Control4=IDC_RADIO2,button,1342177289
Control5=IDC_RADIO3,button,1342177289
Control6=IDC_RADIO4,button,1342177289
Control7=IDC_RADIO5,button,1342177289

[CLS:CTabledlg]
Type=0
HeaderFile=Tabledlg.h
ImplementationFile=Tabledlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CTabledlg
VirtualFilter=dWC

[DLG:IDD_DIALOG5]
Type=1
Class=CSpiralDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_SPIRAL_COLOR,button,1342242816

[CLS:CSpiralDlg]
Type=0
HeaderFile=SpiralDlg.h
ImplementationFile=SpiralDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CSpiralDlg
VirtualFilter=dWC

[DLG:IDD_DIALOG_SOFA]
Type=1
Class=CSofadlg
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_RADIO_sofa,button,1342308361
Control4=IDC_RADIO8,button,1342177289
Control5=IDC_RADIO9,button,1342177289
Control6=IDC_RADIO10,button,1342177289
Control7=IDC_RADIO11,button,1342177289

[CLS:CSofadlg]
Type=0
HeaderFile=Sofadlg.h
ImplementationFile=Sofadlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CSofadlg

