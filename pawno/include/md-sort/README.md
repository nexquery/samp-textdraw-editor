md-sort
=======

md-sort.inc

## Sorting Examples

### Sort an array by the values in the first slot, i.e. `[i][0]`.

```pawn
new array[100][4];
SortDeepArray(array, 0);
```

### Sort a Float array descending by the values in the third slot, i.e. `[i][2]`.

```pawn
new Float:array[100][4];
SortDeepArray(array, 2, .order = SORT_DESC);
```

### Sort a string array.

```pawn
new string[10][32];
SortDeepArray(array, 0, .cmp_string = true, .ignorecase = false);
```

### Sort an enum array by a specified field.

```pawn
enum ENUM_FIELDS
{
	Float:FLOAT_FIELD,
	INT_FIELD,
	STRING_FIELD[32],
	ORDERED_FIELD,
	FINAL_FIELD,
}
new string[10][ENUM_FIELDS];
SortDeepArray(array, ORDERED_FIELD);
```

### Sort an array, using a custom comparison function.

```pawn
#include <a_samp>
#include <md-sort>

enum ENUM_TWO_DIRECTIONS
{
	E_SORT_ORDER:ORDER_FIELD,
	VALUE_FIELD
}

Comparator:MyComparator(left[ENUM_TWO_DIRECTIONS], right[ENUM_TWO_DIRECTIONS])
{
	// Put ascending slots first, then descending ones.
	if (left[ORDER_FIELD] == SORT_ASC)
	{
		if (right[ORDER_FIELD] == SORT_ASC)
			return left[VALUE_FIELD] - right[VALUE_FIELD];
		else
			return -1;
	}
	else
	{
		if (right[ORDER_FIELD] == SORT_ASC)
			return 1;
		else
			return right[VALUE_FIELD] - left[VALUE_FIELD];
	}
}

main()
{
	new array[100][ENUM_TWO_DIRECTIONS];
	for (new i = 0; i != sizeof (array); ++i)
	{
		array[i][ORDER_FIELD] = random(2) ? SORT_ASC : SORT_DESC;
		array[i][VALUE_FIELD] = random(200);
	}
	SortArrayUsingComparator(array, MyComparator);
	for (new i = 0; i != sizeof (array); ++i)
	{
		printf("%s: %d", (array[i][ORDER_FIELD] == SORT_ASC) ? ("UP") : ("DN"), array[i][VALUE_FIELD]);
	}
}
```

### Sort in to a target array.

```pawn
#include <a_samp>
#include <md-sort>

enum ENUM_TWO_DIRECTIONS
{
	E_SORT_ORDER:ORDER_FIELD,
	VALUE_FIELD
}

Comparator:MyComparator(left[ENUM_TWO_DIRECTIONS], right[ENUM_TWO_DIRECTIONS])
{
	// Put ascending slots first, then descending ones.
	if (left[ORDER_FIELD] == SORT_ASC)
	{
		if (right[ORDER_FIELD] == SORT_ASC)
			return left[VALUE_FIELD] - right[VALUE_FIELD];
		else
			return -1;
	}
	else
	{
		if (right[ORDER_FIELD] == SORT_ASC)
			return 1;
		else
			return right[VALUE_FIELD] - left[VALUE_FIELD];
	}
}

main()
{
	new array[100][ENUM_TWO_DIRECTIONS];
	new indexes[100];
	for (new i = 0; i != sizeof (array); ++i)
	{
		array[i][ORDER_FIELD] = random(2) ? SORT_ASC : SORT_DESC;
		array[i][VALUE_FIELD] = random(200);
	}
	SortArrayUsingComparator(array, MyComparator) => indexes;
	for (new i = 0; i != sizeof (indexes); ++i)
	{
		printf("%s: %d", (array[indexes[i]][ORDER_FIELD] == SORT_ASC) ? ("UP") : ("DN"), array[indexes[i]][VALUE_FIELD]);
	}
}
```

## Other Examples

## Shuffling And Resetting An Array

```pawn
enum ENUM_TWO_DIRECTIONS
{
	E_SORT_ORDER:ORDER_FIELD,
	VALUE_FIELD
}

Comparator:MyComparator(left[ENUM_TWO_DIRECTIONS], right[ENUM_TWO_DIRECTIONS])
{
	// Put ascending slots first, then descending ones.
	if (left[ORDER_FIELD] == SORT_ASC)
	{
		if (right[ORDER_FIELD] == SORT_ASC)
			return left[VALUE_FIELD] - right[VALUE_FIELD];
		else
			return -1;
	}
	else
	{
		if (right[ORDER_FIELD] == SORT_ASC)
			return 1;
		else
			return right[VALUE_FIELD] - left[VALUE_FIELD];
	}
}

main()
{
	new array[100][ENUM_TWO_DIRECTIONS];
	new copied[100][ENUM_TWO_DIRECTIONS];
	for (new i = 0; i != sizeof (array); ++i)
	{
		copied[i][ORDER_FIELD] = array[i][ORDER_FIELD] = random(2) ? SORT_ASC : SORT_DESC;
		copied[i][VALUE_FIELD] = array[i][VALUE_FIELD] = random(200);
		printf("%s: %d", (array[i][ORDER_FIELD] == SORT_ASC) ? ("UP") : ("DN"), array[i][VALUE_FIELD]);
	}
	SortArrayUsingComparator(array, MyComparator);
	printf("===========");
	for (new i = 0; i != sizeof (array); ++i)
	{
		printf("%s: %d", (array[i][ORDER_FIELD] == SORT_ASC) ? ("UP") : ("DN"), array[i][VALUE_FIELD]);
	}
	ResetDeepArray(array);
	printf("===========");
	for (new i = 0; i != sizeof (array); ++i)
	{
		printf("%s: %d", (array[i][ORDER_FIELD] == SORT_ASC) ? ("UP") : ("DN"), array[i][VALUE_FIELD]);
	}
	ShuffleDeepArray(array);
	printf("===========");
	for (new i = 0; i != sizeof (array); ++i)
	{
		printf("%s: %d", (array[i][ORDER_FIELD] == SORT_ASC) ? ("UP") : ("DN"), array[i][VALUE_FIELD]);
	}
	ResetDeepArray(array);
	printf("===========");
	for (new i = 0; i != sizeof (array); ++i)
	{
		printf("%s: %d", (array[i][ORDER_FIELD] == SORT_ASC) ? ("UP") : ("DN"), array[i][VALUE_FIELD]);
	}
	ShuffleDeepArray(array);
	printf("===========");
	for (new i = 0; i != sizeof (array); ++i)
	{
		printf("%s: %d", (array[i][ORDER_FIELD] == SORT_ASC) ? ("UP") : ("DN"), array[i][VALUE_FIELD]);
	}
	ResetDeepArray(array);
	printf("===========");
	for (new i = 0; i != sizeof (array); ++i)
	{
		printf("%s: %d", (array[i][ORDER_FIELD] == SORT_ASC) ? ("UP") : ("DN"), array[i][VALUE_FIELD]);
	}
}
```

