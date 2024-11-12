#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

using namespace std;

/* Truc du prof */

/* Lit une ligne du fichier d'entrée */
string litUneString (){
    string uneChaine;
    while (true){
        getline (cin, uneChaine);
        if ((!cin) || (uneChaine.substr(0,2) != "//")) break;
    }
    return uneChaine;
}

/* Converti en entier */
int litUnEntier() {
    string uneChaine;
    while (true) {
        getline(cin, uneChaine);

        if (uneChaine.empty()) continue;
        if (uneChaine.substr(0, 2) == "//") continue;

        /* si il y a une erreur ne pas kill et afficher */
        // ne peux pas convertir "zfer" ou "3ef" en int mais "3423" oui
        try {
            return stoi(uneChaine);
        } catch (const invalid_argument& e) {
            continue;
        }
    }
}

struct candidat {
    string nom;
    int voix = 0;
};

bool comparer(candidat a, candidat b) {
    return a.voix > b.voix;  // Retourner true si a est plus grand que b
}

int main(int argc, char* argv[]) {
    if( argc != 1) {
        cerr << "attendu: ./<nom executable> < <fichier entree> > <fichier sortie>" << endl;
        return 1;
    } else  {
        /* stock les noms des candidats */
        vector<candidat> vCandidat(4);
        for (char i = 0; i < 4; ++i) {
            vCandidat[i].nom = litUneString();
        }

        /* Nombre total de personne votant */
        const int nombreTotalPersonne = 116;

        string gagnantPremierTour;
        string secondGagnantPremierTour;

        /* On récupère les voix et les ajoute aux candidats */
        for (int i = 0; i < (nombreTotalPersonne*2); ++i) {
            int numParti = litUnEntier();

            if (numParti >= 1 && numParti <= 4) {
                if (i < nombreTotalPersonne) {
                    vCandidat[numParti - 1].voix += 1;
                }

                // afficher gagnant & mettre à 0
                if (i == nombreTotalPersonne - 1) {
                    for (int i = 0; i < vCandidat.size(); ++i) {
                        /* Grand gagnant 50% */
                        if (vCandidat[i].voix >= (nombreTotalPersonne / 2)) {
                            gagnantPremierTour = vCandidat[i].nom;
                            cout << gagnantPremierTour << " est le gagnant" << endl;
                            return 0;
                        }
                    }
                    /* Les deux premiers */
                    std::sort(vCandidat.begin(), vCandidat.end(), comparer);
                    gagnantPremierTour = vCandidat[0].nom;
                    secondGagnantPremierTour = vCandidat[1].nom;
                    cout << gagnantPremierTour << " et " << secondGagnantPremierTour << " vont au deuxieme tour" << endl;

                    // reset voix pour les deux premiers candidats
                    for (int i = 2; i < vCandidat.size(); ++i) {
                        vCandidat[i].voix = 0;
                    }
                }

                // Deuxieme tour
                if (i >= nombreTotalPersonne) {
                    // Ajout des voix
                    if (numParti == 1 || numParti == 2) {
                        vCandidat[numParti - 1].voix += 1;
                    }
                    // resultat du deuxieme tour
                    if (i == (nombreTotalPersonne*2) - 1) {
                        if (vCandidat[0].voix < vCandidat[1].voix ) {
                            cout << vCandidat[1].nom << " est le gagnant" << endl;
                        } else {
                            cout << vCandidat[0].nom << " est le gagnant" << endl;
                        }
                    }
                }
            }
        }
    }

    return 0;
}
