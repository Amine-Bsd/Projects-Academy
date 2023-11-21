#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>

typedef struct {
  char nomEtudiant[10];
  char prenomEtudiant[10];
  int numeroEtudiant;
}Etudiant;

typedef struct {
  char nomClasse[10];
  int numeroClasse;
  Etudiant * listeEtudiants;
  int nombreEtudiants;
}Classe;

typedef struct {
  char nomModule[10];
  int coefficient;
  int numeroModule;
}Module;

typedef struct {
  Classe * listeClasses;
  int nombreClasses;
  Module * listeModules;
  int nombreModules;
}Annee;

typedef struct {
  char nomFiliere[10];
  int numeroFiliere;
  Annee listeAnnees[5];
}Filiere;

typedef struct {
  Module *module;
  Etudiant *etudiant;
  float note;
}Note;

typedef struct {
  char nomEtablissement[10];
  Filiere * listeFilieres;
  int nombreFilieres;
  Note * listeNotes;
  int nombreNotes;
}Etablissement;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////Début Filiere///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TestFiliere(Etablissement * e, int nomerFiliere) {
  int i;
  for (i = 0; i < e -> nombreFilieres; i++) {
    if (nomerFiliere == e -> listeFilieres[i].numeroFiliere) {
      return i;
    }
  }
  return -1;
}

void AjouterFiliere(Etablissement * e) {
  int num;
  if (e -> nombreFilieres == 0) {
    e -> listeFilieres = (Filiere *) malloc(sizeof(Filiere));
  } else {
    e->listeFilieres = (Filiere*) realloc(e -> listeFilieres, sizeof(Filiere) * (e -> nombreFilieres + 1));
  }

  for (int i = 0; i < 5; i++) {
    e -> listeFilieres[e -> nombreFilieres].listeAnnees[i].nombreClasses = 0;
    e -> listeFilieres[e -> nombreFilieres].listeAnnees[i].listeClasses = NULL;

    e -> listeFilieres[e -> nombreFilieres].listeAnnees[i].nombreModules = 0;
    e -> listeFilieres[e -> nombreFilieres].listeAnnees[i].listeModules = NULL;
  }

  printf("\n \tdonner le nom de Filiere :");
  scanf("%s", e -> listeFilieres[e -> nombreFilieres].nomFiliere);

  do {
    printf("\n \tdonner le numero de Filiere :");
    scanf("%d", & num);
  } while (TestFiliere(e, num) != -1);

  e -> listeFilieres[e -> nombreFilieres].numeroFiliere = num;
  e -> nombreFilieres++;
}

void ModifierFiliere(Etablissement * e) {
  int pos, num;
  printf("\n \tnumero pour chercher :");
  scanf("%d", & num);
  pos = TestFiliere(e, num);
  if (pos == -1) {
    printf("\n \tFiliere introuvable.");
  } else {
    printf("\n \tdonner le nouveau nom de Filiere :");
    scanf("%s", e -> listeFilieres[pos].nomFiliere);

    do {
      printf("\n \tdonner le nouveau numero de Filiere :");
      scanf("%d", & num);
    } while (TestFiliere(e, num) != -1);
    e -> listeFilieres[pos].numeroFiliere = num;
  }
}

void SupprimerFiliere(Etablissement * e) {
  int i, pos, num;
  printf("\n \tnumero pour chercher :");
  scanf("%d", & num);
  pos = TestFiliere(e, num);
  if (pos == -1) {
    printf("\n \tFiliere introuvable.");
    getch();
  } else {
    for (i = pos; i < e -> nombreFilieres; i++) {
      e -> listeFilieres[i] = e -> listeFilieres[i + 1];
    }
    e -> nombreFilieres--;
    e -> listeFilieres = (Filiere * ) realloc(e -> listeFilieres, sizeof(Filiere) * (e -> nombreFilieres));
  }
}

void RechercherFiliere(Etablissement * e) {

  int pos, num;
  printf("\n \tnumero pour chercher :");
  scanf("%d", & num);
  pos = TestFiliere(e, num);
  if (pos == -1) {
    printf("Filiere introuvable.");
    getch();
  } else {
    printf("\n \tNom Filiere : %s || Numero Filiere : %d \n", e -> listeFilieres[pos].nomFiliere, e -> listeFilieres[pos].numeroFiliere);
    getch();
  }
}

void listerFiliere(Etablissement * e) {
  int i;
  for (i = 0; i < e -> nombreFilieres; i++) {
    printf("\n \t(%d) => Nom Filiere : %s || Numero Filiere : %d \n", i, e -> listeFilieres[i].nomFiliere, e -> listeFilieres[i].numeroFiliere);
    
  }
  getch();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////Fin Filiere///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////Début CLasse///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TestClasse(Etablissement * e, int numclasse, int f, int a) {
  int i;
  for (i = 0; i < e -> listeFilieres[f].listeAnnees[a].nombreClasses; i++) {
    if (numclasse == (e -> listeFilieres[f].listeAnnees[a].listeClasses[i].numeroClasse)) {
      return i;
    }
  }
  return -1;
}

void AjouterClasse(Etablissement * e, int f, int a) {
  int numclasse;

  if (e -> listeFilieres[f].listeAnnees[a].nombreClasses == 0) {
    e -> listeFilieres[f].listeAnnees[a].listeClasses = (Classe * ) malloc(sizeof(Classe));
  } else {
    e -> listeFilieres[f].listeAnnees[a].listeClasses = (Classe * ) realloc(e -> listeFilieres[f].listeAnnees[a].listeClasses, sizeof(Classe) * (e -> listeFilieres[f].listeAnnees[a].nombreClasses + 1));
  }
	e -> listeFilieres[f].listeAnnees[a].listeClasses[e -> listeFilieres[f].listeAnnees[a].nombreClasses].listeEtudiants=NULL;
	e -> listeFilieres[f].listeAnnees[a].listeClasses[e -> listeFilieres[f].listeAnnees[a].nombreClasses].nombreEtudiants=0;
	
  printf("\n \tdonner le nom de Classe :");
  scanf("%s", e -> listeFilieres[f].listeAnnees[a].listeClasses[e -> listeFilieres[f].listeAnnees[a].nombreClasses].nomClasse);

  do {
    printf("\n \tdonner le numero de Classe :");
    scanf("%d", & numclasse);
  } while (TestClasse(e, numclasse, f, a) != -1);
  e -> listeFilieres[f].listeAnnees[a].listeClasses[e -> listeFilieres[f].listeAnnees[a].nombreClasses].numeroClasse = numclasse;

  e -> listeFilieres[f].listeAnnees[a].nombreClasses++;

}

void ModifierClasse(Etablissement * e, int f, int a) {
  int numclasse, pos;

  printf("\n \tdonner le numero de Classe :");
  scanf("%d", & numclasse);
  pos = TestClasse(e, numclasse, f, a);
  if (pos == -1) {
    printf("\n \tClasse introuvable.");
    getch();

  } else {

    printf("\n \tdonner le nouveau nom de Classe :");
    scanf("%s", e -> listeFilieres[f].listeAnnees[a].listeClasses[pos].nomClasse);

    do {
      printf("\n \tdonner le nouveau numero de Classe :");
      scanf("%d", & numclasse);
    } while (TestClasse(e, numclasse, f, a) != -1);
    e -> listeFilieres[f].listeAnnees[a].listeClasses[pos].numeroClasse = numclasse;
  }

}

void SupprimerClasse(Etablissement * e, int f, int a) {
  int numclasse, pos, i;

  printf("\n \tdonner le numero de Classe :");
  scanf("\n \t%d", & numclasse);
  pos = TestClasse(e, numclasse, f, a);
  printf("\n \tposition : %d\n", pos);
  if (pos == -1) {
    printf("\n \tClasse introuvable.");
    getch();
  } else {
    for (i = pos; i < e -> listeFilieres[f].listeAnnees[a].nombreClasses; i++) {
      e -> listeFilieres[f].listeAnnees[a].listeClasses[i] = e -> listeFilieres[f].listeAnnees[a].listeClasses[i + 1];
    }
    e -> listeFilieres[f].listeAnnees[a].nombreClasses--;
    e -> listeFilieres[f].listeAnnees[a].listeClasses = (Classe * ) realloc(e -> listeFilieres[f].listeAnnees[a].listeClasses, sizeof(Classe) * (e -> listeFilieres[f].listeAnnees[a].nombreClasses));
  }

}

void RechercherClasse(Etablissement * e, int f, int a) {
  int numclasse, pos, i;

  printf("\n \tdonner le numero de Classe :");
  scanf("%d", & numclasse);
  pos = TestClasse(e, numclasse, f, a);
  if (pos == -1) {
    printf("\n \tClasse introuvable.");
    getch();
  } else {
    printf("\n \t%d => nomclasse : %s || numclasse : %d ", pos, e -> listeFilieres[f].listeAnnees[a].listeClasses[pos].nomClasse, e -> listeFilieres[f].listeAnnees[a].listeClasses[pos].numeroClasse);
    
  }
  getch();
}

void listerClasse(Etablissement * e, int f, int a) {
  int i;

  for (i = 0; i < e -> listeFilieres[f].listeAnnees[a].nombreClasses; i++) {
    printf("\n \t%d => nomclasse : %s || numclasse : %d \n", i, e -> listeFilieres[f].listeAnnees[a].listeClasses[i].nomClasse, e -> listeFilieres[f].listeAnnees[a].listeClasses[i].numeroClasse);
  }
  getch();

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////Fin Classe///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////Début Module///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TestModule(Etablissement * e, int numModule, int f, int a) {
  int i;
  for (i = 0; i < e -> listeFilieres[f].listeAnnees[a].nombreModules; i++) {
    if (numModule == (e -> listeFilieres[f].listeAnnees[a].listeModules[i].numeroModule)) {
      return i;
    }
  }
  return -1;
}

void AjouterModule(Etablissement * e, int f, int a) {
  int numModule;
  if (e -> listeFilieres[f].listeAnnees[a].nombreModules == 0) {
    e -> listeFilieres[f].listeAnnees[a].listeModules = (Module*) malloc(sizeof(Module));
  } else {
    e -> listeFilieres[f].listeAnnees[a].listeModules = (Module*) realloc(e -> listeFilieres[f].listeAnnees[a].listeModules, sizeof(Module) * (e -> listeFilieres[f].listeAnnees[a].nombreModules + 1));
  }
  printf("\n \tdonner le nom de Module :");
  scanf("%s", e -> listeFilieres[f].listeAnnees[a].listeModules[e -> listeFilieres[f].listeAnnees[a].nombreModules].nomModule);
  
  printf("\n \tdonner le coefficient de Module :");
  scanf("%d", & e-> listeFilieres[f].listeAnnees[a].listeModules[e -> listeFilieres[f].listeAnnees[a].nombreModules].coefficient);
  do {
    printf("\n \tdonner le numero de Module :");
    scanf("%d", & numModule);
  } while (TestModule(e, numModule, f, a) != -1);
  e -> listeFilieres[f].listeAnnees[a].listeModules[e -> listeFilieres[f].listeAnnees[a].nombreModules].numeroModule = numModule;
  e -> listeFilieres[f].listeAnnees[a].nombreModules++;
}

void ModifierModule(Etablissement * e, int f, int a) {
  int numModule, pos;

  printf("\n \tdonner le numero de Module :");
  scanf("%d", & numModule);
  pos = TestModule(e, numModule, f, a);
  if (pos == -1) {
    printf("\n \tModule introuvable.");
    getch();

  } else {

    printf("\n \tdonner le nouveau nom de Module :");
    scanf("%s", e -> listeFilieres[f].listeAnnees[a].listeModules[pos].nomModule);
    
    printf("\n \tdonner le nouveau coefficient :");
    scanf("%d", &(e -> listeFilieres[f].listeAnnees[a].listeModules[pos].coefficient));
    

    do {
      printf("\n \tdonner le nouveau numero de Module :");
      scanf("%d", & numModule);
    } while (TestClasse(e, numModule, f, a) != -1);
    e -> listeFilieres[f].listeAnnees[a].listeModules[pos].numeroModule = numModule;
  }

}

void SupprimerModule(Etablissement * e, int f, int a) {
  int numModule, pos, i;

  printf("\n \tdonner le numero de Module :");
  scanf("%d", & numModule);
  pos = TestModule(e, numModule, f, a);
  printf("\n \tposition : %d\n", pos);
  if (pos == -1) {
    printf("\n \tModule introuvable.");
    getch();
  } else {
    for (i = pos; i < e -> listeFilieres[f].listeAnnees[a].nombreModules; i++) {
      e -> listeFilieres[f].listeAnnees[a].listeModules[i] = e -> listeFilieres[f].listeAnnees[a].listeModules[i + 1];
    }
    
    e -> listeFilieres[f].listeAnnees[a].nombreModules--;
    e -> listeFilieres[f].listeAnnees[a].listeModules = (Module*) realloc(e -> listeFilieres[f].listeAnnees[a].listeModules, sizeof(Module) * (e -> listeFilieres[f].listeAnnees[a].nombreModules));
  }

}

void RechercherModule(Etablissement * e, int f, int a) {
  int numModule, pos, i;

  printf("\n \t donner le numero de Module :");
  scanf("%d", & numModule);
  pos = TestModule(e, numModule, f, a);
  if (pos == -1) {
    printf("\n \tModule introuvable.");
    getch();
  } else {
    printf("\n \t%d => nomModule : %s || numeroModule : %d || coefficient : %d \n", pos, e -> listeFilieres[f].listeAnnees[a].listeModules[pos].nomModule, e -> listeFilieres[f].listeAnnees[a].listeModules[pos].numeroModule,e -> listeFilieres[f].listeAnnees[a].listeModules[pos].coefficient);
    getch();
  }

}

void listerModule(Etablissement * e, int f, int a) {
    int i;

    for (i = 0; i < e -> listeFilieres[f].listeAnnees[a].nombreModules; i++) {
    printf("\n \t%d => nomModule : %s || numeroModule : %d || coefficient : %d \n", i, e -> listeFilieres[f].listeAnnees[a].listeModules[i].nomModule, e -> listeFilieres[f].listeAnnees[a].listeModules[i].numeroModule,e -> listeFilieres[f].listeAnnees[a].listeModules[i].coefficient);
    }
    getch();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////Fin Module///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////Début Etudiant///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TestEtudiant(Etablissement * e, int numEtudiant, int f, int a) {
  int i,j;
  for (i = 0; i < e -> listeFilieres[f].listeAnnees[a].nombreClasses ; i++){
  	for(j=0; j< e -> listeFilieres[f].listeAnnees[a].listeClasses[i].nombreEtudiants ;j++){
    if (numEtudiant == (e -> listeFilieres[f].listeAnnees[a].listeClasses[i].listeEtudiants[j].numeroEtudiant)) {
      return j;
    }
	}
	}
  return -1;
}

void AjouterEtudiant(Etablissement * e, int f, int a, int c) {
  int numeroEtudiant;
  if (e -> listeFilieres[f].listeAnnees[a].listeClasses[c].nombreEtudiants== 0) {
    e -> listeFilieres[f].listeAnnees[a].listeClasses[c].listeEtudiants = (Etudiant*) malloc(sizeof(Etudiant));
  } else {
    e -> listeFilieres[f].listeAnnees[a].listeClasses[c].listeEtudiants = (Etudiant*) realloc(e -> listeFilieres[f].listeAnnees[a].listeClasses[c].listeEtudiants, sizeof(Etudiant) * (e -> listeFilieres[f].listeAnnees[a].listeClasses[c].nombreEtudiants + 1));
  }
  	printf("\n \tdonner le nom de Etudiant :");
  	scanf("%s", e -> listeFilieres[f].listeAnnees[a].listeClasses[c].listeEtudiants[e -> listeFilieres[f].listeAnnees[a].listeClasses[c].nombreEtudiants].nomEtudiant);
	printf("\n \tdonner le prenom de Etudiant :");
  	scanf("%s", e -> listeFilieres[f].listeAnnees[a].listeClasses[c].listeEtudiants[e -> listeFilieres[f].listeAnnees[a].listeClasses[c].nombreEtudiants].prenomEtudiant);
  do {
    printf("\n \tdonner le numero de Etudiant :");
    scanf("%d", & numeroEtudiant);
  } while (TestEtudiant(e, numeroEtudiant, f, a) != -1);
  e -> listeFilieres[f].listeAnnees[a].listeClasses[c].listeEtudiants[e -> listeFilieres[f].listeAnnees[a].listeClasses[c].nombreEtudiants].numeroEtudiant = numeroEtudiant;
  e -> listeFilieres[f].listeAnnees[a].listeClasses[c].nombreEtudiants++;
}

void ModifierEtudiant(Etablissement * e, int f, int a,int c) {
  int numeroEtudiant, pos;

  printf("\n \tdonner le numero de Etudiant :");
  scanf("%d", & numeroEtudiant);
  pos = TestEtudiant(e, numeroEtudiant, f, a);
  if (pos == -1) {
    printf("\n \tEtudiant introuvable.");
    getch();

  } else {

    printf("\n \tdonner le nouveau nom de Etudiant :");
  	scanf("%s", e -> listeFilieres[f].listeAnnees[a].listeClasses[c].listeEtudiants[pos].nomEtudiant);
	printf("\n \tdonner le nouveau prenom de Etudiant :");
  	scanf("%s", e -> listeFilieres[f].listeAnnees[a].listeClasses[c].listeEtudiants[pos].prenomEtudiant);
  do {
    printf("\n \tdonner le nouveau numero de Etudiant :");
    scanf("%d", & numeroEtudiant);
  } while (TestEtudiant(e, numeroEtudiant, f, a) != -1);
  e -> listeFilieres[f].listeAnnees[a].listeClasses[c].listeEtudiants[pos].numeroEtudiant = numeroEtudiant;
  }

}

void SupprimerEtudiant(Etablissement * e, int f, int a, int c) {
  int numeroEtudiant, pos, i;

   printf("\n \t donner le numero de Etudiant :");
  scanf("%d", & numeroEtudiant);
  pos = TestEtudiant(e, numeroEtudiant, f, a);
  if (pos == -1) {
    printf("Etudiant introuvable.");
    getch();

  } else {
    for (i = pos; i < e -> listeFilieres[f].listeAnnees[a].listeClasses[c].nombreEtudiants; i++) {
      e -> listeFilieres[f].listeAnnees[a].listeClasses[c].listeEtudiants[i] =e -> listeFilieres[f].listeAnnees[a].listeClasses[c].listeEtudiants[i+1];
    }
    
    e -> listeFilieres[f].listeAnnees[a].listeClasses[c].nombreEtudiants--;
    e -> listeFilieres[f].listeAnnees[a].listeClasses[c].listeEtudiants = (Etudiant*) realloc(e -> listeFilieres[f].listeAnnees[a].listeClasses[c].listeEtudiants, sizeof(Etudiant) * (e -> listeFilieres[f].listeAnnees[a].listeClasses[c].nombreEtudiants));
    
  }

}

void RechercherEtudiant(Etablissement * e, int f, int a, int c) {
  int numeroEtudiant, pos, i;

  printf("\n \t donner le numero de Etudiant :");
  scanf("%d", & numeroEtudiant);
  pos = TestEtudiant(e, numeroEtudiant, f, a);
  if (pos == -1) {
    printf("Etudiant introuvable.");
    getch();
    
  } else {
    printf("\n \t%d => nomEtudiant : %s || prenomEtudiant : %s || numeroEtudiant : %d \n", pos,  e -> listeFilieres[f].listeAnnees[a].listeClasses[c].listeEtudiants[pos].nomEtudiant ,e -> listeFilieres[f].listeAnnees[a].listeClasses[c].listeEtudiants[pos].prenomEtudiant, e -> listeFilieres[f].listeAnnees[a].listeClasses[c].listeEtudiants[pos].numeroEtudiant);
  }
  getch();

}

void listerEtudiant(Etablissement * e, int f, int a, int c) {
    int i;

    for (i = 0; i < e -> listeFilieres[f].listeAnnees[a].listeClasses[c].nombreEtudiants; i++) {
     printf("\n \t%d => nomEtudiant : %s || prenomEtudiant : %s || numeroEtudiant : %d \n", i,  e -> listeFilieres[f].listeAnnees[a].listeClasses[c].listeEtudiants[i].nomEtudiant ,e -> listeFilieres[f].listeAnnees[a].listeClasses[c].listeEtudiants[i].prenomEtudiant, e -> listeFilieres[f].listeAnnees[a].listeClasses[c].listeEtudiants[i].numeroEtudiant);
    }
    getch();
}

/////////////////////////////////////////////////////////////////////////////////////////////Fin Etudiant//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////Début NOTE///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void listerNote(Etablissement * e) {
  int i;
  for (i = 0; i < e -> nombreNotes; i++) {
    printf("\n \t(%d) => Nom Etudiant : %s || Prenom Etudiant : %s \n", i, e->listeNotes[i].etudiant->nomEtudiant , e->listeNotes[i].etudiant->prenomEtudiant);
    printf("\n \t     => Nom Module : %s || coefficient Module : %d \n",e->listeNotes[i].module->nomModule, e->listeNotes[i].module->coefficient);
    printf("\n \t     => note : %f \n",e->listeNotes[i].note);
    printf("///////////////////////////////////////////////////////////////////////////////////////////");
    
  }
  getch();
}
void AjouterNote(Etablissement * e, int f, int a, int c){
	int pose,posm;
	Module *mt;
	Etudiant *et;
	
	do{
	listerEtudiant(e,f,a,c);
	printf(" \n \t  donner l indice Etudiant : "); scanf("%d",&pose);
	}while(pose < 0 || pose >= e->listeFilieres[f].listeAnnees[a].listeClasses[c].nombreEtudiants);
	et = &(e->listeFilieres[f].listeAnnees[a].listeClasses[c].listeEtudiants[pose]);
	
	do{
	listerModule(e,f,a);
	printf(" \n \t  donner l indice module : ");	scanf("%d",&posm);
	}while(posm < 0 || posm >= e->listeFilieres[f].listeAnnees[a].nombreModules);
	mt = &(e->listeFilieres[f].listeAnnees[a].listeModules[posm]);
	
	if(e->nombreNotes==0)
	{
		e->listeNotes = (Note*) malloc(sizeof(Note));
	} else { 
		e->listeNotes = (Note*) realloc(e->listeNotes, sizeof(Note) * (e->nombreNotes + 1));
	}
	e->listeNotes[e->nombreNotes].note=0;
	e->listeNotes[e->nombreNotes].etudiant = et;
	e->listeNotes[e->nombreNotes].module = mt;
	printf("\n \t entrer la note : ");scanf("%f",&e->listeNotes[e->nombreNotes].note);
	
	e->nombreNotes++;
}

void ModifierNote(Etablissement * e){
	int pos;
	do{
	listerNote(e);
	printf("\n \t Donner l indice de Note :");
	scanf("%d",&pos);
	}while(pos <0 || pos >= e -> nombreNotes);
	
	
	printf("entrer la note : ");scanf("%f",&e->listeNotes[pos].note);
	
}

void SupprimerNote(Etablissement * e){
	int pos,i;
	do{
	listerNote(e);
	
	printf("\n \t Donner l indice de Note :");
	scanf("%d",&pos);
	}while(pos <0 || pos >= e -> nombreNotes);
	
	for(i=pos;i<e->nombreNotes-1;i++);
	{
		e->listeNotes[i]=e->listeNotes[i+1];
	}
	e->nombreNotes--;
	e->listeNotes = (Note*) realloc(e->listeNotes, sizeof(Note) * e->nombreNotes);
}

void RechercherNote(Etablissement * e){
	
	int pos;
	do{
	listerNote(e);
	printf("\n \t Donner l indice de Note :");
	scanf("%d",&pos);
	}while(pos <0 || pos >= e -> nombreNotes);
	
	printf("\n \t (%d) => Nom Etudiant : %s || Prenom Etudiant : %s ",pos,e-> listeNotes[pos].etudiant->nomEtudiant , e-> listeNotes[pos].etudiant->prenomEtudiant);
    printf("\n \t      => Nom Module : %s || coefficient Module : %d ",e-> listeNotes[pos].module->nomModule, e-> listeNotes[pos].module->coefficient);
    printf("\n \t      => note : %f ",e->listeNotes[pos].note);
    printf("///////////////////////////////////////////////////////////////////////////////////////////\n");
	
}


void Notegeneral(Etablissement *e, int f, int a, int c)
{	int pose;
	do{system("cls");
		listerEtudiant(e,f,a,c);
		printf("\n \t donner l indice Etudiant : "); scanf("%d",&pose);
		}while(pose <0 || pose >=  e -> listeFilieres[f].listeAnnees[a].listeClasses[c].nombreEtudiants);
	
	
	float moyenneGenerale = 0;
	int totalCoeff = 0;
	int numEtudiant = e->listeFilieres[f].listeAnnees[a].listeClasses[c].listeEtudiants[pose].numeroEtudiant;
	for(int i = 0 ; i < e->nombreNotes ; i++){
		
		if(e->listeNotes[i].etudiant->numeroEtudiant == numEtudiant){
			moyenneGenerale += e->listeNotes[i].module->coefficient * e->listeNotes[i].note;
			totalCoeff += e->listeNotes[i].module->coefficient;
		}
	}
	
	moyenneGenerale /= totalCoeff;
	printf("\n \t => Nom Etudiant : %s || Prenom Etudiant : %s \n",e->listeFilieres[f].listeAnnees[a].listeClasses[c].listeEtudiants[pose].nomEtudiant ,e->listeFilieres[f].listeAnnees[a].listeClasses[c].listeEtudiants[pose].prenomEtudiant);
	printf("\n \tmoyenne generale = %f \n",moyenneGenerale);
	getch();
	
	
}
/////////////////////////////////////////////////////////////////////////////////////////////Fin NOTE//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////Début MENUS/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void menuP() {
  	system("cls");
  	system("color c7");
	printf("\n\n\t**************************************************\n");
	printf("\t**\t\t\t\t\t\t**\n\t**\t| MENU PRINCIPAL |\t\t\t**\n\t** MENU DES Filieres ---------------------- 1 : **\t\t\t\t\n\t** MENU DES Classes ----------------------- 2 : **\n \t** MENU DES Modules ----------------------- 3 : **\t\t\t\t\n\t** MENU DES Etudiant ---------------------- 4 : **\n \t** MENU DES Notes ------------------------- 5 : **\n \t** Quitter -------------------------------- 0 : **\n\t**\t\t\t\t\t\t**\n \t**");
	printf("************************************************\n");
	printf("\n\t|Donnez votre choix| : ");
}

void menuF() {
  system("cls");
  	system("color 97");
	printf("\n\n\t//////////////////////////////////////////////////\n");
	printf("\t//\t\t\t\t\t\t//\n\t//\t| MENU FILIERES |\t\t\t//\n\t// Ajouter Filiere ------------------------ 1 : //\t\t\t\t\n\t// Modifier Filiere ----------------------- 2 : //\n \t// Supprimer Filiere ---------------------- 3 : //\t\t\t\t\n\t// Rechercher Filiere --------------------- 4 : //\n \t// Lister Filier -------------------------- 5 : //\n \t// Retour --------------------------------- 0 : //\n\t//\t\t\t\t\t\t//\n \t//");
	printf("////////////////////////////////////////////////\n");
	printf("\n\t|Donnez votre choix| : ");
}

void menuC() {
  system("cls");
  	system("color e0");
  	printf("\n\n\t//////////////////////////////////////////////////\n");
	printf("\t//\t\t\t\t\t\t//\n\t//\t| MENU Classes |\t\t\t//\n\t// Ajouter Classe ------------------------- 1 : //\t\t\t\t\n\t// Modifier Classe ------------------------ 2 : //\n \t// Supprimer Classe ----------------------- 3 : //\t\t\t\t\n\t// Rechercher Classe ---------------------- 4 : //\n \t// Lister Classe -------------------------- 5 : //\n \t// Retour --------------------------------- 0 : //\n\t//\t\t\t\t\t\t//\n \t//");
	printf("////////////////////////////////////////////////\n");
	printf("\n\t|Donnez votre choix| : ");
}

void menuM() {
  system("cls");
  	system("color 97");
 	printf("\n\n\t//////////////////////////////////////////////////\n");
	printf("\t//\t\t\t\t\t\t//\n\t//\t| MENU Module |\t\t\t\t//\n\t// Ajouter Module ------------------------- 1 : //\t\t\t\t\n\t// Modifier Module ------------------------ 2 : //\n \t// Supprimer Module ----------------------- 3 : //\t\t\t\t\n\t// Rechercher Module ---------------------- 4 : //\n \t// Lister Module -------------------------- 5 : //\n \t// Retour --------------------------------- 0 : //\n\t//\t\t\t\t\t\t//\n \t//");
	printf("////////////////////////////////////////////////\n");
	printf("\n\t|Donnez votre choix| : ");
}

void menuA() {
  system("cls");
  system("color 37");
  printf("MENU Annee \n LICENCE\n 1-1ère Annee \n 2-2ème Annee \n 3-3ème Annee \n MASTER\n 4-4ème Annee \n 5-5ème Annee \n Votre choix : ");
  
}

void menuE() {
  system("cls");
  	system("color 97");
  	printf("\n\n\t//////////////////////////////////////////////////\n");
	printf("\t//\t\t\t\t\t\t//\n\t//\t| MENU ETUDIANT |\t\t\t//\n\t// Ajouter ETUDIANT ----------------------- 1 : //\t\t\t\t\n\t// Modifier ETUDIANT ---------------------- 2 : //\n \t// Supprimer ETUDIANT --------------------- 3 : //\t\t\t\t\n\t// Rechercher ETUDIANT -------------------- 4 : //\n \t// Lister ETUDIANT ------------------------ 5 : //\n \t// Retour --------------------------------- 0 : //\n\t//\t\t\t\t\t\t//\n \t//");
	printf("////////////////////////////////////////////////\n");
	printf("\n\t|Donnez votre choix| : ");
}
void menuN() {
  system("cls");
  	system("color e0");
 	printf("\n\n\t//////////////////////////////////////////////////\n");
	printf("\t//\t\t\t\t\t\t//\n\t//\t| MENU NOTE |\t\t\t\t//\n\t// Ajouter NOTE --------------------------- 1 : //\t\t\t\t\n\t// Modifier NOTE -------------------------- 2 : //\n \t// Supprimer NOTE ------------------------- 3 : //\t\t\t\t\n\t// Rechercher NOTE ------------------------ 4 : //\n \t// Lister NOTE ---------------------------- 5 : //\n \t// Notegeneral ---------------------------- 6 : //\n \t// Retour --------------------------------- 0 : //\n\t//\t\t\t\t\t\t//\n \t//");
	printf("////////////////////////////////////////////////\n");
	printf("\n\t|Donnez votre choix| : ");
}
/////////////////////////////////////////////////////////////////////////////////////////////Fin MENUS///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


main() {
  int choix, choix1, choix2, choix3 , choix4 ,i, f, a, c;
  Etablissement * e = NULL;
  
  e = (Etablissement * ) malloc(sizeof(Etablissement));
  e->nombreFilieres = 0;
  e->nombreNotes=0;

	
  
  do {
    menuP();
    scanf("%d", & choix);
    switch (choix) {
    	
////////////////////////cas de choix des Filières///////////////////////////////////////////
    case 1:
      do {
        menuF();
        scanf("%d", & choix1);
        switch (choix1) {
        case 1:
          AjouterFiliere(e);
          break;
        case 2:
          ModifierFiliere(e);
          break;
        case 3:
          SupprimerFiliere(e);
          break;
        case 4:
          RechercherFiliere(e);
          break;
        case 5:
          listerFiliere(e);
          break;
        }
      } while (choix1 != 0);
      break;

//////////////////cas de choix des Classes////////////////////////////////////////////////////
    case 2:
      if (e -> nombreFilieres == 0) {
        printf("\n \t !! IMPOSSIBLE DANS '0' FILIERES !!");
        getch();
      } else {
        do {system("cls");
          listerFiliere(e);
          printf("\n \tDonner l\'indice de Filiere :");
          scanf("%d", &f);
        } while (f < 0 || f >= e -> nombreFilieres);

        do {system("cls");
          menuA();
          scanf("%d", &a);
        } while (a <= 0 || a > 5);
        a--;

        do {
          menuC();
          scanf("%d", & choix2);
          switch (choix2) {
          case 1:
            AjouterClasse(e, f, a);
            break;
          case 2:
            ModifierClasse(e, f, a);
            break;
          case 3:
            SupprimerClasse(e, f, a);
            break;
          case 4:
            RechercherClasse(e, f, a);
            break;
          case 5:
            listerClasse(e, f, a);
            break;
          }
        } while (choix2 != 0);
        break;
      }
      break;

////////////////////cas de choix des Modules//////////////////////////////////////////////////////////
    case 3:
      if (e ->nombreFilieres == 0) {
        printf("\n \t !! IMPOSSIBLE DANS '0' FILIERES !!");
        getch();
      } else {
        do {system("cls");
          listerFiliere(e);
          printf("\n \tDonner l\'indice de Filiere :");
          scanf("%d", &f);
        } while (f < 0 || f >= e -> nombreFilieres);

        do {system("cls");
          menuA();
          scanf("%d", &a);
        } while (a <= 0 || a > 5);
        a--;

        do {
          menuM();
          scanf("%d", & choix2);
          switch (choix2) {
          case 1:
            AjouterModule(e, f, a);
            break;
          case 2:
            ModifierModule(e, f, a);
            break;
          case 3:
            SupprimerModule(e, f, a);
            break;
          case 4:
            RechercherModule(e, f, a);
            break;
          case 5:
            listerModule(e, f, a);
            break;
          }
        } while (choix2 != 0);
        break;
      }
      break;
//////////////////////cas de choix des Etudiants///////////////////////////
    case 4:
    	if (e ->nombreFilieres == 0) {
        printf("\n \t !! IMPOSSIBLE DANS '0' FILIERES !!");
        getch();
      } else {
        do {system("cls");
          listerFiliere(e);
          printf("\n \tDonner l\'indice de Filiere :");
          scanf("%d", &f);
        } while (f < 0 || f >= e -> nombreFilieres);
    	
    	do {system("cls");
          menuA();
          scanf("%d", &a);
        } while (a <= 0 || a > 5);
        a--;
        
        if(e->listeFilieres[f].listeAnnees[a].nombreClasses==0)
        {
        	printf("\n \t !! IMPOSSIBLE DANS '0' Classes !!");
        	getch();
		}else{
		do {system("cls");
          listerClasse(e,f,a);
          printf("\n \tDonner l\'indice de Classe :");
          scanf("%d", &c);
        } while (c < 0 || c >= e->listeFilieres[f].listeAnnees[a].nombreClasses);
        do{
        	menuE();
        	scanf("%d",& choix3);
        	switch(choix3)
        	{
        		case 1 : AjouterEtudiant(e,f,a,c);
        				break;
        		case 2 : ModifierEtudiant(e,f,a,c);
        				break;
        		case 3 : SupprimerEtudiant(e,f,a,c);
        				break;
        		case 4 : RechercherEtudiant(e,f,a,c);
        				break;
        		case 5 : listerEtudiant(e,f,a,c);
        				break;
			}
		}while(choix3!=0);
		break;
		}
    }
    case 5 :
    	if (e ->nombreFilieres == 0) {
        printf("\n \t !! IMPOSSIBLE DANS '0' FILIERES !!");
        getch();
      } else {
        do {system("cls");
          listerFiliere(e);
          printf("\n \tDonner l\'indice de Filiere :");
          scanf("%d", &f);
        } while (f < 0 || f >= e -> nombreFilieres);
    	
    	
    	do {system("cls");
          menuA();
          scanf("%d", &a);
        } while (a <= 0 || a > 5);
        a--;
        
        if(e->listeFilieres[f].listeAnnees[a].nombreClasses==0)
        {
        	printf("\n \t !! IMPOSSIBLE DANS '0' Classes !!");
        	getch();
		}else{
		do {system("cls");
          listerClasse(e,f,a);
          printf("\n \tDonner l\'indice de Classe :");
          scanf("%d", &c);
        } while (c < 0 || c >= e->listeFilieres[f].listeAnnees[a].nombreClasses);
        
        if(e->listeFilieres[f].listeAnnees[a].listeClasses[c].nombreEtudiants==0)
        {
        	printf("\n \t !! IMPOSSIBLE DANS '0' Etudiants !!");
        	getch();
		}else{
			if(e->listeFilieres[f].listeAnnees[a].nombreModules==0){
				printf("\n \t !! IMPOSSIBLE DANS '0' Modules !!");
        		getch();
				}else{
					do{
						menuN();
						scanf("%d",&choix4);
						switch(choix4)
						{
							case 1: AjouterNote(e,f,a,c);
									break;
							case 2: ModifierNote(e);
									break;
							case 3: SupprimerNote(e);
									break;
							case 4: RechercherNote(e);
									break;		
							case 5: listerNote(e);
									break;
							case 6: Notegeneral(e,f,a,c);
									break;
						}
						
					}while(choix4!=0);
					break;
				}
			}
		}	
	}	
}
	
  } while (choix != 0);
}
