build_keygen:
	gcc keygen.c -lssl -lcrypto -o keygen.out

clean_keygen:
	rm -rf ./keygen.out

rebuild_keygen:
	@make clean_keygen
	@make build_keygen

keygen:
	./keygen.out

run:
	rm -rf ./main.out && gcc -o main.out main.c -lssl -lcrypto && ./main.out

clean:
	rm -rf *.out
	rm -rf *.pem
