REM Script to reconfigure IP settings

@echo off
set Local_IP=10.21.35.5
set Wireless_IP=10.21.35.6
set Sub_Mask=255.0.0.0
set D_Gate=10.21.35.1
set Eth_Name="Local Area Connection"
set Wlan_Name="Wireless Network Connection"

REM Prompt for setting
echo Choose: 
echo [A] Set Static IP 
echo [B] Set DHCP 
echo

REM Process response
:choice 
SET /P C=[A,B]? 
for %%? in (A) do if /I "%C%"=="%%?" goto A
for %%? in (B) do if /I "%C%"=="%%?" goto B
goto choice

REM Configure static address
:A 
@echo off

REM Request whether to change Ethernet address
set /p change_local=Change Ethernet (LAN) Static IP Address [Y/N]? 
if not "%change_local%"=="Y" goto skip_local

REM Set IP address
set /p response=Enter Ethernet (LAN) Static IP Address [%Local_IP%]: 
if "%response%"=="" goto skip_local_ip
set Local_IP=%response%
:skip_local_ip

REM Set subnet mask
set /p response=Subnet Mask [%Sub_Mask%]: 
if "%response%"=="" goto skip_local_subnet
set Sub_Mask=%response%
:skip_local_subnet

REM Set gateway
set /p response=Default Gateway [%D_Gate%]: 
if "%response%"=="" goto skip_local_gateway
set D_Gate=%response%
:skip_local_gateway

REM Configure Ethernet local area connection
echo "Setting Static IP Information for %Eth_Name%"
if "%change_local%"=="Y" netsh interface ipv4 set address %Eth_Name% static address=%Local_IP% mask=%Sub_Mask% gateway=%D_Gate% 1 
:skip_local

REM Request whether to change Wireless address
set /p change_wireless=Change Wireless Static IP Address [Y/N]? 
if not "%change_wireless%"=="Y" goto skip_wireless

REM Set IP address
set /p response=Enter Wireless Static IP Address [%Wireless_IP%]: 
if "%response%"=="" goto skip_wireless_ip
set Wireless_IP=%response%
:skip_wireless_ip

REM Set subnet mask
set /p response=Subnet Mask [%Sub_Mask%]: 
if "%response%"=="" goto skip_wireless_subnet
set Sub_Mask=%response%
:skip_wireless_subnet

REM Set gateway
set /p response=Default Gateway [%D_Gate%]: 
if "%response%"=="" goto skip_wireless_gateway
set D_Gate=%response%
:skip_wireless_gateway

echo "Setting Static IP Information for %Wlan_Name%"
if "%change_wireless%"=="Y" netsh interface ipv4 set address %Wlan_Name% static address=%Wireless_IP% mask=%Sub_Mask% gateway=%D_Gate% 1 
:skip_wireless

goto end

REM Configure DHCP address
:B 
@echo off 
echo Resetting IP Address and Subnet Mask for %Eth_Name% to DHCP 
netsh interface ipv4 set address name=%Eth_Name% dhcp
pause
echo Resetting IP Address and Subnet Mask for %Wlan_Name% to DHCP 
netsh interface ipv4 set address name=%Wlan_Name% dhcp
pause
ipconfig /renew

goto end

REM Exit path for both selections
:end
pause
echo Here are the new settings for %computername%: 
netsh interface ipv4 show config
pause 
