/*
 * Copyright (C) 2025 ΠΑΝΑΓΙΩΤΗΣ ΠΙΤΕΛΟΣ
 *
 * Αυτό το πρόγραμμα είναι ελεύθερο λογισμικό: μπορείτε να το αναδιανείμετε 
 * ή/και να το τροποποιήσετε υπό τους όρους της GNU General Public License, 
 * όπως αυτή δημοσιεύθηκε από το Ίδρυμα Ελεύθερου Λογισμικού, είτε στην έκδοση 3 
 * της Άδειας, είτε σε οποιαδήποτε μεταγενέστερη έκδοση.
 * * Αυτό το πρόγραμμα διανέμεται με την ελπίδα ότι θα είναι χρήσιμο, αλλά ΧΩΡΙΣ 
 * ΚΑΜΙΑ ΕΓΓΥΗΣΗ· ούτε καν την σιωπηρή εγγύηση ΕΜΠΟΡΕΥΣΙΜΟΤΗΤΑΣ ή ΚΑΤΑΛΛΗΛΟΤΗΤΑΣ 
 * ΓΙΑ ΣΥΓΚΕΚΡΙΜΕΝΟ ΣΚΟΠΟ. Δείτε την GNU General Public License για περισσότερες 
 * λεπτομέρειες.
 * * Θα πρέπει να έχετε λάβει ένα αντίγραφο της GNU General Public License μαζί 
 * με αυτό το πρόγραμμα. Αν όχι, ανατρέξτε στο <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h> 

// Σταθερές για Τζόκερ
#define J_MAIN_COUNT 5
#define J_MAX_MAIN 45
#define J_MAX_JOKER 20

// Σταθερές για Λόττο
#define L_COUNT 6
#define L_MAX 49

// Σταθερές για ΠΡΟΤΟ
#define P_COUNT 7 
#define P_MAX 10 

// Πρωτότυπα συναρτήσεων
void jocker_numbers();
void lotto_numbers();
void proto_numbers(); 
int menu();
void sort_array(int arr[], int size);
int generate_unique_number(int arr[], int count, int max_value);
void clear_input_buffer(); 
void wait_for_key_and_clear(); 

// ------------------------------------------------------------------
// ΚΥΡΙΑ ΣΥΝΑΡΤΗΣΗ MAIN
// ------------------------------------------------------------------
int main() {
    int choice;
    
    srand(time(NULL)); 
    
    while (1) 
    {
        // Χρησιμοποιούμε #ifndef _WIN32 για να πιάσουμε Linux/macOS, όπου χρησιμοποιείται το "clear"
        #ifndef _WIN32
            system("clear");
        #else
            system("cls"); // Αν ήταν Windows
        #endif

        choice = menu();

        switch (choice)
        {
            case 1:
                printf("\n--- Αποτελέσματα κλήρωσης Τζόκερ ---\n");
                jocker_numbers();
                break;
            case 2:
                printf("\n--- Αποτελέσματα κλήρωσης Λόττο ---\n");
                lotto_numbers();
                break;
            case 3: 
                printf("\n--- Αποτελέσματα κλήρωσης ΠΡΟΤΟ ---\n");
                proto_numbers();
                break;
            case 0:
                printf("\nΈξοδος από το πρόγραμμα. Αντίο!\n");
                return 0; 
        }
    }
    
    return 0; 
}

// ------------------------------------------------------------------
// ΣΥΝΑΡΤΗΣΗ: Εμφάνιση Μενού & Λήψη Επιλογής
// ------------------------------------------------------------------
int menu()
{
    int c;
    do
    {
        printf("\n\t  🎲 ΜΕΝΟΥ ΛΑΧΕΙΩΝ 🎰\n");
        printf("1. Αριθμοί Τζόκερ (5+1).\n");
        printf("2. Αριθμοί Λόττο (6).\n");
        printf("3. Αριθμοί ΠΡΟΤΟ (7 ψηφία). \n"); 
        printf("0. Έξοδος\n");
        printf("Δώστε την επιλογή σας (0-3): ");
        
        if (scanf("%d", &c) != 1) 
        {
            clear_input_buffer(); 
            c = -1; 
            printf("Μη έγκυρη εισαγωγή. Παρακαλώ δώστε έναν αριθμό.\n");
        }
        
    } while (c < 0 || c > 3); 
    
    // Καθαρισμός buffer μετά από επιτυχημένο scanf
    clear_input_buffer(); 
    return c;
}

// ------------------------------------------------------------------
// ΣΥΝΑΡΤΗΣΗ: Δημιουργία Μοναδικών Αριθμών Τζόκερ
// ------------------------------------------------------------------
void jocker_numbers()
{
    int main_numbers[J_MAIN_COUNT];
    int joker_number;

    for (int i = 0; i < J_MAIN_COUNT; i++)
    {
        main_numbers[i] = generate_unique_number(main_numbers, i, J_MAX_MAIN);
    }
    
    sort_array(main_numbers, J_MAIN_COUNT);
    joker_number = (rand() % J_MAX_JOKER) + 1; 

    printf("Κύριοι Αριθμοί (1-%d): ", J_MAX_MAIN);
    for (int i = 0; i < J_MAIN_COUNT; i++)
    {
        printf("%d ", main_numbers[i]);
    }
    printf("\n");
    printf("Αριθμός Τζόκερ (1-%d): %d\n", J_MAX_JOKER, joker_number);

    wait_for_key_and_clear(); 
}

// ------------------------------------------------------------------
// ΣΥΝΑΡΤΗΣΗ: Δημιουργία Μοναδικών Αριθμών Λόττο
// ------------------------------------------------------------------
void lotto_numbers()
{
    int numbers[L_COUNT]; 

    for (int i = 0; i < L_COUNT; i++)
    {
        numbers[i] = generate_unique_number(numbers, i, L_MAX);
    }
    
    sort_array(numbers, L_COUNT);
    
    printf("Αριθμοί Λόττο (1-%d): ", L_MAX);
    for (int i = 0; i < L_COUNT; i++)
    {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    wait_for_key_and_clear(); 
}

// ------------------------------------------------------------------
// ΣΥΝΑΡΤΗΣΗ: Δημιουργία Αριθμών ΠΡΟΤΟ
// ------------------------------------------------------------------
void proto_numbers()
{
    printf("Ψηφία ΠΡΟΤΟ (0-9): ");
    
    for (int i = 0; i < P_COUNT; i++)
    {
        int digit = rand() % P_MAX; 
        printf("%d", digit);
    }
    printf("\n");
    printf("(Σημείωση: Τα ψηφία ΠΡΟΤΟ μπορεί να επαναλαμβάνονται)\n");

    wait_for_key_and_clear(); 
}

// ------------------------------------------------------------------
// ΒΟΗΘΗΤΙΚΕΣ ΣΥΝΑΡΤΗΣΕΙΣ
// ------------------------------------------------------------------

// Καθαρισμός Buffer εισόδου
void clear_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

// Παύση και Καθαρισμός Οθόνης
void wait_for_key_and_clear()
{
    printf("\nΠατήστε [Enter] για επιστροφή στο Μενού...");
    getchar(); // Περιμένει το Enter
}

// Δημιουργία Μοναδικού Αριθμού
int generate_unique_number(int arr[], int count, int max_value)
{
    int new_num;
    bool is_duplicate;
    
    do {
        new_num = (rand() % max_value) + 1;
        is_duplicate = false;
        
        for (int i = 0; i < count; i++) {
            if (arr[i] == new_num) {
                is_duplicate = true;
                break;
            }
        }
        
    } while (is_duplicate); 
    
    return new_num;
}

// Ταξινόμηση Πίνακα
void sort_array(int arr[], int size)
{
    int i, j, min_idx, temp;
    for (i = 0; i < size-1; i++)
    {
        min_idx = i;
        for (j = i+1; j < size; j++)
          if (arr[j] < arr[min_idx])
            min_idx = j;

        temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}