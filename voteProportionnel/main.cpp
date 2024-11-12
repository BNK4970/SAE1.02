#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/* Fonction pour lire une ligne du fichier d'entrée */
string litUneString() {
    string uneChaine;
    while (true) {
        if (!getline(cin, uneChaine)) {
            cerr << "Erreur de lecture de la chaîne." << endl;
            exit(1);
        }
        if (uneChaine.substr(0, 2) != "//") break;
    }
    return uneChaine;
}

/* Fonction pour convertir une chaîne en entier sans try */
int litUnEntier() {
    string uneChaine;
    while (true) {
        if (!getline(cin, uneChaine)) {
            cerr << "Erreur de lecture de l'entier." << endl;
            exit(1);
        }
        return stoi(uneChaine);
    }
}

struct Participant {
    string nom;
    string prenom;
    int choixParti;
};

struct Parti {
    string nom;
    int voix;
    int siege;
};

/* Fonction attribuer les sièges */
int AttributionSiege(int voix, int quotient) {
    return voix / quotient;
}

/* Fonction pour calculer le reste des sièges */
int CalculReste(int voix, int quotient) {
    return voix % quotient;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage attendu: ./<nom_executable> <nombre_de_sieges> < <fichier_entree> > <fichier_sortie>" << endl;
        return 1;
    } else {
        int nombreSiegeTotal = stoi(argv[1]);

        // Initialisation des participants
        const int nombreTotalPersonne = 116;
        vector<Participant> vParticipant(nombreTotalPersonne);

        // Initialisation des partis
        vector<Parti> vPartiPref(4);
        for (int i = 0; i < 4; ++i) {
            vPartiPref[i].nom = litUneString();
            vPartiPref[i].voix = 0;  // Initialisation des voix à 0
            vPartiPref[i].siege = 0; // Initialisation des sièges à 0
        }

        // Lecture des noms, prénoms et votes pour chaque participant
        for (int i = 0; i < nombreTotalPersonne; ++i) {
            vParticipant[i].nom = litUneString();
            vParticipant[i].prenom = litUneString();
            int numParti = litUnEntier();

            if (numParti >= 1 && numParti <= 4) {
                vPartiPref[numParti - 1].voix += 1;
            } else {
                cerr << "Numéro de parti invalide pour " << vParticipant[i].nom << " " << vParticipant[i].prenom << ": " << numParti << endl;
                exit(1);
            }
        }

        // Calcul du quotient électoral
        int quotientElectoral = nombreTotalPersonne / nombreSiegeTotal;

        // Vecteur pour stocker les restes et total des sièges distribués
        vector<int> restes(4, 0);
        int totalSiegesDistribues = 0;

        // Attribution initiale des sièges et calcul des restes
        for (int i = 0; i < 4; ++i) {
            vPartiPref[i].siege = AttributionSiege(vPartiPref[i].voix, quotientElectoral);
            restes[i] = CalculReste(vPartiPref[i].voix, quotientElectoral);
            totalSiegesDistribues += vPartiPref[i].siege;
        }

        // Attribution des sièges restants selon les plus grands restes
        int siegesRestants = nombreSiegeTotal - totalSiegesDistribues;
        while (siegesRestants > 0) {
            int maxIndex = -1;
            int maxReste = -1;

            // Trouver le parti avec le plus grand reste
            for (int i = 0; i < 4; ++i) {
                if (restes[i] > maxReste) {
                    maxReste = restes[i];
                    maxIndex = i;
                }
            }

            if (maxIndex == -1) break; // Plus de restes disponibles

            // Attribuer un siège supplémentaire au parti avec le plus grand reste
            vPartiPref[maxIndex].siege += 1;
            restes[maxIndex] = -1; // Marquer comme utilisé
            siegesRestants--;
        }

        // Affichage du nombre de sièges par parti
        for (int i = 0; i < 4; ++i) {
            cout << "Parti " << vPartiPref[i].nom << ": " << vPartiPref[i].siege << " sièges" << endl;
        }

        return 0;
    }


}
