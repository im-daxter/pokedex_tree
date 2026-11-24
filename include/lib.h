#ifndef LIB_H
#define LIB_H

#define DATASET_DIR "dataset"

typedef struct {
    int id;
    char nome[50];
    int ataque;
    int defesa;
    int velocidade;
} Pokemon;

// CRUD
void criarPokemon();
void listarPokemons();
void buscarPokemon();
void atualizarPokemon();
void deletarPokemon();

void menu();

#endif
