CC=gcc
CFLAGS	:= -Wall -ggdb
OBJDIR  := obj
TARGET 	:= complier

SRCS 	:= main.c lexer.c  
OBJS    := $(SRCS:%.c=$(OBJDIR)/%.o)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o complier

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@ 

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(TARGET)
