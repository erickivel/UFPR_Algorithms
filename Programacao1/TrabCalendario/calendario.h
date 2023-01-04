#include<time.h>

struct agendamento {
  char* descricao;
  struct tm data;
  struct agendamento* prox;
};

struct dia {
  int numDia;
  struct agendamento* primeiroAgendamento;
  struct dia* prox;
  int qtdeAgendamentos;
};

struct mes {
  struct dia* primeiroDia;
  int qtdeDias;
};

struct mes* criarCalendario();

void criarAgendamento(struct mes* calendario);

void listarAgendamentos(struct mes* calendario);