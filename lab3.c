#include <stdio.h>
#include <string.h>
#include <math.h>
#define LENGTH 20
#define QUEUE_SIZE 50
#include <time.h>
#define LOOPS 10000
#include <stdlib.h>
#define NUM_SYMPTOMS 10
#define NUM_GENDERS 3

//Global variables

char gender[NUM_GENDERS][LENGTH] = {"Male", "Female", "Other"};
char symptom[NUM_SYMPTOMS][LENGTH] = {"Paralysis", "Numbness", "Sore Throat", "Fainting", "Blurry Vision", "Bloody Nose", "Headache", "Acid Reflux", "Dehydration", "Inflammation"};
double waitByGender[NUM_GENDERS] = {0.0, 0.0, 0.0};
double waitBySymptom[NUM_SYMPTOMS] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
int countByGender[NUM_GENDERS] = {0, 0, 0};
int countBySymptom[NUM_SYMPTOMS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int genderQueue[QUEUE_SIZE];
int symptomQueue[QUEUE_SIZE];
int count = 0;
int turnedAway = 0;


void add() {
	

	if (count == QUEUE_SIZE) {

		turnedAway++;		
		
	} else {

		//Assign random numbers to patientGender & patientSymptom
		int patientGender = rand() % 3;
		int patientSymptom = rand() % 10;
		genderQueue[count] = patientGender;
		symptomQueue[count] = patientSymptom;
		
	}
	
	count++;
	
}

void next() {

	int finalCheck = rand() % 100 + 1;
		
	if (count == 0) {

		return;
			
	}

	int i;
	
		
	double patientWait = (((double)rand())/(double)RAND_MAX * 29.0) + 1;

	waitByGender[genderQueue[0]] += patientWait;
	waitBySymptom[symptomQueue[0]] += patientWait;
	
	countByGender[genderQueue[0]] += 1;
	countBySymptom[symptomQueue[0]] += 1;
	
	if (finalCheck > 85) {
		
		int tempGender = genderQueue[0];
		int tempSymptom = symptomQueue[0];

		for (i = 1; i < count; i++) {

			genderQueue[i-1] = genderQueue[i];
			symptomQueue[i-1] = symptomQueue[i];
	
		}
		
		genderQueue[count-1] = tempGender;
                symptomQueue[count-1] = tempSymptom;		

	} else { 

	for (i = 1; i < QUEUE_SIZE; i++) {

		genderQueue[i-1] = genderQueue[i];
		symptomQueue[i-1] = symptomQueue[i];
		
	}  		

	

	}

count--;
}

void experiment() {

	int start = rand() % 100 + 1;

	if (start > 50) {

		add();

	} else {
		
		next();
	}

}


void printTable() {

	int i;
	int j;

	printf("Gender/Symptom\t\tMean Wait\n");
	
	printf("______________________________________\n");
	
	for (j = 0; j < NUM_GENDERS; j++){

		double avgGenderWait = waitByGender[j] / countByGender[j];
		printf("%s\t\t\t%.02f\n", gender[j], avgGenderWait);
		
	}

	for (i = 0; i < NUM_SYMPTOMS; i++) {

		if (countBySymptom[i] == 0) {
			
			printf("%s\t\tN/A\n", symptom[i]);

		} else {

			double avgWait = waitBySymptom[i] / countBySymptom[i];

			printf("%s\t\t%.02f\n", symptom[i], avgWait);
		
		}

	}


}





int main() {
	
	int i;
        srand(time(0));		

	for (i = 0; i < LOOPS; i++) {

		experiment();		

	}	
			
	printTable();
	printf("\nTurned Away: %d\n", turnedAway);
        return 0;
}
