turtle.out : 
	gcc -o turtle.out turtle.c inbuilts.c ls.c process.c remindme.c pinfo.c helpers.c

.PHONY: turtle.out clean