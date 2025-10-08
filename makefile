# Compilador
CXX = g++
CXXFLAGS = -std=c++11 -Wall -I.

# Bibliotecas SFML
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Nome do executável
TARGET = snake_game

# Arquivos fonte
SOURCES = main.cpp snake.cpp game.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Regra padrão - agora compila E executa
all: $(TARGET)
	@echo "Compilação concluída! Executando o jogo..."
	./$(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(SFML_LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilar e executar (alias para 'all')
run: all

# Apenas compilar sem executar
build: $(TARGET)
	@echo "Compilação concluída! Execute com: ./$(TARGET) ou 'make run'"

# Limpeza
clean:
	rm -f $(OBJECTS) $(TARGET)

# Recompilar tudo e executar
rebuild: clean all

# Instruções de uso
help:
	@echo "Targets disponíveis:"
	@echo "  all     - Compila e executa o jogo (padrão)"
	@echo "  run     - Compila e executa o jogo"
	@echo "  build   - Apenas compila sem executar"
	@echo "  clean   - Remove arquivos objeto e executável"
	@echo "  rebuild - Recompila tudo do zero e executa"
	@echo "  help    - Mostra esta ajuda"

.PHONY: all run build clean rebuild help