#include "HOTEL_LLC_BIBLIO.h"

//Le code de fonctions:-------------------------------------------------------------------------
//1- Gestion de client:
client *creerlisteclient(client *listclient, FILE *fc){
  client *tmp= NULL;
  client *p=NULL;


  do{
    tmp= malloc(sizeof(client));
    fscanf(fc,"%d %s %s %d %d", &(tmp->code), &(tmp->nom), &(tmp->prenom), &(tmp->NI), &(tmp->NT));
    tmp->nextc = NULL;
    if (listclient==NULL){
      listclient= tmp;
    }else{
      p=listclient;
      while (p->nextc != NULL)
        p=p->nextc;
      p->nextc=tmp;
  }
}while(!feof(fc))
;
  return listclient;
};





client *ajouterclient(client *listclient, FILE *fc){
  client *newclient= NULL;
  client *p=listclient;
  newclient= malloc(sizeof(client));

  while (p->nextc->nextc != NULL) p= p->nextc;
  newclient->code= (p->code)+2;
  p->nextc= newclient;

  printf("Entrez le nom et ");
  gets(newclient->nom);

  printf("le prenom: ");
  gets(newclient->prenom);

  printf("Entrez le numero d'identite: ");
  scanf("%d", &(newclient->NI));

  printf("Entrez le numero de telphone: ");
  scanf("%d", &(newclient->NT));
  displaylistc(listclient);

  fseek(fc, 0, SEEK_SET);
  p=listclient;
  while(p!= NULL){
  fprintf(fc, "%d %s %s %d %d\n", p->code, p->nom, p->prenom, p->NI, p->NT);
  p= p->nextc;
  }
    return listclient;
};


client *modifierclient(client *listclient, FILE *fc){
  client *p= NULL;
  int co;
  int rep;
  p= listclient;
  printf("Entrez le code de client a modifier: ");
  scanf("%d", &co);
  p= listclient;
  while((p->code!= co) && (p!=NULL)){
    p= p->nextc;
    printf("cc");
  }
  if (p!= NULL){
  printf("Entrez l'information a modifier:\n\t1: Nom.\n\t2: Prenom.\n\t3: Numero d'identite.\n\t4: Numero de telephone.\nInfo: ");
  scanf("%d", &rep);
  if (rep==1){
    printf("Le nom est: ");
    puts(p->nom);
    printf("Donnez le nouveau nom: ");
    scanf("%s", &(p->nom));
  }else if(rep== 2){
    printf("Le prenom est: ");
    puts(p->prenom);
    printf("Donnez le nouveau prenom: ");
    gets(p->prenom);
  }else if(rep==3){
    printf("Le numero d'identite est: %d", p->NI);
    printf("Donnez le nouveau numero d'identite: ");
    scanf("%d", &(p->NI));
  }else if(rep==4){
    printf("Le numero de telphone est: %d");
    printf("Donnez le nouveau numero de telphone: ");
    scanf("%d", &(p->NT));
  }else{
    printf("\nMal saisi!!!");
  }
}else{
  printf("Ce client n'exist pas.");
}
fseek(fc,0,SEEK_SET);
p= listclient;
while(p!= NULL){
  fprintf(fc, "%d %s %s %d %d\n", p->code, p->nom, p->prenom, p->NI, p->NT);
  p= p->nextc;
}
return listclient;
};


client *supprimerclient(client *listclient, FILE *fc){
  client *tmp= listclient;
  client *tmpprev= listclient;

  int co;

  printf("Donnez le code de client a supprimer: ");
  scanf("%d", &co);

  while ((tmp->code)!= co){
    tmpprev= tmp;
    tmp= tmp->nextc;
  }

    tmpprev->nextc = tmp->nextc;
    free(tmp);


  fc=fopen("client.txt","w");

  client *z=listclient;
   while (z!=NULL)
   {
        fprintf(fc, "%d %s %s %s %s\n", z->code, z->nom, z->prenom, z->NI, z->NT);
        z=z->nextc;
   }


return listclient;
};


client *accesscode(client *listclient, int co){
  client *p= listclient;
  while((p!= NULL) && (p->code != co)){
    p= p->nextc;
  }
  return p;
};

void displaylistc(client *listclient){
client *p= listclient;
while(p->nextc!=NULL){
  printf("\n");
  printf("code: %d\n", p->code);
  printf("\tNom: ");
  puts(p->nom);
  printf("\tPrenom: ");
  puts(p->prenom);
  printf("\tNumero d'identite; %d", p->NI);
  printf("\n\tNumero de telephone: %d", p->NT);
  printf("\n");
  p= p->nextc;
}
};

//2-Gestion de réservation:
reservation *createlistres(reservation *listreser, FILE *f3){
  reservation *tmp= NULL;
  reservation *p= NULL;

  do{
    tmp= malloc(sizeof(reservation));
    fscanf(f3,"%d %d %s %s %d %d %d %f", &(tmp->ref), &(tmp-> nbrnr), tmp->ddr, tmp->ddds, &(tmp->nbrdpc), &(tmp->c), &(tmp->ndch), &(tmp->prixt));


    tmp->nextr= NULL;
    if (listreser== NULL){
      listreser= tmp;
    }else{
      p= listreser;
      while(p->nextr!= NULL){
        p= p->nextr;}
      p->nextr= tmp;
    }

  }while(!feof(f3));
return listreser;
};




reservation *ajouterres(reservation *listreser, client *listclient, chambre *listechambre, FILE *f1, FILE *f3){
  reservation *newreservation= NULL;
  reservation *p= NULL;
  client *lcl= NULL;
  chambre *lch= NULL;
  FILE *fr;
  char dateoftoday[13];
  char dateg[12];
  int rep;
  int saison;
  int npc;
  int co;
  newreservation= malloc(sizeof(reservation));


  p= listreser;
  while (p->nextr->nextr != NULL){
    p= p->nextr;
  }
  newreservation->ref= p->ref+1;
  p->nextr= newreservation;

  time_t currenttime;
  time(&currenttime);


  struct tm *ltime= localtime(&currenttime);
  int d = ltime->tm_mday;
  int m= ltime->tm_mon+1;
  int y= ltime->tm_year+1900;

  int lengthd= snprintf( NULL, 0, "%d", d);
  char *day= malloc(lengthd+1);
  snprintf(day,lengthd+1, "%d", d);


  int lengthm= snprintf( NULL, 0, "%d", m);
  char *month= malloc(lengthm+1);
  snprintf(month,lengthm+1, "%d", m);


  int lengthy= snprintf( NULL, 0, "%d", y);
  char *year= malloc(lengthy+1);
  snprintf(year,lengthy+1, "%d", y);




  char slash[2]= {'/', '\0'};
  strcat(dateoftoday, day);
  strcat(dateoftoday, slash);
  strcat(dateoftoday, month);
  strcat(dateoftoday, slash);
  strcat(dateoftoday, year);
  strcpy(newreservation-> ddr, dateoftoday);
  printf("Entrez le nombre de nuit reservees: ");
  scanf("%d", &(newreservation->nbrnr));



      int j;
      int a;
      int nbrdj;


      printf("Introduisez la date de debut de sejour: ");

      printf("\nEntrez l'annee: ");
      scanf("%d", &a);
      if (a<2022){
        do{
        printf("\nEntrez une annee valide! [2022..]: ");
        scanf("%d", &a);
      }while (a<2022);
      }

      printf("Entrez le mois: \n\t1: Janvier.\n\t2: Fevrier.\n\t3: Mars \n\t4: Avril.\n\t5: Mai. \n\t6: Juin. \n\t7: Juillet.\n\t8: Aout.\n\t9: Septembre.\n\t10: Octobre.\n\t11: Novembre.\n\t12: Decembre.");
      printf("\nLe moi: ");
      scanf("%d", &m);
      if ((m<=0) || (m>12)){
        do{
        printf("\nEntrez un mois valide! [1..12]: ");
        scanf("%d", &m);
      }while((m<=0) || (m>12));
      }

      switch (m) {
                  case 1:
                  case 3:
                  case 5:
                  case 7:
                  case 8:
                  case 10:
                  case 12:
                      nbrdj = 31;
                      break;
                  case 4:
                  case 6:
                  case 9:
                  case 11:
                      nbrdj = 30;
                      break;
                  case 2:
                      if (((a % 4 == 0) &&
                           !(a % 100 == 0))
                           || (a % 400 == 0))
                          nbrdj = 29;
                      else
                          nbrdj = 28;
                      break;

    }

      switch (m){
        case 1:
        case 2:
        case 12:
            saison = 1;
            break;
        case 3:
        case 4:
        case 5:
            saison= 2;
            break;
        case 6:
        case 7:
        case 8:
            saison= 3;
            break;
        case 9:
        case 10:
        case 11:
            saison= 4;
            break;




    }
      printf("Entrez le jour: ");
      scanf("%d", &j);
      if ((j<=0) || (j>nbrdj)){
        do{
        printf("Veuillez entrez un jour valide! [1..%d]", nbrdj);
        scanf("%d", &j);
      }while((j<=0) || (j>nbrdj));
    }


    int lengthj= snprintf( NULL, 0, "%d", j);
    char *jour= malloc(lengthj+1);
    snprintf(jour,lengthj+1, "%d", j);

    lengthm= snprintf( NULL, 0, "%d", m);
    char *mois= malloc(lengthm+1);
    snprintf(mois, lengthm+1, "%d", m);

    int lengtha= snprintf( NULL, 0, "%d", a);
    char *annee= malloc(lengtha+2);
    snprintf(annee,lengthm+3, "%d", a);


    strcat(dateg, jour);
    strcat(dateg, slash);
    strcat(dateg, mois);
    strcat(dateg, slash);
    strcat(dateg, annee);
  strcpy(newreservation->ddds, dateg);
  printf("Entrez le nombre de personnes concernees: ");
  scanf("%d", &(newreservation->nbrdpc));

  printf("Ce client existe?\nEntrez 1 pour oui ou 0 pour sinon.");
  scanf("%d", &rep);
  if (rep==1){
    printf("Entrez le code de ce client: ");
    scanf("%d", &newreservation->c);


}else if (rep==0) {
    printf("Enregistrez le client: ");
    ajouterclient(listclient, f1);
    lcl= listclient;
    while (lcl->nextc->nextc!= NULL) lcl= lcl->nextc;
    newreservation-> c= lcl->code;
  }
  npc= newreservation->nbrdpc;
  lch= listechambre;
  if ((npc>0) && (npc<3)){
  while ((lch->etat!= 0) && (lch->type!= 1))
    lch= lch->nextch;
  }else if ((npc>2) && (npc<5)){
    while ((lch->etat!= 0) && (lch->type!= 2))
      lch= lch->nextch;
  }else if (npc>4) {
    while ((lch->etat!= 0) && (lch->type!= 3))
      lch= lch->nextch;
  }
  if(lch!= NULL){
    newreservation->ndch= lch->nbrdc;
    newreservation->prixt= calculprix(newreservation->nbrnr, saison, lch->type);
    lch->etat= 1;
}


else{
  printf("Aucune chambre vide dans cette date.");
}

return listreser;
};

reservation *modifierres(reservation *listreser, FILE *fr){
  reservation *tmp= listreser;
  reservation *p= listreser;
  int re, rep;
  int j,m,a;
  char dateg[12];
  int nbrdj;
  char slash[2]= {'/', '\0'};
  printf("Donnez la refference de la reservation: ");
  scanf("%d", &re);
  while((tmp->ref!= re)&&(tmp!= NULL)) tmp= tmp->nextr;
  if(tmp!= NULL){
    printf("Donnez l'information a modifier: \n\t1-Date de debnut de sejour.\n\t2-Nombre de personnes concernees.\n\t3-Nombre de nuitees.");
    scanf("%d", &rep);
    switch(rep){
      case 1:
      printf("Introduisez la date de debut de sejour: ");
      printf("\nEntrez l'annee: ");
      scanf("%d", &a);
      if (a<2022){
        do{
          printf("\nEntrez une annee valide! [2022..]: ");
          scanf("%d", &a);
        }while (a<2022);
        }

        printf("Entrez le mois: \n\t1: Janvier.\n\t2: Fevrier.\n\t3: Mars \n\t4: Avril.\n\t5: Mai. \n\t6: Juin. \n\t7: Juillet.\n\t8: Aout.\n\t9: Septembre.\n\t10: Octobre.\n\t11: Novembre.\n\t12: Decembre.");
        printf("\nLe moi: ");
        scanf("%d", &m);
        if ((m<=0) || (m>12)){
          do{
            printf("\nEntrez un mois valide! [1..12]: ");
            scanf("%d", &m);
          }while((m<=0) || (m>12));
        }

        switch (m) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            nbrdj = 31;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            nbrdj = 30;
            break;
        case 2:
            if (((a % 4 == 0) &&
                 !(a % 100 == 0))
                 || (a % 400 == 0))
                nbrdj = 29;
            else
                nbrdj = 28;
            break;

          }


          printf("Entrez le jour: ");
          scanf("%d", &j);
          if ((j<=0) || (j>nbrdj)){
              do{
                printf("Veuillez entrez un jour valide! [1..%d]", nbrdj);
                scanf("%d", &j);
              }while((j<=0) || (j>nbrdj));
            }


            int lengthj= snprintf( NULL, 0, "%d", j);
            char *jour= malloc(lengthj+1);
            snprintf(jour,lengthj+1, "%d", j);

            int lengthm= snprintf( NULL, 0, "%d", m);
            char *mois= malloc(lengthm+1);
            snprintf(mois, lengthm+1, "%d", m);

            int lengtha= snprintf( NULL, 0, "%d", a);
            char *annee= malloc(lengtha+2);
            snprintf(annee,lengthm+3, "%d", a);


            strcat(dateg, jour);
            strcat(dateg, slash);
            strcat(dateg, mois);
            strcat(dateg, slash);
            strcat(dateg, annee);
            strcpy(tmp->ddds, dateg);
            break;
          case 2:
            printf("Entre le nouveau nombre de personnes concernees: ");
            scanf("%d", &(tmp->nbrdpc));
            break;
          case 3:
            printf("Entrez le nouveau nombre de nuitees: ");
            scanf("%d", &(tmp->nbrnr));
            break;
          }//switch



  }else{
    printf("Cette reservation n'existe pas!!!");
  }
return listreser;
};





reservation *annulerres(reservation *listreser, FILE *fr){
  reservation *tmp= listreser;
  reservation *tmpprev= listreser;

  int re;

  printf("Donnez la ref de la reservation: ");
  scanf("%d", &re);

  while((tmp!= NULL) && (tmp->ref!= re)){
    tmpprev= tmp;
    tmp= tmp->nextr;
  }
  if (tmp!= NULL){
    tmpprev->nextr = tmp->nextr;
    tmp->nextr= NULL;
    free(tmp);
    fseek(fr,0,SEEK_SET);


      fr=fopen("reservation.txt","w");

  reservation *p=listreser;
   while (p!=NULL)
   {
        fprintf(fr, "%d %d %s %s %d %d %d %f\n", p->ref, p->nbrnr, p->ddr, p->ddds, p->nbrdpc, p->c, p->prixt);
        p=p->nextr;
   }
    }

else{
  printf("Ce client n'existe pas!!!");
}
return listreser;
};

float calculprix(int ndn, int saison, int tc){ //qui retourne le prix d'une reservation
  float p;
  switch(saison){
  case 1:
    switch(tc){
      case 1:
        p= ndn*0.8*4500;
        break;
      case 2:
        p= ndn*0.8*6000;
        break;
      case 3:
        p= ndn*0.8*6500;
        break;
    }break;

    case 2:
    switch(tc){
      case 1:
        p= ndn*4500;
        break;
      case 2:
        p= ndn*6000;
        break;
      case 3:
        p= ndn*6500;
        break;
    }break;

    case 3:
      switch(tc){
      case 1:
        p= ndn*1.4*4500;
        break;
      case 2:
        p= ndn*1.4*6000;
        break;
      case 3:
        p= ndn*1.4*6500;
        break;
    }break;
    case 4:
    switch(tc){
      case 1:
        p= ndn*1.1*4500;
        break;
      case 2:
        p= ndn*1.1*6000;
        break;
      case 3:
        p= ndn*1.1*6500;
        break;
    }break;

}
return p;
};







void displaylistr(reservation *listreser){
  reservation *p= listreser;
  while(p->nextr !=NULL){
    printf("\n");
    printf("ref: %d\n", p->ref);
    printf("\tNombre de nuits reservees: %d\n", p->nbrnr);
    printf("\tDate de reservation: ");
    puts(p->ddr);
    printf("\tDate de debut de sejour: ");
    puts(p->ddds);
    printf("\tNombre de personnes concenees: %d\n", p->nbrdpc);
    printf("\tCode client: %d\n", p->c);
    printf("\tNumero de chambre: %d\n", p->ndch);
    printf("\tLe prix total: %0.2f", p->prixt);
    printf("\n--------------------------------------------------");
    p=p->nextr;}
};



//2-Gestion de chambre:
chambre *createlistch(chambre *listchambre, FILE *f3){
  chambre *tmp= NULL;
  chambre *p= NULL;
  do{
    tmp= malloc(sizeof(chambre));
    fscanf(f3, "%d %d %d %d %d", &(tmp->nbrdc), &(tmp->type), &(tmp->prix), &(tmp->TV), &(tmp->etat));
    tmp->nextch= NULL;

    if (listchambre== NULL){
      listchambre= tmp;
    }else{
      p= listchambre;
      while (p->nextch != NULL)
        p= p->nextch;
      p->nextch= tmp;
    }
  }while (!feof(f3));
  return listchambre;
};


chambre *accessndc(chambre *listchambre, int ndc){
  chambre *p= listchambre;
  while(p->nbrdc!= ndc) p=p->nextch;
  return p;
};


chambre *libchambre(chambre *listchambre, int ndc){
  chambre *p =listchambre;
  while((p!=NULL)|| p->nbrdc!= ndc){
    p= p->nextch;
  }
  p->etat= 0;
  return listchambre;
};


//3-Autre fonctions:
void ahrc(reservation *listreser){ //Afficher historique de reservation d'un client.
reservation *tmp= NULL;
int co;
int i=1;
int b=0;
tmp= listreser;
printf("Entrez le code de client: ");
scanf("%d", &co);

while(tmp!= NULL){
  if (tmp->c== co){
    b= 1;
    printf("%d-\n", i);
    printf("\tref:  %d", tmp->ref);
    printf("\n\tNombre de nuit reservees:  %d", tmp->nbrnr);
    printf("\n\tDate de reservation:  %s", tmp->ddr);
    printf("\n\tDate de debut de sejour:   %s", tmp->ddds);
    printf("\n\tNombre de personnes concernees:   %d", tmp->nbrdpc);
    printf("\n**************************************************************\n");
    i++;
  }
  tmp= tmp->nextr;
}
if (b==0){
printf("le client n'existe pas ou ce client n'as pas d'historique.");
}
printf("\nTotal de reservations:  %d",i-1);
};



void ahrch(reservation *listreser){
  reservation *tmp= NULL;
  int ndc;
  int i;
  int j,m,a,nbrdj;
  int jour=0; int mois=0; int annee= 0; int saison=0;

  printf("Donnez le nombre de chambre: ");
  scanf("%d", &ndc);
  printf("Introduisez la date de debut d'affichage de l'historique': ");

  printf("\nEntrez l'annee: ");
  scanf("%d", &a);

  printf("Entrez le mois: \n\t1: Janvier.\n\t2: Fevrier.\n\t3: Mars \n\t4: Avril.\n\t5: Mai. \n\t6: Juin. \n\t7: Juillet.\n\t8: Aout.\n\t9: Septembre.\n\t10: Octobre.\n\t11: Novembre.\n\t12: Decembre.");
  printf("\nLe moi: ");
  scanf("%d", &m);
  if ((m<=0) || (m>12)){
    do{
    printf("\nEntrez un mois valide! [1..12]: ");
    scanf("%d", &m);
  }while((m<=0) || (m>12));}
  switch (m) {
              case 1:
              case 3:
              case 5:
              case 7:
              case 8:
              case 10:
              case 12:
                  nbrdj = 31;
                  break;
              case 4:
              case 6:
              case 9:
              case 11:
                  nbrdj = 30;
                  break;
              case 2:
                  if (((a % 4 == 0) &&
                       !(a % 100 == 0))
                       || (a % 400 == 0))
                      nbrdj = 29;
                  else
                      nbrdj = 28;
                  break;

}

  printf("Entrez le jour: ");
  scanf("%d", &j);
  if ((j<=0) || (j>nbrdj)){
    do{
    printf("Veuillez entrez un jour valide! [1..%d]", nbrdj);
    scanf("%d", &j);
  }while((j<=0) || (j>nbrdj));
}
char date[11];
tmp= listreser;
  do{
    strcpy(date, tmp->ddds);
  if (tmp->ndch==ndc){
    jour= 0; mois= 0; annee=0;
    j_m_a(date, &jour, &mois, &annee, &saison);
  if  (annee<a) {
    printf("%d-------------------------------------------------------------\n", i);
    printf("\tref:  %d", tmp->ref);
    printf("\n\tNombre de nuit reservees:  %d", tmp->nbrnr);
    printf("\n\tDate de reservation:  %s", tmp->ddr);
    printf("\n\tDate de debut de sejour:   %s", tmp->ddds);
    printf("\n\tNombre de personnes concernees:   %d", tmp->nbrdpc);
    printf("\n**************************************************************\n");
    i++;
  }else if(annee=a){
    if (mois<m){
    printf("%d-------------------------------------------------------------\n", i);
    printf("\tref:  %d", tmp->ref);
    printf("\n\tNombre de nuit reservees:  %d", tmp->nbrnr);
    printf("\n\tDate de reservation:  %s", tmp->ddr);
    printf("\n\tDate de debut de sejour:   %s", tmp->ddds);
    printf("\n\tNombre de personnes concernees:   %d", tmp->nbrdpc);
    printf("\n**************************************************************\n");

  }else if (mois=m){
    if(jour<=jour){
      printf("%d----------------------------------------------------------\n", i);
      printf("\tref:  %d", tmp->ref);
      printf("\n\tNombre de nuit reservees:  %d", tmp->nbrnr);
      printf("\n\tDate de reservation:  %s", tmp->ddr);
      printf("\n\tDate de debut de sejour:   %s", tmp->ddds);
      printf("\n\tNombre de personnes concernees:   %d", tmp->nbrdpc);
      printf("\n**************************************************************\n");
    }
  }
}
}
tmp= tmp->nextr;
}while(tmp->nextr!= NULL);

}


void j_m_a(char date[11], int *j, int *m, int *a, int *saison){
  int jour;
  char cj[2]= {0};
  int mois;
  char cm[1]= {0};
  int annee;
  char ca[1]= {0};
  int i=strlen(date)-1;
  int puiss_j=1;
  int puiss_a=1;
  int puiss_m=1;

  while (date[i]!= '/'){
    ca[0]= date[i];
    annee= atoi(ca);
    *a= *a+ annee*puiss_a;
    puiss_a= puiss_a* 10;
    i--;
  }
  i--;
  while (date[i]!= '/'){
    cm[0]= date[i];
    mois= atoi(cm);
    *m= *m+ mois*puiss_m;
    puiss_m= puiss_m*10;
    i--;
  }
  i--;
  while(i>=0){
    cj[0]= date[i];
    jour= atoi(cj);
    *j=*j+ jour*puiss_j;
    puiss_j= puiss_j*10;
    i--;
  }

  switch (*m){
    case 1:
    case 2:
    case 12:
        *saison = 1;
        break;
    case 3:
    case 4:
    case 5:
        *saison= 2;
        break;
    case 6:
    case 7:
    case 8:
        *saison= 3;
        break;
    case 9:
    case 10:
    case 11:
        *saison= 4;
        break;

}};




client *ctt(client *listctt, reservation *listreser, client *listclient, chambre *listechambre){
  reservation *lr=listreser;
  client *tmp= NULL;
  client *tmplc= NULL;
  client *p= NULL;
  chambre *lch= NULL;
  int rep;
  int ty;
  printf("Precisez la critique: 1 pour meme type, 0 pour qui contient une TV: ");
  scanf("%d", &rep);
  if (rep==1){
    printf("Donnez le type:\n\t1: Simple.\n\t2: Double.\n\t3: Tripple.\nLe type:  ");
    scanf("%d", &ty);

    while(lr->nextr!= NULL){
      lch= accessndc(listechambre, lr->ndch);
      if (lch->type == ty){
        tmp= malloc(sizeof(client));
        tmplc= accesscode(listclient, lr->c);
        puts(tmplc->nom);
        tmp->code =tmplc->code;
        strcpy(tmp->nom, tmplc->nom);
        strcpy(tmp->prenom, tmplc->prenom);
        tmp->NI =tmplc->NI;
        tmp->NT =tmplc->NT;
        tmp->nextc= NULL;
        if(listctt==NULL){
          listctt= tmp;
        }else{
          p= listctt;
          while(p->nextc!= NULL) p= p->nextc;
          p->nextc= tmp;
        }
      }
      lr=lr->nextr;
    }
  }else if(rep==0){
    while(lr->nextr!= NULL){
      lch= accessndc(listechambre, lr->ndch);
      if (lch->TV== 1){
        tmp= malloc(sizeof(client));
        tmplc= accesscode(listclient, lr->c);
        puts(tmplc->nom);
        tmp->code =tmplc->code;
        strcpy(tmp->nom, tmplc->nom);
        strcpy(tmp->prenom, tmplc->prenom);
        tmp->NI =tmplc->NI;
        tmp->NT =tmplc->NT;
        tmp->nextc= NULL;
        if(listctt==NULL){
          listctt= tmp;
        }else{
          p= listctt;
          while(p->nextc==NULL) p= p->nextc;
          p->nextc= tmp;
        }
      }
      lr=lr->nextr;
    }
  }

  return listctt;
};

void prch(reservation *listreser, chambre *listchambre){
  reservation *tmp= listreser;
  chambre *lch= NULL;
  int ndnr=0;
  int tndnr=0;
  float res=0;
  int ndc;
  time_t currenttime;
  time(&currenttime);
  int j,m,a,s;
  char date[20];
  struct tm *ltime= localtime(&currenttime);
  int y= ltime->tm_year+1900;
  printf("Donnez le numero de la chambre: ");
  scanf("%d", &ndc);

  while(tmp->nextr!= NULL){
  if (tmp->ndch== ndc){
    strcpy(date, tmp->ddds);
    j=0; m= 0; a=0; s= 0;
     j_m_a(date, &j,&m,&a,&s);
     if (a=y){
      ndnr= ndnr + tmp->nbrnr;
    }
  }
    tndnr= tndnr+ tmp->nbrnr;
    tmp= tmp->nextr;
  }
  res= (float)ndnr/tndnr;
  printf("Le pourcentage de la reservation de la chambre %d est: %0.2f %%",ndc, res*100);
};


//4- La gestion  des factures:
facture *createlistfac(facture *listfac, reservation *listreser){

  reservation *lr= NULL;
  facture *tmp= NULL;
  facture *p= NULL;
  lr= listreser;
  while(lr->nextr!= NULL){
    tmp= malloc(sizeof(facture));
    tmp->numdc= lr->c;
    tmp->id= lr->ref;
    tmp->numdn= lr->nbrnr;
    tmp->montant= lr->prixt;
    tmp->nextf= NULL;
    if (listfac==NULL){
      listfac= tmp;
    }else{
      p= listfac;
      while (p->nextf != NULL) p= p->nextf;
      p->nextf= tmp;
    }
    lr= lr->nextr;
  }
  listfac= listfactric(listfac);
  return listfac;
}


void permutf(facture *node1, facture*node2 ){
  int tmpn, tmpc, tmpi; float tmpm;
  tmpn= node1->numdc;
  tmpc= node1->cc;
  tmpi= node1->id;
  tmpm= node1->montant;

  node1->numdc= node2->numdc;
  node1->cc= node2->cc;
  node1->id= node2->id;
  node1->montant= node1->montant;

  node2->numdc= tmpn;
  node2->cc= tmpc;
  node2->id= tmpi;
  node1->montant= tmpm;
};


facture *listfactric(facture *listfac){
  facture *p= NULL;
  facture *q= NULL;
  facture *r= NULL;
  float tmp;
  int per;
  do{
    per=0;
    p= listfac;
    while(p->nextf!= q){
      if (p->numdc > p->nextf->numdc){
        r= p->nextf;
        permutf(p, r);
        per= 1;
      }
      p= p->nextf;
    }
    q= p;
  }while(per==1);
  return listfac;
};

void displaylistf(facture *listfac){
  facture *p= listfac;
  while(p->nextf!= NULL){
    printf("\n------------------------------------------------------------------");
    printf("\n\tNumero de chambre: %d", p->numdc);
    printf("\n\tCode de client: %d", p->cc);
    printf("\n\tref de la chambre: %d", p->id);
    printf("\n\tNombre de nuitees: %d", p->numdn);
    printf("\n\tMontant: %0.2f", p->montant);
    p=p->nextf;
  }
}



void permutr(reservation *node1, reservation *node2){
  int tmprf;
  int tmpndr;
  char tmpddr[11];
  char tmpddds[11];
  int tmpndpc;
  int tmpc;
  int tmpch;
  float tmpprixt;

  tmprf= node1->ref;
  tmpndr= node1->nbrnr;
  strcpy(tmpddr, node1->ddr);
  strcpy(tmpddds, node1->ddds);
  tmpndpc= node1->nbrdpc;
  tmpc= node1->c;
  tmpch= node1->ndch;
  tmpprixt= node1->prixt;

  node1->ref =node2->ref;
  node1->nbrnr=node2->nbrnr;
  strcpy(node1->ddr, node2->ddr);
  strcpy(node1->ddds, node2->ddds);
  node1->nbrdpc= node2->nbrdpc;
  node1->c= node2->c;
  node1->ndch= node2->ndch;
  node1->prixt= node2->prixt;

  node2->ref =tmprf;
  node2->nbrnr= tmpndr;
  strcpy(node2->ddr, tmpddr);
  strcpy(node2->ddds, tmpddds);
  node2->nbrdpc= tmpndpc;
  node2->c= tmpc ;
  node2->ndch= tmpch;
  node2->prixt= tmpprixt;

}

reservation *listresertrim(reservation *listres){
  reservation *p= NULL;
  reservation *q= NULL;
  reservation *r= NULL;
  int per;
  do{
    per= 0;
    p= listres;
    while(p->nextr!= q){
      if (p->prixt > p->nextr->prixt){
        r= p->nextr;
        permutr(p,r);
        per=1;
      }
      p= p->nextr;
    }
    q= p;
  }while (per==1);
  return listres;
}

reservation *createlistresert1(reservation *listreser, reservation *listresert1, chambre *listchambre){
  reservation *lr= listreser;
  reservation *tmp1;
  reservation *p1;
  chambre *lch= NULL;
  lch= listchambre;;

  while(lr->nextr!= NULL){
    lch= accessndc(listchambre, lr->ndch);
    if (lch->type== 1){
      tmp1= malloc(sizeof(reservation));
      tmp1->ref=lr->ref;
      tmp1->nbrnr=lr->nbrnr;
      strcpy(tmp1->ddr, lr->ddr);
      strcpy(tmp1->ddds, lr->ddds);
      tmp1->nbrdpc=lr->nbrdpc;
      tmp1->c=lr->c;
      tmp1->ndch=lr->ndch;
      tmp1->prixt =lr->prixt;
      tmp1->nextr= NULL;
      if (listresert1== NULL){
        listresert1= tmp1;
      }else{
        p1= listresert1;
        while(p1->nextr!= NULL) p1= p1-> nextr;
        p1->nextr= tmp1;
      }
    }
  lr= lr->nextr;
}
listresert1 = listresertrim(listresert1);
return listresert1;
};

reservation *createlistresert2(reservation *listreser, reservation *listresert2, chambre *listchambre){
  reservation *lr= listreser;
  reservation *tmp2;
  reservation *p2;
  chambre *lch= NULL;
  lch= listchambre;;

  while(lr->nextr!= NULL){
    lch= accessndc(listchambre, lr->ndch);
    if (lch->type== 2){
      tmp2= malloc(sizeof(reservation));
      tmp2->ref=lr->ref;
      tmp2->nbrnr=lr->nbrnr;
      strcpy(tmp2->ddr, lr->ddr);
      strcpy(tmp2->ddds, lr->ddds);
      tmp2->nbrdpc=lr->nbrdpc;
      tmp2->c=lr->c;
      tmp2->ndch=lr->ndch;
      tmp2->prixt =lr->prixt;
      tmp2->nextr= NULL;
      if (listresert2== NULL){
        listresert2= tmp2;
      }else{
        p2= listresert2;
        while(p2->nextr!= NULL) p2= p2-> nextr;
        p2->nextr= tmp2;
      }
    }
  lr= lr->nextr;
}
listresert2 = listresertrim(listresert2);
return listresert2;
};

reservation *createlistresert3(reservation *listreser, reservation *listresert3, chambre *listchambre){
  reservation *lr= listreser;
  reservation *tmp3;
  reservation *p3;
  chambre *lch= NULL;
  lch= listchambre;;

  while(lr->nextr!= NULL){
    lch= accessndc(listchambre, lr->ndch);
    if (lch->type== 3){
      tmp3= malloc(sizeof(reservation));
      tmp3->ref=lr->ref;
      tmp3->nbrnr=lr->nbrnr;
      strcpy(tmp3->ddr, lr->ddr);
      strcpy(tmp3->ddds, lr->ddds);
      tmp3->nbrdpc=lr->nbrdpc;
      tmp3->c=lr->c;
      tmp3->ndch=lr->ndch;
      tmp3->prixt =lr->prixt;
      tmp3->nextr= NULL;
      if (listresert3== NULL){
        listresert3= tmp3;
      }else{
        p3= listresert3;
        while(p3->nextr!= NULL) p3= p3-> nextr;
        p3->nextr= tmp3;
      }
    }
  lr= lr->nextr;
}
listresert3 = listresertrim(listresert3);
return listresert3;
};



reservation *fusionlistresert(reservation *listresert1, reservation *listresert2, reservation *listresert3, reservation *listresert){
  reservation *p= NULL;
  listresert= listresert1;
  p= listresert;
  while (p->nextr!= NULL) p= p->nextr;
  p->nextr= listresert2;
  p= listresert;
  while (p->nextr!= NULL) p= p->nextr;
  p->nextr= listresert3;
  listresert= listresertrim(listresert);
  return listresert;
};


void andrptdc(reservation *listreser, chambre *listchambre){
  reservation *tmp= listreser;
  chambre *lch= NULL;
  int ty;
  int n=0;
  printf("Donnez le type:\n\t1: Simple.\n\t2: Double.\n\t3: Tripple\nLe type: ");
  scanf("%d", &ty);
  while(tmp->nextr!= NULL){
    lch= accessndc(listchambre, tmp->ndch);
    if (lch->type == ty){
      n++;
    }
    tmp= tmp->nextr;
  }
  printf("Le nombre de reservation de cet type de chambre est: %d", n);
};


void cda(reservation *listreser, chambre *listchambre){
  reservation *lr= NULL;
  chambre *lch= NULL;
  int rep;
  int ndc;
  float chiff=0;
  int s, saison;
  int j,m,a;
  char date[11];
  printf("Donnez la critique.1 pour: par chambre, 0 pour: par saison\n\tLa critique: ");
  scanf("%d", &rep);
  if (rep==1){
    printf("Donnez le numero de la chambre: ");
    scanf("%d", &ndc);
    lr= listreser;
    while(lr->nextr!= NULL){
      lch= accessndc(listchambre, lr->ndch);
      if (lch->nbrdc== ndc){
        chiff= chiff+ lr->prixt;
      }
      lr= lr->nextr;
    }
    printf("Le chiffre d'affaire de la chambre %d est %0.2f", ndc,chiff);
  }else{
    printf("Donnez la saison:\n\t1:Hiver.\n\t2:Printemps\n\t3:Ete\n\t4:Autumn.\nLa saison:");
    scanf("%d", &s);

    lr= listreser;
    while(lr->nextr!= NULL){
      strcpy(date, lr->ddds);
      lch= accessndc(listchambre, lr->ndch);
      j= 0; m= 0; a=0; saison= 0;
      j_m_a(date, &j, &m, &a, &saison);
      if (saison== s){
        chiff= chiff+ lr->prixt;
      }
      lr= lr->nextr;
    }
    switch(s){
      case 1:
        printf("Le chiffre d'affaire de l'hiver est %0.2f", chiff);
        break;
      case 2:
        printf("Le chiffre d'affaire du printemps est %0.2f",chiff);
        break;
      case 3:
        printf("Le chiffre d'affaire de l'ete est %0.2f",chiff);
        break;
      case 4:
        printf("Le chiffre d'affaire de l'autumn est %0.2f",chiff);
        break;
  }
  }
};


int largestpos(int arr[], int n){
int i;
  int pos;
int max = arr[0];
for (i = 1; i < n; i++)
if (arr[i] > max){
max = arr[i];
pos= i;}
    return pos;
}

void lpr(reservation *listreser, chambre *listchambre){
  reservation *lr= NULL;
  chambre *lch= NULL;
  int chm[9];
  int pos;
  memset(chm, 0, 10*sizeof(chm[0]));
  int j,m,a,saison;
  int t1, t2;
  char date[11];
  printf("Entrez la periode: ");
  printf("\tt1: ");
  scanf("%d",&t1);
  printf("\tt2: ");
  scanf("%d", &t2);

  lr= listreser;
  while(lr->nextr!= NULL){
    strcpy(date, lr->ddds);
    lch= accessndc(listchambre, lr->ndch);
    j= 0; m= 0; a=0; saison= 0;
    j_m_a(date, &j, &m, &a, &saison);
    if ((a>=t1) && (a<=t2)){
      chm[lch->nbrdc]= chm[lch->nbrdc] +1;
    }
    lr= lr->nextr;
  }
    pos= largestpos(chm,10);
    printf("Les chambres sont: \n\t1: %d avec %d reservation.", pos+1, chm[pos]);
    chm[pos]=0;
    pos=0;
    pos= largestpos(chm,10);
    printf("\n\t2: %d avec %d reservation.", pos+1, chm[pos]);
    chm[pos]=0;
    pos=0;
    pos= largestpos(chm,10);
    printf("\n\t3: %d avec %d reservation.", pos+1, chm[pos]);


};
void display1client(client *listclient){
    client *p= listclient;
    int co;
    printf("Donner le code client a afficher: ");
    scanf("%d", &co);

    while((p!= NULL) &&(p->code!= co)) p= p->nextc;

    if (p!= NULL){
    printf("\n");
    printf("code: %d\n", p->code);
    printf("\tNom: ");
    puts(p->nom);
    printf("\tPrenom: ");
    puts(p->prenom);
    printf("\tNumero d'identite; %d", p->NI);
    printf("\n\tNumero de telephone: %d", p->NT);
    printf("\n");
    }else{
    printf("Ce client n'existe pas!!!");
    }
};
void display1res(reservation *listreser){
  reservation *p= listreser;
  int re;

  printf("Donnez la refference de la reservation: ");
  scanf("%d", &re);
  while ((p!= NULL) &&(p->ref!= re)) p= p->nextr;

  if (p!= NULL){
      printf("\n");
      printf("ref: %d\n", p->ref);
      printf("\tNombre de nuits reservees: %d\n", p->nbrnr);
      printf("\tDate de reservation: ");
      puts(p->ddr);
      printf("\tDate de debut de sejour: ");
      puts(p->ddds);
      printf("\tNombre de personnes concenees: %d\n", p->nbrdpc);
      printf("\tCode client: %d\n", p->c);
      printf("\tNumero de chambre: %d\n", p->ndch);
      printf("\tLe prix total: %0.2f", p->prixt);
      printf("\n--------------------------------------------------");
     }
  };

