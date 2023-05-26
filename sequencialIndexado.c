#include <stdlib.h>
#include <stdio.h>
#include "sequencialIndexado.h"

int pesquisa(tipoindice tab[], int tam, Data *item, FILE *arq)
{
  Data pagina[ITENSPAGINA];
  int i, quantItens;
  long desloc;
  // procura pela página onde o item pode se encontrar
  i = 0;
  while (i < tam && tab[i].key <= item->key)
    i++;
  // caso a key desejada seja menor que a 1a key, o item
  // não existe no arquivo
 /* if (i == 0)
    return 0;
  else
  {
    // a ultima página pode não estar completa
    if (i < tam)
      quantItens = ITENSPAGINA;
    else
    {
      fseek(arq, 0, SEEK_END);
      quantItens = (ftell(arq) / sizeof(Data)) % ITENSPAGINA;
    }
    // lê a página desejada do arquivo
    desloc = (tab[i - 1].pos - 1) * ITENSPAGINA * sizeof(Data);

    fseek(arq, desloc, SEEK_SET);
    fread(&pagina, sizeof(Data), quantItens, arq);
    // pesquisa sequencial na página lida
    for (i = 0; i < quantItens; i++)
      if (pagina[i].key == item->key)
      {
        *item = pagina[i];
        return 1;
      }
    return 0;
  }
  */
}