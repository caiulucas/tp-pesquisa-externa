#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "binary_tree.h"
#include "utils.h"

void startBinaryTree(Node **root)
{
  *root = NULL;
}

// Cria um novo nó
Node *createNode(Data data, size_t pos)
{
  Node *node = (Node *)malloc(sizeof(Node));
  node->key = data.key;
  node->pos = pos;
  node->leftNode = -1;
  node->rightNode = -1;
  return node;
}

bool insertBinaryTree(Data data, FILE *binaryTreeFile)
{
  if (!binaryTreeFile)
    return false;

  // Cria um nó auxiliar para percorrer a árvore
  Node aux = {data.key, -1, -1, 0};

  // Pega a quantidade de nós no arquivo
  fseek(binaryTreeFile, 0, SEEK_END);
  size_t length = ftell(binaryTreeFile) / sizeof(Node);
  rewind(binaryTreeFile);

  // Se o arquivo estiver vazio, insere o nó na raiz
  if (length == 0)
  {
    Node *newNode = createNode(data, length);
    fwrite(newNode, sizeof(Node), 1, binaryTreeFile);
    rewind(binaryTreeFile);
    return true;
  }

  // Percorre a árvore até encontrar a posição correta para inserir o nó
  while (fread(&aux, sizeof(Node), 1, binaryTreeFile) == 1)
  {
    size_t displacement;

    // Se a chave for menor que a chave do nó atual, vai para a esquerda
    if (data.key < aux.key)
    {
      // Se não houver um nó a esquerda, insere o nó
      if (aux.leftNode == -1)
      {
        aux.leftNode = length;
        // Volta para o nó anterior e atualiza o nó
        fseek(binaryTreeFile, -sizeof(Node), SEEK_CUR);
        fwrite(&aux, sizeof(Node), 1, binaryTreeFile);
        break;
      }
      // Se houver um nó a esquerda, vai para ele
      displacement = (size_t)(aux.leftNode) * sizeof(Node);
    }
    else if (data.key > aux.key)
    {
      // Se não houver um nó a direita, insere o nó
      if (aux.rightNode == -1)
      {
        aux.rightNode = length;
        // Volta para o nó anterior e atualiza o nó
        fseek(binaryTreeFile, -sizeof(Node), SEEK_CUR);
        fwrite(&aux, sizeof(Node), 1, binaryTreeFile);
        break;
      }

      // Se houver um nó a direita, vai para ele
      displacement = (size_t)(aux.rightNode) * sizeof(Node);
    }
    // Se a chave for igual a chave do nó atual, retorna falso
    else
    {
      rewind(binaryTreeFile);
      return false;
    }

    // Vai para o nó
    fseek(binaryTreeFile, displacement, SEEK_SET);
  }

  // Cria um novo nó e insere no arquivo
  Node *newNode = createNode(data, length);

  // Vai para o final do arquivo e insere o nó
  fseek(binaryTreeFile, 0, SEEK_END);
  fwrite(newNode, sizeof(Node), 1, binaryTreeFile);
  rewind(binaryTreeFile);

  return true;
}

bool findBinaryTree(Data *data, FILE *dataFile, Quantifier *quantifier)
{
  // Abre o arquivo da árvore binária
  FILE *binaryTreeFile = fopen(BINARY_TREE_FILE, "rb");

  if (!binaryTreeFile)
    return false;

  // Cria um nó auxiliar para percorrer a árvore
  Node aux;
  while (fread(&aux, sizeof(Node), 1, binaryTreeFile) == 1)
  {
    // Se a chave for igual a chave do nó atual, retorna verdadeiro
    if (data->key == aux.key)
    {
      // Vai para a posição do registro no arquivo de dados
      fseek(dataFile, aux.pos * sizeof(Data), SEEK_SET);
      fread(data, sizeof(Data), 1, dataFile);
      quantifier->reads += 1;
      quantifier->comparisons += 1;

      rewind(dataFile);
      fclose(binaryTreeFile);
      return true;
    }

    size_t displacement;

    // Se a chave for menor que a chave do nó atual, vai para a esquerda
    quantifier->comparisons += 1;
    if (data->key > aux.key)
      displacement = (size_t)(aux.rightNode) * sizeof(Node);
    else // Se a chave for maior que a chave do nó atual, vai para a direita
      displacement = (size_t)(aux.leftNode) * sizeof(Node);

    // Vai para o nó
    fseek(binaryTreeFile, displacement, SEEK_SET);
    quantifier->reads += 1;
    }

  rewind(dataFile);
  fclose(binaryTreeFile);
  return false;
}

void createBinaryTree(FILE *dataFile)
{
  Data data;
  FILE *binaryTreeFile = fopen(BINARY_TREE_FILE, "wb+");

  if (!binaryTreeFile)
    return;

  rewind(dataFile);
  int i = 1;

  // Lê os registros do arquivo de dados e insere na árvore binária
  while (fread(&data, sizeof(Data), 1, dataFile) == 1)
  {
    clear();
    printf("[INFO] Gerando %d arquivos.\n", i++);
    insertBinaryTree(data, binaryTreeFile);
  }

  fclose(dataFile);
}

void printBinaryTree()
{
  FILE *binaryTreeFile = fopen(BINARY_TREE_FILE, "rb");

  if (!binaryTreeFile)
    return;

  Node aux;

  while (fread(&aux, sizeof(Node), 1, binaryTreeFile) == 1)
  {
    printf("Key: %d ", aux.key);
    printf("Left: %d ", aux.leftNode);
    printf("Right: %d ", aux.rightNode);
    printf("Pos: %d ", aux.pos);
    printf("\n");
  }

  fclose(binaryTreeFile);
}

bool runBinaryTree(Input input, FILE *dataFile)
{
  Quantifier quantifier;
  quantifier.reads = 0;
  quantifier.comparisons = 0;

  Data item;

  item.key = input.key;

  // Procura o item na árvore binária
  if (findBinaryTree(&item, dataFile, &quantifier))
  {
    printf("[SUCCESS] Item encontrado!\n");
    printf("[INFO] %d leituras realizadas.\n", quantifier.reads);
    printf("[INFO] %d comparações realizadas.\n", quantifier.comparisons);
    printData(item);
    return true;
  }

  printf("[INFO] %d leituras realizadas.\n", quantifier.reads);
  printf("[INFO] %d comparações realizadas.\n", quantifier.comparisons);
  printf("[FAIL] Item não encontrado!\n");
  return false;
}