@ECHO OFF

CALL:SetupOpenSSL

:SetupOpenSSL
	ECHO SetupOpenSSL
	CALL :DownloadOpenSSL
	EXIT/b
	
:DownloadOpenSSL
	IF EXIST components\openssl\win (
		ECHO "components openssl win exist"
	) ELSE (
		ECHO "components DOESN'T exist"
		ECHO "MKDIR components\openssl\win"
	)
	EXIT/b 
	