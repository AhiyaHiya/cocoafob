@ECHO OFF

SET "LOCAL_CURRENT_PATH=%CD%"
CALL:SetupOpenSSL
EXIT/b

:SetupOpenSSL
	ECHO SetupOpenSSL
	CALL :DownloadOpenSSL
	CALL :BuildOpenSSL
	EXIT/b
	
:DownloadOpenSSL
	IF EXIST %LOCAL_CURRENT_PATH%\components\openssl\win (
		ECHO "components openssl win exist"
	) ELSE (
		ECHO "components DOESN'T exist"
		MKDIR %LOCAL_CURRENT_PATH%\components\openssl\win
	)
	MKDIR %LOCAL_CURRENT_PATH%\components\openssl\win\tmp_src
	
	git.exe clone -b OpenSSL_1_0_2-stable https://github.com/openssl/openssl

	EXIT/b 
	
	REM Take a look at the install for Vendors cause you did this for Windows
:BuildOpenSSL
	CD %LOCAL_CURRENT_PATH%\components\openssl\win\tmp_src\openssl
	REM perl Configure { VC-WIN32 | VC-WIN64A | VC-WIN64I | VC-CE } 
	perl Configure VC-WIN64I
	nmake 
	nmake test 
	REM nmake install 

	EXIT/b 