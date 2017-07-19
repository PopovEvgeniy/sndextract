install:
	@echo Compiling the program source code. Please wait
	@gcc sndextract.c -g0 -O0 -o sndextract
	@echo Compilation successfuly complete
	@chmod ugo+rx sndextract
	@echo Enter you user password for do last installation step
	@sudo cp -f -p sndextract /bin/
	@echo Installation complete
uninstall:
	@echo Enter you user password for uninstall this software
	@sudo rm -f /bin/sndextract
	@echo Uninstallation complete