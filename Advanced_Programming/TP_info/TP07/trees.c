/* Source Code From Laure Gonnord and Bernard Carré
 * Modified by Walter Rudametkin
 */

#include "trees.h"

#define SIZE 20

// construction of a tree by return value
// struct node * cons(int val, struct node *left, struct node *right)
//{
//     PtNode new = malloc(sizeof(Node));
//     new->val=val;
//     new->left=left;
//     new->right=right;
//     return new;
// }

// construction of a tree by pointer
void cons_tree (struct node **ptr_tree, int val, struct node *left, struct node *right)
{
    if (NULL == *ptr_tree)
    {
        *ptr_tree = malloc(sizeof(struct node));
    }
    (*ptr_tree)->val   = val;
    (*ptr_tree)->left  = left;
    (*ptr_tree)->right = right;
}

// create an empty tree by return value
// struct node * mk_empty_tree()
//{
//	return NULL;
//}

// initialize un empty tree
void mk_empty_tree (struct node **ptr_tree)
{
    /*(**ptr_tree).val   = 0;   //Valeur intermédiaire mené à être supprimé/remplacé
    (**ptr_tree).left  = NULL;
    (**ptr_tree).right = NULL;*/

    *ptr_tree = NULL;   //Car l'arbre est vide, donc son pointeur doit pointer vers "rien"
}

// tree is empty?
bool is_empty (struct node *tree)
{
    return (tree == NULL) ? true : false;
}

// t is a leaf?
bool is_leaf (struct node *tree)
{
    return (!is_empty (tree) && is_empty (tree->left) && is_empty (tree->right));
}

// add x in a bst wtr its value.
void add (struct node **ptr_tree, int x)
{
    if (NULL == *ptr_tree)
    {
        cons_tree(ptr_tree,x,NULL,NULL);
        return;
    }
    if (x <= (*ptr_tree)->val)
    {
        add(&((*ptr_tree)->left),x);
        return;
    }
    else
    {
        add(&((*ptr_tree)->right),x);
        return;
    }
}

// print values of tree in ascendant order (left-value-right)
void print_tree (struct node *tree)
{
    if (NULL == tree) return;
    print_tree(tree->left);
    printf("%d ",tree->val);
    print_tree(tree->right);
}

// build a tree "add"ing values of the file fp
void load_tree (FILE *fp, struct node **ptr_tree)
{
    char *buff = malloc(SIZE * sizeof(char));
    size_t len = 0;
    getline(&buff,&len,fp);
    int val = 0;
    char *tok = strtok(buff," ");

    while (tok != NULL)
    {
        if (strcmp(tok,"\n") == 0) break;
        val = atoi(tok);
        add(ptr_tree,val);
        tok = strtok(NULL," ");
    }


    /*while ((tok = strtok(buff," ")) != NULL)
    {
        //if (tok == "\n") break;
        if (strcmp(tok,"\n") == 0) break;
        val = atoi(tok);
        add(ptr_tree,val);
        tok = strtok(NULL," ");
    }*/
    // Tip: use while(fscanf(..) ...)
}

// Free all memory used by the tree
void free_tree (struct node **ptr_tree)
{
    if (*ptr_tree == NULL) return;
    free_tree(&((*ptr_tree)->left));
    free_tree(&((*ptr_tree)->right));
    free(*ptr_tree);
    *ptr_tree = NULL;
}


// print pairs (father =L/R=> son)
void print_rec_edges (struct node *tree)
{
    if (tree == NULL) return;
    if (tree->left != NULL)
    {
        printf("%d -> %d;\n",tree->val,tree->left->val);
        print_rec_edges(tree->left);
    }
    if (tree->right != NULL)
    {
        printf("%d -> %d;\n",tree->val,tree->right->val);
        print_rec_edges(tree->right);
    }
}

// PART II

// recursively prints arcs of the tree <value,left,right> into the file fp:
// "value -> left;"  if it exists
// "value -> right;" if it exists
// check for: !is_empty(t) & !is_leaf(t)
void recursive_dot (struct node *tree, FILE *fp)
{
    if (is_empty(tree) || is_leaf(tree)) return;
    if (tree->left != NULL)
    {
        fprintf(fp,"\t%d -> %d;\n",tree->val,tree->left->val);
        recursive_dot(tree->left,fp);
    }
    if (tree->right != NULL)
    {
        fprintf(fp,"\t%d -> %d;\n",tree->val,tree->right->val);
        recursive_dot(tree->right,fp);
    }
}


// generate a .dot file for the tree
// limits (no arcs) :
//   is_empty(t) => "empty" digraph
//   is_leaf(t) => only one node
// general case :
//   calls recursive_dot which prints arcs
void generate_dot (struct node *t, FILE *fp)
{
    fprintf (fp, "digraph G {\n");
    if (!is_empty (t))
    {
        if (is_leaf (t))
        {
            fprintf (fp, "\t%d", t->val);
        }
        else
        {
            recursive_dot (t, fp);
        }
    }
    fprintf (fp, "}\n");
}
