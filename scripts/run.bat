@echo off

:: run the first executable
echo Running the simulation
../bin/simulation.exe

:: Set the path to the virtual environment
set VENV_PATH=..\venv

:: Check if the virtual environment exists
if not exist "%VENV_PATH%\Scripts\activate" (
    echo Virtual environment not found at %VENV_PATH%. Exiting...
    pause
    exit /b
)

:: Activate the virtual environment
echo Activating virtual environment...
call "%VENV_PATH%\Scripts\activate"

:: Check if activation was successful
if %errorlevel% neq 0 (
    echo Error: Failed to activate virtual environment. Exiting...
    pause
    exit /b
)

:: Set the path to the second executable
set EXE_PATH=..\bin\graphPlotter.exe


:: Run the second executable within the activated virtual environment
echo Running the Graph Plotter...
"%EXE_PATH%"

:: Deactivate the virtual environment after running the executable
deactivate

echo Operation completed successfully.
pause


