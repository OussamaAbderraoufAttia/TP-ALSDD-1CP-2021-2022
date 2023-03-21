#include "HOTEL_LLC_BIBLIO.h"



int main(void)
{


  FILE *fc= fopen("client.txt", "r+");
  FILE *fr= fopen("reservation.txt", "r+");
  FILE *fch= fopen("chambre.txt", "r+");

  client *listc= NULL;
  reservation *listr= NULL;
  reservation *listrt1= NULL;
  reservation *listrt2= NULL;
  reservation *listrt3= NULL;
  reservation *listrtt= NULL;
  chambre *listch= NULL;
  client *listctt= NULL;
  facture *listf= NULL;
  listc= creerlisteclient(listc, fc);
  listr= createlistres(listr, fr);
  listch= createlistch(listch, fch);


  int rep=1;
  while(rep!= 0){
  printf("\n-----------------------------------------------------------------------------------------------------------------------------------------\n\t\t\t\t\t\tGestion de reservation hoteliere \n\t\t\t\trealisee par: Attia Oussama Abderraouf et Seddiki Wassim.\n----------------------------------------------------------------------------------------------------------------------------------------------\n");
  printf("\n-------------------------------------------------------GESTION DE CLIENT----------------------------------------------------------------------");
  printf("\n\t1-Ajouter un client.\n\t2-Modifier un client.\n\t3-Supprimer un client.\n\t4-Afficher la liste de clients.\n\t5-Afficher un client.\n\t6-Donner la liste des client occupant une chambre de meme type.");
  printf("\n----------------------------------------------------------------------------------------------------------------------------------------------");
  printf("\n------------------------------------------------------GESTION DE RESERVATION------------------------------------------------------------------");
  printf("\n\t7-Ajouter une reservation\n\t8-Modifier une reservation.\n\t9-Annuler une reservation.\n\t10-Afficher la liste des reservations.\n\t11-Afficher une reservation.\n\t12-Afficher l'historique de reservation d'un client.\n\t13-Creer les listes de reservations par type de chambre.\n\t14-Fusionner les listes de reservations par type de chambre.");
  printf("\n----------------------------------------------------------------------------------------------------------------------------------------------");
  printf("\n------------------------------------------------------GESTION DE CHAMBRE----------------------------------------------------------------------");
  printf("\n\t15-Afficher l'historique d'une chambre (toutes les reservations precedente a une date donnee).\n\t16-Afficher le nombre total des reservations par type de chambre.\n\t17-Calculer chiffre d'affaire.\n\t18-Les trois chambres les plus reservees entre deux periodes donnees.");
  printf("\n----------------------------------------------------------------------------------------------------------------------------------------------");
  printf("\n------------------------------------------------------GESTION DE FACTURE----------------------------------------------------------------------");
  printf("\n\t19-Creer la liste des factures.");
  printf("\n----------------------------------------------------------------------------------------------------------------------------------------------");
  printf("\n\t\t\t\t\t\t\t0-Quitter.");
  printf("\nAction:  ");
  scanf("%d", &rep);
  switch(rep){
    case 1: listc= ajouterclient(listc, fc); displaylistc(listc); break;
    case 2: listc= modifierclient(listc, fc); displaylistc(listc); break;
    case 3: listc= supprimerclient(listc, fc); displaylistc(listc); break;
    case 4: displaylistc(listc); break;
    case 5: display1client(listc); break;
    case 6: listctt= ctt(listctt, listr, listc, listch); displaylistc(listc); break;
    case 7: listr= ajouterres(listr,listc, listch, fc, fr); displaylistr(listr); break;
    case 8: listr= modifierres(listr, fr); displaylistr(listr); break;
    case 9: listr= annulerres(listr, fr); break;
    case 10: displaylistr(listr);break;
    case 11: display1res(listr);break;
    case 12: ahrc(listr); break;
    case 13: listrt1= createlistresert1(listr, listrt1, listch); listrt2= createlistresert2(listr, listrt2, listch); listrt3= createlistresert3(listr, listrt3, listch); printf("\ntype simple: \n");
             displaylistr(listrt1); printf("\ntype double: \n"); displaylistr(listrt2); printf("\ntype tripple: \n"); displaylistr(listrt3); break;
    case 14: fusionlistresert(listrt1, listrt2, listrt3, listrtt); displaylistr(listrtt); break;
    case 15: ahrch(listr); break;
    case 16: andrptdc(listr, listch); break;
    case 17: cda(listr, listch);  break;
    case 18: lpr(listr, listch); break;
    case 19: listf= createlistfac(listf, listr); displaylistf(listf); break;

  }
}






fclose(fr);
  fclose(fc);
  fclose(fch);

}
