dim currentDirectory,WshShell 

currentDirectory = left(WScript.ScriptFullName,(Len(WScript.ScriptFullName))-(len(WScript.ScriptName)))

Set WshShell = WScript.CreateObject("WScript.Shell")
'WshShell.Run "cmd /k " &  Chr(34)  & currentDirectory & "agent.exe" &  Chr(34) & "  install"   , 1, TRUE 
WshShell.Run Chr(34) & currentDirectory & "agent.exe" &  Chr(34) & "  install"   , 1, TRUE 

wscript.sleep 1000
