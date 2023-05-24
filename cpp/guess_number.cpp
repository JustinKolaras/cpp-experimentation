#include <cctype>
#include <ctime>
#include <iostream>
#include <string>
#include <tuple>

#include "util.h"

int main() {
    const int rangeMin = 10;
    const int rangeMax = 100000;
    const int attemptsMin = 1;
    const int attemptsMax = 30;

    int guess{};
    int attemptsRemaining{};
    int topEnd{};
    int number{};

    do {
        std::cout << "Welcome to guess the number!\n";
        std::cout << "You will be prompted to guess a number between a specified range within a certain number of attempts.\n";
        std::cout << "Please specify the top-end of the range. The range will always begin at 1.\n";

        std::cout << "Top-end: ";

        /* TO FIX LATER
            std::tuple<bool, int> topEndInput{};

            while (!std::get<0>(topEndInput)) {
                std::cout << "Invalid input. Please enter a valid integer that is within " << rangeMin << " and " << rangeMax << ".\nTop-end: ";
                clearInput();
                topEndInput = input<int>([&]() {
                    return inRange(topEnd, rangeMin, rangeMax);
                });
            }
        */

        while (!(std::cin >> topEnd) || !inRange(topEnd, rangeMin, rangeMax)) {
            std::cout <<
                "Invalid input. Please enter a valid integer that is within " << rangeMin << " and " << rangeMax << ".\nTop-end: ";
            clearInput();
        }

        std::cout << "Please specify the amount of attempts you would like to have.\n";
        std::cout << "Attempts: ";

        while (!(std::cin >> attemptsRemaining) || !inRange(attemptsRemaining, attemptsMin, attemptsMax) || attemptsRemaining >= topEnd) {
            std::cout <<
                "Invalid input. Please enter a valid integer that is within exclusive range that is no greater than " << attemptsMax << ".\nAttempts: ";
            clearInput();
        }

        number = random(1, topEnd);

        std::cout << "Please guess a number between 1 and " << topEnd << ".\n";

        std::string attemptDisplay = (attemptsRemaining == 1) ? "attempt" : "attempts";

        std::cout <<
            attemptsRemaining << " " << attemptDisplay << " remaining.\n";

        // Initialization is needed for the start variable as the compiler
        // thinks it might be impossible due to it's usage in the while loop.
        time_t start{}, end;
        bool setTime = false;

        while (guess != number && attemptsRemaining > 0) {
            if (!setTime) {
                time(&start);
                setTime = true;
            }

            if (!(std::cin >> guess)) {
                std::cout << "Invalid input. Please enter a valid integer.\n";
                clearInput();
                continue;
            }

            if (!inRange(guess, 1, topEnd)) {
                std::cout << "Not in range.\n";
                continue;
            }

            attemptsRemaining--;

            // To stop additional dialogues.
            if (guess == number || attemptsRemaining == 0) {
                break;
            }

            if (guess > number) {
                std::cout << "Lower.\n";
            }
            else if (guess < number) {
                std::cout << "Higher.\n";
            }

            std::string attemptDisplay = (attemptsRemaining == 1) ? "attempt" : "attempts";

            std::cout <<
                attemptsRemaining << " " << attemptDisplay << " remaining.\n";
        }

        time(&end);

        if (guess == number) {
            std::cout <<
                "Congratulations! You guessed the number in " << difftime(end, start) << "s!\n";
        }
        else {
            std::cout << "You lose! The number was " << number << ".\n";
        }

        char playAgain;

        std::cout << "Would you like to play again? (Y/n)\n";
        std::cin >> playAgain;

        if (tolower(playAgain) != 'y') {
            return 0;
        }
    } while (true);
}