build-enviroment:
	mkdir obj
	mkdir bin

manager:
	windres source/en-US.rc -o obj/en-US.o
	gcc -c -o obj/CoreBMGR.o source/main.c
	gcc -o bin/BatteryManager.exe obj/CoreBMGR.o obj/en-US.o -DUNICODE -unicode -mwindows