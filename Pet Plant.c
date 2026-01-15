/* Pet Plant Game
   Description: Mystery seed boxes and interactive plant care game.
   - Short story-style intro
   - Greeting and ready check
   - 3 mystery boxes (Cactus, Peace Lily, Rose)
   - Actions: Show Happiness, Water, Give Sunlight, Check Growth, Exit
   - Happiness numeric (0-100) + text mood
   - Growth stages: Seed -> Sprout -> Young Plant -> Blooming -> Mature
   - Guessing after every 5 steps, reveal and replay options
   - No emojis
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_HAPPINESS 100

/* Functions */
void clear_input();
int clamp(int val, int lo, int hi);
void greeting();
void show_happiness(int happiness);
void show_growth_stage(int happiness);
void water_plant(int *happiness, int *last_action, int chosen_seed);
void give_sunlight(int *happiness, int *last_action, int chosen_seed);
void plant_reveal(int chosen_seed, int happiness);
void game_exit();
const char* plant_name(int id);

/* Clear any remaining characters in input buffer */
void clear_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

/* Clamp an integer value between lo and hi */
int clamp(int val, int lo, int hi) {
    if (val < lo) return lo;
    if (val > hi) return hi;
    return val;
}

/* Short intro + greeting */
void greeting() {
    printf("Once upon a time you found a small wooden seed box on your doorstep.\n");
    printf("Inside there are three mysterious boxes — each hiding a different seed.\n\n");
    printf("Welcome to the Pet Plant Game!\n");
}

/* Show numeric happiness and mood */
void show_happiness(int happiness) {
    printf("\n--- Plant Happiness ---\n");
    printf("Happiness: %d/%d\n", happiness, MAX_HAPPINESS);
    if (happiness >= 85)
        printf("Your plant is very happy! Great care.\n");
    else if (happiness >= 65)
        printf("Your plant is doing well — a little more care will make it excellent.\n");
    else if (happiness >= 40)
        printf("Your plant is okay but needs more attention.\n");
    else if (happiness >= 15)
        printf("Your plant is needy — give it water or sunlight soon.\n");
    else
        printf("Your plant is in poor condition. Care urgently!\n");
    printf("------------------------\n\n");
}

/* Growth stages */
void show_growth_stage(int happiness) {
    printf("\n--- Plant Growth Stage ---\n");
    if (happiness >= 80) {
        printf("Growth stage: Mature\n");
        printf("The plant is fully grown and healthy.\n");
    } else if (happiness >= 60) {
        printf("Growth stage: Blooming\n");
        printf("The plant shows flowers or buds and looks lively.\n");
    } else if (happiness >= 40) {
        printf("Growth stage: Young Plant\n");
        printf("The plant is growing steadily but needs consistent care.\n");
    } else if (happiness >= 20) {
        printf("Growth stage: Sprout\n");
        printf("The plant has sprouted but is fragile.\n");
    } else {
        printf("Growth stage: Seed\n");
        printf("The plant is still at seed stage or struggling to grow.\n");
    }
    printf("---------------------------\n\n");
}

/* Handle watering logic */
void water_plant(int *happiness, int *last_action, int chosen_seed) {
    printf("You watered the plant.\n");
    if (chosen_seed == 0) { // Cactus
        *happiness -= 8;
        printf("Too much water is not ideal. Happiness decreased a bit.\n");
    } else if (chosen_seed == 1) { // Peace Lily
        *happiness += 10;
        printf("Water appreciated! Happiness increased.\n");
    } else if (chosen_seed == 2) { // Rose
        if (*last_action == 1) {
            *happiness += 12;
            printf("Balanced care! Happiness increased significantly.\n");
        } else if (*last_action == 0) {
            *happiness -= 10;
            printf("Repeated watering is not good. Happiness decreased.\n");
        } else {
            *happiness += 6;
            printf("First watering applied.\n");
        }
    }
    *happiness = clamp(*happiness, 0, MAX_HAPPINESS);
    *last_action = 0;
}

/* Handle sunlight logic */
void give_sunlight(int *happiness, int *last_action, int chosen_seed) {
    printf("You gave sunlight to the plant.\n");
    if (chosen_seed == 0) { // Cactus
        *happiness += 10;
        printf("Sunlight makes it happier.\n");
    } else if (chosen_seed == 1) { // Peace Lily
        *happiness =- 7;
        printf("Too much sunlight reduces happiness.\n");
    } else if (chosen_seed == 2) { // Rose
        if (*last_action == 0) {
            *happiness += 12;
            printf("Balanced care! Happiness increased significantly.\n");
        } else if (*last_action == 1) {
            *happiness -= 10;
            printf("Repeated sunlight is not good. Happiness decreased.\n");
        } else {
            *happiness += 6;
            printf("First sunlight applied.\n");
        }
    }
    *happiness = clamp(*happiness, 0, MAX_HAPPINESS);
    *last_action = 1;
}

/* Reveal plant type after guess */
void plant_reveal(int chosen_seed, int happiness) {
    printf("\nThe seed was a %s.\n", plant_name(chosen_seed));
    show_happiness(happiness);
}

/* Exit game */
void game_exit() {
    printf("Exiting game. Thank you for playing!\n");
}

/* Return plant name */
const char* plant_name(int id) {
    if (id == 0) return "Cactus";
    if (id == 1) return "Peace Lily";
    if (id == 2) return "Rose";
    return "Unknown";
}

/* ---------- MAIN GAME LOGIC ---------- */
int main() {
    srand((unsigned int)time(NULL));
    char start_choice[10];
    greeting();

    printf("Are you ready to start? (yes/no): ");
    if (scanf("%9s", start_choice) != 1) return 0;
    clear_input();

    if (strcasecmp(start_choice, "no") == 0) {
        printf("Alright. Exiting the game. Thank you!\n");
        return 0;
    } else if (strcasecmp(start_choice, "yes") != 0) {
        printf("Invalid input. Exiting.\n");
        return 0;
    }

    while (1) { // new round
        int seeds[3] = {0, 1, 2};
        for (int i = 2; i > 0; --i) {
            int j = rand() % (i + 1);
            int tmp = seeds[i]; seeds[i] = seeds[j]; seeds[j] = tmp;
        }

        printf("\nYou have 3 mystery boxes: Box 1, Box 2, Box 3.\n");
        printf("Each box hides one seed: Cactus, Peace Lily, or Rose.\n");
        printf("Which box will you choose? (1-3): ");

        int box_choice;
        while (scanf("%d", &box_choice) != 1 || box_choice < 1 || box_choice > 3) {
            clear_input();
            printf("Please enter 1, 2, or 3: ");
        }
        clear_input();

        int chosen_seed = seeds[box_choice - 1];
        int happiness = 50;
        int steps = 0, last_action = -1;
        printf("\nYou opened Box %d. The game begins!\n\n", box_choice);

        int in_round = 1;
        while (in_round) {
            printf("Actions:\n");
            printf("1. Show Seed Happiness\n");
            printf("2. Water Plant\n");
            printf("3. Give Sunlight\n");
            printf("4. Check Growth Stage\n");
            printf("5. Exit this round\n");
            printf("Enter your choice (1-5): ");

            int opt;
            if (scanf("%d", &opt) != 1) {
                clear_input();
                printf("Invalid input. Try again.\n\n");
                continue;
            }
            clear_input();

            switch (opt) {
                case 1: show_happiness(happiness); break;
                case 2: steps++; water_plant(&happiness, &last_action, chosen_seed); break;
                case 3: steps++; give_sunlight(&happiness, &last_action, chosen_seed); break;
                case 4: show_growth_stage(happiness); break;
                case 5:
                    printf("Exiting this round. Current plant progress will not be saved.\n");
                    in_round = 0;
                    break;
                default:
                    printf("Please choose between 1 and 5.\n");
                    continue;
            }

            if (steps > 0 && steps % 5 == 0) {
                char guess_now[10];
                printf("\nYou have completed %d care steps. Do you want to guess which plant this is? (yes/no): ", steps);
                if (scanf("%9s", guess_now) != 1) continue;
                clear_input();

                if (strcasecmp(guess_now, "yes") == 0) {
                    char user_guess[30];
                    printf("Please type your guess (cactus / peace_lily / rose): ");
                    if (scanf("%29s", user_guess) != 1) continue;
                    clear_input();

                    int guess_id = -1;
                    if (strcasecmp(user_guess, "cactus") == 0) guess_id = 0;
                    else if (strcasecmp(user_guess, "peace_lily") == 0 || strcasecmp(user_guess, "peace") == 0) guess_id = 1;
                    else if (strcasecmp(user_guess, "rose") == 0) guess_id = 2;

                    if (guess_id == chosen_seed) {
                        printf("\nCONGRATULATIONS! You guessed correctly: It is a %s.\n", plant_name(chosen_seed));
                    } else {
                        printf("\nNice try, but that is not correct.\n");
                        plant_reveal(chosen_seed, happiness);
                    }

                    char after_choice[20];
                    printf("\nWould you like to (restart), (continue), or (exit)? ");
                    if (scanf("%19s", after_choice) != 1) break;
                    clear_input();

                    if (strcasecmp(after_choice, "restart") == 0) {
                        printf("Starting a new round...\n");
                        in_round = 0;
                        break;
                    } else if (strcasecmp(after_choice, "exit") == 0) {
                        game_exit();
                        return 0;
                    } else {
                        printf("Continuing with the current plant.\n");
                    }
                } else {
                    printf("Okay. Continue caring for your plant.\n");
                }
            }
        }

        char play_again[10];
        printf("\nDo you want to play another round? (yes/no): ");
        if (scanf("%9s", play_again) != 1) break;
        clear_input();
        if (strcasecmp(play_again, "no") == 0) {
            printf("Goodbye! Thank you for playing the Pet Plant Game.\n");
            break;
        }
    }

    return 0;
}
