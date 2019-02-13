// Subnet Calculator | Jack Nelson

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int ipVerify(char* ipAddress, unsigned char* octetArray) {
	// Function verifies a valid IP has been entered, and then updates the octal array with the validated octets

	char* token;
	int i = 0;
	int j = 0;
	int periodCount = 0;

	// We will continue grabbing tokens whilst it isn't null
	token = strtok(ipAddress, ".");
	while (token != NULL) {

		// Loop through each character and check it's a digit
		// If it isn't break out. We use j to see if it looped the right amount of times
		for (j=0; j<strlen(token); j++) {
			if (isdigit(token[j]) == 0) {
				break;
			}
		}

		// If the right amount of digits have been entered, confirm octal as validated and add to array
		if (strlen(token) > 0 && strlen(token) < 4 && j == strlen(token)
				&& atoi(token) < 256 && atoi(token) >= 0) {
			periodCount++;
			octetArray[i] = atoi(token);
		} else {
			// No point in continuing if even one octet fails the test
			break;
		}

		i++;

		token = strtok(NULL, ".");
	}

	if (periodCount != 4) {
		return(0);
	} else {

		return(1);
	}
}

void printSubnetInfo(u_int32_t* addressOctets, int* CIDR, int* subnetBits) {
	// Prints infomation about the given subnet.
	// Takes pointers to the required data, however does not change anything within them.
	// Any required manipulation is done with local variables

	u_int32_t netAddress;
	u_int32_t netMask;
	
	netMask = (0xFFFFFFFF << (32 - (*CIDR + *subnetBits)) & 0xFFFFFFFF);
	netAddress = *addressOctets & netMask;

	// Unpack and display the network address
	printf("\nNetwork address: %d.%d.%d.%d/%d\n", (netAddress >> 24) & 0xFF, (netAddress >> 16) & 0xFF,
						    (netAddress >> 8) & 0xFF, (netAddress) & 0xFF, *CIDR + *subnetBits);

	// Subtract the network address from the broadcast address and take one from the result for total hosts
	printf("Total hosts: %d\n", ((netAddress | ~netMask) - netAddress) - 1);

	// Display the first host address by adding to each of our unpacked octets
	printf("First host address: %d.%d.%d.%d\n", ((netAddress + 1) >> 24) & 0xFF, ((netAddress + 1) >> 16) & 0xFF,
						    ((netAddress + 1) >> 8) & 0xFF, (netAddress + 1) & 0xFF);
	
	// Bitwise OR the address int with the negated mask to get the broadcast address in the variable
	netAddress = netAddress | ~netMask;

	// Subtract from the from the broadcast address for the final host address
	printf("Last host address: %d.%d.%d.%d\n", ((netAddress - 1) >> 24) & 0xFF, ((netAddress - 1) >> 16) & 0xFF,
						   ((netAddress - 1) >> 8) & 0xFF, (netAddress - 1) & 0xFF);
	
	// Unpack and display the broadcast address
	printf("Broadcast address: %d.%d.%d.%d\n", (netAddress >> 24) & 0xFF, (netAddress >> 16) & 0xFF,
						   (netAddress >> 8) & 0xFF, (netAddress) & 0xFF);
}

int main() {

	char ipAddress[18];
	char buffer[4];
	int CIDR;
	unsigned char* octetArray;
	octetArray = calloc(4, sizeof(char));
	u_int32_t addressOctets;
	
	int subnetNumber;
	int subnetBits = 0;
	int totalSubnets = 0;
	u_int32_t currentSubnet;
	int i;

	// Get the addess
	while (1) {
		printf("Enter IPv4 address now: ");
		fgets(ipAddress, 17, stdin);
		ipAddress[strlen(ipAddress)-1] = '\0';

		printf("Verifying: %s... ", ipAddress);

		// Verify it
		if (ipVerify(ipAddress, octetArray) == 0) {
			printf("Invalid IP entered.\n");
		} else {
			printf("Address verified!\n");
			break;
		}
	}

	// Get the CIDR number
	while (1) {
		printf("Enter subnet mask in CIDR notation now: ");
		fgets(buffer, 4, stdin);

		CIDR = atoi(buffer);

		if (CIDR > 0 && CIDR < 32) {
			break;
		} else {
			printf("Invalid CIDR entered. Try again.\n");
		}
	}

	printf("\n%d.%d.%d.%d/%d ", octetArray[0], octetArray[1], octetArray[2], octetArray[3], CIDR);

	if (octetArray[0] > 239) {
		printf("(Class E)\n");
	} else if (octetArray[0] > 223) {
		printf("(Class D)\n");
	} else  if (octetArray[0] > 191) {
		printf("(Class C)\n");
	} else if (octetArray[0] > 127) {
		printf("(Class B)\n");
	} else {
		printf("(Class A)\n");
	}

	// Pack bits of the IP address into an integer
	addressOctets = (octetArray[0] << 24) | (octetArray[1] << 16) | (octetArray[2] << 8) | (octetArray[3]);

	// Call the subnetinfo function for the network
	printSubnetInfo(&addressOctets, &CIDR, &subnetBits);

	do {
		printf("Enter number of required networks, or q to quit: ");
		fgets(buffer, 4, stdin);
		subnetNumber = atoi(buffer);

		if (subnetNumber == 0) {
			printf("Exiting...\n");
			exit(0);
		}

		// Determine the amount of bits required to contain the required networks
		while (subnetNumber > totalSubnets) {
			subnetBits++;
			totalSubnets = pow(2, subnetBits);
		}

		// Check we have the required amount of bits to subnet successfully
		if ((CIDR + subnetBits) > 31) {
			printf("Amount of networks too large to be accommodated.\n");
		}
	} while ((CIDR + subnetBits) > 31);

	printf("\nTotal subnets to be created: %d\n-------------------------------", totalSubnets); 

	// Construct the subnet network bits, then print the information
	for (i=0; i<totalSubnets; i++) {
		currentSubnet = (addressOctets & ((0xFFFFFFFF << (32 - CIDR)) & 0xFFFFFFFF))
				| i << (32 - (CIDR + subnetBits));
		printSubnetInfo(&currentSubnet, &CIDR, &subnetBits);
	}

	free(octetArray);
	
	return 0;
}

