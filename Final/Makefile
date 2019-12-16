NAME = final
CC = g++
CFLAGS = -Wall -pthread -std=c++11
OBJDIR = obj
SRCDIR = .
BINDIR = bin
DEPS = broker simclient
MAIN = main
MD = mkdir

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@$(MD) -p $(OBJDIR)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: all
all: $(MAIN)
	@echo "Successfully build"

.PHONY: debug
debug: CFLAGS += -g -DDEBUG
debug: $(MAIN)
	@echo "Successfully build the debug version"

$(MAIN): $(addsuffix .o, $(addprefix $(OBJDIR)/, $(DEPS)))
	@$(MD) -p $(BINDIR)
	$(CC) -o $(BINDIR)/$@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean
clean:
	@rm -Rf $(addsuffix .o, $(addprefix $(OBJDIR)/, $(DEPS))) $(BINDIR)/$(NAME)
	@echo "All clean!"