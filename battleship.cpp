#include <iostream>
#include <ctime>
#include <thread>
#include <cctype>
#define nmax 21  

// classe che definisce i colori come variabili grobali, dichiarati come variabili statiche
class Color {
public:
    static std::string violet;
    static std::string red;
    static std::string cyan;
    static std::string green;
    static std::string yellow;
    static std::string fucsia;
    static std::string gray;
    static std::string reset;
};

// assegno i valori alle variabili globali
std::string Color::violet = "\033[1;35m";
std::string Color::red = "\u001b[31m";
std::string Color::cyan = "\u001b[36m";
std::string Color::green = "\u001b[32m";
std::string Color::yellow = "\u001b[33m";
std::string Color::fucsia = "\u001b[35;1m";
std::string Color::gray = "\033[90m";
std::string Color::reset = "\u001b[0m";


// funzione che crea il delay, per rendere il codice pi� pulito
void delay(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

// genero una semplice intro che compare con effetto a cascata all'inizio 
void intro() {
    system("cls");
    std::cout << "\n\n\n\n\n" << Color::violet;
    delay(500);
    std::cout << "        _______  _______  _______  _______  ___      _______  _______  __   __  ___   _______  \n";
    delay(200);
    std::cout << "       |  _    ||   _   ||       ||       ||   |    |       ||       ||  | |  ||   | |       | \n";
    delay(500);
    std::cout << "       | |_|   ||  |_|  ||_     _||_     _||   |    |    ___||  _____||  |_|  ||   | |    _  | \n";
    delay(500);
    std::cout << "       |       ||       |  |   |    |   |  |   |    |   |___ | |_____ |       ||   | |   |_| | \n";
    delay(500);
    std::cout << "       |  _   | |       |  |   |    |   |  |   |___ |    ___||_____  ||       ||   | |    ___| \n";
    delay(500);
    std::cout << "       | |_|   ||   _   |  |   |    |   |  |       ||   |___  _____| ||   _   ||   | |   |     \n";
    delay(500);
    std::cout << "       |_______||__| |__|  |___|    |___|  |_______||_______||_______||__| |__||___| |___|     \n \n";
    delay(700);
    std::cout << Color::green << "        by Andrea Alfano\n\n\n";
    delay(700);
    std::cout << Color::reset << "                                  premere invio per continuare...  ";
    getchar();
}

// funzione che conta il numero di caselle in cui ci sono delle navi, serve per determinare l'avanzamento
int contCaselle(int matrice[nmax][nmax]) {
    int cont = 0;
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            if (matrice[i][j] == 1 or matrice[i][j] == 4)
                cont++;
        }
    }
    return cont;
}

// stampo il campo con le navi in base all'attacco eseguito
void campo(int matrice[nmax][nmax], int ndanni, int caselleOccupate) {
    system("cls");
    std::cout << Color::yellow << "      A B C D E F G H I J K L M N O P Q R S T\n" << Color::cyan << "      ---------------------------------------\n";
    for (int i = 0; i < 20; i++) {
        if (i < 10)
            std::cout << "  " << Color::yellow << i << Color::cyan << " | " << Color::reset;
        else
            std::cout << " " << Color::yellow << i << Color::cyan << " | " << Color::reset;
        for (int j = 0; j < 20; j++) {
            if (matrice[i][j] == 2)
                std::cout << Color::green << "# " << Color::reset;
            else if (matrice[i][j] == 5)
                std::cout << Color::yellow << "# " << Color::reset;
            else if (matrice[i][j] == 3)
                std::cout << Color::red << "# " << Color::reset;
            else {
                if (j % 2 == 0)
                    std::cout << Color::reset << "# ";
                else
                    std::cout << Color::gray << "# " << Color::reset;

            }
            //valore 0
        }
        if (i == 11)
            std::cout << Color::violet << "        avanzamento: " << Color::reset << (100 * ndanni) / caselleOccupate << "%";

        std::cout << "\n";
    }
    std::cout << "\n";
}

// funzione utilizzata solo per testare il gioco
void campod(int matrice[nmax][nmax], int ndanni, int caselleOccupate) {
    system("cls");
    std::cout << Color::yellow << "      A B C D E F G H I J K L M N O P Q R S T\n" << Color::cyan << "      ---------------------------------------\n";
    for (int i = 0; i < 20; i++) {
        if (i < 10)
            std::cout << "  " << Color::yellow << i << Color::cyan << " | " << Color::reset;
        else
            std::cout << " " << Color::yellow << i << Color::cyan << " | " << Color::reset;
        for (int j = 0; j < 20; j++) {
            if (matrice[i][j] == 2)
                std::cout << Color::green << matrice[i][j] << " " << Color::reset;
            else if (matrice[i][j] == 5)
                std::cout << Color::yellow << matrice[i][j] << " " << Color::reset;
            else if (matrice[i][j] == 3)
                std::cout << Color::red << matrice[i][j] << " " << Color::reset;
            else
                std::cout << matrice[i][j] << " ";
        }
        if (i == 11)
            std::cout << Color::violet << "        avanzamento: " << Color::reset << (100 * ndanni) / caselleOccupate << "%";
        std::cout << "\n";
    }
    std::cout << "\n";
}

// funzione che riempie il campo da battaglia con gli 0
void loadMatrix(int matrice[nmax][nmax]) {

    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 21; j++) {
            matrice[i][j] = 0;
        }
    }
}

//funzione che determina l'adiacenza delle navi piccole
bool adiacenti(int matrice[nmax][nmax], int righe, int colonne) {
    bool adiacenza = false;
    for (int i = righe - 1; i <= righe + 1; i++) {
        for (int j = colonne - 1; j <= colonne + 1; j++) {
            if (matrice[i][j] == 1 or matrice[i][j] == 4)
                adiacenza = true;
        }
    }
    return adiacenza;
}

// funzione che controlla l'adiacenza delle navi grandi
bool adiacenti2(int matrice[nmax][nmax], int righe, int colonne, int n) {
    bool adiacenza = false;
    for (int i = righe - n; i <= righe + n; i++) {
        for (int j = colonne - n; j <= colonne + n; j++) {
            if (matrice[i][j] == 1 or matrice[i][j] == 4 or matrice[i + 1][j + 1] == 1 or matrice[i + 1][j + 1] == 4)
                adiacenza = true;
        }
    }
    return adiacenza;
}

// funziona come la funzione 'adiacenti', solo che al posto di controllare solo le 8 caselle intorno alla cella interessata, lo fa per tutte le caselle della nave,
// la variabile 'a' va a stabilire se il controllo va fatto orizzontale o verticale.
bool adiacenti3(int matrice[nmax][nmax], int righe, int colonne, int n, int a) {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i <= 3; i++) {
            for (int j = 0; j <= 3; j++) {
                if (matrice[righe - 1 + i][colonne - 1 + j] == 1 or matrice[righe - 1 + i][colonne - 1 + j] == 4)
                    return true;
            }
        }
        if (a == 0)
            righe++;
        else if (a == 1)
            colonne++;
    }
    return false;
}


// funzione che trasforma i caratteri in numeri
int controlloCarattere(char col) {
    int colonna = int(col) - 65;
    if (colonna < 0 or colonna > 19)
        colonna = -1;
    return colonna;
}

// controlla se tutte le caselle di una nave grande sono state colpite
void controllaDistrutte(int matrice[nmax][nmax], int n) {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            if (matrice[i][j] == 5) {
                bool same = true;
                for (int k = 0; k < n - 1; k++) {
                    if (5 != matrice[i + k + 1][j])
                        same = false;
                }
                if (same == true) {
                    for (int k = 0; k < n; k++) {
                        matrice[i + k][j] = 2;
                    }
                }
                same = true;
                for (int k = 0; k < n - 1; k++) {
                    if (5 != matrice[i][j + k + 1])
                        same = false;
                }
                if (same == true) {
                    for (int k = 0; k < n; k++) {
                        matrice[i][j + k] = 2;
                    }
                }
            }
        }
    }
}

// funzione che esegue le mosse dell'utente e ritorna nel main il numro di mosse eseguite
int sparatoria(int matrice[nmax][nmax], int righe, int colonne, int n, int& ndanni, int giri) {
    double uccisioni = 0, mosse = 0;
    char col;
    bool debug = 1;

    /*
    0. CELLA VUOTA
    1. NAVE SINGOLA
    2. NAVE DISTRUTTA (green)
    3. FAIL (red)
    4. NAVE GRANDE
    5. NAVE GRANDE DANNEGGIATA (yellow)
    */

    do {
        do {
            if (debug) {
                campod(matrice, ndanni, giri); // campo scoperto, per il debug
            }
            else {
                campo(matrice, ndanni, giri); // campo coperto, per giocare
            }
            std::cout << "  inserisci le coordinate dell'attacco (es. 13F) " << Color::cyan << "--> " << Color::reset;
            std::cin >> righe;
            std::cin >> col;
            col = std::toupper(col);
            colonne = controlloCarattere(col);
        } while ((righe < 0 or righe > 19) or (colonne == -1));

        if (matrice[righe][colonne] == 1) {
            std::cout << Color::green << "\n  NAVE DISTRUTTA!" << Color::reset;
            matrice[righe][colonne] = 2;
            uccisioni += 1;
            ndanni++;
            mosse++;
        }
        else if (matrice[righe][colonne] == 4) {
            matrice[righe][colonne] = 5;
            controllaDistrutte(matrice, n);
            if (matrice[righe][colonne] == 5) {
                std::cout << Color::yellow << "\n  NAVE DANNEGGIATA..." << Color::reset;
            }
            else if (matrice[righe][colonne] == 2) {
                std::cout << Color::green << "\n  NAVE DISTRUTTA COMPLETAMENTE!" << Color::reset;
            }
            uccisioni += 1;
            ndanni++;
            mosse++;
        }
        else if (matrice[righe][colonne] == 3) {
            std::cout << Color::red << "\n  HAI GIA' COLPITO IN QUESTO PUNTO..." << Color::reset;
        }
        else if (matrice[righe][colonne] == 5)
            std::cout << Color::red << "\n  HAI GIA' COLPITO QUESTA PARTE DELLA NAVE..." << Color::reset;
        else if (matrice[righe][colonne] == 2)
            std::cout << Color::red << "\n  HAI GIA' DISTRUTTO QUESTA NAVE..." << Color::reset;
        else {
            std::cout << Color::red << "\n  HAI MANCATO LA NAVE..." << Color::reset;
            matrice[righe][colonne] = 3;
            mosse++;
        }
        if (matrice[righe][colonne] == 3 or matrice[righe][colonne] == 1) {
            if (adiacenti(matrice, righe, colonne) == true) {
                std::cout << Color::yellow << "  si percepisce del movimento" << Color::reset;
                for (int i = 0; i < 4; i++) {
                    std::cout << ".";
                    delay(300);
                }
            }
            delay(500);
        }
        else
            delay(1400);

    } while (uccisioni < giri);
    campo(matrice, ndanni, giri);
    return mosse;
}

// simulazione di una finta progressbar per la generazione della partita
void progressbar() {
    int r;
    do {
        r = rand() % 7;
    } while (r < 5);
    for (int i = 0; i < r; i++) {
        system("cls");
        std::cout << "\n\n\n\n\n\n\n                 Generazione partita in corso..." << Color::yellow << "  / \n\n" << Color::reset;
        delay(400);
        system("cls");
        std::cout << "\n\n\n\n\n\n\n                 Generazione partita in corso..." << Color::yellow << "  - \n\n" << Color::reset;
        delay(400);
        system("cls");
        std::cout << "\n\n\n\n\n\n\n                 Generazione partita in corso..." << Color::yellow << "  | \n\n" << Color::reset;
        delay(400);
    }
    delay(500);
    system("cls");
    std::cout << Color::green << "\n\n\n\n\n\n\n\n\n\n                 Generazione partita completata! \n\n" << Color::reset;;
    delay(1500);
}

/*------------------------------------------------------
MAIN - MAIN - MAIN - MAIN - MAIN - MAIN - MAIN - MAIN -
-------------------------------------------------------*/

int main() {
    int matrice[nmax][nmax], righe, colonne, mosse, record, contgiri = 0, ndanni, giri = 0, n;
    double uccisioni;
    bool controlloNavi, lap1, collision;
    char ancora;
    srand(time(NULL));
    intro();
    do {
        //assegnazioni start
        uccisioni = 0;
        ndanni = 0;
        giri = 0;
        lap1 = true;

        // generazione del campo
        loadMatrix(matrice);

        //selezione della grandezza delle navi
        do {
            system("cls");
            std::cout << "\n\n\n\n\n                               Inserisci la grandezza delle navi grandi ( <= 5 ): ",
                std::cin >> n;
        } while (n <= 0 or n > 5);

        system("cls");
        delay(400);
        progressbar();

        // genero 3 navi grandi nel campo
        int ship = 0;
        int a;
        do {
            do {
                do {
                    righe = rand() % 20;
                    colonne = rand() % 20;
                    controlloNavi = adiacenti(matrice, righe, colonne);
                } while (controlloNavi == true);
                a = rand() % 2;
                controlloNavi = false;
                switch (a) {
                case 0:
                    if (righe > 19 - n)
                        for (int i = 1; i <= n; i++) {
                            righe -= 1;
                            if (controlloNavi == false)
                                controlloNavi = adiacenti2(matrice, righe, colonne, n);
                        }
                    else
                        for (int i = 1; i <= n; i++) {
                            righe += 1;
                            if (controlloNavi == false)
                                controlloNavi = adiacenti2(matrice, righe, colonne, n);
                        }
                    break;
                case 1:
                    if (colonne > 19 - n)
                        for (int i = 1; i <= n; i++) {
                            colonne -= 1;
                            if (controlloNavi == false)
                                controlloNavi = adiacenti2(matrice, righe, colonne, n);
                        }
                    else
                        for (int i = 1; i <= n; i++) {
                            colonne += 1;
                            if (controlloNavi == false)
                                controlloNavi = adiacenti2(matrice, righe, colonne, n);
                        }
                    break;
                }
            } while (controlloNavi == true);
            switch (a) {
            case 0:

                for (int i = 0; i < n; i++) {
                    collision = adiacenti3(matrice, righe, colonne, i, a);
                    if (collision) {
                        break;
                    }
                }
                if (collision) break;

                if (righe > 19 - n)
                    for (int i = 1; i <= n; i++) {
                        righe -= 1;
                        matrice[righe][colonne] = 4;
                    }
                else
                    for (int i = 1; i <= n; i++) {
                        righe += 1;
                        matrice[righe][colonne] = 4;
                    }
                break;
            case 1:

                for (int i = 0; i < n; i++) {
                    collision = adiacenti3(matrice, righe, colonne, i, a);
                    if (collision) {
                        break;
                    }
                }
                if (collision) break;
                if (colonne > 19 - n)
                    for (int i = 1; i <= n; i++) {
                        colonne -= 1;
                        matrice[righe][colonne] = 4;
                    }
                else
                    for (int i = 1; i <= n; i++) {
                        colonne += 1;
                        matrice[righe][colonne] = 4;
                    }
                break;
            }
            ship++;
        } while (ship != 3);

        // genero 3 navi (1) nel campo
        for (int i = 0; i < 3; i++) {
            do {
                righe = rand() % 20;
                colonne = rand() % 20;
                controlloNavi = adiacenti(matrice, righe, colonne);
            } while (controlloNavi == true);
            matrice[righe][colonne] = 1;
        }
        if (lap1) {
            giri = contCaselle(matrice);
            lap1 = false;
        }

        // entro all'interno della funzione che dice all'utente di fare le mosse
        mosse = sparatoria(matrice, righe, colonne, n, ndanni, giri);

        if (contgiri == 0)
            record = mosse;
        else if (mosse < record)
            record = mosse;
        contgiri++;
        std::cout << Color::cyan << "\n  HAI DISTRUTTO TUTTE LE NAVI!!!" << Color::reset << "     numero di mosse eseguite : " << mosse;
        std::cout << Color::fucsia << "\n\n        RECORD " << Color::cyan << "--> " << Color::reset << record;
        std::cout << "\n";
        delay(2500);
        std::cout << Color::reset << "\n                                 premere invio per continuare...  ";
        getchar();
        getchar();

        // utilizzo il do-while per chiedere all'utente se vuole giocare ancora 
        do {
            system("cls");
            std::cout << "\n\n\n\n\n                                 Vuoi giocare ancora? (s / n) -->  ";
            std::cin >> ancora;
        } while (ancora != 's' and ancora != 'n' and ancora != 'S' and ancora != 'N');
    } while (ancora == 's' or ancora == 'S');
    system("cls");
    return 0;
}
