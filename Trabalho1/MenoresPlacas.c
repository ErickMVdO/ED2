#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef int Item;
#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define lesseq(A, B) ((A) <= (B))
#define exch(A, B) \
  {                \
    Item t = A;    \
    A = B;         \
    B = t;         \
  }
#define cmpexch(A, B) \
  {                   \
    if (less(B, A))   \
      exch(A, B);     \
  }

void radixsort(Item *v, int l, int n)
{
  // v = vetor de números
  // l = posição onde começa o vetor
  // n = índice mais a direita do vetor
  // ex.: [0, 1, 2, 3] -> n=4

  int aux, aux1, maxdigitos = 8;
  n++;

  // Calcula a maior quantidade de dígitos de um
  // único número no vetor

  for (int j = 0; j < maxdigitos; j++)
  {
    int z = 0, u = 0, d = 0, t = 0, q = 0, c = 0, s = 0, st = 0, o = 0, nv = 0;

    Item *zero = malloc((n - l + 2) * sizeof(Item));
    Item *um = malloc((n - l + 2) * sizeof(Item));
    Item *dois = malloc((n - l + 2) * sizeof(Item));
    Item *tres = malloc((n - l + 2) * sizeof(Item));
    Item *quatro = malloc((n - l + 2) * sizeof(Item));
    Item *cinco = malloc((n - l + 2) * sizeof(Item));
    Item *seis = malloc((n - l + 2) * sizeof(Item));
    Item *sete = malloc((n - l + 2) * sizeof(Item));
    Item *oito = malloc((n - l + 2) * sizeof(Item));
    Item *nove = malloc((n - l + 2) * sizeof(Item));

    int k = 0, h = 0, zeros = 0;
    aux1 = pow(10, j);
    aux = pow(10, j + 1);

    // Dividindo os valores de acordo com a casa de unidade/dezena/...
    for (int i = l; i < n; i++)
    {

      if (v[i] == 0)
      {
        zeros++;
        k++;
      }
      else if (((v[i] % aux) / aux1) == 0)
      {
        zero[z] = v[i];
        z++;
        k++;
      }
      else if (((v[i] % aux) / aux1) == 1)
      {
        um[u] = v[i];
        u++;
        k++;
      }
      else if (((v[i] % aux) / aux1) == 2)
      {
        dois[d] = v[i];
        d++;
        k++;
      }
      else if (((v[i] % aux) / aux1) == 3)
      {
        tres[t] = v[i];
        t++;
        k++;
      }
      else if (((v[i] % aux) / aux1) == 4)
      {
        quatro[q] = v[i];
        q++;
        k++;
      }
      else if (((v[i] % aux) / aux1) == 5)
      {
        cinco[c] = v[i];
        c++;
        k++;
      }
      else if (((v[i] % aux) / aux1) == 6)
      {
        seis[s] = v[i];
        s++;
        k++;
      }
      else if (((v[i] % aux) / aux1) == 7)
      {
        sete[st] = v[i];
        st++;
        k++;
      }
      else if (((v[i] % aux) / aux1) == 8)
      {
        oito[o] = v[i];
        o++;
        k++;
      }
      else if (((v[i] % aux) / aux1) == 9)
      {
        nove[nv] = v[i];
        nv++;
        k++;
      }
    }

    // Adicionando um 0 no final dos vetores
    zero[z] = 0;
    um[u] = 0;
    dois[d] = 0;
    tres[t] = 0;
    quatro[q] = 0;
    cinco[c] = 0;
    seis[s] = 0;
    sete[st] = 0;
    oito[o] = 0;
    nove[nv] = 0;

    // Reagrupando os vetores que estão divididos
    for (int i = 0; i < zeros && zeros != 0; i++)
    {
      v[h] = 0;
      h++;
    }
    for (int i = 0; zero[i] != 0; i++)
    {
      v[h] = zero[i];
      h++;
    }
    for (int i = 0; um[i] != 0; i++)
    {
      v[h] = um[i];
      h++;
    }
    for (int i = 0; dois[i] != 0; i++)
    {
      v[h] = dois[i];
      h++;
    }
    for (int i = 0; tres[i] != 0; i++)
    {
      v[h] = tres[i];
      h++;
    }
    for (int i = 0; quatro[i] != 0; i++)
    {
      v[h] = quatro[i];
      h++;
    }
    for (int i = 0; cinco[i] != 0; i++)
    {
      v[h] = cinco[i];
      h++;
    }
    for (int i = 0; seis[i] != 0; i++)
    {
      v[h] = seis[i];
      h++;
    }
    for (int i = 0; sete[i] != 0; i++)
    {
      v[h] = sete[i];
      h++;
    }
    for (int i = 0; oito[i] != 0; i++)
    {
      v[h] = oito[i];
      h++;
    }
    for (int i = 0; nove[i] != 0; i++)
    {
      v[h] = nove[i];
      h++;
    }
    if (k == 0)
    {
      j = maxdigitos;
    }

    free(zero);
    free(um);
    free(dois);
    free(tres);
    free(quatro);
    free(cinco);
    free(seis);
    free(sete);
    free(oito);
    free(nove);
  }
}

int estaOrdenado(Item *v, int placa, int i)
{
  if (v[i] < placa)
    return 1;
  return 0;
}

int main()
{

  int op, placa, i = 0, tam = 10;
  int ordena = 1, maior = 0, qtd = 0, aux = 0, last = 99;
  int v[100];

  while (scanf("%d %d", &op, &placa) != EOF)
  {
    //printf("Ordena: %d\naux= %d\n", ordena, aux);

    if (op == 1)
    {
      if (qtd >= 100)
      {
        if (last == 0)
        {
          radixsort(v, 0, i - 1);
          ordena = 0;
          last = 99;
          aux = 0;
        }
        if (placa > v[last])
          ordena = 0;
        else
        {
          ordena = 1;
          aux = 1;
          //printf("%d %d -> %d\n", last, v[last], placa);
          v[last] = placa;
          last--;
          //printf("vetor inicial: %d\nvetor final: %d\n", v[0], v[99]);
        }
      }
      else
      {
        v[i++] = placa;
        if (i > 0 && i < 100)
        {
          if (estaOrdenado(v, placa, i - 1) == 1 && aux == 0)
            ordena = 0;
          else
          {
            ordena = 1;
            aux = 1;
          }
        }
      }
      qtd++;
    }
    else
    {
      aux = 0;
      last = 99;
      if (ordena == 1)
        radixsort(v, 0, i - 1);
      for (int j = 0; j < placa; j++)
      {
        if (j == 0)
          printf("%d", v[j]);
        else
          printf(" %d", v[j]);
      }
      printf("\n");
      ordena = 0;
    }
  }
  printf("\n");

  return 0;
}