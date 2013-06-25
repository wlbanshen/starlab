help:
	@echo "- help 			this help"
	@echo "- reinitialize	deletes all sub-repo folders and the .user files"
	@echo "- fresh			reinitialize + download + open"
	@echo "- download 		downloads all sub-repositories"
	@echo "- open	 		opens the starlab_mini.pro in QtCreator"
	@echo "- clean			deletes the deployed application folder e.g. /Applications/Starlab.app"
	@echo "- mini 			builds starlab_mini.pro from sources into ../starlab_mini_build"
	@echo "- full 			builds starlab_full.pro from sources into ../starlab_full_build"

initialize:  clear download open

download: 
	git clone https://code.google.com/p/starlab.core core
	git clone https://code.google.com/p/starlab.surfacemesh surfacemesh
	git clone https://code.google.com/p/starlab.examples examples

clean:
	rm -rf /Applications/Starlab.app

clear:
	rm -rf /Applications/Starlab.app
	rm -rf core
	rm -rf surfacemesh
	rm -rf *.pro.user
	rm -rf ../starlab_mini_build
	rm -rf ../starlab_full_build

open:
ifeq ($(OS),Windows_NT)
	explorer.exe starlab_mini.pro
else
	open starlab_mini.pro
endif

mini:
	mkdir -p ../starlab_mini_build
	cd ../starlab_mini_build; qmake ../starlab/starlab_mini.pro
	cd ../starlab_mini_build; make -j8

full:
	mkdir -p ../starlab_full_build
	cd ../starlab_full_build; qmake ../starlab/starlab_full.pro
	cd ../starlab_full_build; make -j8
