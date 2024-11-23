/*
C Programming Coursework

Kaiwen Zhao 11072741

Project Overview:
1. The program reads ID, Charge, and Energy data from `dataset.txt`. If reading fails, an error is reported. 
   - Code for this part: Lines 23-34. Status return: Lines 39-41.
2. It calculates the mean, sample standard deviation (Sdev), max, and min values for Charge and Energy.
   - Code for this part: Lines 76-84. Function declarations: Lines 6-10.
3. It prints the calculated data in the required table format.
   - Code for this part: Lines 87-94.

Key Features:
- Dynamic Memory Allocation: Allocates memory efficiently to avoid overflow. The program terminates if allocation fails.
- Pointer Usage: Pointers are used for storing and accessing array data, improving memory efficiency and speed. This avoids duplicating arrays.
- Functions: Declared at the top for readability and debugging ease.
- Error Handling: Errors are reported clearly, such as file reading failures (with error codes and descriptions) and incorrect file formatting.
*/


#include <stdio.h> // Include the standard library header for input and output
#include <stdlib.h> // Include the standard library header for malloc()
#include <errno.h>  // Include the errno header for error handling
#include <string.h> // Include the string header for strerror()
#include <math.h> // Include the math header for sqrt()

float calc_mean(float *arr, int size); //declare functions for calculation part
float calc_max(float *arr, int size);
float calc_min(float *arr, int size);
float calc_sdev(float *arr, int size, float mean);


int main(){

// 1. File reading and storing part

    FILE *file = fopen("dataset.txt","r"); // Open the dataset.txt file in read mode.

    if (file == NULL){
        perror("Error opening file");   //error handling
        printf("Error code:%d\n",errno);  //print error code
        printf("Error description:%s\n",strerror(errno));   //print the error code and description

        return 1;   //terminate the program
    }

    
    /* Although the coursework requires 100 lines to be read, I still want to make the number of lines to be read and the data to be stored 
    a variable so that it can be more versatile and flexible to changes. It is worth noting that I deliberately declare this variable before
    reading the file, so that the number of lines in the txt file to be read will be the same as numbers stored in the arrays, in order to 
    use the space more efficiently and improve the total reading and storing process. */

    int num = 100, i = 0, id; //define i for while loop in line 35
    float charge, energy;  //define variables as float that read from file
    char line[256];       //define line as a string with the length of num
    int status = 0;      //define status as 0, which means the file is read successfully


    //allocate dynamic memory for array_id, array_charge, array_energy
    int *array_id = malloc(num * sizeof(int));              //allocate dynamic memory for array_id, array_charge, array_energy
    float *array_charge = malloc(num * sizeof(float));      //float is used for charge and energy because they are float in the file
    float *array_energy = malloc(num * sizeof(float)); 

    
  if (array_id == NULL || array_charge == NULL || array_energy == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        
        //free the memory allocated for arrays to avoid memory overflow
        free(array_id); 
        free(array_charge);
        free(array_energy);
        fclose(file);
        return 1;
    }
    
    while(fgets(line,sizeof(line),file) != NULL && i < num){       //read file line by line and store data in arrays until the end of file or the number of lines required to read is reached

        if (sscanf(line, "%d,%f,%f", &id, &charge, &energy) == 3){  // read data from file and store in arrays only if the data is in the correct format
            
            *(array_id + i) = id;    //using Pointers to store id, charge and energy in arrays
            *(array_charge + i) = charge;
            *(array_energy + i) = energy;
            i++;    //i is used to count the number of lines read and the number of data stored in the arrays
            
        }else {
            printf("Status 1: Error processing line: %s", line);  //error if the data is not in the correct format
            status = 1;   //change status to 1, which means the file is not read successfully
            break;   //terminate the loop
        }
    }
    fclose(file);   //close file
    if (status == 1) {
        //free the memory allocated for arrays to avoid memory overflow
        free(array_id);
        free(array_charge);
        free(array_energy);
        return 1;
    }

// 2. Calculation part

    float charge_mean = calc_mean(array_charge, i);     // calculate mean, max, min and standard deviation of charge and energy using functions
    float energy_mean = calc_mean(array_energy, i);     // the reason I use "i" instead of "num" is that "i" is the exact number of data stored in the arrays, while "num" may exceed that. 
    float charge_max = calc_max(array_charge, i);
    float energy_max = calc_max(array_energy, i);
    float charge_min = calc_min(array_charge, i);
    float energy_min = calc_min(array_energy, i);
    float charge_sdev = calc_sdev(array_charge, i, charge_mean);
    float energy_sdev = calc_sdev(array_energy, i, energy_mean);

// 3. Printing part
    
    // Print the calculated statistics in a formatted table.
    printf("| 2741|  Charge |  Energy |\n");
    printf("|-----|---------|---------|\n");
    printf("| Mean|   %5.2f |   %5.2f |\n", charge_mean, energy_mean);
    printf("| Sdev|   %5.2f |   %5.2f |\n", charge_sdev, energy_sdev);
    printf("| Min |   %5.2f |   %5.2f |\n", charge_min, energy_min);
    printf("| Max |   %5.2f |   %5.2f |\n", charge_max, energy_max);

    //free the memory allocated for arr ays to avoid memory overflow
    free(array_id);
    free(array_charge);
    free(array_energy);

    return 0;   //terminate the program
}

//declare functions for calculation part
float calc_mean(float *arr, int size){  //calculate mean value using pointers
    float sum = 0;
    for (int i = 0; i < size; i++){
        sum += *(arr + i);  //using pointers to access data in arrays by varying the address of the pointer
    }
    float mean = sum / size;
    return mean;    //return the mean value
}

float calc_max(float *arr, int size){   //calculate max value using pointers
    float max = *arr;
    for (int i = 0; i < size; i++){
        float result = *(arr + i);  //using pointers to access data in arrays by varying the address of the pointer
        if (result > max)
        max = result;
    }
    return max;   //return the max value
}

float calc_min(float *arr, int size){   //calculate min value using pointers
    float min = *arr;
    for (int i = 0; i < size; i++){
        float result = *(arr + i);  //using pointers to access data in arrays by varying the address of the pointer
        if (result < min)
        min = result;
    }
    return min;  //return the min value
}

float calc_sdev(float *arr, int size, float mean){  //calculate sample standard deviation using pointers
    float sdsum = 0;
    for(int i = 0; i < size; i++){
        sdsum += (*(arr + i) - mean) * (*(arr + i) - mean);  //using pointers to access data in arrays by varying the address of the pointer
    }

    float sdev = sqrt(sdsum / (size - 1));  //calculate sample standard deviation

    return sdev;    //return the sample standard deviation
}