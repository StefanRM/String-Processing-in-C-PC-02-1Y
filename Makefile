build-t1:
	gcc task1.c -o task1

build-t2:
	gcc task2.c -o task2

build-t3:
	gcc task3.c -o task3

run-t1:
	./task1

run-t2:
	./task2

run-t3:
	./task3

clean:
	rm -f task1 task2 task3
