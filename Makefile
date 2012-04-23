SRC_DIR=src
LIBS=SDL m
FLAGS=-O2
MODULES=engine game init world collision power bullet enemy background item stage stage-1 stage-2 stage-3 gameover
MAIN=main
APP=ld23-dont-leave-our-home

compile: modules
	gcc -o $(APP) $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(MAIN))) $(addsuffix .o, $(MODULES)) $(addprefix -l, $(LIBS)) $(FLAGS)
	rm -rf $(addsuffix .o, $(MODULES))

modules:
	gcc -c $(addprefix $(SRC_DIR)/,$(addsuffix .c, $(MODULES))) $(FLAGS)

clean:
	rm -rf *.o app
