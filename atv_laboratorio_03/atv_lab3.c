#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct series Series;
typedef struct seasons Seasons;
typedef struct participants Participants;

struct participants
{
  char *artist_name;
  char *caracter_name;
  char *caracter_description;
  Participants *left, *right;
};
struct seasons
{
  int number;
  char *title;
  int num_eps;
  int year;
  Participants *participant;
  Seasons *next;
};
struct series
{
  char cod[9];
  char *title;
  int num_seasons;
  Seasons *season;
  Series *left, *right;
};

Series *start();
void insertSerie(Series **bt_series, char cod[9], char *title, int num_seasons);
void insertSeason(Series **bt, char serie_cod[9], int ssn, char *title, int num_eps, int year);
void auxParticipant(Participants **part, char *artist_name, char *caracter_name, char *caracter_description);
void insertParticipant(Series **bt, char cod[9], int season, char *artist_name, char *caracter_name, char *caracter_description);
void letterA(Series *bt);
void letterB(Series *bt, char cod[9]);
void printCaracters(Participants *part);
void letterC(Series *bt, char cod[9], int season);
void printArtirts(Participants *part, int s);
void letterD(Series *bt, char cod[9]);

void main() // Dayan Ramos
{
  Series *bt = start();

  insertSerie(&bt, "222222222", "Umbrella", 5);
  insertSerie(&bt, "111111111", "Scorpion", 8);
  insertSerie(&bt, "333333333", "Dark", 4);

  insertSeason(&bt, "333333333", 1, "1 temporada", 12, 2018);
  insertSeason(&bt, "333333333", 2, "2 temporada", 14, 2019);
  insertSeason(&bt, "333333333", 3, "3 temporada", 14, 2020);
  insertSeason(&bt, "333333333", 4, "4 temporada", 10, 2021);

  insertParticipant(&bt, "333333333", 1, "Mask Waschke", "Noah", "Susposto vilão que controla o tempo");
  insertParticipant(&bt, "333333333", 1, "Louis Hofmann", "Jonas Kahnwald", "Protagonista jovem da serie");
  insertParticipant(&bt, "333333333", 1, "Andreas Pietschmann", "Jonas Kahnwald", "Versao do futuro de jonas, adulto.");
  insertParticipant(&bt, "333333333", 4, "Lisa Vicari", "Martha Nielsen", "Viajante do tempo da terra 2");

  letterA(bt);
  printf("\n");
  letterB(bt, "333333333");
  printf("\n");
  letterC(bt, "333333333", 1);
  printf("\n");
  letterD(bt, "333333333");
}

Series *start()
{
  return NULL;
}

void insertSerie(Series **bt_series, char cod[9], char *title, int num_seasons)
{
  if ((*bt_series) == NULL)
  {
    (*bt_series) = (Series *)malloc(sizeof(Series));
    strcpy((*bt_series)->cod, cod);

    (*bt_series)->title = (char *)calloc(strlen(title), sizeof(char));

    strcpy((*bt_series)->title, title);
    (*bt_series)->num_seasons = num_seasons;

    (*bt_series)->season = NULL;
    (*bt_series)->left = NULL;
    (*bt_series)->right = NULL;
  }
  else if (strcmp((*bt_series)->cod, cod) == -1)
    insertSerie(&(*bt_series)->left, cod, title, num_seasons);
  else if (strcmp((*bt_series)->cod, cod) == 1)
    insertSerie(&(*bt_series)->right, cod, title, num_seasons);
}

void insertSeason(Series **bt, char serie_cod[9], int ssn, char *title, int num_eps, int year)
{
  if ((*bt) != NULL)
  {
    if (strcmp((*bt)->cod, serie_cod) == 0)
    {
      Seasons *node = (Seasons *)malloc(sizeof(Seasons));
      node->number = ssn;
      node->title = (char *)malloc(sizeof(char) * strlen(title));
      strcpy(node->title, title);
      node->num_eps = num_eps;
      node->year = year;
      node->participant = NULL;
      node->next = (*bt)->season;
      (*bt)->season = node;

      Seasons *i, *j;
      for (i = (*bt)->season; i != NULL; i = i->next)
      {
        for (j = i->next; j != NULL; j = j->next)
        {
          if (i->number > j->number)
          {
            int aux_i;
            char *aux_c;
            Participants *aux_p;
            aux_i = i->number;
            i->number = j->number;
            j->number = aux_i;

            aux_c = (char *)malloc(sizeof(char) * strlen(i->title));
            strcpy(aux_c, i->title);
            i->title = (char *)realloc(i->title, sizeof(char) * strlen(j->title));
            strcpy(i->title, j->title);
            j->title = (char *)realloc(j->title, sizeof(char) * strlen(aux_c));
            strcpy(j->title, aux_c);

            aux_i = i->num_eps;
            i->num_eps = j->num_eps;
            j->num_eps = aux_i;

            aux_i = i->year;
            i->year = j->year;
            j->year = aux_i;

            aux_p = i->participant;
            i->participant = j->participant;
            j->participant = aux_p;
          }
        }
      }
    }
    else if (strcmp((*bt)->cod, serie_cod) == -1)
      insertSeason(&(*bt)->left, serie_cod, ssn, title, num_eps, year);
    else if (strcmp((*bt)->cod, serie_cod) == 1)
      insertSeason(&(*bt)->right, serie_cod, ssn, title, num_eps, year);
  }
}
void auxParticipant(Participants **part, char *artist_name, char *caracter_name, char *caracter_description)
{
  if ((*part) == NULL)
  {
    (*part) = (Participants *)malloc(sizeof(Participants));
    (*part)->artist_name = (char *)malloc(sizeof(char) * strlen(artist_name));
    (*part)->caracter_name = (char *)malloc(sizeof(char) * strlen(caracter_name));
    (*part)->caracter_description = (char *)malloc(sizeof(char) * strlen(caracter_description));

    strcpy((*part)->artist_name, artist_name);
    strcpy((*part)->caracter_name, caracter_name);
    strcpy((*part)->caracter_description, caracter_description);
    (*part)->left = NULL;
    (*part)->right = NULL;
  }
  else if (strcmp((*part)->caracter_name, caracter_description) == -1)
    auxParticipant(&(*part)->left, artist_name, caracter_name, caracter_description);
  else if (strcmp((*part)->caracter_name, caracter_description) == 1)
    auxParticipant(&(*part)->right, artist_name, caracter_name, caracter_description);
}
void insertParticipant(Series **bt, char cod[9], int season, char *artist_name, char *caracter_name, char *caracter_description)
{
  if ((*bt) != NULL)
  {
    if (strcmp((*bt)->cod, cod) == 0)
    {
      Seasons *i;
      for (i = (*bt)->season; i != NULL; i = i->next)
      {
        if (i->number == season)
          auxParticipant(&i->participant, artist_name, caracter_name, caracter_description);
      }
    }
    else if (strcmp((*bt)->cod, cod) == -1)
      insertParticipant(&(*bt)->left, cod, season, artist_name, caracter_name, caracter_description);
    else if (strcmp((*bt)->cod, cod) == 1)
      insertParticipant(&(*bt)->right, cod, season, artist_name, caracter_name, caracter_description);
  }
}

void letterA(Series *bt)
{
  if (bt != NULL)
  {
    letterA(bt->left);
    printf("Titulo: %s, %d Temporadas: \n", bt->title, bt->num_seasons);
    letterA(bt->right);
  }
}

void letterB(Series *bt, char cod[9])
{
  if (bt != NULL)
  {
    letterB(bt->left, cod);
    letterB(bt->right, cod);
    if (strcmp(bt->cod, cod) == 0)
    {
      Seasons *i;
      for (i = bt->season; i != NULL; i = i->next)
        printf("Temporada %d; Titulo: %s; Numero de episodios: %d; Ano: %d\n", i->number, i->title, i->num_eps, i->year);
    }
  }
}
void printCaracters(Participants *part)
{
  if (part != NULL)
  {
    printCaracters(part->left);
    printf("Nome do artista: %s, Nome do personagem: %s, Descricao: %s\n", part->artist_name, part->caracter_name, part->caracter_description);
    printCaracters(part->right);
  }
}
void letterC(Series *bt, char cod[9], int season)
{
  if (bt != NULL)
  {
    if (strcmp(bt->cod, cod) == 0)
    {
      Seasons *i;
      for (i = bt->season; i != NULL; i = i->next)
      {
        if (i->number == season)
          printCaracters(i->participant);
      }
    }
    else if (strcmp(bt->cod, cod) == -1)
      letterC(bt->left, cod, season);
    else if (strcmp(bt->cod, cod) == 1)
      letterC(bt->right, cod, season);
  }
}

void printArtirts(Participants *part, int s)
{
  if (part != NULL)
  {
    printArtirts(part->left, s);
    printf("%s como %s na %d temporada\n", part->artist_name, part->caracter_name, s);
    printArtirts(part->right, s);
  }
}
void letterD(Series *bt, char cod[9])
{
  if (bt != NULL)
  {
    if (strcmp(bt->cod, cod) == 0)
    {
      Seasons *i;
      for (i = bt->season; i != NULL; i = i->next)
        printArtirts(i->participant, i->number);
    }
    else if (strcmp(bt->cod, cod) == -1)
      letterD(bt->left, cod);
    else if (strcmp(bt->cod, cod) == 1)
      letterD(bt->right, cod);
  }
}
