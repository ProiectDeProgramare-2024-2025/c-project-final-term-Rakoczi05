#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITLE 100
#define MAX_DESC 300

#define GREEN "\033[0;32m"
#define BLUE "\033[0;34m"
#define RESET "\033[0m"


typedef struct {
    char title[MAX_TITLE];
    char description[MAX_DESC];
    int duration;
} Film;

void adauga_film(const char *filename) {
    FILE *file = fopen(filename, "a");
    if (!file) {
        printf("Eroare la deschiderea fisierului!\n");
        return;
    }

    Film film;

    printf("Introdu titlul filmului: ");
    fgets(film.title, MAX_TITLE, stdin);
    film.title[strcspn(film.title, "\n")] = 0;

    printf("Introdu descrierea filmului: ");
    fgets(film.description, MAX_DESC, stdin);
    film.description[strcspn(film.description, "\n")] = 0;

    printf("Introdu durata filmului (in minute): ");
    scanf("%d", &film.duration);
    getchar();

    fprintf(file, "%s|%s|%d\n", film.title, film.description, film.duration);
    fclose(file);
    printf("Film adaugat cu succes!\n");
}

void sterge_film(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Eroare la deschiderea fisierului!\n");
        return;
    }

    char temp[] = "temp.txt";
    FILE *temp_file = fopen(temp, "w");

    char search_title[MAX_TITLE];
    printf("Introdu titlul filmului de sters: ");
    fgets(search_title, MAX_TITLE, stdin);
    search_title[strcspn(search_title, "\n")] = 0;

    char line[500];
    int found = 0;

    while (fgets(line, sizeof(line), file)) {
        if (strncasecmp(line, search_title, strlen(search_title)) == 0) {
            found = 1;
            continue;
        }
        fprintf(temp_file, "%s", line);
    }

    fclose(file);
    fclose(temp_file);

    remove(filename);
    rename(temp, filename);

    if (found)
        printf("Film sters cu succes!\n");
    else
        printf("Film inexistent in lista!\n");
        
    
    printf("\nApasa Enter pentru a continua...");
    getchar();
    system("clear");
}


void cauta_film(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Eroare la deschiderea fisierului!\n");
        return;
    }

    char search_title[MAX_TITLE];
    printf("Introdu titlul filmului de cautat: ");
    fgets(search_title, MAX_TITLE, stdin);
    search_title[strcspn(search_title, "\n")] = 0;

    char line[500];
    int found = 0;

    while (fgets(line, sizeof(line), file)) {
        char title[MAX_TITLE], description[MAX_DESC];
        int duration;
        sscanf(line, "%[^|]|%[^|]|%d", title, description, &duration);

        if (strcasecmp(title, search_title) == 0) {
            printf(GREEN "%s - %s " BLUE "(%d min)\n" RESET, title, description, duration);
            found = 1;
        }
    }

    if (!found) {
        printf("Film inexistent in lista!\n");
    }

    fclose(file);
    
    printf("\nApasa Enter pentru a continua...");
    getchar();
    system("clear");
}

void afisare_film(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Eroare la deschiderea fisierului!\n");
        return;
    }

    char line[500];
    printf("Lista de filme:\n");
    while (fgets(line, sizeof(line), file)) {
        char title[MAX_TITLE], description[MAX_DESC];
        int duration;
        sscanf(line, "%[^|]|%[^|]|%d", title, description, &duration);
        printf(GREEN "%s - %s " BLUE "(%d min)\n" RESET, title, description, duration);
    }

    fclose(file);

    printf("\nApasa Enter pentru a continua...");
    getchar();
    system("clear");
}

int main()
{
    int choice;

    do
    {
        printf("\n");
        printf("1.Adauga film in Watched \n");
        printf("2.Adauga film in To Watch \n");
        printf("3.Sterge film din Watched \n");
        printf("4.Sterge film din To Watch \n");
        printf("5.Cauta film in Watched \n");
        printf("6.Cauta film in To Watch \n");
        printf("7.Afiseaza lista Watched \n");
        printf("8.Afiseaza lista To Watch \n");
        printf("9.Iesire \n");
        printf("\n");
        printf("Alege o optiune: ");
        scanf("%d", &choice);
        getchar();

        system("clear");
        
        switch (choice)
        {
        case 1:
            printf("Ai ales sa adaugi un film in Watched.\n");
            adauga_film("watched.txt");
            break;
        case 2:
            printf("Ai ales sa adaugi un film in To Watch.\n");
            adauga_film("towatch.txt");
            break;
        case 3:
            printf("Ai ales sa stergi un film din Watched.\n");
            break;
        case 4:
            printf("Ai ales sa stergi un film din To Watch.\n");
            break;
        case 5:
            printf("Ai ales sa cauti un film in Watched.\n");
            break;
        case 6:
            printf("Ai ales sa cauti un film in To Watch.\n");
            break;
        case 7:
            printf("Afiseaza lista Watched.\n");
            afisare_film("watched.txt");
            break;
        case 8:
            printf("Afiseaza lista to Watch.\n");
            afisare_film("towatch.txt");
            break;
        case 9:
            printf("Iesire.\n");
            break;
        
        default:
            printf("Optiune invalida! \n");
            break;
        }
    } while (choice != 9);
    
    return 0;
}
