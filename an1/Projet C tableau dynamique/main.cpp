#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef struct 
 {
	int numeroprof;
	char nomprof[10];
	char prenomprof[10];
	int nombrematP;
	int numm[5];
}Prof;

typedef struct
{
	char nom[20];
	int coeff;				
	int numMa;
}Matiere;

typedef struct
{
	char nom[20];
	char prenom[20];
	char numE[10];
}Etudiant;

typedef struct 
{
	Etudiant *te;
	int numE;
	int nm;
	Matiere *tm;
}niveau;

typedef struct 
{
	Prof *tp;
	int np;
	niveau tn[6];
}etablissement;

void trier_etudiant(etablissement *e,int n)
{
	int i , j;
	Etudiant x;
	for(i=0;i<e->tn[n].numE;i++)
	{
		for(j=i+1;j<e->tn[n].numE;j++)
		{
			if(strcmp(e->tn[n].te[i].numE,e->tn[n].te[j].numE)>0)
			{
				x=e->tn[n].te[i];
				e->tn[n].te[i]=e->tn[n].te[j];
				e->tn[n].te[j]=x;
			}
		}
	}
}

void trierProf(etablissement *e)
{
	int i , j;
	Prof x;
	for(i=0;i<e->np;i++)
	{
		for(j=i+1;j<e->np;j++)
		{
			if(e->tp[i].numeroprof>e->tp[j].numeroprof)
			{
				x=e->tp[i];
				e->tp[i]=e->tp[j];
				e->tp[j]=x;
			}
		}
	}
}

void trierMat(etablissement *e, int n)
{
	int i , j;
	Matiere x;
	for(i=0;i<e->tn[n].nm;i++)
	{
		for(j=i+1;j<e->tn[n].nm;j++)
		{
			if(e->tn[n].tm[i].numMa > e->tn[n].tm[j].numMa)
			{
				x=e->tn[n].tm[i];
				e->tn[n].tm[i]=e->tn[n].tm[j];
				e->tn[n].tm[j]=x;
			}
		}
	}
}

int testunique(etablissement *e, char numE[10])
{
	int i,j;
	for(i=1;i<=5;i++)
	{
		for(j=0;j<e->tn[i].numE;j++)
		{
			if(strcmp(numE,e->tn[i].te[j].numE)==0)
			{
				return i;
			}
		}
	}
	return -1;
}

int testuniqueM(etablissement *e, int NM)
{
	int i,j;
	for(i=1;i<=5;i++)
	{
		for(j=0;j<e->tn[i].nm;j++)
		{
			if(NM==e->tn[i].tm[j].numMa)
			{
				return i;
			}
		}
	}
	return -1;
}

int rechercher_prof(etablissement *e, int npc)
{
	int i;
	for(i=0;i<e->np;i++)
	{
		if(e->tp[i].numeroprof==npc)
		{
			return i;
		}
	}
	return -1;
}

void ajouterProf(etablissement *e)
{
	int numeroprof,i;
	if(e->np==0)
	{
		e->tp=(Prof*)malloc(sizeof(Prof));
	}
	else
	{
		realloc(e->tp,sizeof(Prof)*(e->np+1));
	}
	do
	{
		printf("Veuillez saisir un numeroprof ");
		scanf("%d",&numeroprof);	
	}while(rechercher_prof(e,numeroprof)!=-1);
	
	e->tp[e->np].numeroprof=numeroprof;
	printf("Veuillez saisir un nom ");
	scanf("%s",e->tp[e->np].nomprof);
	printf("Veuillez saisir un pre ");
	scanf("%s",e->tp[e->np].prenomprof);
	printf("Veuillez saisir le nombre de matiere : ");
	scanf("%d",&e->tp[e->np].nombrematP);
	for(i=1;i<=e->tp[e->np].nombrematP;i++)
	{
		printf("Donnez le num de %d matiere : ",i);
		scanf("%d",&e->tp[e->np].numm[i]);
	}
	e->np++;
	trierProf(e);
}

void modifierProf(etablissement *e)
{	
	int i;
	int pos;
	int npc;
	printf("saisir le numero a midifier :");
	scanf("%d",&npc);
	pos=rechercher_prof(e,npc);
	if(pos==-1)
	{
		printf("Prof introuvable.");
		getch();
	}
	else
	{
		printf("Veuillez saisir un nom : ");
		scanf("%s",e->tp[pos].nomprof);
		printf("Veuillez saisir un prenom : ");
		scanf("%s",e->tp[pos].prenomprof);
		printf("Veuillez saisir un num : ");
		scanf("%d",&e->tp[pos].numeroprof);
		printf("Veuillez saisir le nombre de matiere : ");
		scanf("%d",&e->tp[pos].nombrematP);
		for(i=1;i<=e->tp[pos].nombrematP;i++)
		{
			printf("Donnez le num de %d matiere : ",i);
			scanf("%d",&e->tp[pos].numm[i]);
		}
	}
	trierProf(e);
}

void supprimer_prof(etablissement *e)
{
	int pos,i;
	int npc;
	printf("saisir le numero de prof a suprimer : ");
	scanf("%d",&npc);
	pos=rechercher_prof(e,npc);
	if(pos==-1)
	{
		printf("Prof introuvable.");
		getch();
	}
	else
	{
		for(i=pos;i<e->np;i++)
		{
			e->tp[i]=e->tp[i+1];
		}
		realloc(e->tp,sizeof(Prof)*(e->np-1));
		e->np--;
	}
}

void listerProf(etablissement *e)
{
	
	int i,j;
	for(i=0;i<e->np;i++)
	{
		printf(" %s | %s |  %d \n",e->tp[i].nomprof,e->tp[i].prenomprof,e->tp[i].numeroprof);
		printf(" MATIERES :");
		for(j=1;j<=e->tp[i].nombrematP;j++)
		{
			printf("%d |",e->tp[i].numm[j]);
		}
		printf("\n");
	}
	getch();
}

int rechercher_etudiant(etablissement *e, char nec[10], int n)
{
	int i;
	for(i=0;i<e->tn[n].numE;i++)
	{
		if(strcmp(e->tn[n].te[i].numE,nec)==0)
		{
			return i;
		}
	}
	return -1;
}

void ajouter_etudiant(etablissement *e, int n)
{
	char numE[10];
	if(e->tn[n].numE==0)
	{
		e->tn[n].te=(Etudiant*)malloc(sizeof(Etudiant));
	}
	else
	{
		realloc(e->tn[n].te,sizeof(Etudiant)*(e->tn[n].numE+1));
 	}
 	do{
 		printf("veuillez saisir le numero d'etudiant: ");
		scanf("%s",numE);
	 }while(testunique(e,numE)!=-1);
	strcpy(e->tn[n].te[e->tn[n].numE].numE,numE);
	printf("Veuillez saisir un nom ");
	scanf("%s",e->tn[n].te[e->tn[n].numE].nom);
	printf("Veuillez saisir un pre ");
	scanf("%s",e->tn[n].te[e->tn[n].numE].prenom);
	e->tn[n].numE++;
	trier_etudiant(e,n);
}

void modifier_etudiant(etablissement *e , int n)
{
	int pos;
	char nec[10],numE[10];
	printf("saisir le numero a modifier : ");
	scanf("%s",nec);
	pos=rechercher_etudiant(e,nec,n);
	if(pos==-1)
	{
		printf("Etudiant introuvable.");
		getch();
	}
	else
	{	
		do{
			printf("Veuillez saisir un num Etudiant : ");
			scanf("%s",numE);
		}while(testunique(e,numE)!=-1);
		strcpy(e->tn[n].te[pos].numE,numE);
		printf("Veuillez saisir un nom : ");
		scanf("%s",e->tn[n].te[pos].nom);
		printf("Veuillez saisir un prenom : ");
		scanf("%s",e->tn[n].te[pos].prenom);
		
	}
	trier_etudiant(e,n);
}

void supprimer_etudiant(etablissement *e , int n)
{
	int pos,i;
	char nec[10];
	printf("saisir le numero a supprimer : ");
	scanf("%s",nec);
	pos=rechercher_etudiant(e,nec,n);
	if(pos==-1)
	{
		printf("Etuidiant introuvable.");
		getch();
	}
	else
	{
		for(i=pos;i<e->tn[n].numE;i++)
		{
			e->tn[n].te[i]=e->tn[n].te[i+1];
		}
		realloc(e->tn[n].te,sizeof(Etudiant)*(e->tn[n].numE-1));
		e->tn[n].numE--;
	}
}

void lister_etudiant(etablissement *e, int n)
{
	int i;
	
	for(i=0;i<e->tn[n].numE;i++)
	{
		printf("%s		| %s		| %s	\n",e->tn[n].te[i].nom,e->tn[n].te[i].prenom,e->tn[n].te[i].numE);
	}
	getch();
}

int rechercher_matiere(etablissement *e ,int nmc , int n)
{
	int i;
	for(i=0;i<e->tn[n].nm;i++)
	{
		if(e->tn[n].tm[i].numMa==nmc)
		{
			return i;
		}
	}
	return -1;
}

void ajouter_matiere(etablissement *e, int n)
{
	int NM;
	if(e->tn[n].nm==0)
	{
		e->tn[n].tm=(Matiere*)malloc(sizeof(Matiere));
	}
	else
	{
		realloc(e->tn[n].tm,sizeof(Matiere)*(e->tn[n].nm+1));
	}
	do{
		printf("Veuillez saisir le numero de matiere : ");
		scanf("%d",&NM);
	}while(testuniqueM(e,NM)!=-1);
	e->tn[n].tm[e->tn[n].nm].numMa=NM;
	printf("Veuillez saisir la matiere : ");
	scanf("%s",e->tn[n].tm[e->tn[n].nm].nom);
	printf("Veuillez saisir le coef : ");
	scanf("%d",&e->tn[n].tm[e->tn[n].nm].coeff);
	e->tn[n].nm++;
	trierMat(e,n);
}

void modifier_matiere(etablissement *e , int n)
{
	int pos;
	int nmc,NM;
	printf("Le numero de matiere a modifier :");
	scanf("%d",&nmc);
	pos=rechercher_matiere(e,nmc,n);
	if(pos==-1)
	{
		printf("Matiere introuvable.");
		getch();
	}
	else
	{
		do{
			printf("Veuillez saisir le numero de matiere : ");
			scanf("%d",&NM);
		}while(testuniqueM(e,NM)!=-1);
		e->tn[n].tm[pos].numMa=NM;
		printf("Veuillez saisir la mateire : ");
		scanf("%s",e->tn[n].tm[pos].nom);
		printf("Veuillez saisir le coef : ");
		scanf("%d",&e->tn[n].tm[pos].coeff);	
	}
	trierMat(e,n);
}

void supprimer_matiere(etablissement *e , int n)
{
	int pos,i;
	int nmc;
	printf("Le numero de matiere chercher :");
	scanf("%d",&nmc);
	pos=rechercher_matiere(e,nmc,n);
	if(pos==-1)
	{
		printf("Matiere introuvable.");
		getch();
	}
	else
	{
		for(i=pos;i<e->tn[n].nm;i++)
		{
			e->tn[n].tm[i]=e->tn[n].tm[i+1];
		}
		realloc(e->tn[n].tm,sizeof(Matiere)*(e->tn[n].nm-1));
		e->tn[n].nm--;
	}
}

void lister_matiere(etablissement *e, int n)
{
	int i;

	for(i=0;i<e->tn[n].nm;i++)
	{
		printf("%s		| %d		| %d \n",e->tn[n].tm[i].nom,e->tn[n].tm[i].coeff,e->tn[n].tm[i].numMa);
	}
	getch();
}

void menuP()
{
	system("cls");
	printf("MENU PRINCIPAL \n 1-MENU DES PROFS \n 2-MENU DES NIVEAUX \n 3-SAVE \n 4-Quitter \n Votre choix : ");
}

void menuPr()
{
	system("cls");
	printf("MENU PROF \n 1-Ajouter Prof \n 2-Modifier Prof \n 3-Supprimer Prof \n 4-Lister Prof \n 5-Retour \n Votre choix : ");
}

void menuA()
{
	system("cls");
	printf("MENU NIVEAU \n 1-1annee \n 2-2annee \n 3-3annee \n 4-4annee \n 5-5annee \n 6-Retour \n Votre choix : ");
}

void menuNiv()
{
	system("cls");
	printf(" 1-Tableau d'etudiant \n 2-Tableau de matiere \n 3-Retour \n Votre choix : ");
}

void menuE()
{
	system("cls");
	printf("MENU ETUDIANT \n 1-Ajouter Etudiant \n 2-Modifier Etudiant \n 3-supprimer Etudiant \n 4-Lister Etudiant \n 5-Retour \n Votre choix : ");
}

void menuM()
{
	system("cls");
	printf("MENU MATIERE \n 1-Ajouter matiere \n 2-Modifier matiere \n 3-Supprimer matiere \n 4-Lister matiere \n 5-Retour \n Votre choix : ");
}

main()
{
	etablissement *e=NULL;
	Prof *tp=NULL;
	e=(etablissement*)malloc(sizeof(etablissement));
	e->np=0;
	int choixP,npc,pos;
	int choixNiv,i;
	for(i=1;i<6;i++)
	{
		e->tn[i].nm=0;
		e->tn[i].numE=0;
		e->tn[i].te=NULL;
		e->tn[i].tm=NULL;
	}
	do{
		menuP();
		scanf("%d",&choixP);
		switch(choixP)
		{
			case 1: 
				int choixPr;
				do
				{
					menuPr();
					scanf("%d",&choixPr);
					switch(choixPr)
					{
						case 1 : ajouterProf(e);
							break;
						case 2 : modifierProf(e);
							break;
						case 3 : supprimer_prof(e);
							break;
						case 4 : listerProf(e); 
							break;
					}	
				}
				while(choixPr!=5);
			break;	
				
			case 2:
				int choixA;
				do{
					menuA();
					scanf("%d",&choixA);
					switch(choixA)
					{
						case 1:	
							do{
								menuNiv();
								scanf("%d",&choixNiv);
								switch(choixNiv)
								{
									case 1:
										int choixE1;
										do
										{
											menuE();
											scanf("%d",&choixE1);
											switch(choixE1)
											{
												case 1 : ajouter_etudiant(e,1);
													break;
												case 2 : modifier_etudiant(e,1);
													break;
												case 3 : supprimer_etudiant(e,1);
													break;
												case 4 : lister_etudiant(e,1);
													break;
											}
												
										}while(choixE1!=5);
										break;
									case 2: 
										int choixM1;
										do
										{
											menuM();
											scanf("%d",&choixM1);
											switch(choixM1)
											{
												case 1 : ajouter_matiere(e,1);
													break;
												case 2 : modifier_matiere(e,1);
													break;
												case 3 : supprimer_matiere(e,1);
													break;
												case 4 : lister_matiere(e,1);
													break;
											}
												
										}while(choixM1!=5);
										break;
								}

							}while(choixNiv!=3);
						break;
						
						case 2:	
							do{
								menuNiv();
								scanf("%d",&choixNiv);
								switch(choixNiv)
								{
									case 1:
										int choixE2;
										do
										{
											menuE();
											scanf("%d",&choixE2);
											switch(choixE2)
											{
												case 1 : ajouter_etudiant(e,2);
													break;
												case 2 : modifier_etudiant(e,2);
													break;
												case 3 : supprimer_etudiant(e,2);
													break;
												case 4 : lister_etudiant(e,2);
													break;
											}
												
										}while(choixE2!=5);
										break;
									case 2: 
										int choixM2;
											do
											{
												menuM();
												scanf("%d",&choixM2);
												switch(choixM2)
												{
													case 1 : ajouter_matiere(e,2);
														break;
													case 2 : modifier_matiere(e,2);
														break;
													case 3 : supprimer_matiere(e,2);
														break;
													case 4 : lister_matiere(e,2);
														break;
												}
													
											}while(choixM2!=5);
										break;
								}

							}while(choixNiv!=3);
							break;
							
						case 3:
							do{
								menuNiv();
								scanf("%d",&choixNiv);
								switch(choixNiv)
								{
									case 1:
										int choixE3;
										do
										{
											menuE();
											scanf("%d",&choixE3);
											switch(choixE3)
											{
												case 1 : ajouter_etudiant(e,3);
													break;
												case 2 : modifier_etudiant(e,3);
													break;
												case 3 : supprimer_etudiant(e,3);
													break;
												case 4 : lister_etudiant(e,3);
													break;
											}
												
										}while(choixE3!=5);
										break;
									case 2: 
										int choixM3;
										do
										{
											menuM();
											scanf("%d",&choixM3);
											switch(choixM3)
											{
												case 1 : ajouter_matiere(e,3);
													break;
												case 2 : modifier_matiere(e,3);
													break;
												case 3 : supprimer_matiere(e,3);
													break;
												case 4 : lister_matiere(e,3);
													break;
											}
												
										}while(choixM3!=5);
										break;
								}

							}while(choixNiv!=3);
							break;
							
						case 4:
							do{
								menuNiv();
								scanf("%d",&choixNiv);
								switch(choixNiv)
								{
									case 1:
										int choixE4;
										do
										{
											menuE();
											scanf("%d",&choixE4);
											switch(choixE4)
											{
												case 1 : ajouter_etudiant(e,4);
													break;
												case 2 : modifier_etudiant(e,4);
													break;
												case 3 : supprimer_etudiant(e,4);
													break;
												case 4 : lister_etudiant(e,4);
													break;
											}
												
										}while(choixE4!=5);
										break;
									case 2: 
										int choixM4;
										do
										{
											menuM();
											scanf("%d",&choixM4);
											switch(choixM4)
											{
												case 1 : ajouter_matiere(e,4);
													break;
												case 2 : modifier_matiere(e,4);
													break;
												case 3 : supprimer_matiere(e,4);
													break;
												case 4 : lister_matiere(e,4);
													break;
											}
												
										}while(choixM4!=5);
										break;
								}

							}while(choixNiv!=3);
							break;
							
						case 5:
							do{
								menuNiv();
								scanf("%d",&choixNiv);
								switch(choixNiv)
								{
									case 1:
										int choixE5;
										do
										{
											menuE();
											scanf("%d",&choixE5);
											switch(choixE5)
											{
												case 1 : ajouter_etudiant(e,5);
													break;
												case 2 : modifier_etudiant(e,5);
													break;
												case 3 : supprimer_etudiant(e,5);
													break;
												case 4 : lister_etudiant(e,5);
													break;
											}
												
										}while(choixE5!=5);
										break;
									case 2: 
										int choixM5;
										do
										{
											menuM();
											scanf("%d",&choixM5);
											switch(choixM5)
											{
												case 1 : ajouter_matiere(e,5);
													break;
												case 2 : modifier_matiere(e,5);
													break;
												case 3 : supprimer_matiere(e,5);
													break;
												case 4 : lister_matiere(e,5);
													break;
											}
												
										}while(choixM5!=5);
										break;
								}

							}while(choixNiv!=3);
							break;
					}
					
				}while(choixA!=6);
			break;
		}
	}while(choixP!=4);
	free(e);
}

