#include <stdio.h>
#include <stdlib.h>

#include "ptree.h"


int main(int argc, char *argv[]) {
    // Creates a ptree to test printing
    struct TreeNode root, child_one, child_two, grandchild, ggc ,gc1;
    root.pid = 123;
    root.name = "root process";
    root.child_procs = &child_one;
    root.next_sibling = NULL;

    child_one.pid = 456;
    child_one.name = "first child";
    child_one.child_procs = &gc1;
    child_one.next_sibling = &child_two;

    gc1.pid = 111;
    gc1.name = "gc1";
    gc1.child_procs = NULL;
    gc1.next_sibling = NULL;

    child_two.pid = 222;
    child_two.name = "second child";
    child_two.child_procs = &grandchild;
    child_two.next_sibling = NULL;

    grandchild.pid = 333;
    grandchild.name = "grandchild";
    grandchild.child_procs = &ggc;
    grandchild.next_sibling = NULL;

    ggc.pid = 444;
    ggc.name = "ggc";
    ggc.child_procs = NULL;
    ggc.next_sibling = NULL;

    print_ptree(&root, 1);

    return 0;
}

