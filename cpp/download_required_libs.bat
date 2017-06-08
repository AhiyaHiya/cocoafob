@ECHO OFF

SET "LOCAL_CURRENT_PATH=%CD%"
CALL:SetupOpenSSL
EXIT/b

:SetupOpenSSL
	ECHO SetupOpenSSL
	REM CALL :DownloadOpenSSL
	CALL :BuildOpenSSL
	EXIT/b
	
:DownloadOpenSSL
	IF EXIST %LOCAL_CURRENT_PATH%\components\openssl\win\tmp_src (
		ECHO "components openssl win exist"
	) ELSE (
		ECHO "components DOESN'T exist"
		MKDIR %LOCAL_CURRENT_PATH%\components\openssl\win\tmp_src
	)
	CD %LOCAL_CURRENT_PATH%\components\openssl\win\tmp_src
	git.exe clone -b OpenSSL_1_0_2-stable https://github.com/openssl/openssl

	EXIT/b 
	
REM Used information from http://developer.covenanteyes.com/building-openssl-for-visual-studio/
REM for below build settings
:BuildOpenSSL
	CD %LOCAL_CURRENT_PATH%\components\openssl\win\tmp_src\openssl
	
	perl Configure VC-WIN32 --prefix=%LOCAL_CURRENT_PATH%\components\openssl\win\tmp_src\openssl\build_win32
	CALL ms\do_ms
	nmake -f ms\ntdll.mak
	nmake -f ms\ntdll.mak test
	nmake -f ms\ntdll.mak install
	
	CD %LOCAL_CURRENT_PATH%\components\openssl\win\tmp_src\openssl
	perl Configure VC-WIN64A --prefix=%LOCAL_CURRENT_PATH%\components\openssl\win\tmp_src\openssl\build_x64
	CALL ms\do_win64a
	nmake -f ms\ntdll.mak
	nmake -f ms\ntdll.mak test
	nmake -f ms\ntdll.mak install 

	EXIT/b 