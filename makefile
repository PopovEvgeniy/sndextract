install:
	@echo Installation in progress. Please wait
	@gcc sndextract.c -g0 -O0 -o /bin/sndextract
	@chmod ugo+rx /bin/sndextract
	@echo Installation successfully complete
uninstall:
	@rm -f /bin/sndextract
	@echo Uninstallation successfully complete