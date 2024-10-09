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

#Reglas por defecto
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

#Asegúrate de que el archivo CSS esté presente
style.css:
	@echo "Asegúrate de que el archivo style.css esté en el directorio actual."

.PHONY: all clean run style.css
