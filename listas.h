#include<stdbool.h>


typedef struct lista{
  void* info;
  struct lista* prox;
}Lista;

typedef struct professor{
	char nome[255];
	int siape;
	char areaDeAtuacao[255];
	char titulacao[255];
}Professor;

typedef struct curso{
	int codigo;
	char nome[255];
}Curso;

typedef struct disciplina{
	int codigo;
	Curso* curso;
	char nome[255];
	int cargaHoraria;
	Lista* preRequisitos;
}Disciplina;

typedef struct turma{
	int codigo;
	Lista* professores;
	Lista* alunos;
	Lista* avaliacoes;
	Disciplina* disciplina;
	Lista* aulas;
	Lista* situacoes;
}Turma;

typedef struct aluno{
	char nome[255];
	int matricula;
	Curso* curso;
}Aluno;

typedef struct avaliacao{
	int codigo;
	Lista* notas;
}Avaliacao;

typedef struct nota{
	Aluno* aluno;
	float valor;
}Nota;

typedef struct aula{
	char data[255];
	char conteudo[255]; 
	Lista* presencas;
}Aula;

typedef struct presenca{
	Aluno* aluno;
	bool presente;
}Presenca;

typedef struct relatorio{
	Lista* aprovados;
	Lista* reprovadosPorNota;
	Lista* reprovadosPorFreq;
}Relatorio;

typedef struct situacao{
    Aluno* aluno;
    float sumNotas;
	float media; // sum(notas)/numAvaliacoes >= 7.00
	float frequencia; // presencas >= cargaHoraria*0.75
	float sumPresencas;
}Situacao;

/*Funções Genéricas*/

// Verifica situação da lista
bool vazia(Lista* lista);

// Retorna o ultimo membro da lista
Lista* ultimo(Lista* lista);

// Função auxiliar para criar lista nulla
Lista* criarLista(void);

// Verifica o estado da lista e insere inicio da lista
Lista* inserirInicio(Lista* lista, void* elemento);

// Verifica estado da lista e insere fim da lista
Lista* inserirFim(Lista* lista, void* elemento);

// Retira elementos da lista usando uma lista temporaria
Lista* retirar(Lista* lista, void* elemento, bool iguais(void*, void*));

// Imprime a lista toda
void imprimirLista(Lista* lista, void imprimirElemento(void*));

// Executa a busca de um elemento na lista, retornando o elemento ou
// NULL quando não encontrado
void* buscar(Lista* lista, void* elemento, bool iguais(void*, void*));

// Libera a lista do espaço alocado na memoria
Lista* liberar(Lista* lista);

/*Funções Específicas*/

	/*Professor*/

// Alloca os dados do professor(siape) criado e o retorna
Professor* criarProfessorPK(int siape);

// Alloca os dados do professor(nome, siape, area e titulacao) criado e o retorna
Professor* criarProfessor(char nome[255], int siape, char areaDeAtuacao[255], char titulacao[255]);

// Imprime a tela e recebe os dados dos professores
void adicionarProfessor(Lista* professores);

// 
void imprimirProfessor(void* lista);
Professor* buscarProfessor(Lista* professores, int siape);
bool professoresIguais(void* professor1, void* professor2);

	/*Aluno*/

Aluno* criarAlunoPK(int matricula);
Aluno* criarAluno(char nome[255], int matricula, Curso* curso);
void adicionarAluno(Lista *alunos, Lista* cursos);
void imprimirAluno(void* aluno);
Aluno* buscarAluno(Lista* alunos, int matricula);
bool alunosIguais(void* aluno1, void* aluno2);

	/*Disciplina*/

Disciplina* criarDisciplinaPK(int codigo);
Disciplina* criarDisciplina(int codigo, Curso* curso, char nome[255], int cargaHoraria);
void adicionarDisciplina(Lista *disciplinas, Lista *cursos);
void imprimirDisciplina(void* disciplina);
Disciplina* buscarDisciplina(Lista* disciplinas, int codigo);
bool disciplinasIguais(void* disciplina1, void* disciplina2);
void adicionarPreRequisito(Disciplina* disciplina, Disciplina* preRequisito);

	/*Turma*/

Turma* criarTurmaPK(int codigo);
Turma* criarTurma(int codigo);
Lista* retirarTurmaP(Lista* turmas, Turma* turma);
Lista* retirarTurma(Lista* turmas, int codigo);
void inscreverAluno(Turma* turma, Aluno* aluno);
void inscreverProfessor(Turma* turma, Professor* professor);
Turma* buscarTurma(Lista* turmas, int codigo);
bool turmasIguais(void* turma1, void* turma2);
void imprimirTurma(void* turma);
void desinscreverAluno(Turma* turma, int matricula);
Lista* retirarAlunoP(Lista* alunos, Aluno* aluno);
void desinscreverProfessor(Turma* turma, int siape);
Lista* retirarProfessorP(Lista* professores, Professor* professor);
bool quantidadeMax(Lista* lista);
void adicionarAvaliacao(Turma* turma, int codigo);
void inscreverDisciplina(Turma* turma, Disciplina* d);
void adicionarAula(Turma* turma, char data[255], char conteudo[255]);
void adicionarFrequencia(Situacao* situacao, Turma* turma);
void retirarFrequencia(Situacao* situacao, Turma* turma);
void adicionarMedia(Situacao* s, Lista* lista, float valor);

	/*Curso*/

Curso* criarCurso(int codigo, char nome[255]);
void imprimirCurso(void* curso);
Curso* criarCursoPK(int codigo);
void adicionarCurso(Lista *cursos);
Curso* buscarCurso(Lista* cursos, int codigo);
bool cursosIguais(void* curso1, void* curso2);
	
	/*Avaliações*/

Avaliacao* criarAvaliacao(int codigo);
void imprimirAvaliacao(void* avaliacao);
Avaliacao* criarAvaliacaoPK(int codigo);
Avaliacao* buscarAvaliacao(Lista* avaliacoes, int codigo);
bool avaliacoesIguais(void* avaliacao1, void* avaliacao2);
void adicionarNota(Avaliacao* avaliacao, Aluno* aluno, float valor);


	/*Notas*/
Nota* criarNota(Aluno* aluno, float valor);
void imprimirNota(void* valor);
Nota* criarNotaPK(Aluno* aluno);
Nota* buscarNota(Lista* notas, Aluno* aluno);
bool notasIguais(void* nota1, void* nota2);

	/*Aulas*/
Aula* criarAula(char data[255], char conteudo[255]);
void imprimirAula(void* aula);
Aula* criarAulaPK(char data[255]);
Aula* buscarAula(Lista* aulas, char data[255]);
bool aulasIguais(void* aula1, void* aula2);
void adicionarPresenca(Aula* aula, Aluno* aluno, bool presente);

	/*Presenças*/
Presenca* criarPresenca(Aluno* aluno, bool presente);
void imprimirPresenca(void* presenca);
Presenca* criarPresencaPK(Aluno* aluno);
Presenca* buscarPresenca(Lista* presencas, Aluno* aluno);
bool presencasIguais(void* presenca1, void* presenca2);

	/*Situacao*/
Situacao* criarSituacao(Aluno* aluno);
void imprimirSituacao(void* situacao);
Situacao* criarSituacaoPK(Aluno* aluno);
void adicionarSituacao(Turma* turma, Aluno* aluno);
Situacao* buscarSituacao(Lista* situacoes, Aluno* aluno);
bool situacoesIguais(void* situacao1, void* situacao2);

/*Funções Manter*/

void manterProfessores(Lista* professores);
void manterAlunos(Lista *alunos, Lista* cursos);
void manterDisciplinas(Lista *disciplinas, Lista *cursos);
void manterDisciplina(Disciplina *disciplina, Lista *disciplinas);
void manterCursos(Lista* cursos);
void manterTurmas(Lista *turmas, Lista *alunos, Lista *professores, Lista *disciplinas);
void manterTurma(void *turma, Lista *alunos, Lista* professores);
void manterAvaliacao(void* avaliacao, Lista* alunos, Turma* turma);
void manterAula(void* aula, Lista* alunos, Turma* turma);
