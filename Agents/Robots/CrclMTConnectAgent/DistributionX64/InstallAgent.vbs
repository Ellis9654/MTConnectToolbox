
dim objShell, FSO, strPath, wshShell, UAC
Set objShell = CreateObject("Shell.Application")
Set FSO = CreateObject("Scripting.FileSystemObject")
strPath = FSO.GetParentFolderName (WScript.ScriptFullName) + "\CrclAgent.exe"
msgbox strPath


Set UAC = CreateObject("Shell.Application")
UAC.ShellExecute "sc.exe", "create CrclAgent binPath= " & strPath, "", "runas", 1

UAC.ShellExecute "sc.exe", "start CrclAgent " , "", "runas", 1



