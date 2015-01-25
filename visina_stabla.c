#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

#define MAX_TREE_STRING 100
#define MAX_NODES 100

// sirina i visina 2D polja koje se koristi za funkciju print_tree
#define WIDTH 80
#define HEIGHT 10

typedef struct node {
    int key;
    struct node *left;
    struct node *right;
} Node;

int print_tree(Node *tree, int is_left, int offset, int depth, char s[HEIGHT][WIDTH]) {
    char b[HEIGHT];
    int i, left, right, width = 3;

    if (!tree) return 0;
    sprintf(b,"(%c)",tree->key);
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

Node *create_tree(char *tree_string) {
    Node *queue[MAX_NODES];
    Node *trenutni, *parent;
    int tail, head, i;

    tail = head = -1;
    trenutni = parent = NULL;

    for(i=0; i<strlen(tree_string); i++) {
        if (tree_string[i]!=';') {
            if (tree_string[i]=='-') continue;
            trenutni = (Node *)malloc(sizeof(Node));
            trenutni->key = tree_string[i];
            trenutni->left = trenutni->right = NULL;

            queue[++tail] = trenutni;
            if (parent && tree_string[i-1]==';') {
                parent->left = trenutni;
            } else if (i>0) {
                parent->right = trenutni;
            }
        } else {
            parent = queue[++head];
        }
    }
    return queue[0];
}


int visina(Node *node) {
    if(!node) //jedino kada je root==NULL
        return 0;
    if(node->left == NULL && node->right == NULL)
        return 0;
    else{
        int left = -1;
        int right = -1;
        if (node->left)
            left = visina(node->left);
        if (node->right)
            right = visina(node->right);
        if(left > right)
            return visina(node->left)+1;
        else
            return visina(node->right)+1;
    }
}
/* nacin sa vanjskom provjerom ako je root == NULL
int visina(Node *node){
    if(!node)
        return 0;
    else
    return visina(node->left)>visina(node->right)?1+visina(node->left): 1+visina(node->right);
}
*/

int main () {
    Node *root=NULL;
    int i, menu_choice;
    char c, tree_string[MAX_TREE_STRING];
    char print_format[6], empty_line[WIDTH], s[HEIGHT][WIDTH];

    setbuf(stdout, NULL);
    do {
        menu_choice = 0;
        DEBUG("\n1 Visina stabla (visina)");
        DEBUG("\n2 Kreiraj stablo \n3 Ispis \n4 Izlaz\n");
        scanf("%d", &menu_choice);
        switch (menu_choice) {
            case 1:
               // if (root==NULL) //dodao, ne znam drukcije razlikovati izmedu stabla s 1 ili 0 cvora
                 //   printf("0\n");
                printf("%d\n", visina(root));
                break;
            case 2:
                DEBUG("Unesite stablo kao niz alfanumerickih znakova odvojenih sa znakom ;\n");
                scanf(" %s", tree_string);
                root = create_tree(tree_string);
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
                while((c = getchar()) != '\n' && c != EOF);
        }
    } while(menu_choice!=4);
    return 0;
}
