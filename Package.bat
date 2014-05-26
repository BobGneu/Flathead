@echo off

rd /q/s Packaging 

mkdir Packaging
cd Packaging

:BASE
mkdir Flathead
cd Flathead

copy ..\..\README.md .\
copy ..\..\LICENSE .\

:BINARIES
mkdir Binaries

mkdir Binaries\Win32
copy ..\..\Binaries\Win32\*.lib .\Binaries\Win32

mkdir Binaries\Win64
copy ..\..\Binaries\Win64\*.dll .\Binaries\Win64


:RESOURCES
mkdir Resources

copy ..\..\Resources\* .\Resources\

:SCRIPTS
mkdir Scripts

copy ..\..\Scripts\* .\Scripts

:SOURCE
mkdir Source
mkdir Source\Flathead
mkdir Source\Flathead\Public

copy ..\..\Source\Flathead\Public\* .\Source\Flathead\Public

cd ..
cd ..
