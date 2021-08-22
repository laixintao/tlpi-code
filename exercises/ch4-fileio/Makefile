tee:
	gcc tee.c -o tee

test-tee: tee
	cat tee.c | ./tee tee_copy.log

clean:
	rm -f tee
	rm -f create_filehole filehole cp filehole2


create-filehole: clean
	gcc create_filehole.c -o create_filehole

cp: clean
	gcc cp.c -o cp

test-cp-hole: create-filehole cp
	./create_filehole
	./cp filehole filehole2
