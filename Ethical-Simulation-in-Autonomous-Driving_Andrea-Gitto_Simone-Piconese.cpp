#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

/* Questo codice simula un'IA di una macchina a guida autonoma (Intelligenza Artificiale) che deve prendere una decisione etica
   basandosi su un algoritmo di valutazione. Il problema del trolley è modellato attraverso
   due gruppi di persone, A e B, e l'IA deve decidere quale gruppo sacrificare per massimizzare
   il proprio punteggio etico. L'algoritmo tiene conto del peso etico della macchina e di variabili
   come l'età delle persone nei gruppi. L'obiettivo è esplorare il comportamento dell'IA
   in differenti scenari, considerando le sue scelte e i risultati ottenuti. Al fine di ottenere 
   risultati oggettivi non sono stati autoimposti principi etici particolari come quelli umani 
   (che hanno come priorità salvare i più giovani), bensì la macchina ha la possibilità di
   analizzare anche il caso opposto, ottenendo così risultati prettamente matematici senza alcun pregiudizio.
*/

// Definizione della struttura Macchina
struct Macchina {
    int punteggio;
    float PesoEtico;
    float MoltEta;
    float risultatoA = 0;
    float risultatoB = 0;
    bool Priori;
    std::string scelta;
};

// Funzione per calcolare il punteggio di un individuo macchina per il gruppo A
float CalcolaRisultatoA(const Macchina& macchina, const std::vector<int>& gruppoA, bool priori) {
    float risultatoA = 0;
    for (size_t i = 0; i < gruppoA.size(); ++i) {
        // Calcolo del valore di MoltEta per gruppo A
        float moltEtaA = priori ? (5.0f - (gruppoA[i] / 100.0f) * 4.0f) : (1.0f + (gruppoA[i] / 100.0f) * 4.0f);
        risultatoA += gruppoA[i] * macchina.PesoEtico * moltEtaA;
    }
    return risultatoA;
}

// Funzione per calcolare il punteggio di un individuo macchina per il gruppo B
float CalcolaRisultatoB(const Macchina& macchina, const std::vector<int>& gruppoB, bool priori) {
    float risultatoB = 0;
    for (size_t i = 0; i < gruppoB.size(); ++i) {
        // Calcolo del valore di MoltEta per gruppo B
        float moltEtaB = priori ? (5.0f - (gruppoB[i] / 100.0f) * 4.0f) : (1.0f + (gruppoB[i] / 100.0f) * 4.0f);
        risultatoB += gruppoB[i] * macchina.PesoEtico * moltEtaB;
    }
    return risultatoB;
}

int main() {
    // Inizializzazione del generatore di numeri casuali
    std::srand(static_cast<unsigned>(std::time(0)));
    std::string uccisione;
    // Creazione di una popolazione di 10 macchine
    const int numMacchine = 10;
    std::vector<Macchina> popolazione(numMacchine);
    
    for (int iterazione = 1; iterazione <= 100; ++iterazione) {
     std::cout << "\n\n" << std::endl;
     
    // Riempi vettore popolazione con valori casuali
    for (int i = 0; i < numMacchine; ++i) {
        popolazione[i].punteggio = 0;
        popolazione[i].PesoEtico = (static_cast<float>(std::rand() % 5) + 1);  // Valore tra 0 e 10
        popolazione[i].MoltEta = 0;  // Inizializzato a 0
        popolazione[i].Priori = (std::rand() % 2 == 0);  // Scegli casualmente vero o falso
    }

    // Creazione e riempimento del vettore A
    const int grandezzaA = std::rand() % 10 + 1;
    std::vector<int> A(grandezzaA);
    for (int i = 0; i < grandezzaA; ++i) {
        A[i] = std::rand() % 76 + 5;  // Valore tra 5 e 80
    }

    // Output del vettore A
    std::cout << "Grandezza vettore A: " << grandezzaA << std::endl;
    for (int i : A) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
 
    // Creazione e riempimento del vettore B
    const int grandezzaB = std::rand() % 10 + 1;
    std::vector<int> B(grandezzaB);
    for (int i = 0; i < grandezzaB; ++i) {
        B[i] = std::rand() % 76 + 5;  // Valore tra 5 e 80
    }

    // Output del vettore B
    std::cout << "Grandezza vettore B: " << grandezzaB << std::endl;
    for (int i : B) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    // Calcola il punteggio per ogni individuo macchina e stampa i risultati
    for (auto& macchina : popolazione) {
        macchina.risultatoA = CalcolaRisultatoA(macchina, A, macchina.Priori);
        macchina.risultatoB = CalcolaRisultatoB(macchina, B, macchina.Priori);

        // Confronta i risultati e aggiorna il punteggio e la scelta
        if (macchina.risultatoA > macchina.risultatoB) 
        {
            
            if(A.size() > B.size()){
                uccisione = "Persone salvate: ";
                macchina.punteggio += A.size();
            }
            if(A.size() < B.size()){
                uccisione = "Persone @ uccise @: ";
                macchina.punteggio += B.size();
            }
            
              macchina.scelta = "Uccide il gruppo B ";
        } else if (macchina.risultatoB > macchina.risultatoA) {
           if(A.size() < B.size()){
                uccisione = "Persone salvate: ";
                macchina.punteggio += B.size();
            }
            if(A.size() > B.size()){
                uccisione = "Persone @ uccise @: ";
                macchina.punteggio += A.size();
            }
            
            macchina.scelta = "Uccide il gruppo A ";
        } else {
          
            macchina.scelta = "Nessuna scelta ";
        }

if(A.size() == B.size()){
     uccisione = "Persone salvate: ";
     macchina.punteggio += A.size();
} 

        // Stampa i risultati
        std::cout << uccisione << macchina.punteggio << " - PesoEtico: " << macchina.PesoEtico
                  << " - Favorisce i " << (macchina.Priori ? "Bambini" : "Vecchi") << " - Scelta: " << macchina.scelta << " - Risultato A: " << macchina.risultatoA << " e Risultato B: " << macchina.risultatoB << std::endl;
    }
 }

    return 0;

}

