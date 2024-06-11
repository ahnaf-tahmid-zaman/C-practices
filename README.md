# IPv4 and Binary Conversion Program

This program converts an IPv4 address to its binary representation and vice versa. Below is a detailed explanation of how the code works.

## Main Program
```C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
```
These are library includes. They let us use standard input/output functions, memory allocation, and string handling functions.

```c
#define IPV4_SEGMENT_COUNT 4
#define IPV4_SEGMENT_BITS 8
#define MAX_IP_LENGTH 50
```
These are `#define` directives. They create constants:

* `IPV4_SEGMENT_COUNT` is 4 because an IPv4 address has 4 segments (like 192.168.1.1).
* `IPV4_SEGMENT_BITS` is 8 because each segment of an IPv4 address is 8 bits (like 192 in binary is 11000000).
* `MAX_IP_LENGTH` is 50 to define the maximum length of the input IP address string.

## Main Function
```c
void convertIPv4ToBinary(const char ipv4Address[]);
void convertBinaryToIPv4(const char binaryAddress[]);
void printMenu();
```
These lines declare three functions that we'll define later. Declaring them here lets the main function use them.

```c
int main() {
    int choice;
    char input[MAX_IP_LENGTH];
```
Here, `main()` is the starting point of the program. We declare `choice` to store the user's menu selection and `input` to store the IP address they enter.

```c
    printMenu();
    scanf("%d", &choice);
    getchar(); // to consume the newline character after scanf
```
* `printMenu()` shows the menu to the user.
* `scanf("%d", &choice)` reads the user's choice.
* `getchar()` removes the newline character left by scanf.

```c
    if (choice == 1) {
        printf("Enter IPv4 address: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // remove newline character
        convertIPv4ToBinary(input);
    } else if (choice == 2) {
        printf("Enter Binary address: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // remove newline character
        convertBinaryToIPv4(input);
    } else {
        printf("Invalid choice!\n");
    }
```
* If the user chooses `1`, they want to convert an IPv4 address to binary:
    * We prompt them to enter the IPv4 address and read it into `input`.
    * `input[strcspn(input, "\n")] = '\0';` removes the newline character from the input.
    * `convertIPv4ToBinary(input)` converts and prints the binary representation.
* If the user chooses `2`, they want to convert a binary address to IPv4:
    * Similar steps are followed to read the binary address.
    * `convertBinaryToIPv4(input)` converts and prints the IPv4 representation.
* If the user enters anything else, we print "Invalid choice!".

```c
    return 0;
}
```
This line ends the `main()` function, returning `0` to indicate the program ran successfully.

## printMenu Function
```c
void printMenu() {
    printf("Choose an option:\n");
    printf("1. IPv4 to Binary\n");
    printf("2. Binary to IPv4\n");
    printf("Enter your choice: ");
}
```
This function prints the menu options for the user to choose from.

## convertIPv4ToBinary Function
```c
void convertIPv4ToBinary(const char ipv4Address[]) {
    unsigned int segments[IPV4_SEGMENT_COUNT];
    char binaryRepresentation[MAX_IP_LENGTH] = "";
    char segmentBinary[IPV4_SEGMENT_BITS + 1];
    int i;
```
* `segments` is an array to store the 4 segments of the IPv4 address.
* `binaryRepresentation` is a string to build the final binary result.
* `segmentBinary` is a temporary string to store each segment's binary form.

```c
    if (sscanf(ipv4Address, "%u.%u.%u.%u", &segments[0], &segments[1], &segments[2], &segments[3]) != 4) {
        printf("Invalid IPv4 address format.\n");
        return;
    }
```
* `sscanf` reads the IPv4 address and splits it into four segments.
* If it doesn't find exactly 4 segments, it prints an error message and exits the function.

```c
    for (i = 0; i < IPV4_SEGMENT_COUNT; i++) {
        segmentBinary[0] = '\0';
        for (int j = IPV4_SEGMENT_BITS - 1; j >= 0; j--) {
            sprintf(segmentBinary + strlen(segmentBinary), "%d", (segments[i] >> j) & 1);
        }
        strcat(binaryRepresentation, segmentBinary);
        if (i < IPV4_SEGMENT_COUNT - 1) {
            strcat(binaryRepresentation, ".");
        }
    }
```
* We loop through each segment:
    * Reset `segmentBinary`.
    * For each bit in the segment, calculate its binary value and append it to `segmentBinary`.
    * Append `segmentBinary` to `binaryRepresentation`.
    * Add a dot after each segment except the last one.

```c
    printf("Binary representation: %s\n", binaryRepresentation);
}
```
Finally, print the complete binary representation.

## convertBinaryToIPv4 Function
```c
void convertBinaryToIPv4(const char binaryAddress[]) {
    unsigned int segments[IPV4_SEGMENT_COUNT] = {0};
    char segmentBinary[IPV4_SEGMENT_BITS + 1];
    char tempBinary[MAX_IP_LENGTH];
    int segmentIndex = 0;
    int charIndex = 0;
```
* `segments` stores the 4 segments of the IPv4 address.
* `segmentBinary` stores each segment's binary part.
* `tempBinary` is a copy of the input binary address.
* `segmentIndex` and `charIndex` are counters.

```c
    strcpy(tempBinary, binaryAddress);

    for (int i = 0; i <= strlen(tempBinary); i++) {
        if (tempBinary[i] == '.' || tempBinary[i] == '\0') {
            segmentBinary[charIndex] = '\0';
            charIndex = 0;
            for (int j = 0; j < IPV4_SEGMENT_BITS; j++) {
                if (segmentBinary[j] == '1') {
                    segments[segmentIndex] |= 1 << (IPV4_SEGMENT_BITS - 1 - j);
                } else if (segmentBinary[j] != '0') {
                    printf("Invalid binary digit.\n");
                    return;
                }
            }
            segmentIndex++;
        } else {
            segmentBinary[charIndex++] = tempBinary[i];
        }
    }
```
* Copy the binary address to `tempBinary`.
* Loop through `tempBinary`:
    * When a dot or end of the string is found, process the current segment:
        * Convert the binary string to a number.
        * Move to the next segment.
    * Otherwise, keep adding characters to segmentBinary.

```c
    if (segmentIndex != IPV4_SEGMENT_COUNT) {
        printf("Invalid binary address format.\n");
        return;
    }

    printf("IPv4 representation: %u.%u.%u.%u\n", segments[0], segments[1], segments[2], segments[3]);
}
```
* If we don't have exactly 4 segments, print an error.
* Otherwise, print the IPv4 representation.
