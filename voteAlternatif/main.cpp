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
        } catch (const std::invalid_argument& e) {
            continue;
        }
    }
}

struct candidat{
    string nom;
    int voix;
};

int main() {

    // Initialisation des participants
    const int nombreTotalPersonne = 116;

    // Initialisation des candidats
    vector<candidat> candidats(4);
    for (int i = 0; i < 4; ++i) {
        candidats[i].nom = litUneString();
        candidats[i].voix= 0;
    }

    int choix;
    for (unsigned i = 0; i < nombreTotalPersonne; ++i) {
        choix = litUnEntier();
        if (choix <= candidats.size() && choix >= 1) //verification de la validité du vote
        {
            candidats[choix - 1].voix = candidats[choix - 1].voix + 1; //on ajoute un au compteur de vote du candidats correspondant
        }
        else
        {
            cout << "Il n'y a pas de candidats associées au numéro inserer, le vote ne sera pas comptabiliser" << endl;
        }
    }

    candidat elu; //initialisation de l'elu de type candidat(struct)
    elu = candidats[0];
    for (unsigned i = 1 ; i < candidats.size() ; ++i)
    {
        if (elu.voix < candidats[i].voix)
        {
            elu = candidats[i];
        }
    }
    cout << "Le gagnant est " << elu.nom << " avec " << elu.voix << " votes";
    return 0;
}
