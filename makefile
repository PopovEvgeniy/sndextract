install:
	@echo Installation in progress. Please wait
	@gcc sndextract.c -g0 -O0 -o sndextract
	@chmod ugo+rx sndextract
	@cp -f -p sndextract /bin/
	@echo Installation was successfuly complete
uninstall:
	@rm -f /bin/sndextract
	@echo Uninstallation was successfuly complete