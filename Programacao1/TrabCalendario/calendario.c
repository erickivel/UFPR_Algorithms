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

  printf("Qual data você quer criar seu agendamento? (dd/mm)\n");
  strDataTam = getline(&strData, &tamInicial, stdin);
  char* diaStr = strtok(strData, "/");
  if (diaStr == NULL) diaStr = "0";
  char* mesStr = strtok(NULL, "/");
  if (mesStr == NULL) mesStr = "0";
  int dia = atoi(diaStr);
  int mes = atoi(mesStr);

  // Verifica se: 
  //  - A data possui exatamente 5 digitos "dd/mm";
  //  - O dia recebido está entre 1 e 31;
  //  - O mês recebido está entre 1 e 12;
  while(dia > 31 || dia < 1 || mes > 12 || mes < 1) {
    printf("Data inválida, digite novamente:\n");
    strData = malloc(tamInicial * sizeof(char));
    strDataTam = getline(&strData, &tamInicial, stdin);
    diaStr = strtok(strData, "/");
    if (diaStr == NULL) diaStr = "0";
    mesStr = strtok(NULL, "/");
    if (mesStr == NULL) mesStr = "0";
    dia = atoi(diaStr);
    mes = atoi(mesStr);
  }

  printf("Qual horário você quer criar seu agendamento? (0-23)\n");
  char horarioStr[10];
  fgets(horarioStr, sizeof(horarioStr), stdin);
  int horario = atoi(horarioStr);
  while (horario > 23 || horario < 0) {
    printf("A hora deve ser entre 0 e 23 (inclusos), digite a hora do agendamento novamente:\n");
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

  while (diaCal->numDia != dia) {
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
  size_t tamInicial = 1;
  size_t strDescTam;
  char* strDesc = malloc(tamInicial * sizeof(char));

  if (strDesc == NULL) {
    perror("Não foi possível alocar a descrição");
    exit(1);
  } 

  printf("Esse horário está livre, digite a descrição do seu agendamento: \n");
  getline(&strDesc, &strDescTam, stdin);

  return strDesc;
}

void inserirAgendamento(struct mes* calend, struct tm* data, char* desc) {
  int dia = data->tm_mday;
  int mes = data->tm_mon;

  struct dia* diaAnt = calend[mes].primeiroDia;

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

  while (diaAtual == NULL || diaAtual->numDia < dia) {
    diaAtual = diaAtual->prox;
  }
}

void criarAgendamento(struct mes* calendario) {
  struct tm* dataRecebida = receberData(calendario);

  // struct dia* d = calendario[11].primeiroDia;
  // if (d != NULL) 
  //   printf("Date Depaosoosaiasi : %d\n", d->primeiroAgendamento->data->tm_hour);

  int estaOcupado = buscarAgendamentoPorData(dataRecebida, calendario);
  printf("Esta Ocupado: %d\n", estaOcupado);

  // if (1) {
  //   printf("\nJá existe um agendamento nesse horário, você deseja verificar outra data?\n");
  //   printf("0 - NÃO\n");
  //   printf("1 - SIM\n");
  //   printf("--> ");
  //   int opcao;
  //   scanf("%d", &opcao);

  //   if (opcao == 1)
  //     criarAgendamento(calendario);
  //   else
  //     return;
  // }
  
  if (estaOcupado) {
    printf("\nJá existe um agendamento nesse horário\n");
    return;
  }

  char* desc = receberDescricao();

  inserirAgendamento(calendario, dataRecebida, desc);
  free(desc);
  
  return;
}

void listarAgendamentos(struct mes* calendario) {

}