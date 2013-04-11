all: config clear download open

config:

download: 
	git clone https://code.google.com/p/starlab.core core
	git clone https://code.google.com/p/starlab.surfacemesh surfacemesh

clean:
	rm -rf /Applications/Starlab.app

clear:
	rm -rf /Applications/Starlab.app
	rm -rf core
	rm -rf surfacemesh
	rm -rf *.user.pro

open:
ifeq ($(OS),Windows_NT)
	explorer.exe starlab_mini.pro
else
	open starlab_mini.pro
endif
