#ifndef HOTEL_LLC_BIBLIO_H_INCLUDED
#define HOTEL_LLC_BIBLIO_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


//Les structures utilisees:------------------------------------------------------------------------
typedef struct client{
  /*1*/ int code;
  /*2*/ char nom[20];
  /*3*/ char prenom[20];
  /*4*/ int NI; //NI= Numero d'identit�.
  /*5*/ int NT; //NT= numero de telephon.
  /*6*/ struct client *nextc;
}client;

typedef struct reservation{
    int ref; //La r�f�rence (unique).
    int nbrnr; //Le nombre de nuit�es  r�serv�es.
    char ddr[11]; //La date de r�servation.
    char ddds[11]; //La date du d�but de s�jour.
    int nbrdpc; //Le nombre de  personnes concern�es.
    int c; //Le code d'un client.
    int ndch; //Le numero de chambre;
    float prixt;
    struct reservation *nextr;
}reservation;
/*Une r�servation se caract�rise par une r�f�rence (unique), par le nombre de nuit�es  r�serv�es, par la
 date de r�servation,par la date du d�but de s�jour ainsi que par le nombre de  personnes concern�es*/


typedef struct chambre{
  int nbrdc; //le numero de chambre.
  int type; // 1 pour simple; 2 pour double; 3 pour triple.
  int prix; //Le prix de base d'une chambre selon sa type.
  int TV; // 0 pour n'est pas disponible; 1 pour le contraire.
  int etat; //1 pour occup�e; 0 pour le contraire.
  struct chambre *nextch;
}chambre;
/*Une chambre de l�h�tel se caract�rise par un num�ro de chambre, par son type (simple, double,
triple), par son prix, par la disponibilit� d�une TV ou non et par son �tat actue*/


typedef struct facture{
  int numdc; //Le numero de chambre.
  int cc; //Le code du client.
  int id; //L'identifiant de la reservation (ou la ref).
  int numdn; //Le nombre de nuit�es.
  float montant; //Le montant ou le prixt qui et le prix total afin d'une reservation.
  struct facture *nextf;
}facture;
/*Une facture d'un hotel est caract�ris� par: (num�ro de chambre,
code du client, identifiant de la r�servation,  nombre de nuit�es, montant)*/


//Les tetes des fonctions:-----------------------------------------------------------------------
//1-Gestion de client:
client *creerlisteclient(client *listclient, FILE *fc); //Qui cree la liste de client et retourne la tete de la liste a partir d'un fichier.
client *ajouterclient(client *listclient, FILE *fc); //Qui ajoute un client.
client *modifierclient(client *listclient, FILE *fc); //Qui modifie un client.
client *supprimerclient(client *listclient, FILE *fc); //Qui supprime un client.
client *accesscode(client *listclient, int c); //Retourne le maillon de client du code donn�.
void displaylistc(client *listclient); //Qui affiche la liste des clients.
void display1client(client *listclient);//Qui affiche un client selon son code.
void display1res(reservation *listreser);//Qui affiche une reservation selon la refference.
//-----------------------------------------------------------------------------------------------



//2-Gestion de r�servation:----------------------------------------------------------------------
reservation *createlistres(reservation *listreser, FILE *f3);//Qui cree la liste de reservation et retourne la tete de la liste a partir d'un fichier.
reservation *ajouterres(reservation *listreser, client *listclient, chambre *listechambre,FILE *f1, FILE *f3); //Qui ajoute une reservation.
reservation *modifierres(reservation *listreser, FILE *fr);//qui modifier une reservation.
reservation *annulerres(reservation *listreser, FILE *fr);  //Qui annule une reservation.
float calculprix(int ndn, int saison, int tc); //Qui calcule le prix d'une reservation.
void dateda(char dateoftoday[20]); //Qui donne la date d'aujourd'hui en chaine de caracteres.
void displaylistr(reservation *listreser);
//-----------------------------------------------------------------------------------------------



//3-Gestion de chambre:
chambre *createlistch(chambre *listchambre, FILE *f3); //Qui cree la liste de chambre et retourne la tete de la liste a partir d'un fichier.
chambre *libchambre(chambre *listchambre, int ndc); //Qui permet de liberer une chambre.
chambre *accessndc(chambre *listchambre, int ndc); //Qui retourne le pointeur qui pointe vers le maillon dont le numero de chambre entr�.

//4-Les autres fonctions demand�es:-----------------------------------------------------------------------------------------------------
void ahrc(reservation *listreser); //Qui affiche l'historique d'un client a partir de son code.
void ahrch(reservation *listreser); //Qui affiche l'historique d'une chambre avant une date donn�e.
void j_m_a(char date[11], int *j, int *m, int *a, int *saison);// Qui recupere  le nombre de jour le mois l'ann�e � partir une date donn�e en chaine de caracteres.
client *ctt(client *listctt, reservation *listreser, client *listclient, chambre *listechambre); //Qui retourne la liste de clients occupant le meme type et qui contient TV.
void prch(reservation *listreser, chambre *listchambre);//Calculer le pourcentage de r�servation d'une chambre pendant l�ann�e en cours.
void permutr(reservation *node1, reservation *node2); //Qui permut entre deux maillons de structure reservation;
reservation *listresertrim(reservation *listres); //Qui permet de trier une liste de reservation selon le montant
reservation *createlistresert1(reservation *listreser, reservation *listresert1, chambre *listchambre);//Qui retourne toutes les reseervation de type Simple
reservation *createlistresert2(reservation *listreser, reservation *listresert2, chambre *listchambre);//Qui retourne toutes les reseervation de type Double
reservation *createlistresert3(reservation *listreser, reservation *listresert3, chambre *listchambre); //Qui retourne toutes les reseervation de type Triple
reservation* fusionlistresert(reservation *listresert1, reservation *listresert2, reservation *listresert3, reservation *listresert); //Qui permet de fusionner trois listes de type reservation.
void andrptdc(reservation *listreser, chambre *listchambre); //Qui permet de calculer le nombre de reservation d'une chalbre de type donn�.
void cda(reservation *listreser, chambre *listchambre); //Qui calcule le chiffre d'affaire.
void lpr(reservation *listreser, chambre *listchambre); // Qui calcule les chambres les plus reservees entre deux periodes donn�es.
int largestpos(int arr[], int n); //Qui retourne la position de la grande valeur dans un tableaux d'entiers.
//-------------------------------------------------------------------------------------------------------------------------------------



//5-La gestion des factures:-----------------------------------------------------------------------------------------------------------
facture *createlistfac(facture *listfac, reservation *listreser); //Qui retourne la liste de factures.
void permutf(facture *node1, facture*node2); //Qui permute entre deux maillons de type facture.
facture *listfactric(facture *listfac); //Qui permet de trier une liste de type facture.
void displaylistf(facture *listfac); //Qui affiche une liste de type facture.
//-------------------------------------------------------------------------------------------------------------------------------------






#endif // HOTEL_LLC_BIBLIO_H_INCLUDED
