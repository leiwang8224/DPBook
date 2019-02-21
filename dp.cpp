// Find length of longest substring of a given string of digits, such that 
// sum of digits in the first half and second half of the substring is the same
// input: 142124
// output: 6
int maxSubStringLength(char *str) {
	int n = strlen(str);
	int maxLen = 0;

	// i = starting index of substring
	for (int i = 0; i <n; i++) {
		// j = End index of substring (even length)
		for (int j = i+1; j < n; j += 2) {
			//len = length of currnet substring int
			len = j - i + 1;
			// if maxLen is > length of current string.
			// Do nothing
			if (maxLen >= len) {
				continue;
			}

			int lSum = 0;
			int rSum = 0;
			for (int k = 0; k < len / 2; k++) {
				lSum += (str[i+k] - '0');
				rSum += (str[i+k+len/2] - '0');
			}

			if (lSum == rSum) {
				maxLen = len;
			}
		}
	}
	return maxLen;
}

// sum[i][j] is sum of digits from i to j
// if i > j, then value holds no meaning.
int sum[N][N];
int maxSubStringLengthDP(char *str) {
	int n = strlen(str);
	int maxLen = 0;

	// Lower diagonal of matrix is not used (i > j)
	// filling diagonal values.
	for (int i = 0; i < n; i ++) 
		sum[i][i] = str[i] - '0';
	
	for (int len = 2; len <= n; len ++) {
		// pick i and j for current substring
		for (int i = 0; i < n-len+1; i ++) {
			int j = i + len - 1;
			int k = len /2;
			// calculate value of sum[i][j]
			sum[i][j] = sum[i][j-k] + sum[j-k+1][j];
			//update if 'len' is even, left and right
			// sums are same and len is more than maxLen
			if (len % 2 == 0 && 
				sum[i][j-k] == sum[(j-k+1][j] && 
				len > maxLen) 
				maxLen = len;
		}
	}
	return maxLen;
}

//single dimensional array
int maxSubStringLengthDP(string str, int n) 
{ 
    int sum[n+1]; // To store cumulative sum from first digit to nth digit 
    sum[0] = 0; 
  
    /* Store cumulative sum of digits from first to last digit */
    for (int i = 1; i <= n; i++) 
        sum[i] = (sum[i-1] + str[i-1]  - '0'); /* convert chars to int */
  
    int ans = 0; // initialize result 
  
    /* consider all even length substrings one by one */
    for (int len = 2; len <= n; len += 2) 
    { 
        for (int i = 0; i <= n-len; i++) 
        { 
            int j = i + len - 1; 
  
            /* Sum of first and second half is same than update ans */
            if (sum[i+len/2] - sum[i] == sum[i+len] - sum[i+len/2]) 
                ans = max(ans, len); 
        } 
    } 
    return ans; 
} 

// Consider a game where a player can score 3,5, or 10 points in one move. Given
// a total score N, find the total number of unique ways to reach a score of N.
int waysToScore(int n) {
	if (n < 0)
		return 0;
	if (n == 0)
		return 1;
	
	return waysToScore(n-10) +
		   waysToScore(n-5) +
		   waysToScore(n-3);
}

int waysToScoreDP(int n) {
	// arr[i] will store numberOfWays to score i.
	int arr[n+1] = {0};
	int i;

	arr[0] = 1;

	for (i = 1; i <= n; i++) {
		if (i-3>=0)
			arr[i] += arr[i-3];
		if (i-5>=0)
			arr[i] += arr[i-5];
		if (i-10>=0)
			arr[i] += arr[i-10];
	}
	return arr[n];
}

// Given an array of integers, write a function that returns the max sum of sub array,
// such that elements are contiguous.
// input: -2,-3,4,-1,-2,1,5,-3
// output: 4,-1,-2,1,5,-3
int maxSubArraySum(int *arr, int n) {
	int maxSum = 0;
	int tempSum = 0;
	for(int i = 0; i < n; i ++) {
		tempSum = arr[i];
		for (int j = i + 1; j < n; j++) {
			//tempSum hold sum of all elements from 
			// i to j index (both including)
			tempSum += arr[j];
			if (tempSum > maxSum)
				maxSum = tempSum;
		}
	}
	return maxSum;
}

// Find minimum edit distance between two strings:
// Can only use delete, replace, insert.
int editDistanceBruteForce(char* str1, char* str2) {
	// if str1 is empty, then all chars of str2 need to be inserted
	if (str1 == NULL || *str1 == '\0')
		return strlen(str2);

	// if str2 is empty, then all chars of str1 need to be deleted
	if (str2 == NULL || *str2 == '\0')
		return strlen(str1);

	// if first chars of both are same, then ignore it and find
	// edit distance of rest of the strings
	if (*str1 == *str2)
		return editDistanceBruteForce(str1+1, str2+1);
	
	// find edit distance for all 3
	int d, u, i;
	d = editDistanceBruteForce(str1+1, str2);
	u = editDistanceBruteForce(str1+1, str2+1);
	i = editDistanceBruteForce(str1, str2+1);

	// return min of the three values plus 1
	return getMin(d, u, i) + 1;
	
}

int editDistanceDP(char* str1, char* str2, int m, int n) {
	int editD[m+1][n+1];

	for (int j = 0; j <= m; j++) {  // TOP ROW
		editD[0][j] = j;
	}

	for (int i = 0; i <= n; i++) {  // LEFT COLUMN
		editD[i][0] = i;
	}

	for (int i = 1; i <= m; i++) {
		for(int j = 1; j <= n; j++) {
			// IF TWO CHAR ARE THE SAME
			if (s1[i-1] == s2[j-1]) {
				editD[i][j] = editD[i-1][j-1];
			} else {
				editD[i][j] = getMin(editD[i][j-1],
									editD[i-1][j],
									editD[i-1][j-1]) + 1;
			}
		}
	}
	return editD[m][n];
}

// Given a two dimensional array, find total number of paths possible from top-left
// to botoom right cell.
int numOfPaths(int m, int n) {
	if (m == 0 && n == 0)
		return 0; // cell 0,0
	if (m == 0 || n == 0)
		return 1; // first row or column
	// only option is to move from left or from the top
	return numOfPaths(m-1, n) + numOfPaths(m, n-1);
}

int numOfPathsDP(int m, int n) {
	int cache[m][n];

	for (int i = 1; i < m; i++) {
		cache[i][0] = 1;
	}

	for (int j = 1; j < n; j++) {
		cache[0][j] = 1;
	}

	// populating other cells
	for (int i = 1; i < m; i ++) {
		for (int j = 1; j < n; j++) {
			cache [i][j] = cache[i-1][j] + cache[i][j-1];
		}
	}

	return cache;
}

// String C is said to be interleaving of string A and B if it contains
// all characters of A and B and relative orders of chars are preserved in C.
int isInterleavingRecurse(char* str1, char* str2, char* str3) {
	// if all strings are empty
	if (!(*str1) && !(*str2) && !(*str3))
		return true;

	// if str3 is empty, str1 or str2 is not empty (or both)
	if (*str3 == '\0')
		return false;

	// if both str1 and str2 are empty, but str3 is not
	if (*str1 == '\0' && *str2 == '\0')
		return false;

	int first = false;
	int second = false;

	// if first char of str1 = first char of str3
	if (*str1 == *str3) {
		first = isInterleavingRecurse(str1+1, B, str3+1);
	}

	// if first char of str2 = first char of str3
	if (*str2 == *str3) {
		second = isInterleavingRecurse(str1, str2+1, str3+1);
	}

	return (first || second);
}


bool isInterleavedDP(char *str1, char* str2, char* str3) {
	// length of 2 strings
	int m = strlen(str1);
	int n = strlen(str2);

	// str3 should have exactly m+n chars
	if (strlen(str3) != m + n)
		return false;
	
	// 2 dim array, all vals set to 0(false)
	bool mat[m+1][n+1];

	mat[0][0] = true;

	// populating first column
	for (int i = 1; i <=m; i++) {
		if (str1[i-1] != str3[i-1]) {
			mat[i][0] = false;
		} else {
			mat[i][0] = mat[i-1][0];
		}
	}

	// populating first row
	for (int j = 1; j <=n; j++) {
		if (str2[j-1] != str3[j-1])
			mat[0][j] = false;
		else
			mat[0][j] = mat[0][j-1];
	}

	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= n; ++j) {
			// cur char of str3 same as str1 but not str2
			if (str1[i-1] == str3[i+j-1] && str2[j-1] != str3[i+j-1])
			{
				mat[i][j] = mat[i-1][j];
			}

			// cur char of str3 same as str2 but not str1
			else if (str1[i-1] != str3[i+j-1] &&
					str2[j-1] == str3[i+j-1]) {
				mat[i][j]=mat[i][j-1];
			}

			// cur char of str3 same as both str1 and str2
			else if (str1[i-1] == str3[i+j-1] &&
					str2[j-1] == str3[i+j-1]) {
				mat[i][j] = mat[i-1][j] || mat[i][j-1];
			}

			else {
				mat[i][j] = 0;  // false
			}
		}
	}
	return mat[m][n];
}