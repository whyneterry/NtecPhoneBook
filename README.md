Make sure to specify correct full path to oatpp-swagger/res folder !!!

How to build a project:
1. Terminal
	mkdir build && cd $_
	cmake ..
	cmake --build .

	App-Exe should be in ${source_dir}/build/src/Debug
	Tests-Exe shoud be in ${source_dir}/build/tests/Debug

2. Microsoft Visual Studio Code
	Right-click on main CMakeLists.txt (that is in source directory)
	Then click "Build all projects"

	You should get out/build/x64-debug directory. Let's name it ${debug_dir}.
	App-Exe should be in ${debug_dir}/src
	Tests-Exe shoud be in ${source_dir}/tests

	Your bind for "CMake: Run Without Debugging" should automatically run App-Exe.
	(Ctrl + Shift + F5 by default) I guess)))

3. Microsoft Visual Studio
	Right-click on main CMakeLists.txt (that is in source directory)
	Then click "Build"

	You should get out/build/x64-debug directory. Let's name it ${debug_dir}.
	App-Exe should be in ${debug_dir}/src
	Tests-Exe shoud be in ${source_dir}/tests

	Then you should be able to choose debug target. Choose App-Exe or Tests-Exe
	and run them by hitting your "Run Without Debugging" key-bind. 
	(Ctrl + Shift + F5 by default) I guess)))

P.S.
	App-Exe should be NtecPhoneBookApp-exe.exe
	Tests-Exe should be NtecPHoneBookApp-tests.exe