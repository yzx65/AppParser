del bin_output /Q
echo d | xcopy bin_r bin_output /E /Y
cd bin_output
del *.ilk
del *.lib
del *.pdb
del *.temp
del *.exp
cd ..
%~dp0/bin_r/7z a bin.7z %~dp0bin_output
rd bin_output /S /Q