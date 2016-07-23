#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NUM_WORDS 10000
#define MAX_WORD_SIZE 100

typedef struct s_word
{
     char *w;
     unsigned int n;
}
t_word;

void init_words(t_word *words)
{
     int i;

     for (i = 0; i < MAX_NUM_WORDS; i++)
     {
          words[i].w = NULL;
          words[i].n = 0;
     }
}

void remove_char(char *w, const int pos)
{
     char tmp[MAX_WORD_SIZE];

     strcpy(tmp, w);
     strcpy(w + pos, tmp + pos + 1);
}

void clean_word(char *w)
{
     int i;

     i = 0;
     while (w[i])
     {
          w[i] = tolower(w[i]);
          if (!isalpha(w[i]))
          {
               remove_char(w, i);
               i--;
          }
          i++;
     }
}

int add_word(const char *w, t_word *words)
{
     int i;

     i = 0;
     while (i < MAX_NUM_WORDS && words[i].w != NULL)
     {
          if (!strcmp(words[i].w, w))
          {
               words[i].n++;
               return (0);
          }
          i++;
     }
     if (i < MAX_NUM_WORDS)
     {
          words[i].w = strdup(w);
          words[i].n = 1;
          return (i + 1);
     }
     fprintf(stderr, "Not enough space in the array of words\n");
     exit(1);
}

void print_words(const t_word *words)
{
     int i;

     i = 0;
     while (words[i].w)
     {
          printf("% 4d %s\n", words[i].n, words[i].w);
          i++;
     }
}

int word_cmp(const t_word *w1, const t_word *w2)
{
     if (w1->n > w2->n)
     {
          return (-1);
     }
     if (w1->n < w2->n)
     {
          return (1);
     }
     return (0);
}

int main(void)
{
     t_word words[MAX_NUM_WORDS];
     char w[MAX_WORD_SIZE];
     int n;
     int nb_words;

     nb_words = 0;
     init_words(words);
     while (!feof(stdin))
     {
          scanf("%s", w);
          clean_word(w);
          /* printf("word = [%s]\n", w); */
          n = add_word(w, words);
          if (n)
          {
               nb_words = n;
          }
          qsort(words, nb_words, sizeof(t_word), (int (*)(const void *, const void *))word_cmp);
     }
     print_words(words);
     return (0);
}
