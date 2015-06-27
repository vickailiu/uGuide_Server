#include "image_search.h"

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "ROSE_CDVSLib.h"

void run_sdk()
{
	//** First of all, Init SDK
	ROSE_InitSDK();

	ROSE_INDEX_Ptr pku_index = NULL;

	{
		///////Read database_0
		//** 0. Read all image files to a list
		FILE_NAME image_list0[10];
		int len = 10;

		FILE *fin = fopen("database0.txt", "r");
		for (int i = 0; i < len; i++)
			fscanf(fin, "%s", image_list0[i]);
		fclose(fin);

		//** 1. Create Index
		cout << "1. Create Index...." << endl;
		pku_index = ROSE_CreateIndex(image_list0, len);

		//** 2. Save index to File
		ROSE_SaveIndex(pku_index, "db_0.bin");

		//** 3. Free index
		ROSE_FreeIndex(pku_index);
		pku_index = NULL;
	}
	{
		///////Read database_1
		//** 0. Read all image files to a list
		FILE_NAME image_list1[12];
		int len = 12;

		FILE *fin = fopen("database1.txt", "r");
		for (int i = 0; i < len; i++)
			fscanf(fin, "%s", image_list1[i]);
		fclose(fin);

		//** 1. Create Index
		cout << "1. Create Index...." << endl;
		ROSE_INDEX_Ptr pku_index = NULL;
		pku_index = ROSE_CreateIndex(image_list1, len);

		//** 2. Save index to File
		ROSE_SaveIndex(pku_index, "db_1.bin");

		//** 3. Free index
		ROSE_FreeIndex(pku_index);
		pku_index = NULL;
	}

	//** 4. Merge index
	FILE_NAME index_list[2] = { "db_0.bin", "db_1.bin" };
	int len = 2;

	pku_index = ROSE_MergeIndex(index_list, len);
	cout << "Merge Index...." << endl;
	ROSE_SaveIndex(pku_index, "db.bin");
	cout << "Save Index...." << endl;
	ROSE_FreeIndex(pku_index);
	pku_index = NULL;
	cout << "Free Index...." << endl;

	//** 4. Load index
	pku_index = ROSE_LoadIndex("db.bin");
	cout << "Load Index...." << endl;

	//** 5. Add new image to index
	ROSE_AddToIndex(pku_index, "database/wangbook.jpg");
	cout << "Add to Index...." << endl;

	//** 6. Retrieval
	ROSE_Result pku_result[100];
	int max_ret_num = 100;
	ROSE_Retrieval(pku_index, "1.jpg", pku_result, &max_ret_num);

	printf("Retrieval return %d\n", max_ret_num);
	for (int i = 0; i < max_ret_num; i++)
		printf("i = %d, %s, %.3lf\n", i, pku_result[i].image_id, pku_result[i].score);

	ROSE_SaveIndex(pku_index, "db.bin");
	ROSE_FreeIndex(pku_index);
	pku_index = NULL;

	//** 7. Matching
	float score1 = ROSE_Matching("1.jpg", "11.jpg");
	printf("score1 = %.3lf\n", score1);

	float score2 = ROSE_Matching("1.jpg", "2.jpg");
	printf("score2 = %.3lf\n", score2);

	//** Remember to finish SDK
	ROSE_FinishSDK();
}
/*
IMAGE_FILE image_list[2500];
int len = 1000;

void run_sdk_1k()
{
//** First of all, Init SDK
ROSE_InitSDK();

//** 0. Read all image files to a list
FILE *fin = fopen("1a_images.txt", "r");
for (int i = 0; i < len; i ++)
fscanf(fin, "%s", image_list[i]);
fclose(fin);

ROSE_INDEX_Ptr pku_index = NULL;

//** 1. Create Index
cout << "1. Create Index...." << endl;
pku_index = ROSE_CreateIndex(image_list, len);

//** 2. Save index to File
ROSE_SaveIndex(pku_index, "db.bin");

//** 3. Free index
ROSE_FreeIndex(pku_index);
pku_index = NULL;

//** 4. Load index
pku_index = ROSE_LoadIndex("db.bin");

//** 5. Add new image to index
ROSE_AddToIndex(pku_index, "database/wangbook.jpg");

//** 6. Retrieval
ROSE_Result pku_result[100];
int max_ret_num = 100;
ROSE_Retrieval(pku_index, "1.jpg", pku_result, &max_ret_num);

printf("Retrieval return %d\n", max_ret_num);
for (int i = 0; i < max_ret_num; i ++)
printf("i = %d, %s, %.3lf\n", i, pku_result[i].image_id, pku_result[i].score);

ROSE_SaveIndex(pku_index, "db.bin");
ROSE_FreeIndex(pku_index);
pku_index = NULL;

//** 7. Matching
float score1 = ROSE_Matching("1.jpg", "11.jpg");
printf("score1 = %.3lf\n", score1);

float score2 = ROSE_Matching("1.jpg", "2.jpg");
printf("score2 = %.3lf\n", score2);

//** Remember to finish SDK
ROSE_FinishSDK();
}
*/
//int main(int argc, char* argv[])
//{
//	try {
//		run_sdk();
//		//run_sdk_1k();
//	}
//	catch (exception & ex)				// catch any exception, including CdvsException
//	{
//		cerr << "Exception: " << ex.what() << endl;
//	}
//	return 0;
//}
