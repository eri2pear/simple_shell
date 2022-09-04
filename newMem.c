#include "main.h"

/**
 * _memcpy - Function copies info from intial pointer source to new pointer.
 * @newptr: var name for new pointer.
 * @ptr: var name for intial pointer source.
 * @size: var name for size of the new pointer.
 *
 * Return: no return.
 */
void _memcpy(void *newptr, const void *ptr, unsigned int size)
{
	char *char_ptr = (char *)ptr;
	char *char_newptr = (char *)newptr;
	unsigned int i;

	for (i = 0; i < size; i++)
		char_newptr[i] = char_ptr[i];
}

/**
 * _realloc - Function to reallocate a memory block.
 * @ptr: var name for pointer to the memory previously allocated.
 * @old_size: var name for size, in bytes, of the allocated space for the ptr.
 * @new_size: varname for new size, in bytes, of the new memory block.
 *
 * Return: newptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *newptr;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(new_size);
	if (newptr == NULL)
		return (NULL);

	if (new_size < old_size)
		_memcpy(newptr, ptr, new_size);
	else
		_memcpy(newptr, ptr, old_size);

	free(ptr);
	return (newptr);
}

/**
 * _reallocdp - Function to reallocate a memory block of a double pointer.
 * @ptr: var name for double pointer to the memory previously allocated.
 * @old_size: var name for size, in bytes, of the allocated space of ptr.
 * @new_size: var name for new size, in bytes, of the new memory block.
 *
 * Return: newptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **newptr;
	unsigned int i;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(sizeof(char *) * new_size);
	if (newptr == NULL)
		return (NULL);

	for (i = 0; i < old_size; i++)
		newptr[i] = ptr[i];

	free(ptr);

	return (newptr);
}
