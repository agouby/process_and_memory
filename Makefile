SRC=get_pid_info
DEST=/usr/src/linux-$(shell uname -r)

all:
	rm -rf $(DEST)/$(SRC)
	cp -R $(SRC) $(DEST)
	cp syscalls.h $(DEST)/include/linux
	cp syscall_64.tbl $(DEST)/arch/x86/entry/syscalls
	cp Makefile.kernel $(DEST)/Makefile
ifneq ("$(wildcard $(DEST)/.config)","")
	mv $(DEST)/.config $(DEST)/.config.old
endif
	cp config $(DEST)/.config
	make -C $(DEST) -j8
	cp $(DEST)/arch/x86/boot/bzImage /boot/vmlinuz-process_and_memory
	cp $(DEST)/System.map /boot/System.map-process_and_memory
	cp $(DEST)/.config /boot/config-process_and_memory
	gcc -Wall -Werror -Wextra test.c -o test
	reboot

clean:
	rm -f test
