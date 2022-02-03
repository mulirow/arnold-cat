# code directory name
SRCDIR := src

# binary output directory name
OUTPUTDIR := bin

# C flags
CFLAGS := 

# load flags
LDLIB := `pkg-config --cflags --libs opencv4`

# compiler
CC := g++

# extension
EXT := cpp

SRCS := $(wildcard $(SRCDIR)/*.$(EXT))
OBJS := $(subst $(SRCDIR)/, , $(patsubst %.$(EXT), %, $(SRCS)))

all: mkdirs $(OBJS)

%: $(SRCDIR)/%.$(EXT)
	$(CC) $< -o $(OUTPUTDIR)/$@ $(CFLAGS) $(LDLIB)

mkdirs:
	@mkdir -p $(OUTPUTDIR)