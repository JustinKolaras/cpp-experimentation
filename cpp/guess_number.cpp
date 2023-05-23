#include <iostream>
#include <random>
#include <cctype>
#include <ctime>
#include <string>

int random(int start, int end) {
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distribution(start, end);

    return distribution(eng);
}

bool inRange(int value, int start, int end) {
    return value >= start && value <= end;
}

int main() {
    const int number = random(1, 100);

    int guess = 0;
    int attemptsRemaining = 5;

    std::cout << "Welcome to guess the number! Please guess a number between 1 and 99.\n";
    std::cout << attemptsRemaining << " attempts remaining.\n";

    // Initialization is needed for the `start` variable as the compiler
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
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (!inRange(guess, 1, 99)) {
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

    if (tolower(playAgain) == 'y') {
        main();
    }

    return 0;
}