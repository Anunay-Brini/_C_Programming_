#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_ROOMS 10
#define FILENAME "bookings.dat"
struct Guest
{
	char name[50];
	char phoneNumber[15];
	char checkInDate[11];
	char checkOutDate[11];
	int roomNumber;
};


struct Room
{
	int roomNumber;
	float rent;
	int isBooked;
	struct Guest guest;
};


int calculateDays(char *startDate, char *endDate)
{
	int startYear, startMonth, startDay;
	int endYear, endMonth, endDay;
	sscanf(startDate, "%d-%d-%d", &startYear, &startMonth, &startDay);
	sscanf(endDate, "%d-%d-%d", &endYear, &endMonth, &endDay);
	int startTotalDays = startYear * 365 + startMonth * 30 + startDay;
	int endTotalDays = endYear * 365 + endMonth * 30 + endDay;
	return endTotalDays - startTotalDays;
}


void loadRoomData(struct Room rooms[])
{
	FILE *file = fopen(FILENAME, "rb");
	if(file) {
		fread(rooms, sizeof(struct Room), MAX_ROOMS, file);
		fclose(file);
	}
}


void saveRoomData(struct Room rooms[])
{
	FILE *file = fopen(FILENAME, "wb");
	if(file) {
		fwrite(rooms, sizeof(struct Room), MAX_ROOMS, file);
		fclose(file);
	}
}


void initializeRooms(struct Room rooms[])
{
	int i;
	for(i=0; i<MAX_ROOMS; i++)
	{
		rooms[i].roomNumber = i + 1;
		rooms[i].rent = 2000;
		rooms[i].isBooked = 0;
	}
}


void displayAvailableRooms(struct Room rooms[])
{
	int i;
	printf("\n--- Available Rooms ---\n");
	for(i=0; i< MAX_ROOMS; i++)
	{
		if(!rooms[i].isBooked)
		{
			printf("Room %d (Rent: %f)\n", rooms[i].roomNumber, rooms[i].rent);
		}
	}
}


int isRoomAvailable(struct Room rooms[],int roomNumber,
                    char*checkInDate,char*checkOutDate)
{
	int i;
	for(i=0; i<MAX_ROOMS; i++)
	{
		if (rooms[i].roomNumber == roomNumber && rooms[i].isBooked) {
			int days = calculateDays(rooms[i].guest.checkInDate, rooms[i]
			                         .guest.checkOutDate);
			int requestedDays = calculateDays(checkInDate, checkOutDate);
			if ((strcmp(checkInDate, rooms[i].guest.checkOutDate) < 0) &&
			        (strcmp(checkOutDate, rooms[i].guest.checkInDate) > 0)) {
				return 0;
			}
		}
	}
	return 1;
}



void bookRoom(struct Room rooms[])
{
	int roomNumber;
	char checkInDate[11], checkOutDate[11];
	struct Guest guest;
	displayAvailableRooms(rooms);
	printf("Enter the room number to book: ");
	scanf("%d", &roomNumber);
	if(roomNumber<1||roomNumber>MAX_ROOMS||rooms[roomNumber-1].isBooked)
	{
		printf("Invalid room number or room is already booked.\n");
		return;
	}
	printf("Enter guest name: ");
	getchar();
	fgets(guest.name, sizeof(guest.name), stdin);
	guest.name[strcspn(guest.name, "\n")] = '\0';
	printf("Enter guest phone number: ");
	fgets(guest.phoneNumber, sizeof(guest.phoneNumber), stdin);
	guest.phoneNumber[strcspn(guest.phoneNumber, "\n")] = '\0';
	printf("Enter check-in date (YYYY-MM-DD): ");
	scanf("%s", checkInDate);
	printf("Enter check-out date (YYYY-MM-DD): ");
	scanf("%s", checkOutDate);
	if(isRoomAvailable(rooms, roomNumber, checkInDate, checkOutDate))
	{
		rooms[roomNumber - 1].isBooked = 1;
		strcpy(rooms[roomNumber - 1].guest.name, guest.name);
		strcpy(rooms[roomNumber - 1].guest.phoneNumber, guest.phoneNumber);
		strcpy(rooms[roomNumber - 1].guest.checkInDate, checkInDate);
		strcpy(rooms[roomNumber - 1].guest.checkOutDate, checkOutDate);
		rooms[roomNumber - 1].guest.roomNumber = roomNumber;
		printf("Room %d booked successfully.\n", roomNumber);
	}
	else
	{
		printf("Room %d is not available for the selected dates.\n", roomNumber);
	}
}



void calculateBill(struct Room rooms[])
{
	int roomNumber;
	printf("Enter room number to calculate the bill: ");
	scanf("%d", &roomNumber);
	if(roomNumber<1||roomNumber>MAX_ROOMS||!rooms[roomNumber-1].isBooked)
	{
		printf("Invalid room number or room is not booked.\n");
		return;
	}
	int stayDuration = calculateDays(rooms[roomNumber-1].guest.checkInDate,
	                                 rooms[roomNumber - 1].guest.checkOutDate);
	float totalBill = rooms[roomNumber - 1].rent * stayDuration;
	printf("Total Bill for Room %d: %.2f\n",roomNumber,totalBill);
}

int main()
{
	struct Room rooms[MAX_ROOMS];
	int choice;
	initializeRooms(rooms);
	loadRoomData(rooms);
	while(1)
	{
		printf("\n----- Hotel Room Booking System -----\n");
		printf("1. Book a Room\n");
		printf("2. View Available Rooms\n");
		printf("3. Calculate Bill\n");
		printf("4. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			bookRoom(rooms);
			break;
		case 2:
			displayAvailableRooms(rooms);
			break;
		case 3:
			calculateBill(rooms);
			break;
		case 4:
			saveRoomData(rooms);
			printf("Exiting the system. Goodbye!\n");
			return 0;
		default:
			printf("Invalid choice. Please try again.\n");
		}
	}
	return 0;
}

