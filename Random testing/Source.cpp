#include <Windows.h>
#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <limits>
#include <string>
#include <cstdlib>

bool separate_words(std::string text) {
    std::string word = "";

    for (int i = 0 ; i < text.size(); i++) {
        if (text[i] == ' ') {

            break;

        } else{

        word += text[i];

        }
        
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
    for (char c : text) {
        int ran = (rand() % 400) + 0;
        SHORT vk = VkKeyScan(c);  // Get the virtual key for the character
        PressKey(vk);
        ReleaseKey(vk);
        Sleep(ran);
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
    srand(time(NULL));
    while (true) {
        std::cout << "Press the 'F2' key to continue...\n";

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
            Sleep(100); // Add a small delay to prevent high CPU usage
        }

        // Continue with the rest of the code
        std::string wordlist = "you even go people eye since open change make late eye under after begin where feel man become where up now mean because";
        TypeString(wordlist);


        /*PressKey(VK_LWIN);
        PressKey(keyMap['R']);
        ReleaseKey(VK_LWIN);
        ReleaseKey(keyMap['R']);
        Sleep(100);
        TypeString("notepad");
        Sleep(200);
        PressKey(VK_RETURN);
        ReleaseKey(VK_RETURN);*/
        
        
     
     
    }
    return 0;
}
