turtle.out : 
	gcc -o turtle.out turtle.c inbuilts.c ls.c process.c remindme.c pinfo.c helpers.c redirection.c piping.c control_flow.c

.PHONY: turtle.out clean