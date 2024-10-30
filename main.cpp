/* Assignment-6-making-a-doubly-linked-list-clvessells */


// Libraries and headers
#include <iostream> 
#include <vector>
#include <cstdlib>
#include <cstddef>
#include <cmath>
#include "coordinate.h"

using namespace std;


// Function Prototypes 
void add_coordinate(Coordinate *&list_tail, int x, int y);
void forward_display(Coordinate *list_head);
void backward_display(Coordinate *list_tail);
void delete_coordinate(Coordinate *list_head, int coord_id_to_delete);
int list_length(Coordinate *list_head);
void closest_to(Coordinate *list_head, int x, int y);
void farthest_from(Coordinate *list_head, int x, int y);
int random_number_generator();



int main(int argc, char *argv[]){
	
	// Generate a seed number using number of seconds since Janurary 1970. Only needs to happen 1x per run.
	srand((unsigned)(time(0)));

		
	// Get number of pairs desired from user using the command line. If none entered, close program.
	int number_of_pairs = 0;
	
	if (argc > 1){
		
		number_of_pairs = atoi(argv[1]);
		cout << "\n\nYou requested " << number_of_pairs << " (X,Y) pairs.\n" << endl;
		
	}else{
		
		cout << "\n\n*****************NO INPUT ENTERED. CLOSING PROGRAM *******************\n\n" << endl;
		return 0;
	}
	
	
	// Declare struct and fill it with random ints.
	Coordinate *coordinates = new Coordinate[number_of_pairs];
	
	for(int i = 0; i < number_of_pairs; i++){
		
		coordinates[i].x = random_number_generator();
		coordinates[i].y = random_number_generator();
		coordinates[i].coord_id = i;
		
		// Set up pointers for each element.
		if (i > 0) {
			
			coordinates[i].previous = &coordinates[i - 1];
			coordinates[i - 1].next = &coordinates[i];
			
		} else {
			
			coordinates[i].previous = NULL; // First element has no previous
		}
			coordinates[i].next = NULL; // Last element's `next` will remain NULL initially
	}
		
	cout << "You have successfully filled " << number_of_pairs << " (X,Y) coordinates.\n" << endl;
	
	
	// Set up head and tail pointers.
	Coordinate *list_head = &coordinates[0];
	Coordinate *list_tail = &coordinates[number_of_pairs - 1];
	
	
	//Test Prints and Calls
	cout << "Your first random number is " << random_number_generator() << ".\n" << endl;
	cout << "Your second random number is " << random_number_generator() <<".\n" << endl;
	
	add_coordinate(list_tail, random_number_generator(), random_number_generator());
	add_coordinate(list_tail, random_number_generator(), random_number_generator());
	
	
	//Function calls
	forward_display(list_head);
	backward_display(list_tail);
	list_length(list_head);
	closest_to(list_head, 0, 0);
	farthest_from(list_head, 0, 0);	
	
	
	return 0;
}


/* Functions */ 


/* coord_id should be automatically incremented in the add_coordinate function based on the length of the list*/
//add_coordinate: adds a coordinate to the end of the linked list 
void add_coordinate(Coordinate *&list_tail, int x, int y){
	
	Coordinate *new_coordinate = new Coordinate;
	
	new_coordinate-> x = x;
	new_coordinate-> y = y;
	new_coordinate->coord_id = list_tail ? list_tail->coord_id + 1 : 0;
	new_coordinate->next = NULL;
    new_coordinate->previous = list_tail;
	
	list_tail->next = new_coordinate;
    list_tail = new_coordinate;
	
	cout << "Addition of new coordinate successful." << endl;
	cout << "You now have " << new_coordinate->coord_id + 1 << " (X,Y) pairs.\n" << endl;
}


// forward_display: displays all coordinates from beginning to end
void forward_display(Coordinate *list_head){
	
	cout << "\nDisplaying coordinates on list from head to tail:" << endl;
	
	Coordinate *current = list_head;
	
    while (current != NULL) {
        cout << "Coordinate Number " << current->coord_id + 1 << ":\n X: " << current->x << " Y: " << current->y << endl;
        current = current->next;
	}
	
    cout << "\n" << endl;
}


// backwards_display: displays all coordinates from end to beginning
void backward_display(Coordinate *list_tail){
	
	cout << "Displaying coordinates on the list from tail to head:" << endl;
	
	Coordinate *current = list_tail;
	
    while (current != NULL) {
		
        cout << "Coordinate Number " << current->coord_id + 1 << ":\n X: " << current->x << " Y: " << current->y << endl;
        current = current->previous;
    }
	cout << "\n" << endl;
}

// THIS IS THE FUNCTION I CAN NOT GET WORKING!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// delete_coordinate: removes a coordinate from the linked list (free memory!)
void delete_coordinate(Coordinate *list_head, int coord_id_to_delete){
	
	
}


//list_length: return the length of the list
int list_length(Coordinate *list_head){
	
	cout << "Display the length of the list:" << endl;
	
	Coordinate *current = list_head;
	int length = 0;
	
	while(current != NULL){
		
		length++;
		current = current->next;
	}
	
	cout << length << " elements total.\n" << endl;
}


// closest_to: find the coordinate that is closest to the given x, y and output the distance between the 2
void closest_to(Coordinate *list_head, int x, int y){
	
	Coordinate *current = list_head;
    double closest_distance = sqrt(pow(current->x - x, 2) + pow(current->y - y, 2));
    Coordinate *closest_coordinate = NULL;

    while (current != NULL) {
		
        double distance = sqrt(pow(current->x - x, 2) + pow(current->y - y, 2));
       
	   if (distance < closest_distance) {
            closest_distance = distance;
            closest_coordinate = current;
        }
		
        current = current->next;
    }

    if (closest_coordinate != NULL) {
        
		cout << "Closest Coordinate Number to (" << x << "," << y << ") is: " 
			 << closest_coordinate->coord_id 
             << " \nX: " << closest_coordinate->x << " Y: " << closest_coordinate->y 
             << " \nWith a distance of " << closest_distance << ".\n" << endl;
			 
    } else {
		
        cout << "No coordinates found." << endl;
    }
}


// farthest_from: find the coordinate that is furthest from the given x, y and output the distance between the 2
void farthest_from(Coordinate *list_head, int x, int y){
	
	Coordinate *current = list_head;
	
    double farthest_distance = sqrt(pow(current->x - x, 2) + pow(current->y - y, 2));
	
    Coordinate *farthest_coordinate = NULL;

    while (current != NULL) {
		
        double distance = sqrt(pow(current->x - x, 2) + pow(current->y - y, 2));
        
		if (distance > farthest_distance) {
			
            farthest_distance = distance;
            farthest_coordinate = current;
        }
		
        current = current->next;
    }

    if (farthest_coordinate != NULL) {
		
        cout << "Farthest Coordinate Number from (" << x << "," << y << ") is: " 
			 << farthest_coordinate->coord_id 
             << " \nX: " << farthest_coordinate->x << " Y: " << farthest_coordinate->y 
             << " \nWith a distance of " << farthest_distance << ".\n" << endl;
			 
    } else {
		
        cout << "No coordinates found." << endl;
    }
}

// random number generator
int random_number_generator(){
	
	int min = -50;
	int max = 50;
	
	//Generate random numbers
	int random = min + rand() % (max - min + 1);
	
	
	return random;
	
}