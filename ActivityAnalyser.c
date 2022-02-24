//irfan kaan algan 2328599
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


struct TempSensors{// this struct takes the elements of txt file without doing any operation
    int TempSensorID;
    char TempStatus[5];
    int TempTime;
    
};
struct sensors{ // this struct takes the elements of tempSensors by ignoring tempTime-> time less than two minutes
    int sensorID;
    char status[5];
    int time;
};
struct sensors *createSensorDataArray(int *);
int searchPattern(struct sensors*,char [],int);
void printPatern(struct sensors*,int, int );

int main(){
	int i,size; // holds size of sensor table
    int factor = 1; // we will use to split string (patternInput)
	char patternInput[10];  //we will take the input as string
    struct sensors *sensorsDataTable; //sensor table struct
    sensorsDataTable = createSensorDataArray(&size);    //initialise table
    char iot[10][50] = {"Watering the flowers","Sleeping","Eating","Relaxing","Studying","Washing","Cooking","Bathroom","Getting Dressed","Entering/Leaving"}; // store internet of things sensors name
    printf("\nCreate a pattern now.\n0. Watering the flowers\n1. Sleeping\n2. Eating\n3. Relaxing\n4. Studying\n5. Washing\n6. Cooking\n7. Bathroom\n8. Getting Dressed\n9. Entering/Leaving\n");
    printf("Enter a pattern: ");
    scanf("%s",patternInput); 
    int sizeOfPattern = strlen(patternInput); // we will use the size of input to split the string and print the result
    if(sizeOfPattern > size+1){ // Cannot enter more than the number of patterns given in the txt file. our txt file size is 16 now and it may be changed.
        printf("size of pattern cannot be bigger than iot");
        exit(1);
    }
	printf("Pattern is created: ");
    int element = atoi(patternInput);   //convert patternInput to integer
    int temp = element;     //holds that integer in temp.
    while(temp){
        temp=temp/10;
        factor = factor*10;}
    while(factor>1){
        factor = factor/10;
        printf("%s > ",iot[element/factor]);
        i++;
        element = element % factor;}
    //these 2 while split the integer into pieces and find that piece in iot table and print
    printf("\n");
	searchPattern(sensorsDataTable,patternInput,size);
    return 0;
}
void printPatern(struct sensors *sensorsRecord,int size,int index){
    int totalTime = 0;
    int i;
    int hour, minute, second;
    char iot[10][50] = {"Watering the flowers","Sleeping","Eating","Relaxing","Studying","Washing","Cooking","Bathroom","Getting Dressed","Entering/Leaving"};
    for(i = 0;i < size;i++){
        totalTime = totalTime +sensorsRecord[index].time;   //when we find the index, it should start from the index we find and go up to the size of the text entered.
                                                            // and we will add the time of that indexes
        printf("%s > ",iot[sensorsRecord[index].sensorID]);
        index++;
    }
    hour = (totalTime/3600); 
	minute = (totalTime -(3600*hour))/60;
	second = (totalTime -(3600*hour)-(minute*60));
    printf("%d hour(s), %d minute(s), %d second(s)\n",hour,minute,second);  //converts total time(s) into hour, minute and second
		
}
int searchPattern(struct sensors *sensorsRecord,char pattern[10],int size){
	int M = strlen(pattern);
    int N =  size+1;
    int element = atoi(pattern);
    int factor = 1, i= 0;
    int temp = element;
    int* out = (int*) malloc(M * sizeof(int));
   while(temp){
        temp=temp/10;
        factor = factor*10;}
    while(factor>1){
        factor = factor/10;
        out[i] = element/factor;
        i++;
        element = element % factor;}	
        // I converted the string array entered into the int array because the sensorID in our txt file were written in integer format.
   i = 0;
   int j = 0;
   int p = 0;
   int t = 0;
   int h = 1;
   int d = 10;
   int q = 11;
   for (i = 0; i < M - 1; i++)
      h = (h * d) % q;
   for (i = 0; i < M; i++){
      p = (d * p + out[i]) % q;
      t = (d * t + sensorsRecord[i].sensorID) % q;
   }
   for (i = 0; i <= N - M; i++){
      if (p == t){
         for (j = 0; j < M; j++){
            if (sensorsRecord[i + j].sensorID != out[j]){
                break;
            }
         }
         if (j == M){
            printPatern(sensorsRecord,M,i);
            return main();
         }

      }
      if (i < N - M){
         t = (d * (t - sensorsRecord[i].sensorID * h) + sensorsRecord[i + M].sensorID) % q;
         if (t < 0)
            t = (t + q);
      }
   }
	//Rabin-Karp Algorithm
}

struct sensors *createSensorDataArray(int *size){
	
    int timeRecord, i = 0, count = 0;
    int newSize;
    FILE *fileIn = fopen("C:\\Users\\IRPHAN\\Desktop\\Assignment 4\\sensordata.txt","r");

    if(fileIn == NULL)
    {
        printf("FAILED!\n");
        exit(1);
    }
    int listLength=0;
    char charNum;
    while ((charNum=fgetc(fileIn))!=EOF){
        if (charNum=='\n'){
            listLength++;   //calculate number of lines in txt file
        }
    }
    fclose(fileIn);
    struct TempSensors *TempSensorTable = malloc(sizeof(struct TempSensors) * listLength);  // allocate for the number we find.(listLength)
    
    FILE *file1In = fopen("C:\\Users\\IRPHAN\\Desktop\\Assignment 4\\sensordata.txt","r");
    if(file1In == NULL)
    {
        printf("FAILED!\n");
        exit(1);
    }
    
    
    while (fscanf(file1In,"%d %s %d\n", &TempSensorTable[i].TempSensorID, TempSensorTable[i].TempStatus, &TempSensorTable[i].TempTime)!=EOF){
        i++;
    }

    fclose(file1In);
	for(i = 0;i <= listLength;i = i + 2){
		if(TempSensorTable[i+1].TempTime < TempSensorTable[i].TempTime){	// we need to check if sensor.time passed one day period
			timeRecord = (TempSensorTable[i+1].TempTime - TempSensorTable[i].TempTime) + 86399;
			if(timeRecord < 120)
				count++;		// I calculated the number of sensor time lower than 2 min
				 
		}	
		else{
			timeRecord = fabs(TempSensorTable[i+1].TempTime - TempSensorTable[i].TempTime);
			if(timeRecord < 120)
				count++; 
		}
	}
	
	newSize = (listLength - count*2)/2; // we calculate the new size by doing listlengt - (number of elemets that is less than two min *2) because each element has on and off state thats whe we multiplied by 2
	
	
	struct sensors *sensorTable = malloc(sizeof(struct sensors) * newSize); 

	int j= 0, k = 0, z = 0;
	for(i = 0;i <= listLength ; i = i + 2){
		k = j;
		z = i;
		if(TempSensorTable[i+1].TempTime < TempSensorTable[i].TempTime){	// we need to check if sensor.time passed one day period
			timeRecord = (TempSensorTable[i+1].TempTime - TempSensorTable[i].TempTime) + 86399;
			if(timeRecord > 120){
				sensorTable[j].sensorID = TempSensorTable[z].TempSensorID;
				sensorTable[j].time = timeRecord;	
				z++;
				j++;
			}
			k++;
		}	
		else{
			timeRecord = fabs(TempSensorTable[i+1].TempTime - TempSensorTable[i].TempTime); 
			if(timeRecord > 120){
				sensorTable[j].sensorID = TempSensorTable[z].TempSensorID;
				sensorTable[j].time = timeRecord;	
				z++;
				j++;
			}
			k++;
		}
	}       ///  copy the old table to new table(sensorTable)
	*size = newSize;
    return sensorTable;
}


