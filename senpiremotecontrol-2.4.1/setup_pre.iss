#define MyAppName "QRemoteControl-Server"
#define MyAppPublisher "Alexander R�ssler"
#define MyAppURL "http://qremote.org"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{793ECCC2-7229-4A4C-A89B-B4F02C86A2C5}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\{#MyAppName}
DefaultGroupName={#MyAppName}
LicenseFile={#MyAppSourceDir}gpl.txt
OutputDir={#MyAppDeploymentDir}
OutputBaseFilename={#MyAppSetupName}
SetupIconFile={#MyAppSourceDir}icons\qremotecontrol.ico
Compression=lzma
SolidCompression=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "basque"; MessagesFile: "compiler:Languages\Basque.isl"
Name: "brazilianportuguese"; MessagesFile: "compiler:Languages\BrazilianPortuguese.isl"
Name: "catalan"; MessagesFile: "compiler:Languages\Catalan.isl"
Name: "czech"; MessagesFile: "compiler:Languages\Czech.isl"
Name: "danish"; MessagesFile: "compiler:Languages\Danish.isl"
Name: "dutch"; MessagesFile: "compiler:Languages\Dutch.isl"
Name: "finnish"; MessagesFile: "compiler:Languages\Finnish.isl"
Name: "french"; MessagesFile: "compiler:Languages\French.isl"
Name: "german"; MessagesFile: "compiler:Languages\German.isl"
Name: "hebrew"; MessagesFile: "compiler:Languages\Hebrew.isl"
Name: "hungarian"; MessagesFile: "compiler:Languages\Hungarian.isl"
Name: "italian"; MessagesFile: "compiler:Languages\Italian.isl"
Name: "japanese"; MessagesFile: "compiler:Languages\Japanese.isl"
Name: "norwegian"; MessagesFile: "compiler:Languages\Norwegian.isl"
Name: "polish"; MessagesFile: "compiler:Languages\Polish.isl"
Name: "portuguese"; MessagesFile: "compiler:Languages\Portuguese.isl"
Name: "russian"; MessagesFile: "compiler:Languages\Russian.isl"
Name: "serbiancyrillic"; MessagesFile: "compiler:Languages\SerbianCyrillic.isl"
Name: "serbianlatin"; MessagesFile: "compiler:Languages\SerbianLatin.isl"
Name: "slovak"; MessagesFile: "compiler:Languages\Slovak.isl"
Name: "slovenian"; MessagesFile: "compiler:Languages\Slovenian.isl"
Name: "spanish"; MessagesFile: "compiler:Languages\Spanish.isl"
Name: "ukrainian"; MessagesFile: "compiler:Languages\Ukrainian.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "{#MyAppSetupDir}{#MyAppExeName}"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#MyAppSetupDir}D3DCompiler_43.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#MyAppSetupDir}icudt51.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#MyAppSetupDir}icuin51.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#MyAppSetupDir}icuuc51.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#MyAppSetupDir}libGLESv2.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#MyAppSetupDir}libEGL.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#MyAppSetupDir}Qt5Core.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#MyAppSetupDir}Qt5Gui.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#MyAppSetupDir}Qt5Network.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#MyAppSetupDir}Qt5Widgets.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#MyAppSetupDir}msvcr100.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#MyAppSetupDir}msvcp100.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#MyAppSetupDir}libeay32.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#MyAppSetupDir}ssleay32.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#MyAppSetupDir}\platforms\qminimal.dll"; DestDir: "{app}\platforms\"; Flags: ignoreversion
Source: "{#MyAppSetupDir}\platforms\qwindows.dll"; DestDir: "{app}\platforms\"; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

