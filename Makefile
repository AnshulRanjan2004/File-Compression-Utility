# Nome do projeto e do executável encontrado no diretório corrente após compilação
PROJ_NAME = mata54comp

# Arquivos .c encontrados em src/
C_SOURCE = $(wildcard ./src/*.cpp)

# Arquivos .h encontrados em include/
H_SOURCE = $(wildcard ./include/*.h)

# Arquivos objetos .o encontrados em build/ após compilação
OBJ = $(subst .cpp,.o,$(subst src,build,$(C_SOURCE)))

# Compilador utilizado
CC = g++

# Flags utilizadas na compilação
CC_FLAGS = -c \
           -g \
           -std=c++0x \

# Comando de construção de diretório
MKDIR = mkdir -p

# Comando de limpeza de alvos 
RM = rm -rf

GREEN=\033[0;32m
NC=\033[0m

CFOLDER = tests/compress
DFOLDER = tests/decompress

# Regras de compilação
all: clean objFolder $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	@ $(CC) $^ -o $@
	@ echo -e -n " [${GREEN} OK ${NC}]"
	@ echo " Binário construido: $@"

./build/%.o: ./src/%.cpp ./include/%.h
	@ $(CC) $< $(CC_FLAGS) -o $@
	@ echo -e -n " [${GREEN} OK ${NC}]"
	@ echo " Compilado $< em $@"

# Regra de criação de diretório para os objetos
objFolder:
	@ $(MKDIR) build
	@ echo -e -n " [${GREEN} OK ${NC}]"
	@ echo ' Criado diretório para objetos' 

# Regra de limpeza de objetos e executável
clean: clean-tests
	@ $(RM) build $(PROJ_NAME) *~
	@ echo -e -n " [${GREEN} OK ${NC}]"
	@ echo ' Workspace limpo'

tests: init compress decompress check

init: ./tests/compression-checker.cpp
	@ $(CC) $< -o $(subst .cpp,,$<)
	@ $(MKDIR) $(CFOLDER)
	@ $(MKDIR) $(DFOLDER)

compress:
	@ $(foreach file, $(wildcard $(CFOLDER)/*), ./$(PROJ_NAME) -c $(file) && ./tests/compression-checker $(file) $(subst $(suffix $(file)),.cmp,$(file)) && mv $(CFOLDER)/*.cmp $(DFOLDER)/;)

decompress:
	@ $(foreach file, $(wildcard $(DFOLDER)/*), ./$(PROJ_NAME) -d $(file);)
	
check:
	@ $(foreach file, $(wildcard $(CFOLDER)/*), diff -s $(file) $(subst $(CFOLDER), $(DFOLDER), $(subst $(suffix $(file)),,$(file)));)

clean-tests:
	@ $(RM) ./tests/compression-checker
	@ $(RM) $(DFOLDER)/*

.PHONY: all clean 