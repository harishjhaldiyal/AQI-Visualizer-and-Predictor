/**
* ENGG1110 Problem Solving by Programming
*
* Project Phase 3, Task ABC
*
* I declare that the assignment here submitted is original
* except for source material explicitly acknowledged,
* and that the same or closely related material has not been
* previously submitted for another course.
* I also acknowledge that I am aware of University policy and
* regulations on honesty in academic work, and of the disciplinary
* guidelines and procedures applicable to breaches of such
* policy and regulations, as contained in the website.
*
* University Guideline on Academic Honesty:
*   http://www.cuhk.edu.hk/policy/academichonesty/
*
* Student Name : HARISH-KUMAR
* Student ID   : 1155090935
* Class/Section: JL01
* Date         : 6 APRIL 2017
*/


#define _CRT_SECURE_NO_WARNINGS // to disable Microsoft VS warnings
#include <stdio.h> // standard i/o header file
#include <string.h>
typedef struct
{
	int date, month, year, hour;
	double NO2, PM10;
} timestamp;						// Defining a structure named 'timestamp' having 'date','month','year','hour','NO2' and 'PM10' as members
int main(void)
{
	FILE *fptr, *fptr2, *fptr3;		// Declaring file pointer variables
	char s[101];
	int l, n, i, count = 0, minpos, j;
	timestamp array1[11000], temp;	// Declaring an array of structure 
	printf("AQI Processing Final Phase\n");
	printf("Input filename: ");
	// Inputting a string as filename and removing the trailing newline character if needed
	fgets(s, 101, stdin);
	l = (int)strlen(s);
	if (s[l - 1] == '\n')
		s[l - 1] = '\0';
	fptr = fopen(s, "r");		// Opening a file 's' for reading only
	if (fptr == NULL)			// Checking if the file successfully opens or not and print out the required message
	{
		printf("Cannot open input file %s\n", s);
		return 0;
	}
	fscanf(fptr, "%d", &n);		// Reading number of records from the file and initializing it to a variable 'n'
	for (i = 0; i < n; i++)
	{
		fscanf(fptr, "%d-%d-%d%d%lf%lf", &array1[i].date, &array1[i].month, &array1[i].year, &array1[i].hour, &array1[i].NO2, &array1[i].PM10);		// Reading data from the file in the required format and initializing them to the members of array of structure
		// Counting the number of N.A.
		if (array1[i].NO2 == 0)
			count++;
		if (array1[i].PM10 == 0)
			count++;
	}
	printf("Read %d record(s)\n", n);
	printf("Hit %d N.A.\n", count);
	// Initializing a new string having the same name as file name before with an extension of '.bak.csv'
	char backup[101];
	strcpy(backup, s);
	strcat(backup, ".bak.csv");
	fptr2 = fopen(backup, "w");		// Creating a new file 'backup' and opening it for writing only
	if (fptr2 == NULL)				// Checking if the file successfully opens or not and print out the required message
	{
		printf("Cannot open output file %s\n", backup);
		return 0;
	}
	fprintf(fptr2, "%d\n", n);
	for (i = 0; i < n; i++)
	{
		fprintf(fptr2, "%d-%02d-%02d,%02d,%.2f,%.2f\n", array1[i].year, array1[i].month, array1[i].date, array1[i].hour, array1[i].NO2, array1[i].PM10);		// Writing data to the 'backup' file from the original file in the required format
	}
	fclose(fptr2);		// Closing 'backup' file
	// Initializing a new string having the same name as 'backup' file name with an extension of '.sorted.csv'
	char sorted[101];
	strcpy(sorted, s);
	strcat(sorted, ".sorted.csv");
	fptr3 = fopen(sorted, "w");		// Creating a new file 'sorted' and opening it for writing only
	if (fptr3 == NULL)				// Checking if the file successfully opens or not and print out the required message
	{
		printf("Cannot open output file %s\n", sorted);
		return 0;
	}
	// Performing selection sort method to sort the members of structure in the required format
	for (i = 0; i<n-1; i++)
	{
		minpos = i;		// Letting the minimum position (the position where minimum valued member of array of structure occur) to be equal to the value of loop variable 'i'
		for (j = i + 1; j<n; j++)
		{
			if (array1[j].year<array1[minpos].year)
			{
				minpos = j;
			}
			else if (array1[j].year == array1[minpos].year && array1[j].month<array1[minpos].month)
			{
				minpos = j;
			}
			else if (array1[j].year == array1[minpos].year && array1[j].month == array1[minpos].month && array1[j].date<array1[minpos].date)
			{
				minpos = j;
			}
			else if (array1[j].year == array1[minpos].year && array1[j].month == array1[minpos].month && array1[j].date == array1[minpos].date && array1[j].hour<array1[minpos].hour)
			{
				minpos = j;
			}
		}
		// Swapping the values when new minimum valued position has found
		if (minpos != 0)
		{
			temp = array1[minpos];
			array1[minpos] = array1[i];
			array1[i] = temp;
		}
	}
	fprintf(fptr3, "%d\n", n);
	// Writing the values of sorted members of array of structure in the required format into the 'sorted' file
	for (i = 0; i < n; i++)
	{
		fprintf(fptr3, "%d-%02d-%02d,%02d,%.2f,%.2f\n", array1[i].year, array1[i].month, array1[i].date, array1[i].hour, array1[i].NO2, array1[i].PM10);
	}
	fclose(fptr3);		// Closing 'sorted' file
	return 0;
}
