all:
	$(CC) -c kernel/main.c -o build/main.o
	# Compile other files...
	ld -T build/linker.ld -o build/coreX.bin build/*.o
	grub-mkrescue -o build/coreX.iso build/all:
	
