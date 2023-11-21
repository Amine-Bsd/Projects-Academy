#include <stdio.h>
#include <stdlib.h>

typedef struct Tcel
{
    int info;
    int nbl, nbc;
    struct Tcel* suivc;
    struct Tcel* suivl;
} Tcel;

typedef Tcel* pcel;

typedef struct Tmat
{
    pcel th[50], thq[50], tv[50], tvq[50];
} Tmat;

typedef Tmat* pmat;

void initmat(pmat m, int nbl, int nbc)
{
    int i;
    for (i = 0; i < nbl; i++)
    {
        m->tv[i] = NULL;
        m->tvq[i] = NULL;
    }
    for (i = 0; i < nbc; i++)
    {
        m->th[i] = NULL;
        m->thq[i] = NULL;
    }
}


void creerM(char chemin[20], pmat* m,int &nbl,int &nbc)
{
    int i, j, val;
    pcel p;
    FILE* f = fopen(chemin, "r");
    if (f)
    {
        fscanf(f, "%d", &nbl);
        fscanf(f, "%d", &nbc);
        *m = (pmat)malloc(sizeof(Tmat));
        initmat(*m, nbl, nbc);
        for (i = 0; i < nbl; i++)
        {
            for (j = 0; j < nbc; j++)
            {
                fscanf(f, "%d", &val);
                if (val != 0)
                {
                    p = (pcel)malloc(sizeof(Tcel));
                    p->info = val;
                    p->nbl = i;
                    p->nbc = j;
                    p->suivl = NULL;
                    p->suivc = NULL;
                    if ((*m)->tv[i] == NULL)
                    {
                        (*m)->tv[i] = p;
                        (*m)->tvq[i] = p;
                    }
                    else
                    {
                        (*m)->tvq[i]->suivl = p;
                        (*m)->tvq[i] = p;
                    }
                    if ((*m)->th[j] == NULL)
                    {
                        (*m)->th[j] = p;
                        (*m)->thq[j] = p;
                    }
                    else
                    {
                        (*m)->thq[j]->suivc = p;
                        (*m)->thq[j] = p;
                    }
                }
            }
        }
        fclose(f);
    }
    else
    {
        printf("erreur: impossible d'ouvrir le fichier %s", chemin);
        exit(1);
    }
}



void afficher(pmat m, int nbl, int nbc)
{
    pcel p;
    int i, j;
    for (i = 0; i < nbl; i++)
    {
        p = m->tv[i];
        for (j = 0; j < nbc; j++)
        {
            if (p == NULL)
            {
                printf("0 |");
            }
            else if (p->nbc == j)
            {
                printf("%d |", p->info);
                p = p->suivl;
            }
            else
            {
                printf("0 |");
            }
        }
        printf("\n");
    }
}

void ajoutfin(pmat& m, int i, int j, int val)
{
    pcel p;

    p = (pcel)malloc(sizeof(Tcel));
                    p->info = val;
                    p->nbl = i;
                    p->nbc = j;
                    p->suivl = NULL;
                    p->suivc = NULL;
                    if (m->tv[i] == NULL)
                    {
                        m->tv[i] = p;
                        m->tvq[i] = p;
                    }
                    else
                    {
                        m->tvq[i]->suivl = p;
                        m->tvq[i] = p;
                    }
                    if (m->th[j] == NULL)
                    {
                        m->th[j] = p;
                        m->thq[j] = p;
                    }
                    else
                    {
                        m->thq[j]->suivc = p;
                        m->thq[j] = p;
                    }
}

void somme(pmat m1, pmat m2, pmat* m3, int nbl, int nbc)
{
    int i, s;
    pcel p1, p2;

    *m3 = (pmat)malloc(sizeof(Tmat));
    initmat(*m3, nbl, nbc);

    for (i = 0; i < nbl; i++) {
        p1 = m1->tv[i];
        p2 = m2->tv[i];

        while (p1 != NULL || p2 != NULL) {
            if (p1 != NULL && p2 != NULL)
				{
                if (p1->nbc == p2->nbc) {
                    s = p1->info + p2->info;

                    if (s != 0) {
                        ajoutfin(*m3, i, p1->nbc, s);
                    }
                    p1 = p1->suivl;
                    p2 = p2->suivl;

                }
                else if (p1->nbc < p2->nbc) {
                    ajoutfin(*m3, i, p1->nbc, p1->info);
                    p1 = p1->suivl;
                }
                else {
                    ajoutfin(*m3, i, p2->nbc, p2->info);
                    p2 = p2->suivl;
                }
            }
            else if (p1 != NULL) {
                ajoutfin(*m3, i, p1->nbc, p1->info);
                p1 = p1->suivl;
            }
            else {
                ajoutfin(*m3, i, p2->nbc, p2->info);
                p2 = p2->suivl;
            }
        }
    }
}

void Produit(pmat m1, pmat m2, pmat* m3, int n)
{
    int i, j, k, s;
    pcel p1, p2;

    *m3 = (pmat)malloc(sizeof(Tmat));
    initmat(*m3, n, n);

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            s = 0;
            p1 = m1->tv[i];
            p2 = m2->th[j];

            while (p1 != NULL && p2 != NULL) {
                if (p1->nbc < p2->nbl) {
                    p1 = p1->suivl;
                }
                else if (p1->nbc > p2->nbl) {
                    p2 = p2->suivc;
                }
                else {
                    s += p1->info * p2->info;
                    p1 = p1->suivl;
                    p2 = p2->suivc;
                }
            }

            if (s != 0) {
                ajoutfin(*m3, i, j, s);
            }
        }
    }
}

void copier(pmat m1, pmat* m2, int nbl, int nbc) {
    pcel p1, p2;
    int i, j;
	*m2 = (pmat)malloc(sizeof(Tmat));
	initmat(*m2, nbl, nbc);

    for (i = 0; i < nbl; i++) {
        p1 = m1->tv[i];
        p2 = (*m2)->tv[i];

        for (j = 0; j < nbc; j++) {
            if (p1 != NULL && p1->nbc == j) {
                ajoutfin(*m2, i, j, p1->info);
                p1 = p1->suivl;
            } else {
                ajoutfin(*m2, i, j, 0);
            }
        }
    }
}


void puissance(pmat m, int p, pmat* res, int nbl, int nbc)
{
    pmat tmp, base;
    copier(m, res, nbl, nbc);
    int i;
    for (i = 1; i < p; i++)
    {
        copier(*res, &base, nbl, nbc);
        Produit(base, m, &tmp, nbl);
        copier(tmp, res, nbl, nbc);
        free(base);
        free(tmp);
    }
}


void freemat(pmat m, int nbl)
{
    pcel p, q;
    int i, j;

    // Parcours de chaque élément de la matrice
    for (i = 0; i < nbl; i++) {
        p = m->tv[i];
        while (p != NULL) {
            q = p->suivl;
            free(p);
            p = q;
        }
    }

    // Libération des tableaux de pointeurs
    for (i = 0; i < nbl; i++) {
        m->tv[i] = NULL;
        m->tvq[i] = NULL;
    }
    for (j = 0; j < nbl; j++) {
        m->th[j] = NULL;
        m->thq[j] = NULL;
    }
}


int main()
{
	int nbl,nbc;
    pmat m1,m2,m3,m4;
    creerM("m1.txt", &m1,nbl,nbc);
    creerM("m2.txt", &m2,nbl,nbc);
    
    printf("/////////m1.txt////////\n");
    afficher(m1,nbl,nbc);

    
    printf("//////////m2.txt////////\n");
    afficher(m2,nbl,nbc);
	
	printf("/////////SOMME m1 et m2////////\n");
	somme(m1,m2,&m3,nbc,nbl);
	afficher(m3,nbl,nbc);
	
	printf("/////////PRODUIT m1//////////\n");
	Produit(m1,m1,&m3,nbl);
	afficher(m3,nbl,nbc);
	
	printf("/////////COPIER m3 sur m4/////////\n");
	copier(m3,&m4,nbl,nbl);
	afficher(m4,nbl,nbc);
	
	printf("///////PUISSANCE de m1-3////////\n");
	puissance(m1,3,&m4,nbl,nbc);
	afficher(m4,nbl,nbc);
	
	freemat(m1,nbl);
	freemat(m2,nbl);
	freemat(m3,nbl);
	freemat(m4,nbl);
	
	return 0;
}
