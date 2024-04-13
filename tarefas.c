#include <stdio.h>
#include <string.h>
#include "tarefas.h"

ERROS criar(Tarefa tarefas[], int *pos){
    if(*pos >= TOTAL)
        return MAX_TAREFA;

  printf("Entre com a prioridade: ");
  if (scanf("%d", &tarefas[*pos].prioridade) != 1) {
      printf("Erro na leitura da prioridade\n");
  } else if (tarefas[*pos].prioridade > 10) {
      printf("A prioridade não pode ser maior que 10\n");
      return LER; 
  }
  
      clearBuffer();

      printf("Entre com a categoria: ");
      if (fgets(tarefas[*pos].categoria, 100, stdin) == NULL) { 
          printf("Erro na leitura da categoria\n");
          return LER; 
      }
      tarefas[*pos].categoria[strcspn(tarefas[*pos].categoria, "\n")] = '\0';

      printf("Entre com a descricao: ");
      if (fgets(tarefas[*pos].descricao, 300, stdin) == NULL) { 
          printf("Erro na leitura da descricao\n");
          return LER; 
      }
      tarefas[*pos].descricao[strcspn(tarefas[*pos].descricao, "\n")] = '\0';
      pos = pos + 1;

      return OK;
  }

ERROS deletar(Tarefa tarefas[], int *pos){
    
    if(*pos == 0)
        return SEM_TAREFAS;

    
    int pos_deletar;
    printf("Entre com a posicao da tarefa a ser deletada: ");
  if (scanf("%d", &pos_deletar) != 1) { 
      printf("Erro na leitura da posição\n");
      return LER; 
  }
    pos_deletar--; 
    if(pos_deletar >= *pos || pos_deletar < 0)
        return NAO_ENCONTRADO;

      for(int i = pos_deletar; i < *pos - 1; i++){ 
      tarefas[i].prioridade = tarefas[i+1].prioridade;
      strcpy(tarefas[i].categoria, tarefas[i+1].categoria);
      strcpy(tarefas[i].descricao,  tarefas[i+1].descricao);
  }

    *pos = *pos - 1;

    return OK;
}

ERROS listar(Tarefa tarefas[], int *pos){
    if(*pos == 0)
        return SEM_TAREFAS;

    for(int i=0; i<*pos; i++){
        printf("Pos: %d\t", i+1);
        printf("Prioridade: %d\t", tarefas[i].prioridade);
        printf("Categoria: %s\t", tarefas[i].categoria);
        printf("Descricao: %s\n", tarefas[i].descricao);
    }

    return OK;
}

ERROS salvar(Tarefa tarefas[], int *pos){
    FILE *f = fopen("tarefas.bin", "wb");
    if(f == NULL)
        return ABRIR;

    int qtd = fwrite(tarefas, TOTAL, sizeof(Tarefa), f);
    if(qtd == 0)
        return ESCREVER;

    qtd = fwrite(pos, 1, sizeof(int), f);
    if(qtd == 0)
        return ESCREVER;

    if(fclose(f))
        return FECHAR;

    return OK;
}

ERROS carregar(Tarefa tarefas[], int *pos){
    FILE *f = fopen("tarefas.bin", "rb");
    if(f == NULL)
        return ABRIR;

    int qtd = fread(tarefas, TOTAL, sizeof(Tarefa), f);
    if(qtd == 0)
        return LER;

    qtd = fread(pos, 1, sizeof(int), f);
    if(qtd == 0)
        return LER;

    if(fclose(f))
        return FECHAR;

    return OK;

}

ERROS listar_por_categoria(Tarefa tarefas[], int *pos){
    char categoria[TAM_CATEGORIA];
    printf("Digite a categoria que deseja listar (deixe em branco para listar todas): ");

    
    if (fgets(categoria, TAM_CATEGORIA, stdin) == NULL) { 
        printf("Erro na leitura da categoria\n");
        return LER; 
    }
    categoria[strcspn(categoria, "\n")] = '\0'; 

    int encontrou_tarefa = 0;

    for (int i = 0; i < *pos; i++) {
        if (categoria[0] == '\0' || strcmp(tarefas[i].categoria, categoria) == 0) {
            printf("Pos: %d\t", i + 1);
            printf("Prioridade: %d\t", tarefas[i].prioridade);
            printf("Categoria: %s\t", tarefas[i].categoria);
            printf("Descricao: %s\n", tarefas[i].descricao);
            encontrou_tarefa = 1;
        }
    }

    if (!encontrou_tarefa) {
        printf("Nenhuma tarefa encontrada para a categoria especificada\n");
        return NAO_ENCONTRADO;
    }

    return OK;
}

ERROS exportar(Tarefa tarefas[], int *pos) {
    char nome_arquivo[100];
    printf("Digite o nome do arquivo de texto para exportar as tarefas: ");
  if (scanf("%s", nome_arquivo) != 1) {
      printf("Erro na leitura do nome do arquivo\n");
      return LER;
  }

    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita\n");
        return ABRIR;
    }

    for (int i = 0; i < *pos; i++) {
        fprintf(arquivo, "Prioridade: %d\tCategoria: %s\tDescricao: %s\n", tarefas[i].prioridade, tarefas[i].categoria, tarefas[i].descricao);
    }

    fclose(arquivo);
    printf("Tarefas exportadas com sucesso para o arquivo %s\n", nome_arquivo);

    return OK;
}

ERROS salvar_binario(Tarefa tarefas[], int *pos) {
    FILE *arquivo = fopen("tarefas.bin", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo binário para escrita\n");
        return ABRIR;
    }

    int qtd_escrita = fwrite(tarefas, sizeof(Tarefa), *pos, arquivo);
    if (qtd_escrita != *pos) {
        printf("Erro ao escrever no arquivo binário\n");
        fclose(arquivo);
        return ESCREVER;
    }

    qtd_escrita = fwrite(pos, sizeof(int), 1, arquivo);
    if (qtd_escrita != 1) {
        printf("Erro ao escrever no arquivo binário\n");
        fclose(arquivo);
        return ESCREVER;
    }

    fclose(arquivo);
    printf("Tarefas salvas com sucesso no arquivo binário\n");

    return OK;
}

ERROS carregar_binario(Tarefa tarefas[], int *pos) {
    FILE *arquivo = fopen("tarefas.bin", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo binário para leitura\n");
        return ABRIR;
    }

    int qtd_lida = fread(tarefas, sizeof(Tarefa), TOTAL, arquivo);
    if (qtd_lida <= 0) {
        printf("Erro ao ler do arquivo binário\n");
        fclose(arquivo);
        return LER;
    }

    qtd_lida = fread(pos, sizeof(int), 1, arquivo);
    if (qtd_lida != 1) {
        printf("Erro ao ler do arquivo binário\n");
        fclose(arquivo);
        return LER;
    }

    fclose(arquivo);
    printf("Tarefas carregadas com sucesso do arquivo binário\n");

    return OK;
}



void clearBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
