#include <stdio.h>  /*For printf and getchar functions*/
#include <stdlib.h> /*For system function*/
int MaxSumArray(int nums[], size_t len, int *left, int *right);

int main()
{
	int nums[] = {-2, 1, -3 , 4, -1, 2, 3, -5, -30};
	size_t arr_size = 9;
	int r = 0, l = 0;
	int *right = &r;
	int *left = &l;
	
	printf("Right index: %d\nLeft index: %d\nMax sum:%d\n",r ,l, MaxSumArray(nums, arr_size, left, right));

	return 0 ;
}


int MaxSumArray(int nums[], size_t len, int *left, int *right)
{

	size_t i = 0, left_index_keeper = 0;
	int max_sum = 0;
	int current_sum= 0;
	
	
	for(i = 0; i < len; i++)
	{
		current_sum += nums[i];
		
		if(current_sum < 0)
		{
			current_sum = 0;
			left_index_keeper = i + 1;
		}
		
		if(current_sum > max_sum)
		{
			max_sum = current_sum;
			*right = i;
			*left = left_index_keeper;
		}	
	}
	
	return max_sum;
}







