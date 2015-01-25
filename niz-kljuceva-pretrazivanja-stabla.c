#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

int niz_pretrazivanja(int *list, int len) {
    int i;
    int max = INT_MAX;
    int min = INT_MIN;
    for(i = 1; i < len; i++){
        if (list[i] < list[i-1]){
            max = list[i-1];
        }else{
            min = list[i-1];
        }
        if (list[i]>max || list[i]< min)
            return 0;
    }
    return 1;
}

int main() {
    int menu_choice, i, num, len=0, *list=NULL;
    char c;

    setbuf(stdout, NULL);
    do {
        DEBUG("\n1.Niz pretrazivanja (niz_pretrazivanja)");
        DEBUG("\n2.Unos niza\n3.Izlaz\n");
        scanf("%d", &menu_choice);
        switch(menu_choice) {
            case 1:
                printf("%c\n", niz_pretrazivanja(list, len) ? 'Y' :'N');
                break;
            case 2:
                DEBUG("\nUnesite broj elemenata niza: ");
                scanf("%d", &len);
                DEBUG("\nUnesite elemente niza: ");
                if (list) free(list);
                list = malloc(len*sizeof(int));
                for (i=0; i<len; i++) {
                    scanf("%d", &num);
                    list[i] = num;
                }
                DEBUG("\nUneseni niz:\n");
                for (i=0; i<len; i++) {
                    DEBUG("%d ", list[i]);
                }
                DEBUG("\n");
                break;
            case 3:
                break;
            default:
                while((c=getchar())!='\n' && c!=EOF);
        }
    } while(menu_choice!=3);
    return 0;
}
