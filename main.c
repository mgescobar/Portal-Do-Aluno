
/*
################################################################################
#                                INCLUSÕES                                     #
################################################################################
*/

#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include"listas.h"

/*
################################################################################
#                                MAIN                                          #
################################################################################
*/

void main(){
  int opcao;

  Lista* professores = criarLista();
  Lista* alunos = criarLista();
  Lista* disciplinas = criarLista();
  Lista* turmas = criarLista();
  Lista* cursos = criarLista();



	while(1){
		printf("\nBem-Vindo ao Portal do Aluno!\n");
		printf("\n 1) Professores \n 2) Alunos \n 3) Disciplinas \n 4) Cursos \n 5) Turmas \n 0) Sair do Portal \n\n ");
		scanf("%d", &opcao);
		switch(opcao){
			case(0):
        alunos = liberar(alunos);
        professores = liberar(professores);
        disciplinas = liberar(disciplinas);
        turmas = liberar(turmas);
        cursos = liberar(cursos);
				return;
			case(1):	
				manterProfessores(professores);
				break;
			case(2):
				manterAlunos(alunos, cursos);
				break;
			case(3):
				manterDisciplinas(disciplinas, cursos);
				break;
			case(4):
				manterCursos(cursos);
				break;
      case(5):
        manterTurmas(turmas, alunos, professores, disciplinas);
        break;
			default:
				printf("Essa opção não existe, tente outra!");
				break;
		}
	}
}

