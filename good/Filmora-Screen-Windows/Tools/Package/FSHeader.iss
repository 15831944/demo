;FilmoraScrn֮Ԥ���弰���ô����ļ�

#define AppName "Wondershare Filmora Scrn"
#define OldAppName "Wondershare Filmora Scrn"
#define AppPath "Wondershare\Filmora Scrn"
;#define JpAppName "Wondershare Filmora �ӻ�����"
;#define JpAppPath "Wondershare\Filmora �ӻ�����"
#define NewExeName "FSRecorder.exe"
;#define ResourceInstallExeName "EffectStore.exe"
;#define ExeName "FilmoraScreen.exe"
#define ProductID "3235"
#define ProductName "Filmora Scrn"
#define ProductShortName "Filmora Scrn"
#define ConfigName "FilmoraScrn.ini"
#define UpdateRegisterConfigName "UpdateRegister.ini"
#define CrashReportConfigName "CrashReport.ini"
;#define RegisterPath "SOFTWARE\Wondershare\Filmora Scrn"

;��ַ���
#define UpdatePage "http://cbs.wondershare.com/go.php?m=upgrade_info&pid=%s&version=%s&email=%s"
#define EmailServerURL "http://api.wondershare.com/interface.php?m=smtpinfo"
;Affiliate���ư汾֮��������
#define AgentPage "https://www.regnow.com/softsell/nph-softsell.cgi?item=15969-115&affiliate=%s"

;ע�����...62088607-14102045-12206945
#define SGUID "{{79B718BE-67C9-4B30-A9AD-6BB96ED6AFF7}"
#define RegKeyN "924839719"
#define RegKeyD "19332601"

;Size&Version��
#ifdef CPUX64
#define AppSize FileSize("..\..\bin\x64\Release\FSRecorder.exe");
#define AppVersion GetFileVersion(AddBackslash(SourcePath) + "..\..\bin\x64\Release\FSRecorder.exe")
#else
#define AppSize FileSize("..\..\bin\x86\Release\FSRecorder.exe");
#define AppVersion GetFileVersion(AddBackslash(SourcePath) + "..\..\bin\x86\Release\FSRecorder.exe")
#endif
;�����ź�
#define AppMutex "Wondershare Filmora Scrn"
#define OutputName "Filmora Scrn"
;��װͼƬ
#define WizardImage "WizardImage.bmp"

;ע����̽ڵ�
#define ProjectExt ".wfsproj"
#define ProjNodeName "WFSFile"
;#define ResNodeName "fmrespack"

;������ע�����
#define Publisher "Wondershare"
;************ CBS ƽ̨�ͻ��˳�������
#define CBSHelperAppName "Wondershare Helper Compact"
#define CBSHelperExeName CBSHelperAppName + ".exe"

;����һ�����ʵ�ֹ�沿������Ϣ����Ĳ�Ʒ
#define CBSHelperShortExeName "WSHelper.exe"

;xp�밲װWinBurn Engine
#define IMApiXPSrv "IMAPI_XP_SRV2003_x86.exe"

;�����̶������...
;���������ļ�
#define MyAppCustomizedFileName "Customization.xml"
;���Ƹ�����̬��
#define ProductInfoManagerDLL "WSUtilities_Setup.dll"

[code]

const
  CSIDL_PERSONAL     = $0005;
  WM_CLOSE           = $0010;

var
  //�Ƿ����°�װ
  g_overInstall: Boolean;
  //�����Զ�������ȡ֮ǰע����
  g_regMail, g_regCode: string;

type
//  TGUID = record
//    D1: LongWord;
//    D2: Word;
//    D3: Word;
//    D4: array[0..7] of Byte;
//  end;
  pchar = pansichar;
  //��װ, ж��, ע��, ��������
  TCBSProcessType = (cptInstall, cptUnInstall, cptRegister, cptOnlineUpdate);
  
//�����̶������
function InstallCustomized(const ALangName, AExeFileName, AExtractedConfigFile, AInstalledConfigFile,APublisherName,
  AProductName: PAnsichar):BOOL;  external 'InnoInstallProcessAllA@files:{#ProductInfoManagerDLL} stdcall delayload';

function UnInstallCustomized(const ALangName, AInstalledConfigFile, APublisherName,
  AProductName: PAnsichar):BOOL; external 'InnoUnInstallProcessAllA@{app}\{#ProductInfoManagerDLL} stdcall uninstallonly';

function CoCreateGuid(var Guid: TGUID):integer; external 'CoCreateGuid@ole32.dll stdcall';
procedure SHChangeNotify(wEventId: Longint; uFlags: UINT; dwItem1, dwItem2: Longint);
external 'SHChangeNotify@shell32.dll stdcall';

function ShellExecute(hWnd: Integer; Operation, FileName, Parameters,
  Directory: pchar; ShowCmd: Integer): Integer;
external 'ShellExecuteA@shell32.dll stdcall';


//���ش�����֮��������
function WSOpenURLI(pszURL: PChar; nOpenMode: Integer): Boolean;
external 'WSOpenURLA@files:WSUtilities_Setup.dll stdcall setuponly';
function WSOpenURLU(pszURL: PChar; nOpenMode: Integer): Boolean;
external 'WSOpenURLA@{app}\WSUtilities_Setup.dll stdcall uninstallonly';

function GetFileMD5(const pFileName: PChar; szBuf : array of Char): BOOL;
external 'GetFileMD5@files:WS_Log_Setup.dll stdcall';

function GetFileMD5Ex(const pFileName: PChar): PChar;
external 'GetFileMD5Ex@files:WS_Log_Setup.dll stdcall';

//function PopFileFromReserved(sPatchFile, sOverlayFile: PChar): Boolean;
//external 'PopFileFromReserved@files:WSOverlay.dll stdcall';

//�����̶��ƹ���
function PopFileFromReservedA(const APatchedFileName, AOverlayFileName: String):BOOL; external 'PopFileFromReservedW@files:{#ProductInfoManagerDLL} stdcall delayload';
function LoadCustomizeXMLFileA(const AConfigFileName: PAnsiChar):BOOL; external 'LoadCustomizeXMLFileA@files:{#ProductInfoManagerDLL} stdcall delayload';
function ReadCustomizeBoolInfoA(const AInfoName, ALangName: PAnsiChar):BOOL; external 'ReadCustomizeBoolInfoA@files:{#ProductInfoManagerDLL} stdcall delayload';
function ReadCustomizeInfoA(const AInfoName, ALangName: PAnsichar; AValue: PAnsiChar; AValueLen: integer; AType: PAnsiChar; ATypeLen: integer):BOOL; external 'ReadCustomizeInfoA@files:{#ProductInfoManagerDLL} stdcall delayload';
function ProcessDRCustomizeA(const AConfigFileName, ADRRegSubPath, ADRBuyUrlRegKey: PAnsiChar):BOOL; external 'ProcessDRCustomizeA@files:{#ProductInfoManagerDLL} stdcall delayload';
function CustomizeUpdateProcessA(const ASrcConfigFile, ADstConfigFile: PAnsiChar):BOOL; external 'CustomizeUpdateProcessA@files:{#ProductInfoManagerDLL} stdcall delayload';
function WSOpenURLA(const AURL: PAnsichar; nOpenMode: integer):BOOL; external 'WSOpenURLA@files:{#ProductInfoManagerDLL} stdcall delayload';
function UninstallLoadCustomizeXMLFileA(const AConfigFileName: PAnsiChar):BOOL; external 'LoadCustomizeXMLFileA@{app}\{#ProductInfoManagerDLL} stdcall uninstallonly';
function UninstallReadCustomizeInfoA(const AInfoName, ALangName: PAnsichar; AValue: PAnsiChar; AValueLen: integer; AType: PAnsiChar; ATypeLen: integer):BOOL; external 'ReadCustomizeInfoA@{app}\{#ProductInfoManagerDLL} stdcall uninstallonly';
function UninstallWSOpenURLA(const AURL: PAnsichar; nOpenMode: integer):BOOL; external 'WSOpenURLA@{app}\{#ProductInfoManagerDLL} stdcall uninstallonly';

function ReadCustomizedStringInfo(const AInfoName: ansistring): ansistring; forward;
function GetProductID(const APID: string): string; forward;

//�Զ��庯��...

function KillProcess(szFileName: string): Boolean;
var
  ErrorCode: Integer;
begin
  ShellExec('open', ExpandConstant('{sys}') + '\TASKKILL.exe', '/F /IM ' + szFileName,'', SW_HIDE, ewWaitUntilTerminated, ErrorCode);
  Result := ErrorCode = 0;
end;

function GetLanguageCode: string;
begin
  Result := ExpandConstant('{language}');
  if Result = 'ARA' then
    Result := 'ARG';
end;

procedure UninstallCustomizedProcess; // ж����ת
var
  configFile, LanguageCode, publishName, ProductName, sType: ansistring;
  sUrl: string;
  ErrorCode : Integer;
  sJumpPage: ansistring;
  sRes: string;
begin
  LanguageCode:= GetLanguageCode;
  configFile:= AddBackslash(ExpandConstant('{app}')) + '{#MyAppCustomizedFileName}';
  publishName:= '{#Publisher}';
  ProductName:= '{#AppName}';

  if not UninstallLoadCustomizeXMLFileA(PAnsichar(configFile)) then Exit;
  
  sRes := '0';
  RegQueryStringValue(HKEY_LOCAL_MACHINE, 'Software\Wondershare\{#ProductID}', 'Register', sRes);  // ����ע����

  SetLength(sJumpPage, 1024);
  if sRes = '0' then UninstallReadCustomizeInfoA('UninstallTrialJumpPage', PAnsichar(LanguageCode), PAnsichar(sJumpPage), 1024, PAnsichar(sType), 0)
  else UninstallReadCustomizeInfoA('UninstallJumpPage', PAnsichar(LanguageCode), PAnsichar(sJumpPage), 1024, PAnsichar(sType), 0);
  UninstallWSOpenURLA(PAnsichar(sJumpPage), 0);

  //publishName:= '{#Publisher}';
  //ProductName:= '{#AppName}';
  // ����ʧ�ܣ�ԭ���������ܸ���̬���йء��Ĵ�ע����ж���UninstallJumpPage��ʹ��ShellExecִ����ת��
  //MsgBox('ж����ת1', mbConfirmation, MB_YESNO);   // test
  //MsgBox(GetProductID('{#ProductID}'), mbConfirmation, MB_YESNO);   // test
  //MsgBox(PAnsichar(LanguageCode), mbConfirmation, MB_YESNO);   // test
  //MsgBox(PAnsichar(configFile), mbConfirmation, MB_YESNO);   // test
  //MsgBox(PAnsichar(publishName), mbConfirmation, MB_YESNO);   // test
  //MsgBox(PAnsichar(ProductName), mbConfirmation, MB_YESNO);   // test
  //UnInstallCustomized(PAnsichar(LanguageCode),PAnsichar(configFile),PAnsichar(publishName), PAnsichar(ProductName));
  //MsgBox('ж����ת2', mbConfirmation, MB_YESNO);   // test
  //configFile := AddBackslash(ExpandConstant('{sd}')) + ExpandConstant('ProgramData/Wondershare Filmora Scrn/') + ExpandConstant('{#ConfigName}');
  //MsgBox(configFile, mbConfirmation, MB_YESNO);
  //sPID := GetIniString('UpdateRegister', 'ProdID', '{#ProductID}', configFile);
  //MsgBox(sPID, mbConfirmation, MB_YESNO);
  //RegQueryStringValue(HKEY_LOCAL_MACHINE, 'SOFTWARE\Wondershare\' + sPID, 'UninstallJumpPage', sUrl);
  //MsgBox('ж����ת', mbConfirmation, MB_YESNO);   // test
  //MsgBox(sUrl, mbConfirmation, MB_YESNO);   // test
  //sUrl := ReadCustomizedStringInfo('UninstallJumpPage'); 
  //ShellExec('open', sUrl, '', '', SW_SHOW, ewNoWait, ErrorCode);
  //sUrl := ReadCustomizedStringInfo('UninstallJumpPage');
  //sPID := ReadCustomizedStringInfo('PID');
  //MsgBox(g_PID, mbConfirmation, MB_YESNO);   // test
  //RegQueryStringValue(HKEY_LOCAL_MACHINE, 'SOFTWARE\Wondershare\' + g_PID, 'UninstallJumpPage', sUrl);
  //ShellExec('open', g_sJumpPage, '', '', SW_SHOW, ewNoWait, ErrorCode);
  //var ErrorCode : Integer;
  //if RegQueryStringValue(HKEY_LOCAL_MACHINE, 'SOFTWARE\Wondershare\3235', 'UninstallJumpPage', sUrl) then
  //begin
  //MsgBox(sUrl, mbConfirmation, MB_YESNO);
  //ShellExec('open', sUrl, '', '', SW_SHOW, ewNoWait, ErrorCode);
  //end;
end;

function GetPersonalFolder(Param: string): string;
begin
  Result := GetShellFolderByCSIDL(CSIDL_PERSONAL, True);
  //��ʵҲ���ô˴��룺ExpandConstant('{userdocs}')
end;

function GetAgentValue(const AKey: string): string;
begin
  //��Customization.xml�ж�ȡ���ӵ�ַ
  Result := ReadCustomizedStringInfo(AKey);
end;

function GetAppPublisher(const APublisher: string): string;
begin
  Result := ReadCustomizedStringInfo('Publisher');
  if Result = '' then Result := APublisher;
end;

function GetAppShortVersion(const AVersion: string): string;
var
  i, n: Integer;
begin
  //RPos�ڴ˴����в����ã�������ISPP�У����Դ˴��ñȽϷ�������
  n := 0;
  for i := 1 to Length(AVersion) do
    if AVersion[i] = '.' then
    begin
      n := n + 1;
      if n = 3 then
      begin
        Result := Copy(AVersion, 1, i - 1);
        Break;
      end;
    end;
end;

//�Ƿ�������װ
function IsUpdateSetup: Boolean;
var
  i: Integer;
begin
  Result := False;
  for i := 0 to ParamCount  do
    if (ParamStr(i) = '/SILENT') or (ParamStr(i) = '/NOTSHOWCBS') then
    begin
      Result := True;
      Break;
    end;
end;
            
//�Ƿ���������װ
function IsDownloaderSetup: Boolean;
var
  i: Integer;
begin
  Result := False;
  for i := 0 to ParamCount  do
    if (ParamStr(i) = '/VERYSILENT') then
    begin
      Result := True;
      Break;
    end;
end;

//�Ƿ񸲸�ж��
function IsOverUnInstall: Boolean;
var
  i: Integer;
begin
  Result := False;
  //Ϊ���ǰ�װж����ȫ�����
  if not Result then
    for i := 0 to ParamCount  do
      if ParamStr(i) = '/REINSTALL' then
      begin
        Result := True;
        Break;
      end;
end;

//������
function OpenUrl(const AUrl: string): Boolean;
var
  sUrl: string;
begin
  sUrl := AUrl;
  if Pos(':', sUrl) = 0 then sUrl := 'http://' + sUrl;
  Result := ShellExecute(0, 'open', PChar(sUrl), '', '', 1) > 32;
  if not Result then Result := ShellExecute(0, '', 'IEXPLORE.EXE', PChar(sUrl), '', 1) > 32;
end;


//�������������Ƿ��в�����ҳ
function NoJumpPage: Boolean;
var
  i: Integer;
begin
  Result := False;
  for i := 0 to ParamCount  do
    if (ParamStr(i) = '/NOPAGE') then
    begin
      Result := True;
      Break;
    end;
end;


//�Ƿ�/VERYSILENT��װ
function IsVERYSILENTSetup: Boolean;
var
  i: Integer;
begin
  Result := False;
  for i := 0 to ParamCount  do
    if (ParamStr(i) = '/VERYSILENT') then
    begin
      Result := True;
      Break;
    end;
end;

//�Ƿ�󶨲�Ʒ��װ
function IsBindProduct: Boolean;
var
  i: Integer;
begin
  Result := False;
  for i := 0 to ParamCount  do
    if (ParamStr(i) = '/ISBind') then
    begin
      Result := True;
      Break;
    end;
end;


//�Ƿ�Ĭ��װ
function IsSilentInstall: Boolean;
var
  i: Integer;
begin
  Result := False;
  for i := 0 to ParamCount  do
    if (ParamStr(i) = '/VERYSILENT') then
    begin
      Result := True;
      Break;
    end;
end;

function GetParamByName(paramName: string): string;
var
  i: Integer;
begin
  Result := '';
  for i := 0 to ParamCount  do
  begin
    Log('>>>>ParamStr(i):'+ ParamStr(i));
    if (Uppercase(ParamStr(i)) = Uppercase(paramName)) then
    begin
      Result := ParamStr(i+1);
      Break;
    end;
  end;
end;

//��ȡ��ת���ͼ���ת����
procedure OpenJumpPage(const AProcessType: TCBSProcessType);       // ��װ��ת
var
  sJumpType, sJumpPage: string;
begin
  sJumpType := ReadCustomizedStringInfo('CBSJumpType');
  //MsgBox('sJumpType', mbConfirmation, MB_YESNO);     // test
  //MsgBox(sJumpType, mbConfirmation, MB_YESNO);       // test
  //����ת
  if compareText(sJumpType, 'Disable') = 0 then Exit;

  //��ת����
  case AProcessType of
    cptInstall:      
    begin
      if IsBindProduct then
        sJumpPage := ReadCustomizedStringInfo('C10')
      else
        sJumpPage := ReadCustomizedStringInfo('InstallJumpPage');
    end;
    //MsgBox('sJumpPage1', mbConfirmation, MB_YESNO);     // test
    //MsgBox(sJumpPage, mbConfirmation, MB_YESNO);       // test 
    cptOnlineUpdate: sJumpPage := ReadCustomizedStringInfo('UpdateJumpPage');
    cptUnInstall:    sJumpPage := ReadCustomizedStringInfo('UninstallJumpPage');
  end;
  if sJumpPage = '' then Exit;
  //MsgBox('��װ��ת', mbConfirmation, MB_YESNO);     // test
  //MsgBox(sJumpPage, mbConfirmation, MB_YESNO);       // test 
  //������
  if CompareText(sJumpType, 'Jump') = 0 then
  begin
    if NoJumpPage then
      WSOpenURLA(sJumpPage, 1)
    else
      OpenURL(sJumpPage);
  end
  //���ش�...'Hide'
  else
  begin
    if AProcessType = cptInstall then WSOpenURLI(sJumpPage, 1);
    if AProcessType = cptUnInstall then WSOpenURLU(sJumpPage, 1);
  end;
end;

// ����һ����Դ����̲�֧�ֹ������
procedure SetRemindSwitch(AEnable: Boolean);
var
  RegPath: string;
begin
  RegPath:= 'SOFTWARE{#x6432Node}\{#Publisher}\{#OldAppName}';
  RegWriteDWordValue(HKEY_LOCAL_MACHINE, RegPath, 'RemindSwitch', Integer(AEnable));
end;

// ����һ����԰�װʱ�����Ƿ�μ��û������ռ�
procedure SetEnableUserDataCollect(AEnable: Boolean);
var
  RegPath, sPID, sVersion: string;
begin
  sPID := ReadCustomizedStringInfo('PID');
  sVersion := ReadCustomizedStringInfo('ProductVersion');
  RegPath:= 'SOFTWARE\{#Publisher}\{#CBSHelperAppName}\' + sPID + '\' + sVersion;
  RegWriteDWordValue(HKEY_LOCAL_MACHINE, RegPath, 'JoinUserExperience', integer(AEnable));
end;

function ReadCustomizedStringInfo(const AInfoName: ansistring): ansistring;
var
  Value, sType: ansistring;
begin
  result:= '';
  SetLength(Value, 1024);
  if ReadCustomizeInfoA(PAnsichar(AInfoName), PAnsichar(GetLanguageCode), PAnsichar(value), 1024, PAnsichar(sType), 0) then
    result:= string(PAnsichar(value));
end;

//�ִ����ܺ�����ʼ...
function ExChange(const S: string): String;
var
  i: Integer;
begin
  Result := S;
  for i := 1 to Length(S) do
    Result[i] := S[Length(S) - i + 1];
end;

function ByteToHex(b: Byte): string;
begin
  SetLength(Result, 3);
  if (b div 16) > 9 then
    Result[1] := Chr((b div 16) - 10 + Ord('A'))
  else Result[1] := Chr(b div 16 + Ord('0'));
  if (b mod 16) > 9 then
    Result[2] := Chr((b mod 16) - 10 + Ord('A'))
  else Result[2] := Chr(b mod 16 + Ord('0'));

  Result[3] := #0;
end;

function EncryptStr(const Src, Key: string): string;
var
  i, j, Keyidx, step, SrcLen, KeyLen, DstLen: Integer;
  pch, str: string;
  ntmp: Integer;
begin
  SrcLen := Length(Src);
  KeyLen := Length(Key);
  if SrcLen > KeyLen then
    DstLen := 2 * (SrcLen + 1)
  else DstLen := 2 * (KeyLen + 1);

  SetLength(Result, DstLen);
  ntmp := DstLen div 2;
  SetLength(pch, ntmp);
  SetLength(str, ntmp);
  pch[ntmp] := chr(SrcLen - KeyLen);
  for i := 1 to KeyLen do
    pch[ntmp] := Chr(Ord(pch[ntmp]) xor Ord(Key[i]));
  for i := 0 to ntmp - 2 do
    pch[i + 1] := Chr(Ord(Src[i mod SrcLen + 1]) xor Ord(Key[i mod KeyLen + 1]) xor Ord(pch[ntmp]));

  i := 1;
  Keyidx := 0;
  while i < ntmp do
  begin
    step := Ord(Key[(Keyidx mod KeyLen) + 1]) mod 10;
    if i + step > ntmp then
    Step :=  ntmp - i;
    str := Copy(pch, i, step);
    str := ExChange(str);
    for j := 0 to step - 1 do
      pch[i + j] := str[j + 1];
    i := i + Step;
    Keyidx := Keyidx + 1;
  end;

  for i := 1 to ntmp do
  begin
    str := ByteToHex(Ord(pch[i]));
    Result[2 * i - 1] := str[1];
    Result[2 * i] := str[2];
  end;
end;

//�����Ƿ�����������
function CheckProgramRunning(): Boolean;
begin
  Result := (FindWindowByClassName('Qt5QWindowIcon') <> 0) or (FindWindowByClassName('Qt5QWindowToolSaveBits') <> 0) or (FindWindowByClassName('SysListView32') <> 0);
end;

//�ر��������еĳ���
procedure TerminateProgram();
begin
  if FindWindowByClassName('Qt5QWindowIcon') <> 0 then SendMessage(FindWindowByClassName('Qt5QWindowIcon'), WM_CLOSE, 0, 0);
end;

//��ȡж���ļ�·��
function UninstallExeFile(): string;
var
  AppPath: string;
  i: Integer;
begin
  Result := '';
  //Ϊ���ⰲװ�ļ���Ϊunins000��������
  if not RegQueryStringValue(HKEY_CLASSES_ROOT, ExpandConstant('{#ProjNodeName}'), 'path', AppPath) then
    //���2.0����ǰ�汾
    if RegQueryStringValue(HKEY_LOCAL_MACHINE, 'SOFTWARE\Wondershare\3235', 'EXEPath', AppPath) then
      AppPath := ExtractFileDir(AppPath);

  if DirExists(AppPath) then
    for i := 0 to 9 do
      if FileExists(AppPath + '\unins00' + IntToStr(i) + '.exe') then
      begin
        Result := AppPath + '\unins00' + IntToStr(i) + '.exe';
        Exit;
      end;
end;

//xpϵͳ��װ��¼����
procedure InstallWinBurnEngine;
var
  Version: TWindowsVersion;
  sExePath: string;
  ErrorCode: Integer;
begin
  GetWindowsVersionEx(Version);
  if Version.NTPlatform and (Version.Major = 5) and (Version.Minor = 1) then
  begin
    sExePath := ExpandConstant('{tmp}\{#IMApiXPSrv}');
    ExtractTemporaryFile(ExtractFileName(sExePath));
    ShellExec('open', sExePath, '/quiet', '', SW_HIDE, ewNoWait, ErrorCode);
  end;
end;

//����������ļ�
function ProcessAgentData(): Boolean;
var
  configFile, DstConfigFile: ansistring;
  exeFile: String;
  CBSJumpType, PID, PIDRegPath, UninstallJumpPage: ansistring;
  EnableAD: Boolean;
begin
  Result := True;
  //ֻ�ڴ����ļ�ʱ��ִ�д˺���
  if not FileExists(AddBackslash(ExpandConstant('{app}')) + '{#NewExeName}') then Exit;
  SetRemindSwitch(True);
  // ��exe����ȡ���������ļ�
  configFile:= AddBackslash(ExpandConstant('{tmp}')) + '{#MyAppCustomizedFileName}';
  exeFile:= ExpandConstant('{srcexe}');
  if not PopFileFromReservedA(exeFile, configFile) then Exit;
  // ���������ļ�...2012-05-19��֤����win 7ϵͳ��Loadʧ��
  if not LoadCustomizeXMLFileA(PAnsichar(configFile)) then Exit;
  // ��������, ��[Files]�е������ļ��滻Ϊexe����ȡ�������ļ�,�������������������ӵ�ַ
  // ���������򽫵�ǰ�����ļ�֮��Ϣ����������װ����ѹ��ģ��ϲ��������ڳ���Ŀ¼��
  DstConfigFile:= AddBackslash(ExpandConstant('{app}')) + '{#MyAppCustomizedFileName}';
  if not CustomizeUpdateProcessA(PAnsichar(configFile), PAnsichar(dstConfigFile)) then Exit;
  // DR���ƴ�����DR������ע����ж�ȡ�����ַ����Ҫ�Ƚ�����������...���ڴ˴���ʹ����д���������������ļ���
  ProcessDRCustomizeA(PAnsichar(dstConfigFile), 'SoftWare\Digital River\SoftwarePassport\', 'BuyURL');
  // ���������ļ�
  if not LoadCustomizeXMLFileA(PAnsichar(dstConfigFile)) then Exit;
  Result := False;
  // ��ȡPID, CBSJumpType, InstallJumpPage�ȶ�����Ϣ
  PID:= ReadCustomizedStringInfo('PID');
  CBSJumpType:= ReadCustomizedStringInfo('CBSJumpType');
  if (PID = '') or (CBSJumpType = '') then Exit;
  // ���ù�浯��ʹ��
  EnableAD:= ReadCustomizeBoolInfoA('EnableAD', PAnsichar(GetLanguageCode));
  SetRemindSwitch(EnableAD);
  
  // ����CBS��ת, ���þɰ汾��ʽд��ע���
  PIDRegPath:= 'SOFTWARE\{#Publisher}\' + PID;
  if CompareText(CBSJumpType, 'Hide') = 0 then
    RegWriteStringValue(HKEY_LOCAL_MACHINE, PIDRegPath, 'JumpType', '1')
  else if CompareText(CBSJumpType, 'Jump') = 0 then
    RegWriteStringValue(HKEY_LOCAL_MACHINE, PIDRegPath, 'JumpType', '0')
  else RegWriteStringValue(HKEY_LOCAL_MACHINE, PIDRegPath, 'JumpType', '2');
  UninstallJumpPage:= ReadCustomizedStringInfo('UninstallTrialJumpPage');
  //MsgBox('PID: ' + PID, mbConfirmation, MB_YESNO);     // test
  RegWriteStringValue(HKEY_LOCAL_MACHINE, PIDRegPath, 'UninstallJumpPage', UninstallJumpPage);
end;

function GetProductID(const APID: string): string;
begin
  Result := ReadCustomizedStringInfo('PID');
  if Result = '' then Result := APID;
end;

//�����ַ�����.�ĸ���
function CountPoint(const sStr: string): integer;
var i, j: integer;
begin
  j:=0;
  for i:=1 to length(sStr) do
  if sStr[i] = '.' then j := j + 1;
  Result:= j;
end;

//д�����ļ�
procedure WriteConfigFile();
var
  sConfigIni, sKey: string;
  count: integer;
  sVersion: string;
begin
  //��FilmoraScrn.iniд��
  //sConfigIni := AddBackslash(ExpandConstant('{app}')) + ExpandConstant('{#ConfigName}');
  sConfigIni := AddBackslash(ExpandConstant('{sd}')) + ExpandConstant('ProgramData/Wondershare Filmora Scrn/') + ExpandConstant('{#ConfigName}');
  //if FileExists(sConfigIni) = False then 
  SetIniString('System', 'DefInstallLang', GetLanguageCode, sConfigIni);
  SetIniString('System', 'ProdID', GetProductID('{#ProductID}'), sConfigIni);

  //��UpdateRegister.iniд��
  sConfigIni := AddBackslash(ExpandConstant('{app}')) + ExpandConstant('{#UpdateRegisterConfigName}');
  //��EXE�ļ���MD5ֵ��Ϊ����Key
  sKey := GetFileMD5Ex(PChar(ExpandConstant('{app}') + '\' + ExpandConstant('{#NewExeName}')));
  //System Section
  SetIniString('System', 'CodeKey', sKey, sConfigIni);
  SetIniString('System', 'GUID', EncryptStr(ExpandConstant('{#SGUID}'), sKey), sConfigIni);
  SetIniString('System', 'Value1', EncryptStr(ExpandConstant('{#RegKeyN}'), sKey), sConfigIni);
  SetIniString('System', 'Value2', EncryptStr(ExpandConstant('{#RegKeyD}'), sKey), sConfigIni);
  //SetIniInt('System', 'UpdatePeriod', 7, sConfigIni);
  //SetIniString('System', 'DefInstallLang', GetLanguageCode, sConfigIni);
  //SetIniString('System', 'DefLanguage', GetLanguageCode, sConfigIni);
  //SetIniString('System', 'ProductID', ExpandConstant('{#ProductID}'), sConfigIni);
  //ע����Ϣ
  if g_regMail <> '' then SetIniString('UpdateRegister', 'Email', g_regMail, sConfigIni);
  if g_regCode <> '' then SetIniString('UpdateRegister', 'RegkeyCode', g_regCode, sConfigIni);

  sVersion := ExpandConstant('{#AppVersion}');
  if CountPoint(sVersion) = 3 then sVersion := copy(sVersion, 1, length(sVersion) - 2);

  //UpdateRegister Section
  SetIniString('UpdateRegister', 'ProdID', GetProductID('{#ProductID}'), sConfigIni);
  SetIniString('UpdateRegister', 'ProductName', ExpandConstant('{cm:AppName}'), sConfigIni);
  SetIniString('UpdateRegister', 'Version', sVersion, sConfigIni);

  //CrashReport.ini
  sConfigIni := AddBackslash(ExpandConstant('{app}')) + ExpandConstant('{#CrashReportConfigName}');
  SetIniString('bug_splat', 'product_version', sVersion, sConfigIni);

  //Http Section
  //SetIniString('HTTP', 'UpdateUrl', ExpandConstant('{#UpdatePage}'), sConfigIni);
  //SetIniString('HTTP', 'EmailServerURL', ExpandConstant('{#EmailServerURL}'), sConfigIni);
end;

function IntToHex(Value: Integer; Digits: Integer): String;
var
  s: string;
begin
  s := Format('%x', [Value]);
  if Length(s) < Digits then
    Result := StringOfChar('0', Digits - Length(s)) + s
  else Result := s;
end;

function GetGuid(dummy: string): string;
var
  Guid: TGuid;
begin
  if CoCreateGuid(Guid) = 0 then
  begin
    Result := '{' + IntToHex(Guid.D1, 8) + '-' +
      IntToHex(Guid.D2, 4) + '-' +
      IntToHex(Guid.D3, 4) + '-' +
      IntToHex(Guid.D4[0], 2) + IntToHex(Guid.D4[1], 2) + '-' +
      IntToHex(Guid.D4[2], 2) + IntToHex(Guid.D4[3], 2) +
      IntToHex(Guid.D4[4], 2) + IntToHex(Guid.D4[5], 2) +
      IntToHex(Guid.D4[6], 2) + IntToHex(Guid.D4[7], 2) +
      '}';
  end
  else Result := '{00000000-0000-0000-0000-000000000000}';
end;

//���ư�װ������غ�����...

procedure LicenseCheckBoxOnClick(Sender: TObject);
begin
  WizardForm.LicenseAcceptedRadio.Checked := TNewCheckBox(Sender).Checked;
  WizardForm.LicenseNotAcceptedRadio.Checked := not TNewCheckBox(Sender).Checked;
end;

procedure CreateLicenseCheckBox(ParentPage: TNewNotebookPage; const ALeft, ATop: Integer);
begin
  with TNewCheckBox.Create(ParentPage) do
  begin
    Parent := ParentPage;
    Caption := ExpandConstant('{cm:AcceptLicense}');
    Left := ALeft;
    Top := ATop;
    Width := ParentPage.Width;
    OnClick := @LicenseCheckBoxOnClick;
  end;
end;

procedure LaunchCheckBoxOnClick(Sender: TObject);
//var
//  i: Integer;
begin
  //�˴���Run֮�����б������������������ɰ�װ����ִ��
  //2012-06-13���Ʒȷ�ϣ���CheckBoxֻΪ�������ã���ִ�о������
  //with WizardForm.RunList do
  //  for i := 0 to Items.Count - 1 do
  //    if ItemCaption[i] = TNewCheckBox(Sender).Caption then
  //    begin
  //      Checked[i] := TNewCheckBox(Sender).Checked;
  //      Break;
  //    end;
end;

procedure CreateFinishedPage;
var
  Page: TWizardPage;
  h: Integer;
begin
  Page := CreateCustomPage(wpInfoAfter, '{#AppName}', '');

  //��ǩ
  with TNewStaticText.Create(Page) do
  begin
    Left := 0;
    Top := 0;
    Width := Page.SurfaceWidth;
    //Height := Page.SurfaceHeight - 48;
    AutoSize := True;
    Parent := Page.Surface;

    Caption := ExpandConstant('{cm:UninstMsg3}') + #13#10 + #13#10
      + ExpandConstant('{cm:UninstMsg4}') + #13#10
      + ExpandConstant('{cm:UninstMsg5}') + #13#10 + #13#10
      + ExpandConstant('{cm:UninstMsg6}') + #13#10
      + ExpandConstant('{cm:UninstMsg7}') + #13#10
      + ExpandConstant('{cm:UninstMsg8}');
    h := Height;
  end;

  with TNewCheckBox.Create(Page) do
  begin
    Top := h + 12;//Page.SurfaceHeight - 48;
    Width := Page.SurfaceWidth;
    Parent := Page.Surface;
    Caption := ExpandConstant('{cm:TakePlan}');
    Checked := True;
    OnClick := @LaunchCheckBoxOnClick;
  end;
end;





















