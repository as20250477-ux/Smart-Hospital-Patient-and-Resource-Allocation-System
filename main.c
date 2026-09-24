#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100
#define NUM_SPECIALTIES 4
#define NUM_WARDS 4

char specialtyName[NUM_SPECIALTIES][30] = {"General Practice (OPD)",
     "Paediatrics","Cardiology","Neurology"};

float baseFee[NUM_SPECIALTIES]     = {1500.00,2500.00,4500.00,5000.00};
float consultTime[NUM_SPECIALTIES] = {15,20,30,30};
int dailyCap[NUM_SPECIALTIES]      = {30,20,12,10};
int queueCount[NUM_SPECIALTIES]    = {0,0,0,0};

char wardName[NUM_WARDS][30]  = {"General Ward","Paediatric Ward",
     "Surgical Ward","ICU"};

float wardDailyRate[NUM_WARDS] = {3000.00,6000.00,12000.00,25000.00};
int wardCapacity[NUM_WARDS]    = {20,10,10,5};
int bedOccupancy[NUM_WARDS][20] = {0};

char patientName[MAX_PATIENTS][50];
int patientAge[MAX_PATIENTS];
int urgencyLevel[MAX_PATIENTS];
int specialtyChoice[MAX_PATIENTS];
int isAdmitted[MAX_PATIENTS];
int wardChoice[MAX_PATIENTS];
int daysAdmitted[MAX_PATIENTS];
int bedNunber[MAX_PATIENTS];

float waitTime[MAX_PATIENTS];
float surcharge[MAX_PATIENTS];
float wardCost[MAX_PATIENTS];
float grossTotal[MAX_PATIENTS];
float discount[MAX_PATIENTS];
float finalAmount[MAX_PATIENTS];

int patientCount = 0;
