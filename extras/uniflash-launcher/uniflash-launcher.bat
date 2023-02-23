@echo off
set sh_file="%~dp0/uniflash-launcher.sh"
set sh_correct=%sh_file:\=/%
"%~dp0/busybox.exe" sh %sh_correct% %*