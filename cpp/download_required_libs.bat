@ECHO OFF
REM https://stackoverflow.com/questions/38572948/openssl-nmake-fatal-error-u1077-ias-return-code-0x1
SET "LOCAL_CURRENT_PATH=%CD%"
CALL:SetupOpenSSL
EXIT/b

:SetupOpenSSL
	ECHO SetupOpenSSL
	REM CALL :DownloadAndBuild32Bit
	CALL :DownloadAndBuild64Bit

	CD %LOCAL_CURRENT_PATH%	
	EXIT/b
	
	
REM Used information from http://developer.covenanteyes.com/building-openssl-for-visual-studio/
REM https://stackoverflow.com/questions/34410711/how-to-build-openssl-in-vs2015-x86cpuid-asm-is-an-empty-file
REM for below build settings
:DownloadAndBuild32Bit
	SET PATH=%PATH%;"C:\Program Files (x86)\NASM"
	SET LOCAL_SRC_PATH=%LOCAL_CURRENT_PATH%\components\tmp_openssl_src_win32
	MKDIR %LOCAL_SRC_PATH%
	
	CD %LOCAL_SRC_PATH%
	git.exe clone -b OpenSSL_1_0_2-stable https://github.com/openssl/openssl
	
	CD %LOCAL_SRC_PATH%\openssl
	perl Configure VC-WIN32 --prefix=%LOCAL_SRC_PATH%\build_win32
	CALL ms\do_ms
	nmake -f ms\ntdll.mak
	nmake -f ms\ntdll.mak test
	nmake -f ms\ntdll.mak install
	
	EXIT/b 
	
:DownloadAndBuild64Bit
	SET PATH=%PATH%;"C:\Program Files\NASM"
	SET LOCAL_SRC_PATH=%LOCAL_CURRENT_PATH%\components\tmp_openssl_src_x64
	REM MKDIR %LOCAL_SRC_PATH%
	REM CD %LOCAL_SRC_PATH%
	REM git.exe clone -b OpenSSL_1_0_2-stable https://github.com/openssl/openssl
	
	CD %LOCAL_SRC_PATH%\openssl
	perl Configure VC-WIN64A --prefix=%LOCAL_SRC_PATH%\build_x64
	CALL ms\do_win64a
	nmake -f ms\ntdll.mak
	nmake -f ms\ntdll.mak test
	nmake -f ms\ntdll.mak install 

	EXIT/b 
	