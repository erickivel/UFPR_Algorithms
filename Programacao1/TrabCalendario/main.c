#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include"calendario.h"

int main() {
  struct mes* calendario = criarCalendario();

  printf("\n======== CALENDÁRIO ========\n");
  printf("  0 - Sair do Menu\n");
  printf("  1 - Criar Agendamento\n");
  printf("  2 - Listar Agendamentos\n");
  printf("============================\n");
  printf("\n--> ");
  char opcaoEscolhidaStr[8];
  fgets(opcaoEscolhidaStr, sizeof(opcaoEscolhidaStr), stdin);
  int opcaoEscolhida = atoi(opcaoEscolhidaStr);

  while (opcaoEscolhida != 0) {
    if (opcaoEscolhida == 1)
      criarAgendamento(calendario);

    if (opcaoEscolhida == 2)
      listarAgendamentos(calendario);

    printf("\n======== CALENDÁRIO ========\n");
    printf("0 - Sair do Menu\n");
    printf("1 - Criar Agendamento\n");
    printf("2 - Listar Agendamentos\n");
    printf("============================\n");
    printf("\n--> ");
    fgets(opcaoEscolhidaStr, sizeof(opcaoEscolhidaStr), stdin);
    opcaoEscolhida = atoi(opcaoEscolhidaStr);
  }

  printf("\nFechando calendário...\n");
  fecharCalendario(calendario);

  return 0;
}