build:
	python3 setup.py build
install:
	python3 setup.py install
clean:
	rm -rf build
uninstall:
	rm -rf /usr/local/lib/python3.6/dist-packages/bcoll.cpython-36m-x86_64-linux-gnu.so
	rm -rf /usr/local/lib/python3.6/dist-packages/BColl-1.0.egg-info
