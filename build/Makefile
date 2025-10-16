all:
	$(CC) -c kernel/init/kernel_main.c -o build/kernel_main.o
	# Compile other files...
	ld -T build/linker.ld -o build/coreX.bin build/*.o
	grub-mkrescue -o build/coreX.iso build/all:
	
