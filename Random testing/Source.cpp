#include <Windows.h>
#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <limits>
#include <string>
#include <cstdlib>
#include <chrono>
#include <thread>

//******* Dont got time to fix but the words typed where more than the words inside the word list likey needs to be reset inset of just stacking up

int words_typed{};
// Set time limit (in seconds)
int timeLimit = 30;
std::vector<std::string> vectorwordlist;

void separate_words(const std::string text) {
    std::string word = "";

    for (int i = 0; i < text.size(); i++) {
        if (text[i] == ' ') {
            if (!word.empty()) { // To avoid pushing empty words for consecutive spaces
                vectorwordlist.push_back(word);
                word = ""; // Reset word
            }
        }
        else {
            word += text[i];
        }
    }

    // Push the last word if it exists
    if (!word.empty()) {
        vectorwordlist.push_back(word);
    }
}

void PressKey(WORD key) {
    INPUT input = { 0 };
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = key;
    SendInput(1, &input, sizeof(INPUT));
}

void ReleaseKey(WORD key) {
    INPUT input = { 0 };
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = key;
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
}

void TypeString(const std::string& text) {
    // Get the starting time
    auto startTime = std::chrono::steady_clock::now();
    int lastPrintedTime = -1;  // Initialize to an invalid value

    for (char c : text) {
        auto currentTime = std::chrono::steady_clock::now();
        std::chrono::duration<int> elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime);
        
        // Only print if the time has changed (i.e., every second)
        if (elapsedTime.count() != lastPrintedTime) {
            std::cout << "Elapsed Time: " << elapsedTime.count() << " seconds\n";
            lastPrintedTime = elapsedTime.count();  // Update the last printed time
        }
        if (elapsedTime.count() >= timeLimit) {
            std::cout << "Out of time ending loop\n time limit: " << timeLimit << std::endl;
            break;
        }
        
        int ran = (rand() % 100) + 0;
        SHORT vk = VkKeyScan(c);  // Get the virtual key for the character
        PressKey(vk);
        ReleaseKey(vk);
        Sleep(ran);
        if (vk == VK_SPACE) {
            words_typed++;
        }
    }
    
}
// Map of each letter and the Hexadecimal code for them
std::map<char, int> keyMap = {
    {'A', 0x41}, {'B', 0x42}, {'C', 0x43}, {'D', 0x44},
    {'E', 0x45}, {'F', 0x46}, {'G', 0x47}, {'H', 0x48},
    {'I', 0x49}, {'J', 0x4A}, {'K', 0x4B}, {'L', 0x4C},
    {'M', 0x4D}, {'N', 0x4E}, {'O', 0x4F}, {'P', 0x50},
    {'Q', 0x51}, {'R', 0x52}, {'S', 0x53}, {'T', 0x54},
    {'U', 0x55}, {'V', 0x56}, {'W', 0x57}, {'X', 0x58},
    {'Y', 0x59}, {'Z', 0x5A}, {' ', 0x20}
};

int main() {
    // Set the time limit (in seconds)
    int timeLimit = 30;  // Time limit of 10 seconds
    srand(time(NULL));
    std::string wordlist = "No Word list has been input";
    std::cout << "Please enter your word list: ";
    std::cin.clear();
    std::getline(std::cin, wordlist);
    while (true) {
    std::cout << "Press the 'F2' key to continue or the 'F3' key for a new word list...\n";

     // Loop until the key is pressed
     while (true) {
         // Check if the key is pressed
         if (GetAsyncKeyState(VK_F2) & 0x8000) { // Replace the key with any key
             std::cout << "'F2' key pressed! Continuing...\n";
             break; // Exit the loop when keyMap[' '] is pressed
         }
         // Check if the key is pressed
         if (GetAsyncKeyState(keyMap['X']) & 0x8000) { // Replace the key with any Key
            return 0;
         }
         if (GetAsyncKeyState(VK_F3) & 0x8000) {
             std::cout << "Please enter your word list: ";
             std::cin.clear();  // Clear any errors
             std::getline(std::cin, wordlist);  // Read a new word list from the user
             std::cout << "Press the 'F2' key to continue or the 'F3' key for a new word list...\n";
         }
        Sleep(100); // Add a small delay to prevent high CPU usage
     }
     vectorwordlist.clear();//allows code to run multiple times without stacking up in vector

    // Continue with the rest of the code

    
    separate_words(wordlist);
    //for (int i = 0; i < vectorwordlist.size(); i++) {std::cout << vectorwordlist[i] << '\n';}
    
    TypeString(wordlist);
    std::cout << vectorwordlist.size() << " Words are inside the word list\n" <<words_typed << " Words have been typed\n";

    Sleep(500);
     
    }
    return 0;
}
