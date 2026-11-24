#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/lib.h"

#include <vlc/vlc.h>

#ifdef _WIN32
    #include <windows.h>
    #define SLEEP_MS(ms) Sleep(ms)
#else
    #include <unistd.h>
    #define SLEEP_MS(ms) usleep((ms) * 1000)
#endif

#define QUANTIDADE_JANELAS 5

void criarPokemon() {
    Pokemon p;
    char caminho[100];

    printf("\n=== CADASTRAR POKEMON ===\n");

    printf("ID: ");
    scanf("%d", &p.id);

    // Verifica se o ID ja existe
    sprintf(caminho, DATASET_DIR "/doc%03d.txt", p.id);

    FILE *arquivo = fopen(caminho, "r");

    if (arquivo != NULL) {
        printf("Pokemon com esse ID ja existe!\n");
        fclose(arquivo);
        return;
    }

    printf("Nome: ");
    scanf(" %49[^\n]", p.nome);

    printf("Ataque (0-100): ");
    scanf("%d", &p.ataque);

    printf("Defesa (0-100): ");
    scanf("%d", &p.defesa);

    printf("Velocidade (0-100): ");
    scanf("%d", &p.velocidade);

    if (p.ataque < 0 || p.ataque > 100 ||
        p.defesa < 0 || p.defesa > 100 ||
        p.velocidade < 0 || p.velocidade > 100) {
        printf("Valores devem estar entre 0 e 100!\n");
        return;
    }

    arquivo = fopen(caminho, "w");

    if (arquivo == NULL) {
        printf("Erro ao criar arquivo!\n");
        return;
    }

    fprintf(arquivo, "%d\n", p.id);
    fprintf(arquivo, "%s\n", p.nome);
    fprintf(arquivo, "%d\n", p.ataque);
    fprintf(arquivo, "%d\n", p.defesa);
    fprintf(arquivo, "%d\n", p.velocidade);

    fclose(arquivo);

    printf("Pokemon cadastrado com sucesso!\n");
}


void listarPokemons() {
    Pokemon p;
    char caminho[100];

    printf("\n=== LISTA DE POKEMONS ===\n");

    for (int i = 1; i <= 100; i++) {

        sprintf(caminho, DATASET_DIR "/doc%03d.txt", i);

        FILE *arquivo = fopen(caminho, "r");

        if (arquivo == NULL)
            continue;

        if (fscanf(arquivo, "%d\n", &p.id) == 1 &&
            fgets(p.nome, sizeof(p.nome), arquivo) != NULL &&
            fscanf(arquivo, "%d%d%d",
                   &p.ataque,
                   &p.defesa,
                   &p.velocidade) == 3) {

            p.nome[strcspn(p.nome, "\n")] = '\0';

            printf("\nID: %d\n", p.id);
            printf("Nome: %s\n", p.nome);
            printf("Ataque: %d\n", p.ataque);
            printf("Defesa: %d\n", p.defesa);
            printf("Velocidade: %d\n", p.velocidade);
        }

        fclose(arquivo);
    }
}


void buscarPokemon() {
    int id;
    Pokemon p;
    char caminho[100];

    printf("\n=== BUSCAR POKEMON ===\n");

    printf("Digite o ID: ");
    scanf("%d", &id);

    if (id < 1 || id > 100) {
        printf("ID invalido!\n");
        return;
    }

    sprintf(caminho, DATASET_DIR "/doc%03d.txt", id);

    FILE *arquivo = fopen(caminho, "r");

    if (arquivo == NULL) {
        printf("Pokemon nao encontrado!\n");
        return;
    }

    if (fscanf(arquivo, "%d\n", &p.id) != 1 ||
        fgets(p.nome, sizeof(p.nome), arquivo) == NULL ||
        fscanf(arquivo, "%d%d%d",
               &p.ataque,
               &p.defesa,
               &p.velocidade) != 3) {
        printf("Arquivo com formato invalido!\n");
        fclose(arquivo);
        return;
    }

    p.nome[strcspn(p.nome, "\n")] = '\0';

    printf("\nID: %d\n", p.id);
    printf("Nome: %s\n", p.nome);
    printf("Ataque: %d\n", p.ataque);
    printf("Defesa: %d\n", p.defesa);
    printf("Velocidade: %d\n", p.velocidade);

    fclose(arquivo);
}


void atualizarPokemon() {
    int id;
    Pokemon p;
    char caminho[100];

    printf("\n=== ATUALIZAR POKEMON ===\n");

    printf("Digite o ID: ");
    scanf("%d", &id);

    if (id < 1 || id > 100) {
        printf("ID invalido!\n");
        return;
    }

    sprintf(caminho, DATASET_DIR "/doc%03d.txt", id);

    FILE *arquivo = fopen(caminho, "r");

    if (arquivo == NULL) {
        printf("Pokemon nao encontrado!\n");
        return;
    }

    if (fscanf(arquivo, "%d\n", &p.id) != 1 ||
        fgets(p.nome, sizeof(p.nome), arquivo) == NULL ||
        fscanf(arquivo, "%d%d%d",
               &p.ataque,
               &p.defesa,
               &p.velocidade) != 3) {
        printf("Arquivo com formato invalido!\n");
        fclose(arquivo);
        return;
    }

    fclose(arquivo);

    p.nome[strcspn(p.nome, "\n")] = '\0';

    printf("Novo nome: ");
    scanf(" %49[^\n]", p.nome);

    printf("Novo ataque (0-100): ");
    scanf("%d", &p.ataque);

    printf("Nova defesa (0-100): ");
    scanf("%d", &p.defesa);

    printf("Nova velocidade (0-100): ");
    scanf("%d", &p.velocidade);

    if (p.ataque < 0 || p.ataque > 100 ||
        p.defesa < 0 || p.defesa > 100 ||
        p.velocidade < 0 || p.velocidade > 100) {
        printf("Valores devem estar entre 0 e 100!\n");
        return;
    }

    arquivo = fopen(caminho, "w");

    if (arquivo == NULL) {
        printf("Erro ao atualizar Pokemon!\n");
        return;
    }

    fprintf(arquivo, "%d\n", p.id);
    fprintf(arquivo, "%s\n", p.nome);
    fprintf(arquivo, "%d\n", p.ataque);
    fprintf(arquivo, "%d\n", p.defesa);
    fprintf(arquivo, "%d\n", p.velocidade);

    fclose(arquivo);

    printf("Pokemon atualizado com sucesso!\n");
}

void removePokemon() {
    const char *caminho_video = "dataset/picareta.mp4";

#ifdef _WIN32
    const char *args[] = {
        "--no-video-title-show"
    };
    int num_args = 1;
#else
    const char *args[] = {
        "--avcodec-hw=none",
        "--vout=gl",
        "--no-x11-shm",
        "--no-video-title-show"
    };
    int num_args = 4;
#endif

    libvlc_instance_t *inst = libvlc_new(num_args, args);

    if (!inst) {
        fprintf(stderr, "Erro ao inicializar LibVLC.\n");
        return;
    }

    libvlc_media_t *media =
        libvlc_media_new_path(inst, caminho_video);

    if (!media) {
        fprintf(stderr, "Erro ao carregar o video.\n");
        libvlc_release(inst);
        return;
    }

    libvlc_media_player_t *players[QUANTIDADE_JANELAS] = {NULL};

    for (int i = 0; i < QUANTIDADE_JANELAS; i++) {
        players[i] = libvlc_media_player_new_from_media(media);

        if (players[i]) {
            libvlc_media_player_play(players[i]);
            SLEEP_MS(150);
        }
    }

    libvlc_media_release(media);

    SLEEP_MS(1000);

    int algum_tocando;

    do {
        algum_tocando = 0;

        for (int i = 0; i < QUANTIDADE_JANELAS; i++) {
            if (players[i]) {
                libvlc_state_t estado =
                    libvlc_media_player_get_state(players[i]);

                if (estado == libvlc_Playing ||
                    estado == libvlc_Buffering ||
                    estado == libvlc_Opening) {
                    algum_tocando = 1;
                }
            }
        }

        SLEEP_MS(200);

    } while (algum_tocando);

    for (int i = 0; i < QUANTIDADE_JANELAS; i++) {
        if (players[i]) {
            libvlc_media_player_stop(players[i]);
            libvlc_media_player_release(players[i]);
        }
    }

    libvlc_release(inst);
}

void deletarPokemon() {
    int id;
    char caminho[100];

    printf("\n=== DELETAR POKEMON ===\n");

    printf("Digite o ID: ");
    scanf("%d", &id);

    if (id < 1 || id > 100) {
        printf("ID invalido!\n");
        return;
    }

    sprintf(caminho, DATASET_DIR "/doc%03d.txt", id);

    FILE *arquivo = fopen(caminho, "r");

    if (arquivo == NULL) {
        printf("Pokemon nao encontrado!\n");
        return;
    }

    fclose(arquivo);

    if (remove(caminho) == 0) {
        printf("Pokemon deletado com sucesso!\n");

	removePokemon();
    } else {
        printf("Erro ao deletar Pokemon!\n");
	removePokemon();
    }

    removePokemon();
}


void menu() {
    int opcao;

    do {
        printf("\n========== POKEDEX ==========\n");
        printf("1 - Cadastrar Pokemon\n");
        printf("2 - Listar Pokemons\n");
        printf("3 - Buscar Pokemon\n");
        printf("4 - Atualizar Pokemon\n");
        printf("5 - Deletar Pokemon\n");
        printf("0 - Sair\n");
        printf("=============================\n");

        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                criarPokemon();
                break;

            case 2:
                listarPokemons();
                break;

            case 3:
                buscarPokemon();
                break;

            case 4:
                atualizarPokemon();
                break;

            case 5:
                deletarPokemon();
                break;

            case 0:
                printf("Encerrando Pokedex...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);
}
