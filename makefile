<<<<<<< HEAD
enviroment:
	mkdir bin/
	mkdir obj/
=======
build-enviroment:
	mkdir obj
	mkdir bin
>>>>>>> 8197e6e22a81f89518d93d9109530d2af3aed7f4

manager:
	windres source/en-US.rc -o obj/en-US.o
	gcc -c -o obj/CoreBMGR.o source/main.c
	gcc -o bin/BatteryManager.exe obj/CoreBMGR.o obj/en-US.o -DUNICODE -unicode -lgdi32 -mwindows
	
dbg-manager:
	cls
	windres source/en-US.rc -o obj/en-US.o
	gcc -c -o obj/CoreBMGR.o source/main.c
	gcc -o bin/BatteryManager.exe obj/CoreBMGR.o obj/en-US.o -DUNICODE -unicode -lgdi32