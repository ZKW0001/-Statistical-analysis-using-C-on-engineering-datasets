# Statistical_Analysis_Using_C_on_Engineering_Datasets

## Project Overview:  
1. The program reads ID, Charge, and Energy data from `dataset.txt`. If reading fails, an error will be reported. 
   - Code for this part: Lines 23-34. Status return: Lines 39-41.
2. It calculates the mean, sample standard deviation (Sdev), max, and min values for Charge and Energy.
   - Code for this part: Lines 76-84. Function declarations: Lines 6-10.
3. It prints the calculated data in the required table format.
   - Code for this part: Lines 87-94.

## Key Features:  
- **Dynamic Memory Allocation:** Allocates memory efficiently to avoid overflow. The program terminates if allocation fails.
- **Pointer Usage:** Pointers are used for storing and accessing array data, improving memory efficiency and speed. This avoids duplicating arrays.
- **Functions:** Declared at the top for readability and debugging ease.
- **Error Handling:** Errors are reported clearly, such as file reading failures (with error codes and descriptions) and incorrect file formatting.

## Example output:  
| 2741|  Charge |  Energy |  
|-----|---------|---------|  
| Mean|    3.32 |   12.89 |  
| Sdev|    0.15 |    0.53 |  
| Min |    1.91 |    7.69 |  
| Max |    3.40 |   13.15 |  
