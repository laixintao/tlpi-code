tee:
	gcc tee.c -o tee

test-tee: tee
	cat tee.c | ./tee tee_copy.log

clean:
	rm -f tee
