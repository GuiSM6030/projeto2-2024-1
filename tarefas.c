#include <stdio.h>
#include <string.h>
#include "tarefas.h"

ERROS criar(Tarefa tarefas[], int *pos){
    if(*pos >= TOTAL)
        return MAX_TAREFA;

  printf("Entre com a prioridade: ");
      if (scanf("%d", &tarefas[*pos].prioridade) != 1) { 
          printf("Erro na leitura da prioridade\n");
          return LER; 
      }
      clearBuffer();

      printf("Entre com a categoria: ");
      if (fgets(tarefas[*pos].categoria, 100, stdin) == NULL) { 
          printf("Erro na leitura da categoria\n");
          return LER; 
      }
      tarefas[pos].categoria[strcspn(tarefas[pos].categoria, "\n")] = '\0';

      printf("Entre com a descricao: ");
      if (fgets(tarefas[*pos].descricao, 300, stdin) == NULL) { 
          printf("Erro na leitura da descricao\n");
          return LER; 
      }
      tarefas[pos].descricao[strcspn(tarefas[pos].descricao, "\n")] = '\0';
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
      return LER; /
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
    // Implementação para listar tarefas por categoria
}

ERROS exportar (Tarefa tarefas[], int *pos);

ERROS salvar_binario(Tarefa tarefas[], int *pos);

ERROS carregar_binario (Tarefa tarefas[], int *pos);

void clearBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
