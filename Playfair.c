// string.h
// ctype.h
// stdlib.h
/***********************************************/

int Mod(int a, int b)
{
	return (a % b + b) % b;
}

char** Create2DArray(int rowCount, int colCount) {
	char** arr = new char*[rowCount];

	for (int i = 0; i < rowCount; ++i)
		arr[i] = new char[colCount];

	return arr;
}

char* ToUpper(char* str) {
	int strLen = strlen(str);
	char* output = (char*)malloc(strLen + 1);

	for (int i = 0; i < strLen; ++i)
		output[i] = toupper(str[i]);

	output[strLen] = '\0';
	return output;
}

char* GetSubString(char* str, int index, int count) {
	int strLen = strlen(str);
	int lastIndex = index + count;

	if (index >= 0 && lastIndex > strLen) return "";

	char* subStr = (char*)malloc(count + 1);

	for (int i = 0; i < count; i++) {
		subStr[i] = str[index + i];
	}

	subStr[count] = '\0';

	return subStr;
}

char* AppendString(const char* str1, const char* str2) {
	int str1Len = strlen(str1);
	int str2Len = strlen(str2);
	int strLen = str1Len + str2Len + 1;
	char* str = (char*)malloc(strLen);

	for (int i = 0; i < str1Len; i++)
		str[i] = str1[i];

	for (int i = 0; i < str2Len; i++)
		str[(str1Len + i)] = str2[i];

	str[strLen - 1] = '\0';

	return str;
}

char* RemoveString(char* str, int index, int count) {
	int strLen = strlen(str);
	int lastIndex = index + count;

	char* s = GetSubString(str, 0, index);
	s = AppendString(s, GetSubString(str, lastIndex, strLen - lastIndex));

	return s;
}

char* InsertString(char* str, int index, char* subStr) {
	char* s = GetSubString(str, 0, index);
	s = AppendString(s, subStr);
	s = AppendString(s, GetSubString(str, index, strlen(str) - index));

	return s;
}

char* RemoveChar(char* str, char ch) {
	char* output = str;

	for (int i = 0; i < strlen(output); ++i)
		if (output[i] == ch)
			output = RemoveString(output, i, 1);

	return output;
}

int* AddItemInArray(int* arr, int count, int item) {
	int* newArr = (int*)malloc(sizeof(int) * (count + 1));

	for (int i = 0; i < count; ++i) {
		newArr[i] = arr[i];
	}

	newArr[count] = item;

	return newArr;
}

int* FindAllOccurrences(char* str, char value, int* count)
{
	int* indexes = (int*)malloc(sizeof(int));
	char *tmp = str;
	*count = 0;

	tmp = strchr(tmp, value);
	while (tmp != NULL) {
		indexes = AddItemInArray(indexes, *count, (tmp - str));
		++(*count);
		tmp = strchr(tmp + 1, value);
	}

	return indexes;
}

char* RemoveAllDuplicates(char* str, int* indexes, int count)
{
	char* retVal = str;

	for (int i = count - 1; i >= 1; i--)
		retVal = RemoveString(retVal, indexes[i], 1);

	return retVal;
}

char** GenerateKeySquare(char* key)
{
	char** keySquare = Create2DArray(5, 5);
	char* defaultKeySquare = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
	char* tempKey = (strlen(key) <= 0) ? "CIPHER" : ToUpper(key);

	tempKey = RemoveChar(tempKey, 'J');
	tempKey = AppendString(tempKey, defaultKeySquare);

	for (int i = 0; i < 25; ++i)
	{
		int count = 0;
		int* indexes = FindAllOccurrences(tempKey, defaultKeySquare[i], &count);
		tempKey = RemoveAllDuplicates(tempKey, indexes, count);
	}

	tempKey = GetSubString(tempKey, 0, 25);

	for (int i = 0; i < 25; ++i)
		keySquare[(i / 5)][(i % 5)] = tempKey[i];

	return keySquare;
}

void GetPosition(char** keySquare, char ch, int* row, int* col)
{
	if (ch == 'J')
		GetPosition(keySquare, 'I', row, col);

	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j)
			if (keySquare[i][j] == ch)
			{
				*row = i;
				*col = j;
				return;
			}
}

char* SameRow(char** keySquare, int row, int col1, int col2, int encipher)
{
	char* output = (char*)malloc(3);
	output[0] = keySquare[row][Mod((col1 + encipher), 5)];
	output[1] = keySquare[row][Mod((col2 + encipher), 5)];
	output[2] = '\0';
	return output;
}

char* SameColumn(char** keySquare, int col, int row1, int row2, int encipher)
{
	char* output = (char*)malloc(3);
	output[0] = keySquare[Mod((row1 + encipher), 5)][col];
	output[1] = keySquare[Mod((row2 + encipher), 5)][col];
	output[2] = '\0';
	return output;
}

char* SameRowColumn(char** keySquare, int row, int col, int encipher)
{
	char* output = (char*)malloc(3);
	output[0] = keySquare[Mod((row + encipher), 5)][Mod((col + encipher), 5)];
	output[1] = keySquare[Mod((row + encipher), 5)][Mod((col + encipher), 5)];
	output[2] = '\0';
	return output;
}

char* DifferentRowColumn(char** keySquare, int row1, int col1, int row2, int col2)
{
	char* output = (char*)malloc(3);
	output[0] = keySquare[row1][col2];
	output[1] = keySquare[row2][col1];
	output[2] = '\0';
	return output;
}

char* RemoveOtherChars(char* input)
{
	char* output = input;
	int strLen = strlen(input);

	for (int i = 0; i < strLen; ++i)
		if (output[i] != '\0' && !isalpha(output[i]))
			output = RemoveString(output, i, 1);

	return output;
}

char* AdjustOutput(char* input, char* output)
{
	char* retVal = output;
	int strLen = strlen(input);

	for (int i = 0; i < strLen; ++i)
	{
		if (!isalpha(input[i])) {
			char s[2] = { input[i], '\0' };
			retVal = InsertString(retVal, i, s);
		}

		if (islower(input[i]))
			retVal[i] = tolower(retVal[i]);
	}

	return retVal;
}

char* Cipher(char* input, char* key, bool encipher)
{
	char* retVal = "";
	char** keySquare = GenerateKeySquare(key);
	char* tempInput = RemoveOtherChars(input);
	int e = encipher ? 1 : -1;
	int tempInputLen = strlen(tempInput);

	if ((tempInputLen % 2) != 0)
		tempInput = AppendString(tempInput, "X");

	for (int i = 0; i < tempInputLen; i += 2)
	{
		int row1 = 0;
		int col1 = 0;
		int row2 = 0;
		int col2 = 0;

		GetPosition(keySquare, toupper(tempInput[i]), &row1, &col1);
		GetPosition(keySquare, toupper(tempInput[i + 1]), &row2, &col2);

		if (row1 == row2 && col1 == col2)
		{
			retVal = AppendString(retVal, SameRowColumn(keySquare, row1, col1, e));
		}
		else if (row1 == row2)
		{
			char* a = SameRow(keySquare, row1, col1, col2, e);
			retVal = AppendString(retVal, a);
		}
		else if (col1 == col2)
		{
			retVal = AppendString(retVal, SameColumn(keySquare, col1, row1, row2, e));
		}
		else
		{
			retVal = AppendString(retVal, DifferentRowColumn(keySquare, row1, col1, row2, col2));
		}
	}

	retVal = AdjustOutput(input, retVal);

	return retVal;
}

char* Encipher(char* input, char* key)
{
	return Cipher(input, key, true);
}

char* Decipher(char* input, char* key)
{
	return Cipher(input, key, false);
}
