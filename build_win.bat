rmdir /s /q VS
mkdir VS
cd VS
cmake -G "Visual Studio 14 2015 Win64" ..
msbuild XPlanePluginTemplate.vcxproj /p:Configuration=Release

cd ..
copy lib\Release\XPlanePluginTemplate_win.xpl lib\XPlanePluginTemplate_win.xpl
rmdir /s /q lib\Release
rmdir /s /q VS

PAUSE
