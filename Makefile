.PHONY: gitclean
all:

gitclean:
	git clean -idX

install-toolchain:
	cd nachos-3.4/code/test && ./install_cross_gcc.sh
