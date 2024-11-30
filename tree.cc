#include "tree.h"

#include "utest.h"

#include <random>

#define NO_ENTRIES 10000

using SplayTree = FinalProject::SplayTree<int>;
using TreeNode  = SplayTree::TreeNode;

const auto Comparison = [](TreeNode* lhs, TreeNode* rhs) {
    return lhs->key - rhs->key;
};

UTEST(SplayTree, InsertAndSearch) {
  auto tree = SplayTree(Comparison);
  TreeNode data[NO_ENTRIES];
  for (int i = 0; i < NO_ENTRIES; i++) {
    data[i].key = i * 2 + 1;
    ASSERT_TRUE(tree.Insert(&data[i]));
  }

  TreeNode query;
  TreeNode *cur;

  for (int i = 0; i < 2 * NO_ENTRIES; i++) {
    query.key = i;
    cur       = tree.Search(&query);
    if (i % 2) {
      ASSERT_EQ(cur->key, i);
      ASSERT_EQ(cur, tree.RootPtr());
    } else {
      ASSERT_EQ(cur, nullptr);
    }
  }
}

UTEST(SplayTree, RemoveAndLowerBound) {
  auto tree = SplayTree(Comparison);
  TreeNode data[NO_ENTRIES];
  for (int i = 0; i < NO_ENTRIES; i++) {
    data[i].key = i;
    ASSERT_TRUE(tree.Insert(&data[i]));
  }

  bool already_deleted[NO_ENTRIES + 1] = {false};

  TreeNode query;
  TreeNode *cur;
  
  for (int i = 0; i < NO_ENTRIES * 1.5; i++) {
    query.key = rand() % (NO_ENTRIES);
    cur       = tree.Search(&query);

    if (already_deleted[query.key]) {
      ASSERT_EQ(cur, nullptr);
    } else {
      already_deleted[query.key] = true;
      ASSERT_NE(cur, nullptr);
      ASSERT_TRUE(tree.Delete(&query));
      cur = tree.Search(&query);
      ASSERT_EQ(cur, nullptr);
    }

    cur = tree.LowerBound(&query);
    if (cur) { ASSERT_GT(cur->key, query.key); }
  }
}

UTEST_MAIN();
