all: client.c server.c
	@echo Building client...
	$(CC) client.c -g -Wall -o client
	@echo Building server...
	$(CC) server.c -g -Wall -o server