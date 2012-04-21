SRC_DIR=src
LIBS=SDL
MODULES=engine game init
MAIN=main
APP=app

compile: modules
	gcc -o $(APP) $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(MAIN))) $(addsuffix .o, $(MODULES)) $(addprefix -l, $(LIBS))
	rm -rf $(addsuffix .o, $(MODULES))

modules:
	gcc -c $(addprefix $(SRC_DIR)/,$(addsuffix .c, $(MODULES)))

clean:
	rm -rf *.o app
