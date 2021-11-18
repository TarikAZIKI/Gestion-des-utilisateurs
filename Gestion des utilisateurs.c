
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/* 
#########################################################################################################################
#                                               LES STRUCTURES                                                          #
#########################################################################################################################
*/
typedef struct{
    int trouve;
    int indice;
}dvar;

typedef struct{
    int admin;
    char user[20];
    char pass[20];
    
}info;



/* 
#########################################################################################################################
#                                           DECLARATION DES VARIABLES / STRUCTURES / FONCTIONS                          #
#########################################################################################################################
*/
dvar D;
info I[100];
int u=0;


/* 
#########################################################################################################################
#                                                       LES FONCTIONS                                                   #
#########################################################################################################################
*/
int loginsys(char ncompte[],char motdp[], int logged)
{   
    int i;
    logged = 0;
    for(i=0;i<20;i++)
    {
        if((strcmp(I[i].user,ncompte)) == 0 && (strcmp(I[i].pass,motdp))== 0 && I[i].admin == 1)
        {
            logged = 2;
            i = 31;
        }
        if((strcmp(I[i].user,ncompte)) == 0 && (strcmp(I[i].pass,motdp))== 0)
        {
            logged = 1;
            i=31;
            
        }
    }
    return logged;
    
}

int regist_user(char ncompte[], char motdp[],int registered)
{
    strcpy(I[u].user,ncompte);
    strcpy(I[u].pass,motdp);
    // verification que le tableau a bien ete copie dans la structure
    if((strcmp(I[u].user,ncompte)) == 0 && (strcmp(I[u].pass,motdp)) == 0)
    {
        registered = 1;
        I[0].admin = 1;
    }
    
    return registered;
}
int supp_user(char ncompte[], char motdp[], int trouve)
{
    int i,j;
    for(i=0,trouve = 0;i<u && trouve == 0;i++)
    {
        if(strcmp(ncompte,I[i].user) == 0)
        {
            trouve = 1;
            for(j=i;j<u;j++)
            {
                I[j] = I[j+1];
                u--;
            }
        }
    }
    return trouve;
}
int ajout_user(char ncompte[], char motdp[], int ajout)
{   
    int i;
    for(i=0;i<u;i++)
    {
        if(strcmp(ncompte,I[i].user) == 0)
        {
            i=20;
            ajout = 0;
        }
        else
        {
            ajout = 1;
        }
    }
    if(ajout)
    {
        strcpy(I[u].user,ncompte);
        strcpy(I[u].pass,motdp);
    }
    return ajout;

}

dvar modif_user(char ncompte[],char motdp[])
{
    int i,j;
    for(i=0,D.trouve = 0;i<u && D.trouve == 0;i++)
    {
            if(strcmp(ncompte,I[i].user) == 0)
            {
                D.trouve = 1;
                D.indice = i;
            }
    }
    return D;
}


main()
{
    int choix,n,i;
    char find_user[10];
    int logged = 0, registered = 0,ajout = 0,trouve = 0;
    char ncompte[20],motdp[10];

// ######################################################################## REGISTER ###########################################################

enreg : printf("#######################################################################################################################\n");
        printf("                    | - Enregistrement d'un utilisateur - |\n\n");
        printf("| - Entrer L'Username souhaite : ");
        fflush(stdin);
        scanf("%s",ncompte);
        printf("| - Entrer le Mot de passe souhaite : ");
        scanf("%s",motdp);
        registered = regist_user(ncompte,motdp,registered);
        if(registered == 1)
        {
            printf("\n \t \t \t -------------------------------------------------");
            printf("\n \t \t \t - UTILISATEUR CREE AVEC SUCCESS, REDIRECTION.. !\n");
            printf("\t \t \t    -------------------------------------------------\n\n");
            printf("\t \t \t            | - Vous etes ADMIN ! - |");
            u++;
            sleep(1);
            system("cls");      
        }
        else
        {
            printf("Erreur 404");
            main();
        }
        
// ########################################################################### LOGIN ######################################################

login :  printf("#######################################################################################################################\n");
        printf("                        | - Login - |\n");
        printf("| - Username : ");
        fflush(stdin);
        scanf("%s",ncompte);
        printf("| - Mot de passe : ");
        scanf("%s",motdp);      
        logged = loginsys(ncompte,motdp,logged);
        if (logged >= 1)
        {
            printf("\n \t \t \t -----------------------------------------------------");
            printf("\n \t \t \t - UTILISATEUR CONNECTE AVEC SUCCESS, REDIRECTION.. !\n");
            printf("\t \t \t    -----------------------------------------------------\n\n"); 
            sleep(2);
            system("CLS");          
        }
        else
        {
            printf("\n \t \t \t -------------------------------------------");
            printf("\n \t \t \t - NOM DU COMPTE OU MOT DE PASSE INCORRECT -\n");
            printf("\t \t \t    -------------------------------------------\n\n"); 
            sleep(1);
            system("cls");
            goto login;
        }
        // ############################################################# MENU ADMIN ##############################################################
        while(logged == 2)
        {
            printf("                    # Bienvenue dans votre espace ADMIN ! #\n");
            printf("\t\t        | - [1]  - Ajouter un utilisateur          -| \n");
            printf("\t\t        | - [2]  - Changer le mot de passe         -|\n");
            printf("\t\t        | - [3]  - Suppression utilisateur             -|\n");
            printf("\t\t        | - [4]  - Afficher la liste des utilisateurs  -|\n");
            printf("\t\t        | - [5]  - Se deconnecter              -|\n");

            printf("\t\t\t\t\t  - Votre choix : ");
            scanf("%d",&choix);
            
            switch(choix)
            {
                case 1:
                    system("cls");
                    printf("------------------------------------------------------------------------------------------------------------------------\n");
                    printf("-                   AJOUT D'UTILISATEUR                                 -\n");
                    printf("------------------------------------------------------------------------------------------------------------------------\n\n");
                    printf("=> Username souhaite : ");
                    scanf("%s",&ncompte);
                    printf("=> Password souhaite : ");
                    scanf("%s",&motdp);
                    ajout = ajout_user(ncompte,motdp,ajout);
                    if(ajout)
                    {
                        printf("\n \t \t \t --------------------------------------");
                        printf("\n \t \t \t - UTILISATEUR %s AJOUTE AVEC SUCCESS -\n",ncompte);
                        printf("\t \t \t    --------------------------------------\n\n");
                        u++;
                        sleep(1);
                    }
                    else
                    {
                        printf("\n \t \t \t     --------------------");
                        printf("\n \t \t \t     - ERREUR D'AJOUT ! -\n");
                        printf("\t \t \t        --------------------\n\n");
                        sleep(1);
                    }
                    system("cls");
                    continue;
                    break;
                case 2:
                    printf("------------------------------------------------------------------------------------------------------------------------\n");
                    printf("-                   MODIFICATION DES UTILISATEURS                                   -\n");
                    printf("------------------------------------------------------------------------------------------------------------------------\n\n");
                    printf("=> L'utilisateur a modifie :");
                    scanf("%s",ncompte);
                    D = modif_user(ncompte,motdp);
                    if(D.trouve == 1 )
                    {
                        printf("=> Reinserer le mot de passe : ");
                        fflush(stdin);
                        gets(I[D.indice].pass);
                        printf("\n \t \t \t     --------------------------------------------------");
                        printf("\n \t \t \t     - MODIFICATION D'UTILISATEUR [%s]AVEC SUCCESS' !-\n",ncompte);
                        printf("\t \t \t        --------------------------------------------------\n\n");
                        sleep(1);                       
                        system("cls");
                    }
                    else
                    {
                        printf("\n \t \t \t ----------------------------");
                        printf("\n \t \t \t - ERREUR DE MODIFICATION ! -\n");
                        printf("\t \t \t    ----------------------------\n\n");
                        sleep(1);
                        system("cls");
                    }
                    continue;
                    break;
                case 3:
                    system("cls");
                    printf("------------------------------------------------------------------------------------------------------------------------\n");
                    printf("-                   SUPPRESSION DES UTILISATEURS                                    -\n");
                    printf("------------------------------------------------------------------------------------------------------------------------\n\n");
                    printf("=> L'utilisateur a supprimer : ");
                    scanf("%s",ncompte);
                    trouve = supp_user(ncompte,motdp,trouve);
                    if(trouve)
                    {
                        printf("\n \t \t \t     -------------------------------------------");
                        printf("\n \t \t \t     - SUPPRESION d'utilisateur [%s] avec success !-\n",ncompte);
                        printf("\t \t \t        -------------------------------------------\n\n");
                        system("cls");
                        sleep(1);
                    }
                    else
                    {
                        printf("\n \t \t \t --------------------------");
                        printf("\n \t \t \t - ERREUR DE SUPPRESION ! -\n");
                        printf("\t \t \t    --------------------------\n\n");
                        sleep(1);
                        system("cls");
                    }

                    continue;
                    break;
                    
                case 4:
                    system("cls");
                    printf("------------------------------------------------------------------------------------------------------------------------\n");
                    printf("-                   AFFICHAGE DES UTILISATEURS                                  -\n");
                    printf("------------------------------------------------------------------------------------------------------------------------\n\n");
                    printf("                    [UTILISATEUR] [ADMIN]\n\n");
                    for(i=0;i<u;i++)
                    {
                        printf("                    [%s] [%d]\n",I[i].user,I[i].admin);
                    }
                    printf("------------------------------------------------------------------------------------------------------------------------\n\n");
                    system("pause");system("cls");
                    continue;
                    break;
                case 5:
                    logged = 0;
                    system("cls");
                    goto login;
                    break;
                    
            }
        }
    
        // ############################################################# MENU NORMAL ##############################################################

        while(logged)
        {
            printf("                # Bienvenue dans votre espace %s ! #\n",ncompte);
            printf("\t\t        | - [1]  - Changer votre mot de passe          -|\n");
            printf("\t\t        | - [2]  - Se deconnecter              -|\n");
            printf("\t\t\t\t\t  - Votre choix : ");
            scanf("%d",&choix);
            switch(choix)
            {
                case 1:
                    printf("------------------------------------------------------------------------------------------------------------------------\n");
                    printf("-                   MODIFICATION DE VOTRE MOT DE PASSE                                  -\n");
                    printf("------------------------------------------------------------------------------------------------------------------------\n\n");
                    printf("=> Inserer votre actuel mot de passe :");
                    scanf("%s",motdp);
                    D = modif_user(ncompte,motdp);
                    if(D.trouve == 1 )
                    {
                        printf("=> Inserer votre nouveau mot de passe :");
                        fflush(stdin);
                        gets(I[D.indice].pass);                 
                        printf("\n \t \t \t     --------------------------------------------------");
                        printf("\n \t \t \t     - MODIFICATION D'UTILISATEUR [%s] AVEC SUCCESS' !-\n",ncompte);
                        printf("\t \t \t        --------------------------------------------------\n\n");
                        system("cls");
                        sleep(1);
                    }
                    else
                    {
                        printf("\n \t \t \t ----------------------------");
                        printf("\n \t \t \t - ERREUR DE MODIFICATION ! -\n");
                        printf("\t \t \t    ----------------------------\n\n");
                        sleep(1);
                        system("cls");
                    }
                    continue;
                    break;  
                case 2:             
                    logged = 0;
                    system("cls");
                    goto login;
                    break;
            }
        }

        
    
}
