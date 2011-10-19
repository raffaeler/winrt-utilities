// WinRTDebug
v1.0 September 27, 2011
This first release support enabling/disabling debugging the activation of a package under the
Windows Runtime (Windows 8 or above required)

v1.1 October 19, 2011
Print error operation result message on the console window:
- successful message or detailed error
- hresult hex number in case of error that cannot be converted in message string
The -v command now output the index of the list. This index can be used in place of the package name
prefixed by '$' character.
For example this command suspend the second (zero-based list) app listed by the command -v
winrtdebug -s $1


TODO List:
- test the session id parameter
- implement the 'environment' for the debugger


Will *not* implement:
- set the target version (_WIN32_WINNT) 0x602  or  0x800. It's already 0x602
- copy the package full name in the clipboard with kinda menu in -v option

