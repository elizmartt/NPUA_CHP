@echo off
setlocal enabledelayedexpansion

:menu
cls
echo ============================
echo           MENU              
echo ============================
echo 1. Display IPv4 and IPv6 Addresses
echo 2. Trace Network Route (traceroute)
echo 3. Resolve Hostname to IP Address
echo 4. Encrypt Text
echo 5. Decrypt Text
echo 6. Compress a File
echo 7. Decompress a File
echo 8. Calculate File Hash (SHA256)
echo 0. Exit
echo ============================
set /p choice=Select an option: 

if "%choice%"=="1" goto show_ip
if "%choice%"=="2" goto trace_route
if "%choice%"=="3" goto resolve_ip
if "%choice%"=="4" goto encrypt_text
if "%choice%"=="5" goto decrypt_text
if "%choice%"=="6" goto compress_file
if "%choice%"=="7" goto decompress_file
if "%choice%"=="8" goto file_hash
if "%choice%"=="0" goto exit
echo Invalid choice. Please try again!
pause
goto menu

:show_ip
cls
echo IPv4 Addresses:
ipconfig | findstr "IPv4"
echo IPv6 Addresses:
ipconfig | findstr "IPv6"
pause
goto menu

:trace_route
cls
set /p hostname=Enter hostname or IP: 
echo Tracing route to %hostname% ...
tracert %hostname%
pause
goto menu

:resolve_ip
cls
set /p hostname=Enter hostname: 
echo Resolving IP address...
nslookup %hostname%
pause
goto menu

:encrypt_text
cls
set /p text=Enter text to encrypt: 
echo Encrypted Text:
echo %text% | certutil -encode stdin encoded.txt >nul
type encoded.txt
del encoded.txt
pause
goto menu

:decrypt_text
cls
set /p file=Enter encoded file name: 
echo Decrypted Text:
certutil -decode %file% decoded.txt
type decoded.txt
del decoded.txt
pause
goto menu

:compress_file
cls
set /p file=Enter file path to compress: 
echo Compressing file...
compact /c "%file%"
pause
goto menu

:decompress_file
cls
set /p file=Enter file path to decompress: 
echo Decompressing file...
compact /u "%file%"
pause
goto menu

:file_hash
cls
set /p file=Enter file path to calculate hash: 
echo SHA256 Hash Value:
certutil -hashfile "%file%" SHA256
pause
goto menu

:exit
echo Exiting... Goodbye!
pause
exit
