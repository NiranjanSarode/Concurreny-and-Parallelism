list:
	gcc -o obj/list_test test/list_test.c src/list.c
	./obj/list_test

hash:
	gcc -o obj/hashmap_test test/hashmap_test.c src/hm.c src/list.c src/mythread.c
	./obj/hashmap_test

main:
	gcc -o obj/main test/main.c src/hm.c src/list.c src/mythread.c
	./obj/main data/in1.txt data/in2.txt data/in3.txt data/in4.txt
	
timer:
	gcc -o obj/main test/main.c src/hm.c src/list.c src/mythread.c
	time ./obj/main data/in1.txt data/in2.txt data/in3.txt data/in4.txt