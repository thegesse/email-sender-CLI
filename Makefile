# Compiler and flags
CC = gcc

# Auto-detect PostgreSQL paths
PG_INCLUDE = $(shell pg_config --includedir)
PG_LIB = $(shell pg_config --libdir)

CFLAGS = -Wall -Wextra -g \
         -I$(DB_DIR) -I$(EMAIL_DIR) -I$(QUERIES_DIR) \
         -I$(PG_INCLUDE)

LDFLAGS = -L$(PG_LIB) -lpq


# Directories
DB_DIR = database-connection
EMAIL_DIR = email
QUERIES_DIR = queries

# Source files
SRCS = main.c \
       $(EMAIL_DIR)/email_sender.c \
       $(QUERIES_DIR)/sql_queries.c \
       $(DB_DIR)/connection.c

# Object files
OBJS = main.o \
       $(EMAIL_DIR)/email_sender.o \
       $(QUERIES_DIR)/sql_queries.o \
       $(DB_DIR)/connection.o

# Target executable
TARGET = email_sender

# Default target
all: $(TARGET)

# Link executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile rules
main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

$(EMAIL_DIR)/email_sender.o: $(EMAIL_DIR)/email_sender.c
	$(CC) $(CFLAGS) -c $< -o $@

$(QUERIES_DIR)/sql_queries.o: $(QUERIES_DIR)/sql_queries.c
	$(CC) $(CFLAGS) -c $< -o $@

$(DB_DIR)/connection.o: $(DB_DIR)/connection.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(OBJS) $(TARGET)

rebuild: clean all

run: $(TARGET)
	@set -a; . $(DB_DIR)/db.env; set +a; ./$(TARGET)

.PHONY: all clean rebuild run