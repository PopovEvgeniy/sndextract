install:
	@echo Installation in progress. Please wait
	@gcc sndextract.c -g0 -O0 -o /bin/sndextract
	@chmod ugo+rx /bin/sndextract
	@echo Installation was successfuly complete
uninstall:
	@rm -f /bin/sndextract
	@echo Uninstallation was successfuly complete