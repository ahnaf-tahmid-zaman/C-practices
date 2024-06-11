#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IPV4_SEGMENT_COUNT 4
#define IPV4_SEGMENT_BITS 8
#define MAX_IP_LENGTH 50

void convertIPv4ToBinary(const char ipv4Address[]);
void convertBinaryToIPv4(const char binaryAddress[]);
void printMenu();

int main()
{
    int choice;
    char input[MAX_IP_LENGTH];

    printMenu();
    scanf("%d", &choice);
    getchar(); // to consume the newline character after scanf

    if (choice == 1)
    {
        printf("Enter IPv4 address: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // remove newline character
        convertIPv4ToBinary(input);
    }
    else if (choice == 2)
    {
        printf("Enter Binary address: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // remove newline character
        convertBinaryToIPv4(input);
    }
    else
    {
        printf("Invalid choice!\n");
    }

    return 0;
}

void printMenu()
{
    printf("Choose an option:\n");
    printf("1. IPv4 to Binary\n");
    printf("2. Binary to IPv4\n");
    printf("Enter your choice: ");
}

void convertIPv4ToBinary(const char ipv4Address[])
{
    unsigned int segments[IPV4_SEGMENT_COUNT];
    char binaryRepresentation[MAX_IP_LENGTH] = "";
    char segmentBinary[IPV4_SEGMENT_BITS + 1];
    int i;

    if (sscanf(ipv4Address, "%u.%u.%u.%u", &segments[0], &segments[1], &segments[2], &segments[3]) != 4)
    {
        printf("Invalid IPv4 address format.\n");
        return;
    }

    for (i = 0; i < IPV4_SEGMENT_COUNT; i++)
    {
        segmentBinary[0] = '\0';
        for (int j = IPV4_SEGMENT_BITS - 1; j >= 0; j--)
        {
            sprintf(segmentBinary + strlen(segmentBinary), "%d", (segments[i] >> j) & 1);
        }
        strcat(binaryRepresentation, segmentBinary);
        if (i < IPV4_SEGMENT_COUNT - 1)
        {
            strcat(binaryRepresentation, ".");
        }
    }

    printf("Binary representation: %s\n", binaryRepresentation);
}

void convertBinaryToIPv4(const char binaryAddress[])
{
    unsigned int segments[IPV4_SEGMENT_COUNT] = {0};
    char segmentBinary[IPV4_SEGMENT_BITS + 1];
    char tempBinary[MAX_IP_LENGTH];
    int segmentIndex = 0;
    int charIndex = 0;

    strcpy(tempBinary, binaryAddress);

    for (int i = 0; i <= strlen(tempBinary); i++)
    {
        if (tempBinary[i] == '.' || tempBinary[i] == '\0')
        {
            segmentBinary[charIndex] = '\0';
            charIndex = 0;
            for (int j = 0; j < IPV4_SEGMENT_BITS; j++)
            {
                if (segmentBinary[j] == '1')
                {
                    segments[segmentIndex] |= 1 << (IPV4_SEGMENT_BITS - 1 - j);
                }
                else if (segmentBinary[j] != '0')
                {
                    printf("Invalid binary digit.\n");
                    return;
                }
            }
            segmentIndex++;
        }
        else
        {
            segmentBinary[charIndex++] = tempBinary[i];
        }
    }

    if (segmentIndex != IPV4_SEGMENT_COUNT)
    {
        printf("Invalid binary address format.\n");
        return;
    }

    printf("IPv4 representation: %u.%u.%u.%u\n", segments[0], segments[1], segments[2], segments[3]);
}
