@echo off
setlocal enabledelayedexpansion

:: Set the required Python version
set REQUIRED_PYTHON_VERSION=Python39

:: Check if Python is in the PATH
echo Checking if Python is in the PATH...
where python >nul 2>nul
if %errorlevel% neq 0 (
    echo Python is not in the PATH. Checking default installation path...

    REM Default Python installation path (Windows 10 default)
    set PYTHON_PATH=C:\Users\%USERNAME%\AppData\Local\Programs\Python

    REM Search for the required Python version in the default directory
    for /d %%i in (%PYTHON_PATH%\*) do (
        if exist "%%i\python.exe" (
            set VERSION_DIR=%%i
            set VERSION_NAME=%%~nxi
            echo Found Python version: !VERSION_NAME!
            if /i "!VERSION_NAME!"=="%REQUIRED_PYTHON_VERSION%" (
                echo The required version %REQUIRED_PYTHON_VERSION% found.
                set PATH=!PATH!;%%i
                echo %REQUIRED_PYTHON_VERSION% added to PATH.
                goto :python_found
            )
        )
    )
    
    echo Required Python version %REQUIRED_PYTHON_VERSION% not found in the default directory.
    echo Please enter the correct Python installation directory (e.g., C:\Users\<UserName>\AppData\Local\Programs\Python\Python39):
    set /p PYTHON_PATH=Python path: 
    if not exist "%PYTHON_PATH%" (
        echo Error: The specified Python path does not exist.
        pause
        exit /b
    )
    set PATH=!PATH!;%PYTHON_PATH%
    echo Python added to PATH.
    goto :python_found

) else (
    echo Python is already in the PATH.
)

:python_found

:: Check if g++ is in the PATH
echo Checking if g++ is in the PATH...
where g++ >nul 2>nul
if %errorlevel% neq 0 (
    echo g++ is not in the PATH. Checking default installation path...

    REM Default g++ path (Windows 10 default for MinGW)
    set GPP_PATH=C:\MinGW\bin
    
    REM Check if default g++ path exists
    if exist "%GPP_PATH%" (
        echo g++ found in default location: %GPP_PATH%.
        set PATH=!PATH!;%GPP_PATH%
    ) else (
        echo Default g++ path not found.
        echo Please enter the correct g++ installation directory (e.g., C:\MinGW\bin):
        set /p GPP_PATH=g++ path: 
        if not exist "%GPP_PATH%" (
            echo Error: The specified g++ path does not exist.
            pause
            exit /b
        )
        set PATH=!PATH!;%GPP_PATH%
        echo g++ added to PATH.
    )
) else (
    echo g++ is already in the PATH.
)

:: Set the path for the virtual environment
set VENV_PATH=..\venv\venv

:: Check if the virtual environment already exists
if exist %VENV_PATH%\Scripts\activate (
    echo Virtual environment already exists at %VENV_PATH%.
) else (
    echo Virtual environment does not exist. Creating a new one...
    python -m venv %VENV_PATH%
    if !errorlevel! neq 0 (
        echo Error: Failed to create virtual environment.
        pause
        exit /b
    )
    echo Virtual environment created successfully.
)

:: Activate the virtual environment
echo Activating virtual environment...
call %VENV_PATH%\Scripts\activate
if !errorlevel! neq 0 (
    echo Error: Failed to activate virtual environment.
    pause
    exit /b
)

:: Install required libraries
echo Installing required libraries:

:: Install matplotlib
echo Installing matplotlib...
pip install matplotlib
if !errorlevel! neq 0 (
    echo Error: Failed to install matplotlib.
    pause
    exit /b
) else (
    echo Installed matplotlib successfully.
)

:: Install pandas
echo Installing pandas...
pip install pandas
if !errorlevel! neq 0 (
    echo Error: Failed to install pandas.
    pause
    exit /b
) else (
    echo Installed pandas successfully.
)

:: Deactivate the virtual environment
echo Deactivating virtual environment...
deactivate

echo Operation completed successfully.
echo The virtual environment is ready at %VENV_PATH%.
pause

