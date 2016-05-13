BIN = main
SRCS = main.cpp plugincontainer.cpp
PLUGIN_SRCS = plugin_a.cpp plugin_b.cpp

CFLAGS = -s -O2 -Wall -Werror -std=c++11
LDFLAGS = -ldl
LDFLAGS_PLUGIN = -fPIC -shared

OBJS = $(SRCS:%.cpp=%.o)
PLUGIN_SOBJS = $(PLUGIN_SRCS:%.cpp=%.so)

.PHONY: all clean

all: $(BIN) $(PLUGIN_SOBJS)

%.so: %.cpp
	g++ $(CFLAGS) -o $@ $< $(LDFLAGS_PLUGIN)

%.o: %.cpp
	g++ $(CFLAGS) -c -o $@ $<

$(BIN): $(OBJS)
	g++ $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(BIN) $(OBJS) $(PLUGIN_SOBJS)
