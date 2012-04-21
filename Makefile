SRC_DIR=src
LIBS=SDL
MODULES=engine
MAIN=main
APP=app

compile: modules
	gcc -o $(APP) $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(MAIN))) $(addsuffix .o, $(MODULES)) $(addprefix -l, $(LIBS))

modules:
	gcc -c $(addprefix $(SRC_DIR)/,$(addsuffix .c, $(MODULES)))

clean:
	rm -rf *.o app
