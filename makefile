npextension.so:
	CC='gcc -std=c99' python3 setup.py build_ext --inplace

test:
	python test.py
