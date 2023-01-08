#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#include"calendario.h"

struct mes* criarCalendario() {
  struct mes* novoCalendario = malloc(12 * sizeof(struct mes));

  for(int i = 0; i < 12; i++) {
    novoCalendario[i].qtdeDias = 0;
    novoCalendario[i].primeiroDia = NULL;
  };

  return novoCalendario;
}

struct tm* receberData(struct mes* calendario) {
  size_t tamInicial = 1;
  size_t strDataTam;
  char* strData = malloc(tamInicial * sizeof(char));

  printf("\nQual data você quer criar seu agendamento? (dd/mm) Exemplo: 23/07\n");
  printf("--> ");
  strDataTam = getline(&strData, &tamInicial, stdin);
  char* diaStr = strtok(strData, "/");
  if (diaStr == NULL) diaStr = "0";
  char* mesStr = strtok(NULL, "/");
  if (mesStr == NULL) mesStr = "0";
  int dia = atoi(diaStr);
  int mes = atoi(mesStr);

  // Verifica se: 
  //  - O dia recebido está entre 1 e 31;
  //  - O mês recebido está entre 1 e 12;
  while(dia > 31 || dia < 1 || mes > 12 || mes < 1) {
    printf("Data inválida, digite novamente:\n");
    printf("--> ");
    strData = malloc(tamInicial * sizeof(char));
    strDataTam = getline(&strData, &tamInicial, stdin);
    diaStr = strtok(strData, "/");
    if (diaStr == NULL) diaStr = "0";
    mesStr = strtok(NULL, "/");
    if (mesStr == NULL) mesStr = "0";
    dia = atoi(diaStr);
    mes = atoi(mesStr);
  }

  printf("\nQual horário você quer criar seu agendamento? (0-23)\n");
  printf("--> ");
  char horarioStr[10];
  fgets(horarioStr, sizeof(horarioStr), stdin);
  int horario = atoi(horarioStr);
  while (horario > 23 || horario < 0) {
    printf("A hora deve ser entre 0 e 23 (inclusos), digite a hora do agendamento novamente:\n");
    printf("--> ");
    fgets(horarioStr, 10, stdin);
    horario = atoi(horarioStr);
  } 

  struct tm* date;
  time_t t = time(NULL);
  date = localtime(&t);
  date->tm_sec = 0;
  date->tm_min = 0;
  date->tm_hour = horario;
  date->tm_mday = dia;
  date->tm_mon = mes-1;
  date->tm_year = 123;

  free(strData);

  return date;
}

// Se algum agendamento existir na data/hora recebida retorna 1 senão retorna 0;
int buscarAgendamentoPorData(struct tm* data, struct mes* calendario) {
  int mes = data->tm_mon;
  if (calendario[mes].qtdeDias == 0) {
    return 0;
  }
  
  int dia = data->tm_mday;
  struct dia* diaCal = calendario[mes].primeiroDia;

  while (diaCal != NULL && diaCal->numDia != dia) {
    diaCal = diaCal->prox;
  }

  if (diaCal == NULL)
    return 0;

  if (diaCal->numDia == dia) {
    struct agendamento* agend = diaCal->primeiroAgendamento;
    int hour = data->tm_hour;
    while (agend != NULL) {
      if (agend->data.tm_hour == hour)
        return 1;
      agend = agend->prox;
    }

    if (agend == NULL)
      return 0;
  }
}

char* receberDescricao() {
  size_t tamInicial = 8;
  size_t strDescTam;
  char* strDesc = (char*)malloc(tamInicial * sizeof(char));

  if (strDesc == NULL) {
    perror("Não foi possível alocar a descrição");
    exit(1);
  } 

  printf("\nEsse horário está livre, digite a descrição do seu agendamento: \n");
  printf("--> ");
  strDescTam = getline(&strDesc, &strDescTam, stdin);

  return strDesc;
}

void inserirAgendamento(struct mes* calend, struct tm* data, char* desc) {
  int dia = data->tm_mday;
  int mes = data->tm_mon;

  struct dia* diaAnt = calend[mes].primeiroDia;

  // Inserir em um dia vazio
  if (diaAnt == NULL) {
    calend[mes].qtdeDias = 1;
    diaAnt = malloc(1 * sizeof(struct dia));
    diaAnt->numDia = dia;
    diaAnt->prox = NULL;
    diaAnt->qtdeAgendamentos = 1;
    struct agendamento* agend = malloc(1 * sizeof(struct agendamento));
    agend->descricao = malloc(sizeof(desc));
    strcpy(agend->descricao, desc);
    agend->data = *data;
    agend->prox = NULL;
    diaAnt->primeiroAgendamento = agend;
    calend[mes].primeiroDia = diaAnt;
    return;
  }
  struct dia* diaAtual = diaAnt->prox;

  while (diaAtual != NULL && diaAtual->numDia < dia) {
    diaAnt = diaAnt->prox;
    diaAtual = diaAtual->prox;
  }

  // Se o dia a ser inserido for a própia cabeça
  if (diaAnt->numDia == dia) {
    diaAtual = calend[mes].primeiroDia;
  }

  // Inserir no final (novo dia)
  if (diaAtual == NULL && diaAnt->numDia < dia) {
    calend[mes].qtdeDias += 1;
    struct dia* novoDia = malloc(1 * sizeof(struct dia));
    novoDia->prox = NULL;
    diaAnt->prox = novoDia; 
    novoDia->numDia = dia;
    novoDia->qtdeAgendamentos = 1;
    struct agendamento* agend = malloc(1 * sizeof(struct agendamento));
    agend->descricao = malloc(sizeof(desc));
    strcpy(agend->descricao, desc);
    agend->data = *data;
    agend->prox = NULL;
    novoDia->primeiroAgendamento = agend;
    return;
  }
  
  // Inserir na cabeca (novo dia)
  if (diaAnt->numDia == calend[mes].primeiroDia->numDia && diaAnt->numDia > dia) {
    calend[mes].qtdeDias += 1;
    struct dia* novoDia = malloc(1 * sizeof(struct dia));
    novoDia->prox = diaAnt;
    novoDia->numDia = dia;
    novoDia->qtdeAgendamentos = 1;
    struct agendamento* agend = malloc(1 * sizeof(struct agendamento));
    agend->descricao = malloc(sizeof(desc));
    strcpy(agend->descricao, desc);
    agend->data = *data;
    agend->prox = NULL;
    novoDia->primeiroAgendamento = agend;
    calend[mes].primeiroDia = novoDia;
    return;
  }
  
  // Inserir em um dia já existente 
  if (diaAtual->numDia == dia) {
    diaAtual->qtdeAgendamentos += 1;

    struct agendamento* agend = malloc(1 * sizeof(struct agendamento));
    agend->descricao = malloc(sizeof(desc));
    strcpy(agend->descricao, desc);
    agend->data = *data;

    struct agendamento* agendAnt = diaAtual->primeiroAgendamento;
    struct agendamento* agendAtual = diaAtual->primeiroAgendamento->prox;

    while (agendAtual != NULL && agendAtual->data.tm_hour < agend->data.tm_hour) {
      agendAnt = agendAnt->prox;
      agendAtual = agendAtual->prox;
    }

    // Final
    if (agendAtual == NULL && agendAnt->data.tm_hour < agend->data.tm_hour) {
      agendAnt->prox = agend;
      agend->prox = NULL;
      return;
    }

    // Cabeça
    if (agendAnt->data.tm_hour == diaAtual->primeiroAgendamento->data.tm_hour && agendAnt->data.tm_hour > agend->data.tm_hour) {
      diaAtual->primeiroAgendamento = agend;
      agend->prox = agendAnt;
      return;
    }

    // Meio
    if (agendAtual->data.tm_hour > agend->data.tm_hour) {
      agendAnt->prox = agend;
      agend->prox = agendAtual;
      return;
    }

  }

  // Inserir no meio (novo dia)
  if (diaAtual->numDia > dia) {
    calend[mes].qtdeDias += 1;
    struct dia* novoDia = malloc(1 * sizeof(struct dia));
    novoDia->prox = diaAtual;
    diaAnt->prox = novoDia; 
    novoDia->numDia = dia;
    novoDia->qtdeAgendamentos = 1;
    struct agendamento* agend = malloc(1 * sizeof(struct agendamento));
    agend->descricao = malloc(sizeof(desc));
    strcpy(agend->descricao, desc);
    agend->data = *data;
    agend->prox = NULL;
    novoDia->primeiroAgendamento = agend;
    return;
  }
}

void criarAgendamento(struct mes* calendario) {
  struct tm* dataRecebida = receberData(calendario);

  int estaOcupado = buscarAgendamentoPorData(dataRecebida, calendario);

  while (estaOcupado) {
    printf("\nJá existe um agendamento nesse horário, deseja verificar outra data?\n");
    printf("0 - NÃO\n");
    printf("1 - SIM\n");
    printf("--> ");
    char opcaoStr[10];
    fgets(opcaoStr, sizeof(opcaoStr), stdin);
    int opcao = atoi(opcaoStr);

    if (opcao == 1) {
      dataRecebida = receberData(calendario);
      estaOcupado = buscarAgendamentoPorData(dataRecebida, calendario);
    }
    else
      return;
  }

  char* desc = receberDescricao();

  inserirAgendamento(calendario, dataRecebida, desc);

  const char* mesesStr[] = {"Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho", "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};

  printf("\nAgendamento criado para o dia %d de %s de 2023, às %dh!\n", dataRecebida->tm_mday, mesesStr[dataRecebida->tm_mon],dataRecebida->tm_hour);

  free(desc);
  
  return;
}

// Retorna 1 se ele estiver vazio e 0 caso contrário
int calendarioEstaVazio(struct mes* calend) {
  for(int i = 0; i < 12; i++) {
    if (calend[i].qtdeDias != 0) {
      return 0;
    }
  }

  return 1;
}

void listarAgendamentos(struct mes* calendario) {
  if (calendarioEstaVazio(calendario)) {
    printf("\nNão há agendamentos registrados nesse calendário\n");
    return;
  }

  printf("\nListar Agendamentos\n");
  printf("0 - Sair\n");
  printf("1 - Todos os agendamentos\n");
  printf("2 - Um mês específico\n");
  printf("3 - Um dia específico\n");
  printf("\n--> ");
  char opcaoEscolhidaStr[8];
  fgets(opcaoEscolhidaStr, sizeof(opcaoEscolhidaStr), stdin);
  int opcaoEscolhida = atoi(opcaoEscolhidaStr);

  while (opcaoEscolhida != 0) {
    if (opcaoEscolhida == 1) {
      printf("\nListando todos os agendamentos:\n");
      printf("________________________________________________\n");
      for(int i = 0; i < 12; i++) {
        if (calendario[i].qtdeDias > 0) {
          struct dia* dia = calendario[i].primeiroDia;
          while (dia != NULL) {
            struct agendamento* agend = dia->primeiroAgendamento;
            while (agend != NULL) {
              printf("\nData: %d/%d/2023, %dh\n", agend->data.tm_mday, agend->data.tm_mon+1, agend->data.tm_hour);
              printf("Descrição: %s\n", agend->descricao);
              printf("________________________________________________\n");
              agend = agend->prox;
            }
            dia = dia->prox;
          }

        }
      }
    }


    if (opcaoEscolhida == 2) {
      printf("\nDigite o número do mês no qual você deseja listar os agendamentos: (1-12)\n");
      printf("--> ");
      char mesEscolhidoStr[8];
      fgets(mesEscolhidoStr, sizeof(mesEscolhidoStr), stdin);
      int mesEscolhido= atoi(mesEscolhidoStr);

      while(mesEscolhido < 0 || mesEscolhido > 12) {
        printf("O número deve ser entre 1 e 12 (inclusos), digite novamente:\n");
        printf("--> ");
        fgets(mesEscolhidoStr, sizeof(mesEscolhidoStr), stdin);
        mesEscolhido= atoi(mesEscolhidoStr);

      }

      if (calendario[mesEscolhido-1].qtdeDias == 0) {
        printf("O mês digitado não possui agendamentos registrados!\n");
      } else {
        const char* mesesStr[] = {"Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho", "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};

        printf("\nListando todos os agendamentos do mês de %s:\n", mesesStr[mesEscolhido-1]);
        printf("________________________________________________\n");
        struct dia* dia = calendario[mesEscolhido-1].primeiroDia;
        while (dia != NULL) {
          struct agendamento* agend= dia->primeiroAgendamento;
          while (agend != NULL) {
            printf("\nData: %d/%d/2023, %dh\n", agend->data.tm_mday, agend->data.tm_mon+1, agend->data.tm_hour);
            printf("Descrição: %s\n", agend->descricao);
            printf("________________________________________________\n");
            agend = agend->prox;
          }
          dia = dia->prox;
        }
      }
    }

    if (opcaoEscolhida == 3) {
      printf("\nDigite data na qual você deseja listar os agendamentos: (dd/mm) Exemplo: 23/05\n");
      printf("--> ");
      char mesEscolhidoStr[8];
      fgets(mesEscolhidoStr, sizeof(mesEscolhidoStr), stdin);
      int mesEscolhido= atoi(mesEscolhidoStr);

      while(mesEscolhido < 0 || mesEscolhido > 12) {
        printf("O número deve ser entre 1 e 12 (inclusos), digite novamente:\n");
        printf("--> ");
        fgets(mesEscolhidoStr, sizeof(mesEscolhidoStr), stdin);
        mesEscolhido= atoi(mesEscolhidoStr);

      }

      if (calendario[mesEscolhido-1].qtdeDias == 0) {
        printf("O mês digitado não possui agendamentos registrados!\n");
      } else {
        const char* mesesStr[] = {"Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho", "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};

        printf("\nListando todos os agendamentos do mês de %s:\n", mesesStr[mesEscolhido-1]);
        printf("________________________________________________\n");
        struct dia* dia = calendario[mesEscolhido-1].primeiroDia;
        while (dia != NULL) {
          struct agendamento* agend= dia->primeiroAgendamento;
          while (agend != NULL) {
            printf("\nData: %d/%d/2023, %dh\n", agend->data.tm_mday, agend->data.tm_mon+1, agend->data.tm_hour);
            printf("Descrição: %s\n", agend->descricao);
            printf("________________________________________________\n");
            agend = agend->prox;
          }
          dia = dia->prox;
        }
      }
    }

    printf("\nListar Agendamentos\n");
    printf("0 - Sair\n");
    printf("1 - Todos os agendamentos\n");
    printf("2 - Um mês específico\n");
    printf("3 - Um dia específico\n");
    printf("\n--> ");
    fgets(opcaoEscolhidaStr, sizeof(opcaoEscolhidaStr), stdin);
    opcaoEscolhida = atoi(opcaoEscolhidaStr);

  }
}

void fecharCalendario(struct mes* calendario) {
 return;
}