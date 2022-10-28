#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include <string.h>

struct predmet {
    char sifra [20];
    int ocena;
    struct predmet* next;
    struct predmet* prev;
};

struct zaglavlje {
    struct predmet *prvi;
    struct predmet *poslednji;
    int broj;
};

struct student {
    char indeks [9];
    struct zaglavlje *predmeti;
    struct student *next;
    struct student *prev;
};

struct student *head;

struct student* searchSt() {
    char t [9];
    printf("unesite studenta gg/bbbb:\n");
    scanf("%s", &t);
    struct student* pok=head;
    while (pok) {
        if (strcmp(pok->indeks, t)==0) {
            return pok;
        }
        else {
            pok=pok->next;
        }
    }
    printf("nije pronadjen student\n");
    return NULL;
};

void ukljanjanjePr(struct student *pok1, struct predmet *pok2) {
    if (pok2 == pok1->predmeti->prvi)
        pok1->predmeti->prvi=pok2->next;
    if (pok2->next != NULL)
        (pok2->next)->prev=pok2->prev;
    if (pok2->prev != NULL)
        (pok2->prev)->next=pok2->next;
    free(pok2);
}

void stvaranjeSt() {
    struct student* noviStudent=(struct student*)malloc(sizeof(struct student));
    printf("unesite studenta gg/bbbb:\n");
    scanf("%s", &noviStudent->indeks);
    noviStudent->predmeti=(struct zaglavlje*)malloc(sizeof(struct zaglavlje));
    noviStudent->predmeti->prvi=NULL;
    noviStudent->predmeti->poslednji=NULL;
    noviStudent->predmeti->broj=0;
    noviStudent->prev=NULL;
    noviStudent->next=head;
    if (head != NULL) {
        head->prev=noviStudent;
    }
    head=noviStudent;
}

void dodavanjePr() {
    struct student* pok1=searchSt();
    if (!pok1) return;
    struct predmet* pok2=pok1->predmeti->prvi;
    struct predmet* pok3=NULL;
    struct predmet* noviPredmet=(struct predmet*)malloc(sizeof(struct predmet));
    printf("unesite sifru predmeta i ocenu:\n");
    scanf("%s %d", &noviPredmet->sifra, &noviPredmet->ocena);
    if (noviPredmet->ocena==5) {
        printf("predmet nije polozen\n");
        return;
    }
    else if (noviPredmet->ocena>10 || noviPredmet->ocena<5) {
        printf("los unos\n");
        return;
    }
    else {
        if (pok2) {
            while (pok2 && strcmp(noviPredmet->sifra, pok2->sifra) > 0) {
                pok3 = pok2;
                pok2 = pok2->next;
            }
        }
        if (pok3) {
            noviPredmet->next = pok3->next;
            pok3->next = noviPredmet;
            noviPredmet->prev = pok3;
            if (noviPredmet->next)
                noviPredmet->next->prev = noviPredmet;
        } else {
            noviPredmet->next = pok1->predmeti->prvi;
            noviPredmet->prev = NULL;
            if (pok1->predmeti->prvi)
                pok1->predmeti->prvi->prev = noviPredmet;
            pok1->predmeti->prvi = noviPredmet;
        }
        if (!noviPredmet->next)
            pok1->predmeti->poslednji = noviPredmet;
        pok1->predmeti->broj++;
    }
}

void prikazivanje() {
    int t;
    struct student* pok1=searchSt();
    printf("unesite ocenu:\n");
    scanf("%d", &t);
    if (!pok1) return;
    struct predmet* pok2=pok1->predmeti->prvi;
    while (pok2) {
        if (pok2->ocena==t) {
            printf("%s\n", pok2->sifra);
        }
        pok2=pok2->next;
    }
}

void ponistavanje() {
    char t [20];
    struct student* pok1=searchSt();
    printf("unesite sifru predmeta:\n");
    scanf("%s", &t);
    if (!pok1) return;
    struct predmet* pok2=pok1->predmeti->prvi;
    while (pok2) {
        if (strcmp(pok2->sifra, t)==0) {
            printf("%s: %d\n", pok2->sifra, pok2->ocena);
            ukljanjanjePr(pok1, pok2);
            return;
        }
        pok2=pok2->next;
    }
}

void brisanje() {
    struct student* pok1=searchSt();
    if (!pok1) return;
    struct predmet* pok2=pok1->predmeti->prvi;
    while (pok2) {
        ukljanjanjePr(pok1, pok2);
        pok2=pok2->next;
    }
}

void brojPr() {
    struct student *pok1= searchSt();
    if (!pok1) return;
    printf("%d\n", pok1->predmeti->broj);
}

void ispis() {
    struct student *pok1= searchSt();
    if (!pok1) return;
    struct predmet *pok2= pok1->predmeti->prvi;
    while(pok2) {
        printf("%s\n", pok2->sifra);
        pok2=pok2->next;
    }
}

void razlika () {
    struct predmet *pok1= searchSt()->predmeti->prvi;
    struct predmet *pok2= searchSt()->predmeti->prvi;
    while (pok1) {
        while (pok2 && strcmp(pok1->sifra, pok2->sifra)>0) {
            pok2=pok2->next;
        }
        if (!pok2)
            printf("%s\n", pok1->sifra);
        else if (strcmp(pok1->sifra, pok2->sifra)!=0)
            printf("%s\n", pok1->sifra);
        pok1=pok1->next;
    }
};

void sve() {
    struct student *pok = head;
    while (pok != NULL){
        printf("%s\n", pok->indeks);
        struct predmet* pok1 = pok->predmeti->prvi;
        while (pok1 != NULL) {
            printf( "---%s: %d\n", pok1->sifra, pok1->ocena);
            pok1=pok1->next;
        }
        pok=pok->next;
    }
}

int main() {
    int n;
    head=NULL;
    printf("1 stvaranje novog studenta\n2 dodavanje polozenog predmeta za odredjenog studenta\n"
           "3 prikaz svih predmeta sa odredjenom ocenom\n4 ponistavanje polozenog predmeta\n5 brisanje cele liste"
           "polozenih predmeta\n6 dohvatanje broja polozenih predmeta za studenta\n7 ispisivanje svih polozenih"
           "predmeta odrednjenog studenta\n8 razlika predmeta koji su polozili dva zadata studenta\n9 "
           "izlazak iz programa\n");
    while (true) {
        printf("izaberite stavku menija: ");
        scanf("%d",&n);
        if (n==1) {
            stvaranjeSt();
        }
        else {
            if (head) {
                switch (n) {
                    case 2:
                        dodavanjePr();
                        break;
                    case 3:
                        prikazivanje();
                        break;
                    case 4:
                        ponistavanje();
                        break;
                    case 5:
                        brisanje();
                        break;
                    case 6:
                        brojPr();
                        break;
                    case 7:
                        ispis();
                        break;
                    case 8:
                        razlika();
                        break;
                    case 9:
                        sve();
                        return 0;
                }
            }
            else printf("prvo morate uneti studenta\n");
        }
    }
}

