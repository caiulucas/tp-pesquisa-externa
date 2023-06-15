#include <stdbool.h>
#include "b_star_tree.h"

bool searchBStarTree(Register *reg, Page **node)
{
  Page *page = *node;

  int i = 1;
  if ((*node)->ptr == Internal)
  {
    while (i < page->pages.internalPage.nInternal && reg->key > page->pages.internalPage.internalRegisters[i - 1])
      i++;

    if (reg->key < page->pages.internalPage.internalRegisters[i - 1])
      return searchBStarTree(reg, &page->pages.internalPage.internalPointers[i - 1]);

    return searchBStarTree(reg, &page->pages.internalPage.internalPointers[i]);
  }

  while (i < page->pages.externalPage.nExternal && reg->key > page->pages.externalPage.externalReg[i - 1].key)
    i++;

  if (reg->key == page->pages.externalPage.externalReg[i - 1].key)
  {
    *reg = page->pages.externalPage.externalReg[i - 1];
    return true;
  }

  return false;
}