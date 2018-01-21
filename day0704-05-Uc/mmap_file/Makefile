

mmap_file:mmap_read.o mmap_write.o
	gcc *.o 
	rm *.o
	mv a.out mmap_file
mmap_write.o:mmap_write.c
	gcc -E mmap_write.c -o mmap_write.i
	gcc -S mmap_write.i -o mmap_write.s
	gcc -c mmap_write.s -o mmap_write.o
mmap_read.o:mmap_read.c
	gcc -E mmap_read.c -o mmap_read.i
	gcc -S mmap_read.i -o mmap_read.s
	gcc -c mmap_read.s -o mmap_read.o
clean:
	rm -rf mmap_write mmap_read<strong>


