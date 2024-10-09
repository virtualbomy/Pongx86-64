#Ejecutable
TARGET = app

#Archivos fuente
SRC = main.c menu.c

#Compilador
CC = gcc

#Flags
CFLAGS = -c
GTK_CFLAGS = `pkg-config --cflags gtk+-3.0`
GTK_LDFLAGS = `pkg-config --libs gtk+-3.0`

#Objetivos
OBJS = main.o menu.o

#Regla por defecto
all: $(TARGET)

#Compilación
%.o: %.c
	$(CC) $(CFLAGS) $< -o $@ $(GTK_CFLAGS)

#Compilación del ejecutable
$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(GTK_LDFLAGS)

#Regla para ejecutar el programa
run: $(TARGET)
	./$(TARGET)

#Limpiar archivos generados
clean:
	rm -f $(TARGET) $(OBJS)

