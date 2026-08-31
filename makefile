install:
	@echo Installation in progress. Please wait
	@$(CC) sndextract.c -g0 -O0 -o /bin/sndextract
	@chmod ugo+rx /bin/sndextract
	@echo Installation was successfully complete
uninstall:
	@rm /bin/sndextract
	@echo Uninstallation was successfully complete