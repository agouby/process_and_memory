SRC=get_pid_info
DEST=/usr/src/kernel-$(shell uname -r)

all:
	rm -rf $(DEST)/$(SRC)
	cp -R $(SRC) $(DEST)
	make -C $(DEST) -j8
