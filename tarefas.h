#define TOTAL 100
#define TAM_CATEGORIA 100
#define TAM_DESCRICAO 300
#define NOME_ARQUIVO "tarefas.txt"
#define NOME_ARQUIVO_BINARIO "tarefas.bin"

typedef struct {
    int prioridade;
    char descricao[300];
    char categoria[100];
} Tarefa;

typedef enum {OK, MAX_TAREFA, SEM_TAREFAS, NAO_ENCONTRADO, ABRIR, FECHAR, ESCREVER, LER} ERROS;

typedef ERROS (*funcao)(Tarefa[], int*);

ERROS criar(Tarefa tarefas[], int *pos);
ERROS deletar(Tarefa tarefas[], int *pos);
ERROS listar(Tarefa tarefas[], int *pos);
ERROS salvar(Tarefa tarefas[], int *pos);
ERROS carregar(Tarefa tarefas[], int *pos);
ERROS listar_por_categoria(Tarefa tarefas[], int *pos);

void clearBuffer();

