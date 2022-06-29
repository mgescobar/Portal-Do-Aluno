#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include"listas.h"

bool vazia(Lista* lista){
  return (lista == NULL);
}

Lista* ultimo(Lista* lista){
  Lista* ultimo = lista;
  while (!vazia(ultimo) && !vazia(ultimo->prox))
    ultimo = ultimo->prox;
  return ultimo;
}

Lista* criarLista(){
  return NULL;
}

Lista* inserirInicio(Lista* lista, void* elemento){
  Lista* novo = (Lista*)malloc(sizeof(Lista));
  novo->info = elemento;
  novo->prox = lista;
  return novo;
}

Lista* inserirFim(Lista* lista, void* elemento){
  if(!vazia(lista))
    ultimo(lista)->prox = inserirInicio(NULL, elemento);
  return vazia(lista) ? inserirInicio(NULL, elemento) : lista;
}


Lista* retirar(Lista* lista, void* elemento, bool iguais(void*, void*))
{
   Lista* anterior = NULL;
   Lista* temp = lista;
   while(!vazia(temp) && !iguais(temp->info, elemento)){
      anterior = temp;
      temp = temp->prox;
   }
   if (vazia(temp))
      return lista;
   if (anterior == NULL)
      lista = temp->prox;
   else
      anterior->prox = temp->prox;
   free(temp);
   return lista;
}


void imprimirLista(Lista* lista, void imprimirElemento(void*)){
  while(!vazia(lista)){
    	imprimirElemento(lista->info);
    lista = lista->prox;
  }
}

void* buscar(Lista* lista, void* elemento, bool iguais(void*, void*)){
   Lista* temp = lista;
   while(temp != NULL){
      if (iguais(temp->info, elemento))
      	 return temp->info;
      temp = temp->prox;
   }
   return NULL;
}

Lista* liberar(Lista* lista){
   while(!vazia(lista)){
      Lista* temp = lista->prox;
      free(lista);
      lista = temp;
   }
   return NULL;
}

/*----------------Funções Específicas-----------------*/

Professor* criarProfessorPK(int siape){
  	Professor* p = (Professor*) malloc(sizeof(Professor));
	p->siape = siape;
	return p;
}

Professor* criarProfessor(char nome[255], int siape, char areaDeAtuacao[255], char titulacao[255]){
  Professor* prof = (Professor*) malloc(sizeof(Professor));
  strcpy(prof->nome, nome);
  prof->siape = siape;
  strcpy(prof->areaDeAtuacao, areaDeAtuacao);
  strcpy(prof->titulacao, titulacao);
  return prof;
}

void adicionarProfessor(Lista *professores){
  int codigo;
  char nome[255], areaDeAtuacao[255], titulacao[255];

  printf("\nNome do Professor: ");
  scanf(" %[^\n]s", nome); 
  printf("Siape: ");
  scanf("%d", &codigo);
  printf("Área de Atuação: ");
  scanf(" %[^\n]s", areaDeAtuacao);
  printf("Titulação: ");
  scanf(" %[^\n]s", titulacao);
  professores = inserirFim(professores, criarProfessor(nome, codigo, areaDeAtuacao, titulacao));
}

void imprimirProfessor(void* professor){
  printf(" Nome: ");
  puts(((Professor*)professor)->nome);
  printf(" Siape: %d\n", ((Professor*)professor)->siape);
  printf(" Área de Atuação: ");
  puts(((Professor*)professor)->areaDeAtuacao);
  printf(" Titulação: ");
  puts(((Professor*)professor)->titulacao);
  printf(" ----------------\n");
}

Professor* buscarProfessor(Lista* professores, int siape){
   return (Professor*) buscar(professores, criarProfessorPK(siape), &professoresIguais);
}


bool professoresIguais(void* professor1, void* professor2){
	return ((Professor*) professor1)->siape == ((Professor*) professor2)->siape;
}


/*---------------Aluno-----------------*/



Aluno* criarAlunoPK(int matricula){
  Aluno* a = (Aluno*) malloc(sizeof(Aluno));
  a->matricula = matricula;
  return a;
}

Aluno* criarAluno(char nome[255], int matricula, Curso* curso){
  Aluno* a = (Aluno*) malloc(sizeof(Aluno));
  strcpy(a->nome, nome);
  a->matricula = matricula;
  a->curso = criarCurso(curso->codigo, curso->nome);
  return a;
}

void adicionarAluno(Lista *alunos, Lista* cursos){
  int codigo, matricula;
  char nome[255];

  printf(" Nome do Aluno: ");
  scanf(" %[^\n]s", nome); 
  printf(" Matrícula: ");
  scanf("%d", &matricula);
  printf(" Código do Curso: ");
  scanf("%d", &codigo);
  alunos = inserirFim(alunos, criarAluno(nome, matricula, buscarCurso(cursos, codigo)));
}

void imprimirAluno(void* aluno){
  printf(" Nome: ");
  puts(((Aluno*)aluno)->nome);
  printf(" Matrícula: %d\n", ((Aluno*)aluno)->matricula);
  printf(" Curso do Aluno: \n");
  printf(" ----------------\n");
  imprimirCurso(((Aluno*)aluno)->curso);
}

Aluno* buscarAluno(Lista* alunos, int matricula){
   return (Aluno*) buscar(alunos, criarProfessorPK(matricula), &alunosIguais);
}


bool alunosIguais(void* aluno1, void* aluno2){
  return ((Aluno*) aluno1)->matricula == ((Aluno*) aluno2)->matricula;
}


/*----------------------Disciplinas-----------------------*/



Disciplina* criarDisciplinaPK(int codigo){
  Disciplina* d = (Disciplina*) malloc(sizeof(Disciplina));
  d->codigo = codigo;
  return d;
}

Disciplina* criarDisciplina(int codigo, Curso* curso, char nome[255], int cargaHoraria){
  Disciplina* d = (Disciplina*) malloc(sizeof(Disciplina));
  strcpy(d->nome, nome);
  d->codigo = codigo;
  d->curso = curso;
  d->cargaHoraria = cargaHoraria;
  d->preRequisitos = criarLista();
  return d;
}

void adicionarDisciplina(Lista *disciplinas, Lista *cursos){
  int codigo, cargaHoraria, codCurso;
  char nome[255];

  printf(" Nome da Disciplina: ");
  scanf(" %[^\n]s", nome); 
  printf(" Código da Disciplina: ");
  scanf("%d", &codigo);
  printf(" Código do Curso: ");
  scanf("%d", &codCurso);
  printf(" Carga Horária: ");
  scanf("%d", &cargaHoraria);
  disciplinas = inserirFim(disciplinas, criarDisciplina(codigo, buscarCurso(cursos, codCurso), nome, cargaHoraria));
}

void imprimirDisciplina(void* disciplina){
  printf(" Código da Disciplina: %d\n", ((Disciplina*)disciplina)->codigo);
  printf(" Nome da Disciplina: ");
  puts(((Disciplina*)disciplina)->nome);
  printf(" Carga Horária: %d\n", ((Disciplina*) disciplina)->cargaHoraria);
  printf(" Pré-Requisitos: \n");
  imprimirLista(((Disciplina*)disciplina)->preRequisitos, &imprimirDisciplina);
  printf(" Curso da Disciplina: \n");
  printf(" ----------------\n");
  imprimirCurso(((Disciplina*)disciplina)->curso);
}

Disciplina* buscarDisciplina(Lista* disciplinas, int codigo){
   return (Disciplina*) buscar(disciplinas, criarDisciplinaPK(codigo), &disciplinasIguais);
}


bool disciplinasIguais(void* disciplina1, void* disciplina2){
  return ((Disciplina*) disciplina1)->codigo == ((Disciplina*) disciplina2)->codigo;
}

void adicionarPreRequisito(Disciplina* disciplina, Disciplina* preRequisito){
  disciplina->preRequisitos = inserirFim(disciplina->preRequisitos, preRequisito);
}
/*-------------------------Turmas-------------------------*/

Turma* criarTurmaPK(int codigo){
  Turma* t = (Turma*) malloc(sizeof(Turma));
  t->codigo = codigo;
  t->professores = criarLista();
  t->alunos = criarLista();
  t->avaliacoes = criarLista();
  t->aulas = criarLista();
  return t;
}

Turma* criarTurma(int codigo){
  Turma* t = criarTurmaPK(codigo);
  return t;
}

Lista* retirarTurmaP(Lista* turmas, Turma* turma){
   return retirar(turmas, turma, &turmasIguais);
}

Lista* retirarTurma(Lista* turmas, int codigo){
   return retirarTurmaP(turmas, buscarTurma(turmas, codigo));
}

void inscreverAluno(Turma* turma, Aluno* aluno){
   turma->alunos = inserirFim(turma->alunos, aluno);
}

void inscreverProfessor(Turma* turma, Professor* professor){
   turma->professores = inserirFim(turma->professores, professor);
}

Turma* buscarTurma(Lista* turmas, int codigo){
   return (Turma*) buscar(turmas, criarTurmaPK(codigo), &turmasIguais);
}

bool turmasIguais(void* turma1, void* turma2){
  return ((Turma*) turma1)->codigo == ((Turma*) turma2)->codigo;
}

void imprimirTurma(void* turma){
  Turma* t = (Turma*) turma;
  printf(" Turma: %d\n", t->codigo);
  if(t->professores != NULL){
    printf(" Professores:\n");
    printf(" ----------------\n");
    imprimirLista(t->professores, &imprimirProfessor); 
  }
  if(t->alunos != NULL){    
    printf(" Alunos:\n");
    printf(" ----------------\n");
    imprimirLista(t->alunos, &imprimirAluno);
  }    
  printf(" Disciplina: \n");
  printf(" ----------------\n");
  imprimirDisciplina(t->disciplina);
}

void desinscreverAluno(Turma* turma, int matricula){
  turma->alunos = retirarAlunoP(turma->alunos, buscarAluno(turma->alunos, matricula));
}

Lista* retirarAlunoP(Lista* alunos, Aluno* aluno){
  return retirar(alunos, aluno, &alunosIguais);
}

void desinscreverProfessor(Turma* turma, int siape){
  turma->professores = retirarProfessorP(turma->professores, buscarProfessor(turma->alunos, siape));
}

Lista* retirarProfessorP(Lista* professores, Professor* professor){
  return retirar(professores, professor, &professoresIguais);
}

bool quantidadeMax(Lista* lista){
  int cont = 0;

  Lista* temp = lista;
  while(!vazia(temp)){
    cont++;
    temp = temp->prox;
  }
  
  return (cont >= 50);
}

void adicionarAvaliacao(Turma* turma, int codigo){
  turma->avaliacoes = inserirFim(turma->avaliacoes, criarAvaliacao(codigo));
}

void inscreverDisciplina(Turma* turma, Disciplina* d){
  turma->disciplina = d;
}

void adicionarAula(Turma* turma, char data[255], char conteudo[255]){
  turma->aulas = inserirFim(turma->aulas, criarAula(data, conteudo));
}

void adicionarFrequencia(Situacao* situacao, Turma* turma){
  situacao->sumPresencas += 2;
  situacao->frequencia = situacao->sumPresencas/turma->disciplina->cargaHoraria;
}

void retirarFrequencia(Situacao* situacao, Turma* turma){
  situacao->sumPresencas += 2;
  situacao->frequencia = situacao->sumPresencas/turma->disciplina->cargaHoraria;
}


void adicionarMedia(Situacao* s, Lista* lista, float valor){
  //Situacao* s = ((Situacao*)malloc(sizeof(Situacao)));
  float cont = 0;
  while(!vazia(lista)){
    cont += 1;
    lista = lista->prox;
  }
  printf("%f\n", cont);
  printf("%f\n", valor);
  printf("%f\n", s->sumNotas);
  s->sumNotas += valor;
  printf("%f\n", s->sumNotas);
  s->media = ((s->sumNotas)/cont);
  printf("%f\n", s->sumNotas);
}

/*-------------------------Cursos-------------------------*/

Curso* criarCurso(int codigo, char nome[255]){
  Curso* curso = criarCursoPK(codigo);
  strcpy(curso->nome, nome);
  return curso;
}

void imprimirCurso(void* curso){
  printf(" Código do Curso: %d\n", ((Curso*)curso)->codigo);
  printf(" Nome do Curso: ");
  puts(((Curso*)curso)->nome);
  printf(" ----------------\n");
}

Curso* criarCursoPK(int codigo){
  Curso* c = (Curso*) malloc(sizeof(Curso));
  c->codigo = codigo;
  return c;
}


void adicionarCurso(Lista *cursos){
  int codigo;
  char nome[255];

  printf(" Nome do Curso: ");
  scanf(" %[^\n]s", nome); 
  printf(" Código: ");
  scanf("%d", &codigo);
  cursos = inserirFim(cursos, criarCurso(codigo, nome));
}

Curso* buscarCurso(Lista* cursos, int codigo){
   return (Curso*) buscar(cursos, criarCursoPK(codigo), &cursosIguais);
}


bool cursosIguais(void* curso1, void* curso2){
  return ((Curso*) curso1)->codigo == ((Curso*) curso2)->codigo;
}

/*-----------------------Avaliações-----------------------*/


Avaliacao* criarAvaliacao(int codigo){
  Avaliacao* avaliacao = criarAvaliacaoPK(codigo);
  avaliacao->notas = criarLista();
  return avaliacao;
}

void imprimirAvaliacao(void* avaliacao){
  Avaliacao* a = (Avaliacao*) avaliacao;
  printf(" Avaliação: %d\n ", a->codigo);
  printf("----------------\n");
  printf(" Notas: \n");
  imprimirLista(a->notas, &imprimirNota);
}


Avaliacao* criarAvaliacaoPK(int codigo){
  Avaliacao* a = (Avaliacao*) malloc(sizeof(Avaliacao));
  a->codigo = codigo;
  return a;
}


Avaliacao* buscarAvaliacao(Lista* avaliacoes, int codigo){
   return (Avaliacao*) buscar(avaliacoes, criarAvaliacaoPK(codigo), &avaliacoesIguais);
}


bool avaliacoesIguais(void* avaliacao1, void* avaliacao2){
  return ((Avaliacao*) avaliacao1)->codigo == ((Avaliacao*) avaliacao2)->codigo;
}

void adicionarNota(Avaliacao* avaliacao, Aluno* aluno, float valor){
  avaliacao->notas = inserirFim(avaliacao->notas, criarNota(aluno, valor));
}


/*-------------------------Notas--------------------------*/

Nota* criarNota(Aluno* aluno, float valor){
  Nota* nota = criarNotaPK(aluno);
  nota->valor = valor;
  return nota;
}

void imprimirNota(void* nota){
  Nota* n = (Nota*) nota;
  printf(" Aluno: \n");
  printf(" ----------------\n");
  imprimirAluno(n->aluno);
  printf(" ----------------\n");
  printf(" Nota: %.2f\n", n->valor);
  printf(" ----------------\n");
}


Nota* criarNotaPK(Aluno* aluno){
  Nota* n = (Nota*) malloc(sizeof(Nota));
  n->aluno = aluno;
  return n;
}


Nota* buscarNota(Lista* notas, Aluno* aluno){
   return (Nota*) buscar(notas, criarNotaPK(aluno), &notasIguais);
}


bool notasIguais(void* nota1, void* nota2){
  return ((Nota*) nota1)->aluno->matricula == ((Nota*) nota2)->aluno->matricula;
}

/*-------------------------Aulas--------------------------*/

Aula* criarAula(char data[255], char conteudo[255]){
  Aula* aula = criarAulaPK(data);
  strcpy(aula->conteudo, conteudo);
  aula->presencas = criarLista();
  return aula;
}

void imprimirAula(void* aula){
  Aula* a = (Aula*) aula;
  printf(" Data: ");
  puts(a->data);
  printf(" Conteúdo Ministrado: ");
  puts(a->conteudo);
  printf(" Presenças: \n");
  printf(" ----------------\n");
  imprimirLista(a->presencas, &imprimirPresenca);
}


Aula* criarAulaPK(char data[255]){
  Aula* a = (Aula*) malloc(sizeof(Aula));
  strcpy(a->data, data);
  return a;
}


Aula* buscarAula(Lista* aulas, char data[255]){
   return (Aula*) buscar(aulas, criarAulaPK(data), &aulasIguais);
}


bool aulasIguais(void* aula1, void* aula2){
  return (strcmp(((Aula*) aula1)->data, ((Aula*) aula2)->data) == 0);
}

void adicionarPresenca(Aula* aula, Aluno* aluno, bool presente){
  aula->presencas = inserirFim(aula->presencas, criarPresenca(aluno, presente));
}

/*------------------------Presenca------------------------*/

Presenca* criarPresenca(Aluno* aluno, bool presente){
  Presenca* presenca = criarPresencaPK(aluno);
  presenca->presente = presente;
  return presenca;
}

void imprimirPresenca(void* presenca){
  Presenca* p = (Presenca*) presenca;
  printf(" Aluno: \n");
  printf(" ----------------\n");
  imprimirAluno(p->aluno);
  printf(" ----------------\n");
  printf(" Presente: ");
  if(p->presente)
    printf("Sim\n");
  else
    printf("Não\n");
  printf(" ----------------\n");
}


Presenca* criarPresencaPK(Aluno* aluno){
  Presenca* p = (Presenca*) malloc(sizeof(Presenca));
  p->aluno = aluno;
  return p;
}


Presenca* buscarPresenca(Lista* presencas, Aluno* aluno){
   return (Presenca*) buscar(presencas, criarPresencaPK(aluno), &presencasIguais);
}


bool presencasIguais(void* presenca1, void* presenca2){
  return ( ((Presenca*) presenca1)->aluno->matricula == ((Presenca*) presenca2)->aluno->matricula);
}

/*------------------------Situação-----------------------*/

Situacao* criarSituacao(Aluno* aluno){
  Situacao* situacao = criarSituacaoPK(aluno);
  situacao->frequencia = 0;
  situacao->media = 0;
  situacao->sumNotas = 0;
  situacao->sumPresencas = 0;
  return situacao;
}

void imprimirSituacao(void* situacao){
  Situacao* s = (Situacao*) situacao;
  printf(" Aluno: \n");
  printf(" ----------------\n");
  imprimirAluno(s->aluno);
  printf(" Media: %.2f\n", s->media);
  if(s->media >= 7)
    printf(" Passou por Média\n");
  else if(s->media < 7)
    printf(" Reprovou por Média\n");
  if(s->frequencia >= 0.75)
    printf(" Passou por frequência\n");
  else if (s->frequencia < 0.75)
    printf(" Reprovou por frequência\n");
  printf(" Frequencia: %.2f\n", s->frequencia);
  printf(" ----------------\n");
}

Situacao* criarSituacaoPK(Aluno* aluno){
  Situacao* s = (Situacao*) malloc(sizeof(Situacao));
  s->aluno = aluno;
  return s;
}

void adicionarSituacao(Turma* turma, Aluno* aluno){
  turma->situacoes = inserirFim(turma->situacoes, criarSituacao(aluno));
}

Situacao* buscarSituacao(Lista* situacoes, Aluno* aluno){
   return (Situacao*) buscar(situacoes, criarSituacaoPK(aluno), &situacoesIguais);
}


bool situacoesIguais(void* situacao1, void* situacao2){
  return ( ((Situacao*) situacao1)->aluno->matricula == ((Situacao*) situacao2)->aluno->matricula);
}

/*---------------------Funções Manter---------------------*/

void manterProfessores(Lista *professores){
	int opcao, siape;

	while(1){
		printf("\nManter Professores:\n\n 1) Adicionar Professor \n 2) Excluir Professor \n 3) Mostrar Professores \n 0) Voltar \n\n ");
	  scanf("%d", &opcao);
	  switch(opcao){
	  	case(1):
	  		adicionarProfessor(professores);
	  		break;
	  	case(2):
        printf("\n Siape do professor: ");
        scanf("%d", &siape);
	  		professores = retirar(professores, buscarProfessor(professores, siape), &professoresIguais);
	  		break;
	  	case(3):
	  		printf("\n Lista dos Professores: \n\n");
	  		imprimirLista(professores, &imprimirProfessor);
	  		break;
	  	case(0):
	  		return;
	  }
	}
}

void manterAlunos(Lista *alunos, Lista *cursos){
  int opcao, matricula;

  while(1){
    printf("\nManter Alunos:\n\n 1) Adicionar Aluno \n 2) Excluir Aluno \n 3) Mostrar Alunos \n 0) Voltar \n\n ");
    scanf("%d", &opcao);
    switch(opcao){
      case(1):
        adicionarAluno(alunos, cursos);
        break;
      case(2):
        printf(" Matrícula do Aluno: ");
        scanf("%d", &matricula);
        alunos = retirar(alunos, buscarAluno(alunos, matricula), &alunosIguais);
        break;
      case(3):
        printf("\n Lista dos Alunos: \n\n");
        imprimirLista(alunos, &imprimirAluno);
        break;
      case(0):
        return;
    }
  }
}


void manterDisciplinas(Lista *disciplinas, Lista *cursos){
  int opcao, codigo;

  while(1){
    printf("\nManter Disciplinas:\n\n 1) Adicionar Disciplina \n 2) Excluir Disciplina \n 3) Mostrar Disiplinas \n 4) Manter Disciplina \n 0) Voltar \n\n ");
    scanf("%d", &opcao);
    switch(opcao){
      case(1):
        adicionarDisciplina(disciplinas, cursos);
        break;
      case(2):
        printf(" Código da Disciplina: ");
        scanf("%d", &codigo);
        disciplinas = retirar(disciplinas, buscarDisciplina(disciplinas, codigo), &disciplinasIguais);
        break;
      case(3):
        printf("\n Lista das disciplinas: \n\n");
        imprimirLista(disciplinas, &imprimirDisciplina);
        break;
      case(4):
        printf(" Código da Disciplina: ");
        scanf("%d", &codigo);
        manterDisciplina(buscarDisciplina(disciplinas, codigo), disciplinas);
        break;
      case(0):
        return;
    }
  }
}

void manterDisciplina(Disciplina *disciplina, Lista *disciplinas){
  int opcao, codigo;

  while(1){
    printf("\nManter Disciplinas:\n\n 1) Adicionar Pré-Requisito \n 2) Excluir Pré-Requisito \n 3) Mostrar Disiplina \n 0) Voltar \n\n ");
    scanf("%d", &opcao);
    switch(opcao){
      case(1):
        printf(" Código da Disciplina: ");
        scanf("%d", &codigo);
        adicionarPreRequisito(disciplina, buscarDisciplina(disciplinas, codigo));
        break;
      case(2):
        printf(" Código da Disciplina: ");
        scanf("%d", &codigo);
        disciplina->preRequisitos = retirar(disciplina->preRequisitos, buscarDisciplina(disciplina->preRequisitos, codigo), &disciplinasIguais);
        break;
      case(3):
        printf("\n Disciplina: \n\n");
        imprimirDisciplina(disciplina);
        break;
      case(0):
        return;
    }
  }
}

void manterCursos(Lista* cursos){
  int opcao, codigo;

  while(1){
    printf("\nManter Cursos:\n\n 1) Adicionar Curso \n 2) Excluir Curso \n 3) Mostrar Cursos \n 0) Voltar \n\n ");
    scanf("%d", &opcao);
    switch(opcao){
      case(1):
        adicionarCurso(cursos);
        break;
      case(2):
        printf(" Código do Curso: ");
        scanf("%d", &codigo);
        cursos = retirar(cursos, buscarCurso(cursos, codigo), &cursosIguais);
        break;
      case(3):
        printf("\n Lista dos Cursos: \n\n");
        imprimirLista(cursos, &imprimirCurso);
        break;
      case(0):
        return;
    }
  }
}

void manterTurmas(Lista *turmas, Lista *alunos, Lista *professores, Lista *disciplinas){
  int opcao, codigo, siape, matricula, codDisciplina;

  while(1){
    printf("\nManter Turmas:\n\n 1) Adicionar Turma \n 2) Excluir Turma \n 3) Mostrar Turmas \n 4) Manter Turma \n 0) Voltar \n\n ");
    scanf("%d", &opcao);
    switch(opcao){
      case(1):
        printf("\n Digite um código para a nova turma: ");
        scanf("%d", &codigo);
        turmas = inserirFim(turmas, criarTurma(codigo));
        printf("\n Digite o siape do professor da turma: ");
        scanf("%d", &siape);
        inscreverProfessor(buscarTurma(turmas, codigo), buscarProfessor(professores, siape));
        printf("\n Digite a matrícula de um aluno da turma: ");
        scanf("%d", &matricula);
        inscreverAluno(buscarTurma(turmas, codigo), buscarAluno(alunos, matricula));
        adicionarSituacao(buscarTurma(turmas, codigo), buscarAluno(alunos, matricula));
        printf("\n Digite o código da disciplina da nova turma: ");
        scanf("%d", &codDisciplina);
        inscreverDisciplina(buscarTurma(turmas, codigo), buscarDisciplina(disciplinas, codDisciplina));
        break;
      case(2):
        printf(" Código da Turma: ");
        scanf("%d", &codigo);
        turmas = retirar(turmas, buscarTurma(turmas, codigo), &turmasIguais);
        break;
      case(3):
        printf("\n Lista das Turmas: \n\n");
        imprimirLista(turmas, &imprimirTurma);
        break;
      case(4):
        printf(" Código da Turma: ");
        scanf("%d", &codigo);
        manterTurma(buscarTurma(turmas, codigo), alunos, professores);
        break;
      case(0):
        return;
    }
  }
}


void manterTurma(void *turma, Lista *alunos, Lista* professores){
  Turma* t = (Turma*) turma;
  int opcao, siape, matricula, codigo;
  char data[255], conteudo[255];

  while(1){
    printf("\nManter Turma:\n\n 1) Inscrever Aluno \n 2) Inscrever Professor \n 3) Desinscrever Aluno \n 4) Desinscrever Professor \n 5) Mostrar Turma \n\n 6) Adicionar Avaliação \n 7) Excluir Avaliacao \n 8) Mostrar Avaliações \n 9) Manter Avaliação \n\n 10) Adicionar Aula \n 11) Excluir Aula \n 12) Mostrar Aulas \n 13) Manter Aula \n 14) Gerar Relatório \n 0) Voltar \n\n ");
    scanf("%d", &opcao);
    switch(opcao){
      case(1):
        printf(" Matricula do Aluno: ");
        scanf("%d", &matricula);
        if(!quantidadeMax(t->alunos)){
          inscreverAluno(t, buscarAluno(alunos, matricula));
          adicionarSituacao(t, buscarAluno(alunos, matricula));
        }
        else
          printf("\n Turma Cheia!\n");
        break;
      case(2):
        printf(" Siape do Professor: ");
        scanf("%d", &siape);
        inscreverProfessor(t, buscarProfessor(professores, siape));
        break;
      case(3):
        printf(" Matricula do Aluno: ");
        scanf("%d", &matricula);
        desinscreverAluno(t, matricula);
        t->situacoes = retirar(t->situacoes, buscarSituacao(t->situacoes, buscarAluno(t->alunos, matricula)), &situacoesIguais);
        break;
      case(4):
        printf(" Siape do Professor: ");
        scanf("%d", &siape);
        desinscreverProfessor(t, siape);
        break;
      case(5):
        imprimirTurma(turma);
        break;
      case(6):
        printf(" Código da Avaliação: ");
        scanf("%d", &codigo);
        adicionarAvaliacao(t, codigo);
        break;
      case(7):
        printf(" Código da Avaliação: ");
        scanf("%d", &codigo);
        t->avaliacoes = retirar(t->avaliacoes, buscarAvaliacao(t->avaliacoes, codigo), &avaliacoesIguais);
        break;
      case(8):
        printf(" Lista de Avaliações: \n");
        imprimirLista(t->avaliacoes, &imprimirAvaliacao);
        break;
      case(9):
        printf(" Código da Avaliação: ");
        scanf("%d", &codigo);
        manterAvaliacao(buscarAvaliacao(t->avaliacoes, codigo), t->alunos, t);
        break;
      case(10):
        printf(" Data: ");
        scanf(" %[^\n]s", data);
        printf(" Conteúdo Misnistrado: ");
        scanf(" %[^\n]s", conteudo);
        adicionarAula(t, data, conteudo);
        break;
      case(11):
        printf(" Data da Aula: ");
        scanf(" %[^\n]s", data);
        t->aulas = retirar(t->aulas, buscarAula(t->aulas, data), &aulasIguais);
        break;
      case(12):
        printf(" Lista de Aulas: \n");
        imprimirLista(t->aulas, &imprimirAula);
        break;
      case(13):
        printf(" Data da Aula: ");
        scanf(" %[^\n]s", data);
        manterAula(buscarAula(t->aulas, data), t->alunos, t);
        break;
      case(14):
        printf(" Relatório: \n");
        imprimirLista(t->situacoes, &imprimirSituacao);
        break;
      case(0):
        return;
    }
  }
}

void manterAvaliacao(void* avaliacao, Lista* alunos, Turma* turma){
  Avaliacao* a = (Avaliacao*) avaliacao;
  int opcao, matricula;
  float valor;
  while(1){
    printf("\nManter Avaliacao:\n\n 1) Adicionar Nota \n 2) Excluir Nota \n 3) Mostrar Avaliação\n 0) Voltar \n\n ");
    scanf("%d", &opcao);
    switch(opcao){
      case(1):
        printf(" Matricula do Aluno: ");
        scanf("%d", &matricula);
        printf("\n Nota: ");
        scanf("%f", &valor);
        adicionarNota(a, buscarAluno(alunos, matricula), valor);
        adicionarMedia(buscarSituacao(turma->situacoes, buscarAluno(turma->alunos, matricula)), turma->avaliacoes, valor);
        break;
      case(2):
        printf(" Matrícula: ");
        scanf("%d", &matricula);
        a->notas = retirar(a->notas, buscarNota(a->notas, buscarAluno(alunos, matricula)), &notasIguais);
        break;
      case(3):
        imprimirAvaliacao(avaliacao);
        break;
      case(0):
        return;
    }
  }
}

void manterAula(void* aula, Lista* alunos, Turma* turma){
  Aula* a = (Aula*) aula;
  int opcao, matricula, presenteAux;
  bool presente;

  while(1){
    printf("\nManter Aula:\n\n 1) Adicionar Presenca \n 2) Excluir Presenca \n 3) Mostrar Aula\n 0) Voltar \n\n ");
    scanf("%d", &opcao);
    switch(opcao){
      case(1):
        printf(" Matricula do Aluno: ");
        scanf("%d", &matricula);
        printf("\n Presente [1 - Sim | 0 - Não]: ");
        scanf("%d", &presenteAux);
        presente = presenteAux;
        adicionarPresenca(a, buscarAluno(alunos, matricula), presente);
        adicionarFrequencia(buscarSituacao(turma->situacoes, buscarAluno(alunos, matricula)), turma);
        break;
      case(2):
        printf(" Matrícula: ");
        scanf("%d", &matricula);
        a->presencas = retirar(a->presencas, buscarPresenca(a->presencas, buscarAluno(alunos, matricula)), &presencasIguais);
        retirarFrequencia(buscarSituacao(turma->situacoes, buscarAluno(alunos, matricula)), turma);
        break;
      case(3):
        imprimirAula(aula);
        break;
      case(0):
        return;
    }
  }
}
