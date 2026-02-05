@echo off
setlocal enabledelayedexpansion

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

