#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

// sirina i visina 2D polja koje se koristi za funkciju print_tree
#define WIDTH 80
#define HEIGHT 10

typedef struct node_struct{
    int key;
    struct node_struct *parent;
    struct node_struct *left;
    struct node_struct *right;
} Node;

Node *add_node(Node *node, Node *parent, int key) {
    if (!node) {
        node = (Node*) malloc(sizeof(Node));
        node->key = key;
        node->parent = parent;
        node->left = node->right = NULL;
        return node;
    }
    if (key < node->key) {
        node->left = add_node(node->left,node,key);
    } else {
        node->right = add_node(node->right,node,key);
    }
    return node;
}

int print_tree(Node *tree, int is_left, int offset, int depth, char s[HEIGHT][WIDTH]) {
    char b[HEIGHT];
    int i, left, right, width = 5;

    if (!tree) return 0;
    sprintf(b,"(%03d)",tree->key);
    left = print_tree(tree->left,1,offset,depth+1,s);
    right = print_tree(tree->right,0,offset+left+width,depth+1,s);
    for (i=0; i<width; i++)
        s[depth][offset+left+i] = b[i];
    if (depth) {
        if (is_left) {
            for (i=0; i<width+right; i++)
                s[depth-1][offset+left+width/2+i] = '-';
        } else {
            for (i=0; i<left+width; i++)
                s[depth-1][offset-width/2+i] = '-';
        }
        s[depth-1][offset+left+width/2] = '.';
    }
    return left+width+right;
}

Node *vrati(Node *node, int *val, int *brojac) {
    if(!node)
        return node;
    Node *nti_cvor=NULL;
    nti_cvor = vrati(node->left, val, brojac);
    if(nti_cvor)
        return nti_cvor;
    (*brojac)++;

    if(*brojac == *val)
        return node;

    nti_cvor = vrati(node->right, val, brojac);
    return nti_cvor;
}
Node *vrati_n_ti(Node *node, int *val){
    int brojac = 0;
    return vrati(node, val, &brojac);
}

int main() {
    int i, menu_choice, val;
    char c, print_format[6], empty_line[WIDTH], s[HEIGHT][WIDTH];
    Node *new_node, *root=NULL, *nti=NULL;

    setbuf(stdout, NULL);
    do {
        DEBUG("\n1 Vrati n ti najmanji broj (vrati_n_ti)");
        DEBUG("\n2.Unos elemenata u stablo (1-999)\n3.Ispis stabla\n4.Izlaz\n");
        scanf("%d", &menu_choice);

        switch(menu_choice) {
            case 1:
                DEBUG("Unesite redni broj:\n");
                scanf("%d", &val);
                nti = vrati_n_ti(root, &val);
                if (nti) printf("%d\n", nti->key);
                else printf("0\n");
                break;
            case 2:
                DEBUG("Unos zakljucite bilo kojim nebrojcanim znakom: ");
                while (scanf("%d", &val)==1) {
                    if (val<1 || val>999) continue;
                    new_node = add_node(root,NULL,val);
                    if (new_node) root = new_node;
                }
                while((c=getchar())!='\n' && c!=EOF);
                break;
            case 3:
                sprintf(print_format, "%%%ds", WIDTH-1);
                for (i=0; i<HEIGHT; i++)
                    sprintf(s[i], print_format, " ");

                print_tree(root,0,0,0,s);

                sprintf(empty_line, print_format, " ");
                for (i=0; i<HEIGHT; i++) {
                    if (strcmp(s[i],empty_line))
                        printf("%s\n", s[i]);
                }
                break;
            case 4:
                break;
            default:
                while((c=getchar())!='\n' && c!=EOF);
        }
    } while(menu_choice!=4);
    return 0;
}
