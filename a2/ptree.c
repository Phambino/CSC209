#include <stdio.h>
// Add your system includes here.
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <unistd.h>
#include <dirent.h>
#include "ptree.h"

// Defining the constants described in ptree.h
const unsigned int MAX_PATH_LENGTH = 1024;

// If TEST is defined (see the Makefile), will look in the tests 
// directory for PIDs, instead of /proc.
#ifdef TEST
    const char *PROC_ROOT = "tests";
#else
    const char *PROC_ROOT = "/proc";
#endif


/*
 * Creates a PTree rooted at the process pid. The root of the tree is
 * placed in root. The function returns 0 if the tree was created 
 * successfully and 1 if the tree could not be created or if at least
 * one PID was encountered that could not be found or was not an 
 * executing process.
 */
int generate_ptree(struct TreeNode **root, pid_t pid) {
    // Here's a trick to generate the name of a file to open. Note 
    // that it uses the PROC_ROOT variable
    struct stat buffer;
    char procfile[MAX_PATH_LENGTH + 1];
    if (sprintf(procfile, "%s/%d/exe", PROC_ROOT, pid) < 0) {
        fprintf(stderr, "sprintf failed to produce a filename\n");
        return 1;
    }
    // Your implementation goes here.
    if(lstat(procfile,&buffer) != 0) {
	fprintf(stderr, "exe not found\n");
	return 1;
    }
    
    *root = malloc(sizeof(struct TreeNode));
    (*root)->pid = pid;
    (*root)->name = NULL;
    (*root)->child_procs = NULL;
    (*root)->next_sibling = NULL;
    char temp[MAX_PATH_LENGTH + 1];
    char name[MAX_PATH_LENGTH + 1];

    if (sprintf(temp, "%s/%d/cmdline",PROC_ROOT,pid) < 0) {
	fprintf(stderr, "sprintf failed to produce a filename\n");
	return 1;
    }

    if(lstat(temp,&buffer) !=0) {
	fprintf(stderr, "lstat: No such file or directory\n");
	return 1;
    }
    
    // Assign name
    FILE *f = fopen(temp,"r");
    if(f == NULL){
	fprintf(stderr, "failed to open file\n");
	return 1;
    }
    while(fscanf(f,"%s",name) != EOF) {
	(*root)->name = malloc(strlen(basename(name)) + 1);
	strcpy((*root)->name,basename(name));
    }
    if(fclose(f) == EOF) {
	fprintf(stderr, "failed to close file");
	return 1;
    }
    
    //check if task folder exists
    char temp3[MAX_PATH_LENGTH + 1];
    if(sprintf(temp3, "%s/%d/task",PROC_ROOT,pid) < 0) {
	fprintf(stderr, "sprintf failed to produce a filename\n");
	return 1;
    }
    if(lstat(temp3,&buffer) != 0) {
	fprintf(stderr, "lstat: No such file or directory\n");
	return 1;
    }

    //check if pid folder in tasks exists
    char temp4[MAX_PATH_LENGTH + 1];
    if(sprintf(temp4, "%s/%d/task/%d",PROC_ROOT,pid,pid) < 0) {
	fprintf(stderr, "sprintf failed to produce a filename\n");
	return 1;
    }
    if(lstat(temp4,&buffer) != 0) {
	fprintf(stderr, "lstat: No such file or directory\n");
	return 1;
    }

    //check children file exists
    char temp2[MAX_PATH_LENGTH + 1];
    if (sprintf(temp2, "%s/%d/task/%d/children", PROC_ROOT,pid,pid) < 0) {
	fprintf(stderr, "sprintf failed to produce a filename\n");
	return 1;
    }
    if(lstat(temp2,&buffer) != 0) {
	fprintf(stderr, "lstat: No such file or directory\n");
	return 1;
    }	

    int childpid;
    FILE *g = fopen(temp2,"r");
    if(g == NULL){
	fprintf(stderr, "failed to open file\n");
	return 1;
    }

    struct TreeNode *prev = NULL;
    //Recursive calls
    while(fscanf(g, "%d%*c", &childpid) != -1) {
	struct TreeNode *next;
	generate_ptree(&next,childpid);

	if(prev == NULL) {
	    (*root)->child_procs = malloc(sizeof(struct TreeNode));
	    (*root)->child_procs = next;
	    prev = next;
	} else {
	    prev->next_sibling = next;
	    prev = next;
    	}
    }
    if(fclose(g) != 0) {
	fprintf(stderr, "failed to close file");
	return 1;
    }
    return 0;
}


/*
 * Prints the TreeNodes encountered on a preorder traversal of an PTree
 * to a specified maximum depth. If the maximum depth is 0, then the 
 * entire tree is printed.
 */
void print_ptree(struct TreeNode *root, int max_depth) {
    // Here's a trick for remembering what depth (in the tree) you're at
    // and printing 2 * that many spaces at the beginning of the line.
    static int depth = 0;
    struct TreeNode *prev = root;
    if(root == NULL){
	return;
    }
    if(max_depth == 1){
	if(root->name == NULL) {
	    printf("%*s", depth * 2, "");
	    printf("%d\n",root->pid);
	} else {	
    	    printf("%*s", depth * 2, "");
    	    printf("%d: %s\n",root->pid, root->name);
	}
    } else {
	if(root->name == NULL) {
	    printf("%*s", depth * 2, "");
	    printf("%d\n",root->pid);
	} else {
    	    printf("%*s", depth * 2, "");
    	    printf("%d: %s\n",root->pid, root->name);
	}
	if(depth + 1 < max_depth || max_depth == 0){    
	    depth++;
	    if(root->child_procs != NULL){
	  	print_ptree(root->child_procs, max_depth);
	    }
	    depth--;
	}
	if(root->next_sibling != NULL){
	    print_ptree(prev->next_sibling, max_depth);
	    prev = prev->next_sibling;
	}
    }

}
