#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include"calendario.h"

int main() {
  struct mes* calendario = criarCalendario();

  printf("====== CALENDÁRIO ======\n");
  printf("0 - Sair do Menu\n");
  printf("1 - Criar Agendamento\n");
  printf("2 - Criar Agendamento\n");
  printf("========================\n");
  printf("\n--> ");
  char opcaoEscolhidaStr[8];
  fgets(opcaoEscolhidaStr, sizeof(opcaoEscolhidaStr), stdin);
  int opcaoEscolhida = atoi(opcaoEscolhidaStr);

  while (opcaoEscolhida != 0) {
    if (opcaoEscolhida == 1)
      criarAgendamento(calendario);

    if (opcaoEscolhida == 2)
      listarAgendamentos(calendario);

    printf("====== CALENDÁRIO ======\n");
    printf("0 - Sair do Menu\n");
    printf("1 - Criar Agendamento\n");
    printf("2 - Criar Agendamento\n");
    printf("========================\n");
    printf("\n--> ");
    fgets(opcaoEscolhidaStr, sizeof(opcaoEscolhidaStr), stdin);
    opcaoEscolhida = atoi(opcaoEscolhidaStr);
  }


  struct dia* d = calendario[11].primeiroDia;
  printf("Descricao aw : %s", d->primeiroAgendamento->descricao);
  printf("Datawd : %s", asctime(&(d->primeiroAgendamento->data)));
  
  // printf("First date: %d\n", calendario->qtdeDias);
  //printf("Date here: %s\n", asctime(calendario->primeiroDia->primeiroAgendamento->data));

  return 0;
}