/*Copies bytes directly from a source to a destination*/
void mem_cpy(const void* source, void* dest, size_t numBytes)
{
	//Convert the arrays to char*, since char is 1 byte
	char* byteSource = (char*)source;
	char* byteDest = (char*)dest;

	//Copy all the data
	while(numBytes--)
	{
		*byteDest++ = *byteSource++;
	}
}
