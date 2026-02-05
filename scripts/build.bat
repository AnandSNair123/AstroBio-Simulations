@echo off

:: Check whether source files exist
echo Checking for source files...

if not exist ../src/main.cpp (
    echo Error: ../src/main.cpp not found.
    exit /b
)

if not exist ../src/random.cpp (
    echo Error: ../src/random.cpp not found.
    exit /b
)

if not exist ../src/environment.cpp (
    echo Error: ../src/environment.cpp not found.
    exit /b
)

if not exist ../src/species.cpp (
    echo Error: ../src/species.cpp not found.
    exit /b
)

if not exist ../src/cluster.cpp (
    echo Error: ../src/cluster.cpp not found.
    exit /b
)

:: Start building the project
echo Building project...

g++ -o ../bin/simulation.exe ^
    ../src/main.cpp ^
    ../src/random.cpp ^
    ../src/environment.cpp ^
    ../src/species.cpp ^
    ../src/cluster.cpp

:: Check if the build was successful
if exist ../bin/simulation.exe (
    echo Build successful! The executable is located at: ../bin/simulation.exe
) else (
    echo Build failed. simulation.exe was not created.
)

pause

