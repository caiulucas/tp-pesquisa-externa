#include <stdio.h>
#include "b_star.h"

bool BStarSearch(Data *x, PointerType *Pt) // mudar pra bool
{
  int i;
  PointerType Page;
  Page = *Pt;
  if ((*Pt)->Pt == Internal)
  {
    i = 1;

    while (i < Page->UU.U0.ni && x->key > Page->UU.U0.ri[i - 1])
      i++;
    if (x->key < Page->UU.U0.ri[i - 1])
      if (BStarSearch(x, &Page->UU.U0.pi[i - 1]))
        return true;
      else if (BStarSearch(x, &Page->UU.U0.pi[i]))
        return true;
    return false;
  }
  i = 1;
  while (i < Page->UU.U1.ne && x->key > Page->UU.U1.re[i - 1].key)
    i++;
  if (x->key == Page->UU.U1.re[i - 1].key)
    return true;
  else
    return false;
}
void InitializeBStar(PointerType *root)
{
  *root = (PointerType)malloc(sizeof(PageType));
  (*root)->Pt = External;
  (*root)->UU.U1.ne = 0;
}

bool CreateBStar(FILE *binaryFile, int length, PointerType *bStarTree, Quantifier *quantifier)
{''
  InitializeBStar(bStarTree);

  // Read the base binary file and insert the datas into the B* Tree

  Data *page = (Data *)malloc(sizeof(Data));
  int currentPage = 0, itemCount;
  int totalPages = length / PAGE_ITEMS;

  while (currentPage < totalPages)
  {
    // If the page is not the last one, it is complete,
    // so the number of items is equal to the maximum items per page
    if (currentPage < totalPages)
      itemCount = PAGE_ITEMS;

    // If it is the last page, it may not be complete,
    // so calculate the number of items
    else
    {
      fseek(binaryFile, 0, SEEK_END);
      itemCount = (ftell(binaryFile) / sizeof(Data)) % PAGE_ITEMS;
      fseek(binaryFile, (totalPages - 1) * PAGE_ITEMS * sizeof(Data), SEEK_SET);
    }

    // Read the page
    fread(&page, sizeof(Data), itemCount, binaryFile);
    quantifier->reads += 1;

    // Build the B* Tree
    for (int i = 0; i < itemCount; i++)
    {
      insertIntoBStar(page[i], bStarTree, quantifier);
    }

    currentPage++;
  }

  // Measure the time required to create the tree in main memory

  return true;
}
bool insertIntoBStar(Data data, PointerType *root, Quantifier *quantifier)
{

  bool hasGrown;

  Data returnData;
  PointerType returnPointer;

  // Insert the data
  if (!recursiveInsertion(data, *root, &hasGrown, &returnData, &returnPointer, quantifier))
    return false; // if the insertion is not successful, return false

  // Create a new root when the B* Tree grows from the root
  if (hasGrown)
  {
    // Allocate an auxiliary pointer that receives the information of the new root
    PointerType newRoot = (PointerType)malloc(sizeof(PageType));
    newRoot->Pt = Internal;
    newRoot->UU.U0.ni = 1;                 // update the number of keys
    newRoot->UU.U0.ri[0] = returnData.key; // the leftmost child receives the key from the returned data
    newRoot->UU.U0.pi[1] = returnPointer;  // the right child receives the child to the right of the data
    newRoot->UU.U0.pi[0] = *root;          // the left child receives the subtree
    *root = newRoot;                       // the tree is updated with the address of the new root
  }

  return true;
}

bool recursiveInsertion(Data data, PointerType currentPage, bool *hasGrown, Data *registerReturning, PointerType *returnPointer, Quantifier *quantifier)
{

  int i = 1, j;
  PointerType novapage;

  // Chegou numa página folha
  if (currentPage->Pt == External)
  {

    // Não tem espaço na página folha, precisa criar uma nova e dividir
    if (currentPage->UU.U1.ne == MM)
    {

      // Cria e inicializa uma página folha nova
      novapage = (PointerType)malloc(sizeof(PageType));
      novapage->Pt = External;
      novapage->UU.U1.ne = 0;

      // Divide a página
      if (i < M + 1)
      {
        // Joga o último elemento da página atual para a página nova, abrindo espaço
        insertIntoExternalPage(novapage, currentPage->UU.U1.re[MM - 1]);
        currentPage->UU.U1.ne--; // atualiza a quantidade de registros da página atual
        // Insere o registro na página atual
        insertIntoExternalPage(currentPage, data);
      }

      else
        insertIntoExternalPage(novapage, data);

      // A página nova deve conter os elementos da página atual a partir da posição 2M
      // Joga os elementos da posição 2M até a posição final para a página nova
      for (j = M + 2; j <= MM; j++)
      {
        insertIntoExternalPage(novapage, currentPage->UU.U1.re[j - 1]);
      }

      currentPage->UU.U1.ne = M + 1; // atualiza a quantidade de registros da página atual

      // Atualiza os retornos e aciona a hasGrown
      // Uma vez que a página folha foi dividida, a página nó recebe um novo elemento
      *registerReturning = currentPage->UU.U1.re[M];
      *returnPointer = novapage;
      *hasGrown = true;

      return true;
    }

    // Tem espaço na página folha, insere
    else
    {
      insertIntoExternalPage(currentPage, data);
      *hasGrown = false;
      return true;
    }
  }

  // Está numa página nó
  else
  {
    // Caminha pelas páginas nó até achar uma página com a chave pesquisada
    while (i < currentPage->UU.U0.ni && data.key > currentPage->UU.U0.ri[i - 1])
    {
      i++;
    }

    // Se a chave já está presente e é uma página folha, retorna false e encerra a recursão
    // A chave estar em uma página nó não quer dizer que ela existe como registro em uma página folha
    // Mas, dessa forma, funciona neste caso

    if (data.key == currentPage->UU.U0.ri[i - 1])
    {
      *hasGrown = false;
      return false;
    }

    // Se a chave pesquisada for menor do que a chave atual,
    // diminui 1 do índice para chamar a página anterior à da chave atual.
    // Caso contrário, o índice permanece igual para chamar a página seguinte à da chave atual.

    if (data.key < currentPage->UU.U0.ri[i - 1])
      i--;

    recursiveInsertion(data, currentPage->UU.U0.pi[i], hasGrown, registerReturning, returnPointer, quantifier);

    if (!*hasGrown)
      return true;

    // Se a página tem espaço para inserir, insere e retorna sucesso
    if (currentPage->UU.U0.ni < MM)
    {
      insertIntoInternalPage(currentPage, registerReturning->key, *returnPointer);
      *hasGrown = false;
      return true;
    }

    // Overflow: Se não tiver espaço, a página precisa ser dividida
    novapage = (PointerType)malloc(sizeof(PageType));
    novapage->Pt = Internal;
    novapage->UU.U0.ni = 0;
    novapage->UU.U0.pi[0] = NULL;

    // Verifica a posição do elemento a ser inserido na página
    // Caso ele deva ficar à esquerda do índice do meio, deixamos ele na página atual
    if (i < M + 1)
    {
      insertIntoInternalPage(novapage, currentPage->UU.U0.ri[MM - 1], currentPage->UU.U0.pi[MM]);
      currentPage->UU.U0.ni--;
      insertIntoInternalPage(currentPage, registerReturning->key, *returnPointer);
    }

    // Caso ele deva ficar à direita, ou seja o índice do meio, ele irá ficar na página nova
    else
    {
      insertIntoInternalPage(novapage, registerReturning->key, *returnPointer);
    }

    // Arrasta a metade final dos elementos da página atual para a página nova
    for (j = M + 2; j <= MM; j++)
      insertIntoInternalPage(novapage, currentPage->UU.U0.ri[j - 1], currentPage->UU.U0.pi[j]);

    // Como houve a criação da página nova, pela falta de espaço,
    // a página atual passa a ter a ordem mínima para existência
    currentPage->UU.U0.ni = M;
    novapage->UU.U0.pi[0] = currentPage->UU.U0.pi[M + 1];
    registerReturning->key = currentPage->UU.U0.ri[M];
    *returnPointer = novapage;
  }

  return true;
}

bool insertIntoInternalPage(PointerType page, int key, PointerType rightPointer)
{
  int amountOfItems = page->UU.U0.ni;
  bool notFound = (amountOfItems > 0);

  while (notFound)
  {

    if (key >= page->UU.U0.ri[amountOfItems - 1])
    {
      notFound = false;
      break;
    }

    page->UU.U0.ri[amountOfItems] = page->UU.U0.ri[amountOfItems - 1];
    page->UU.U0.pi[amountOfItems + 1] = page->UU.U0.pi[amountOfItems];
    amountOfItems--;

    if (amountOfItems < 1)
      notFound = false;
  }

  page->UU.U0.ri[amountOfItems] = key;
  page->UU.U0.pi[amountOfItems + 1] = rightPointer;
  page->UU.U0.ni++;

  return true;
}

bool insertIntoExternalPage(PointerType page, Data data)
{
  int amountOfItems = page->UU.U1.ne;
  short notFound = (amountOfItems > 0);

  while (notFound)
  {

    if (data.key >= page->UU.U1.re[amountOfItems - 1].key)
    {
      notFound = false;
      break;
    }

    page->UU.U1.re[amountOfItems] = page->UU.U1.re[amountOfItems - 1];
    amountOfItems--;

    if (amountOfItems < 1)
      notFound = false;
  }

  page->UU.U1.re[amountOfItems] = data;
  page->UU.U1.ne++;

  return true;
}