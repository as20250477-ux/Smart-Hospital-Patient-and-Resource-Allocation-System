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

void registerPatient();
void viewPriorityQueue();
void genarateReport()   {printf("TODO: generate report \n");}
void saveBedStatus()    {printf("TODO: save bed status\n");}
void loadBedStatus()    {printf("TODO: load bed status\n");}

int main()
{
    loadBedStatus();
    int choice;

    do{
        printf("\n---------------------------------");
        printf("\n====  SMART HOSPITAL SYSTEM  ====\n");
        printf("---------------------------------\n");
        printf("1. Register New Patient        \n");
        printf("2. View Patients by Priority   \n");
        printf("3. Generate Reports            \n");
        printf("4. Exit and Save               \n");
        printf("---------------------------------\n");
        printf("Enter choice : ");
        scanf("%d",&choice);
        printf("---------------------------------\n");

        switch (choice)
        {
            case 1: registerPatient(); break;
            case 2: viewPriorityQueue(); break;
            case 3: genarateReport(); break;
            case 4: saveBedStatus(); printf("Bed status saved. good bye!\n"); break;
            default: printf("Invalid choice , Try again. \n");
        }
    }
    while (choice != 4);
    return 0;
}
int findFreeBed(int wardIndex)
{
    for (int b = 0; b < wardCapacity[wardIndex]; b++){
        if (bedOccupancy[wardIndex][b] == 0) return b;
    }
    return -1;
}
void calculateBill(int i);
void printBill(int i);
void appendPatientRecord(int i);

void registerPatient()
{
    if (patientCount >= MAX_PATIENTS){
        printf("Patient Limit reached.\n");
        return;
    }

    int i = patientCount;

    printf("Enter patient name :");
    scanf(" %[^\n]", patientName[i]);

    printf("Enter patient age  :");
    scanf("%d", &patientAge[i]);

    printf("Urgency level \n(1.Normal,2.Urgent,3.Critical):");
    scanf("%d",&urgencyLevel[i]);

    printf("Specialty ID (1-4) :");
    scanf("%d",&specialtyChoice[i]);

    printf("Admitted to ward? (1 = Yes , 0 = No ):");
    scanf("%d", &isAdmitted[i]);

    if (isAdmitted[i] == 1){
        printf("Ward ID (1-4):");
        scanf("%d",&wardChoice[i]);
        printf("Days admitted:");
        scanf("%d",&daysAdmitted[i]);

        int w = wardChoice[i] - 1;
        int bed = findFreeBed(w);
        if (bed == -1){
            printf("Sorry, %s is full.\nRegistering as outpatient instead.\n",wardName[w]);
            isAdmitted[i] = 0;
            daysAdmitted[i] = 0;
            bedNunber[i] =  -1;
        }
        else{
            bedOccupancy[w][bed] = 1;
            bedNunber[i] = bed;
        }
    }
    else{
        daysAdmitted[i] = 0;
        bedNunber[i] = -1;
    }
    void calculateBill(int i);
    void printBill(int i);
    void appendPatientRecord(int i){printf("TODO: append patient record\n");}

    patientCount++;
}
void calculateBill(int i)
{
    int s = specialtyChoice[i] - 1;

    waitTime[i] = queueCount[s] * consultTime[s];
    queueCount[s]++;

    if (urgencyLevel[i] == 1)
        surcharge[i] = 0;
    else if (urgencyLevel[i == 2])
        surcharge[i] = 0.20*baseFee[s];
    else
        surcharge[i] = 0.5 *baseFee[s];

    if (isAdmitted[i] == 1){
        int w = wardChoice[i] - 1;
        wardCost[i] = daysAdmitted[i]*wardDailyRate[w];
    }
    else {
        wardCost[i] = 0;
    }

    grossTotal[i] = baseFee[s] + surcharge[i] + wardCost[i];

    if (patientAge[i] < 5 || patientAge[i] > 65)
        discount[i] = grossTotal[i]*0.15;
    else
        discount[i] = 0;

    finalAmount[i] = grossTotal[i] - discount[i];
}

void printBill(int i)
{
    int s = specialtyChoice[i] - 1;

    printf("\n==============================================================\n");
    printf("          ---SMART HOSPITAL ADMISSION AND BILL---   \n");
    printf("--------------------------------------------------------------\n");
    printf("Patient ID         : PAT-%d\n", 1000 + patientCount + 1);
    printf("Patient Name       : %s\n",patientName[i]);
    printf("Age                : %d Years",patientAge[i]);

    if (discount[i]>0)
        printf("(15%% Subsidy Eligible)");
    printf("\n");
    printf("Specialty          : %s\n",specialtyName[s]);

    if (isAdmitted[i] == 1){
        int w = wardChoice[i] - 1;
        printf("Assigned Ward      : %s (Bed #%02d)\n",wardName[w],bedNunber[i]+1);
    }
    else{
        printf("Assigned Ward      : Outpatient (OPD)\n");
    }

    printf("Urgency Level      : Level %d\n", urgencyLevel[i]);
    printf("------------------------------------------------------------------\n");
    printf("Base Consultation Fee   : LKR %.2f\n", baseFee[s]);
    printf("Emergency Surcharge     : LKR %.2f\n", surcharge[i]);
    printf("ward Stay Cost (%d Days): LKR %.2f\n", daysAdmitted[i], wardCost[i]);
    printf("-------------------------------------------------------------------\n");
    printf("Gross Total Bill        : LKR %.2f\n", grossTotal[i]);
    printf("Age Subsidy Discount    : LKR -%.2f\n", discount[i]);
    printf("-------------------------------------------------------------------\n");
    printf("Final Payable Amount    : LKR %.2f\n", finalAmount[i]);
    printf("Estimated Waiting Time  : %.2f mins\n", waitTime[i]);
    printf("===================================================================\n");

}

void viewPriorityQueue()
{
    int order[MAX_PATIENTS];
    for (int i = 0; i<patientCount; i++) order[i] = i;
    for (int a = 0; a<patientCount -1; a++){
        for (int b = 0; b<patientCount -1 -a; b++){
            if (urgencyLevel[order[b]] < urgencyLevel[order[b+1]]){
                int temp = order[b];
                order[b] = order[b+1];
                order[b+1] = temp;
            }
        }
    }

    printf("\n     --- Patients by Priority --- \n");
    for (int k = 0; k < patientCount; k++){
        int i = order[k];
        printf("%d. %s (Level %d)\n", k + 1 , patientName[i],urgencyLevel[i]);
    }
}
