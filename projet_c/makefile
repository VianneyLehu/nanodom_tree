 opt = -c -Wall -Wextra -g

test_nanodom.exe : p_nanodom.o p_text_enrichi.o test_nanodom.o
	gcc -o runproject.exe p_nanodom.o p_text_enrichi.o test_nanodom.o

test_nanodom.o : p_nanodom.o test_nanodom.c
	gcc ${opt} test_nanodom.c

test_text_enrichi.o: p_text_enrichi.o test_text_enrichi.c
	gcc ${opt} test_text_enrichi.c

p_text_enrichi.o: p_text_enrichi.c p_text_enrichi.h
	gcc ${opt} p_text_enrichi.c

p_nanodom.o : p_nanodom.c p_nanodom.h 
	gcc ${opt} p_nanodom.c 

clean :
	rm *.o
	rm *.exe