// md-sort.inc by Slice
//
// SortDeepArray(array[][], sort_index, .order = SORT_ASC, .ignorecase = false)

#if defined _INC_md_sort
	#endinput
#endif
#define _INC_md_sort

#include <a_samp>

#define SA_4%9.%0, SA_4%0,

#define SA_4size=%0,%9|||%5,%1,%2,%3,%4,%7)       SA_4%9|||%0,%1,%2,%3,%4,%7)
#define SA_4cmp_tag=%0,%9|||%5,%1,%2,%3,%4,%7)    SA_4%9|||%5,%0,%2,%3,%4,%7)
#define SA_4cmp_string=%0,%9|||%5,%1,%2,%3,%4,%7) SA_4%9|||%5,%1,%0,%3,%4,%7)
#define SA_4ignorecase=%0,%9|||%5,%1,%2,%3,%4,%7) SA_4%9|||%5,%1,%2,%0,%4,%7)
#define SA_4order=%0,%9|||%5,%1,%2,%3,%4,%7)      SA_4%9|||%5,%1,%2,%3,%0,%7)

#define SA_4_|||
#define SA_5:$$$

#define SortDeepArray(%1) (_:SA_0:SA_1:SA_2:SA_3:SortDeepArray_Entry(%1)) 
#define SA_0:SA_1:SA_2:SA_3:SortDeepArray_Entry(%1,%2,%3) SA_2:SA_3:SortDeepArray_Entry(%1[0][%2], _:%1[0][(%2) - (%2)], SA_4%3,_|||sizeof(%1),_,bool:SA_5:$$$false,_,_,g_sort_cmp_array,_:%1)
#define SA_1:SA_2:SA_3:SortDeepArray_Entry(%1,%2) SA_2:SA_3:SortDeepArray_Entry(%1[0][%2], _:%1[0][(%2) - (%2)], sizeof(%1), _, _, _, _, g_sort_cmp_array, _:%1)
#define SA_2:SA_3:SortDeepArray_Entry(%3[0][%4string%5:%6],%7,%8$$$false%9) SortDeepArray_Entry(%3[0][%6], _:%3[0][(%6) - (%6)], %8$$$true%9)

enum E_SORT_ORDER {
	SORT_ASC,
	SORT_DESC
};

// Use global variables to be nicer to the stack
stock
	             g_sort_stack[256],
	             g_sort_cmp_array[1][1],
	             g_sort_cmp_offset,
	             g_sort_cmp_type,
	E_SORT_ORDER:g_sort_order,
	        bool:g_sort_ignorecase
;

#if !defined FLOAT_TAG
	stock const
		Float:FLOAT_TAG_;
	
	#define FLOAT_TAG (tagof (FLOAT_TAG_))
#endif

stock SortDeepArray_Entry(&{Float, String, string, _}:cmp1, &_:cmp2, size, cmp_tag = tagof(cmp1), bool:cmp_string = false, bool:ignorecase = false, E_SORT_ORDER:order = SORT_ASC, array[][], ...) {
	if (cmp_string)
		g_sort_cmp_type = 's';
	else if (cmp_tag == FLOAT_TAG)
		g_sort_cmp_type = 'f';
	else
		g_sort_cmp_type = 'i';
	
	g_sort_ignorecase = ignorecase;
	g_sort_order = order;
	
	#emit LOAD.S.pri  cmp1
	#emit LOAD.S.alt  cmp2
	#emit SUB
	#emit SHR.C.pri   2
	#emit STOR.pri    g_sort_cmp_offset
	
	// Copy the array.
	#emit LOAD.S.pri 44
	#emit STOR.S.pri 40
	
	_SortDeepArray(array, 0, size - 1);
}

stock _SortDeepArray(array[][], left, right) {
	
	new
		sp;
_SortDeepArray_recurse:
	new
		left_hold = left,
		right_hold = right,
		pivot_idx = (left + right) / 2,
		pivot = array[pivot_idx][g_sort_cmp_offset]
	;
	
	if (g_sort_cmp_type == 'f' && Float:pivot != Float:pivot) {
		// Pivot is NaN, put everything else before it - NaN ALWAYS goes at the
		// end of the array, regardless of sort order.
		left_hold = right;
		right_hold = right - 1;
		ExchangeArraySlots(array, pivot_idx, right);
	} else while (left_hold <= right_hold) {
		switch (g_sort_cmp_type) {
			case 'f': {
				if (g_sort_order == SORT_ASC) {
					while (Float:pivot > Float:array[left_hold][g_sort_cmp_offset]) left_hold++;
					while (Float:pivot < Float:array[right_hold][g_sort_cmp_offset]) right_hold--;
				} else {
					while (Float:array[left_hold][g_sort_cmp_offset] > Float:pivot) left_hold++;
					while (Float:array[right_hold][g_sort_cmp_offset] < Float:pivot) right_hold--;
				}
			}
			
			case 's': {
				if (g_sort_order == SORT_ASC) {
					while (strcmp(array[left_hold][g_sort_cmp_offset], array[pivot_idx][g_sort_cmp_offset], g_sort_ignorecase) < 0) left_hold++;
					while (strcmp(array[right_hold][g_sort_cmp_offset], array[pivot_idx][g_sort_cmp_offset], g_sort_ignorecase) > 0) right_hold--;
				} else {
					while (strcmp(array[left_hold][g_sort_cmp_offset], array[pivot_idx][g_sort_cmp_offset], g_sort_ignorecase) > 0) left_hold++;
					while (strcmp(array[right_hold][g_sort_cmp_offset], array[pivot_idx][g_sort_cmp_offset], g_sort_ignorecase) < 0) right_hold--;
				}
			}
			
			default: {
				if (g_sort_order == SORT_ASC) {
					while (array[left_hold][g_sort_cmp_offset] < pivot) left_hold++;
					while (array[right_hold][g_sort_cmp_offset] > pivot) right_hold--;
				} else {
					while (array[left_hold][g_sort_cmp_offset] > pivot) left_hold++;
					while (array[right_hold][g_sort_cmp_offset] < pivot) right_hold--;
				}
			}
		}
		
		if (left_hold <= right_hold) {
			ExchangeArraySlots(array, left_hold, right_hold);
			
			left_hold++, right_hold--;
		}
	}
	
	if (left_hold < right) {
		g_sort_stack[sp++] = left_hold;
		g_sort_stack[sp++] = right;
	}
	if (left < right_hold){
		right = right_hold;
		goto _SortDeepArray_recurse;
	}
	if (sp) {
		right = g_sort_stack[--sp];
		left = g_sort_stack[--sp];
		goto _SortDeepArray_recurse;
	}
}

stock ExchangeArraySlots(array[][], slot1, slot2) {
	new
		addr1,
		addr2;
	
	// Get the pointer and its address  for slot1
	#emit LOAD.S.pri  array
	#emit LOAD.S.alt  slot1
	#emit SHL.C.alt   2
	#emit ADD
	#emit MOVE.alt
	
	#emit STOR.S.pri  slot1
	#emit LOAD.I
	#emit ADD
	#emit STOR.S.pri  addr1
	
	// Get the pointer and its address for slot2
	#emit LOAD.S.pri  array
	#emit LOAD.S.alt  slot2
	#emit SHL.C.alt   2
	#emit ADD
	#emit MOVE.alt
	
	#emit STOR.S.pri  slot2
	#emit LOAD.I
	#emit ADD
	#emit STOR.S.pri  addr2
	
	// Swap them
	#emit LOAD.S.pri  addr2
	#emit LOAD.S.alt  slot1
	#emit SUB
	#emit STOR.I
	
	#emit LOAD.S.pri  addr1
	#emit LOAD.S.alt  slot2
	#emit SUB
	#emit STOR.I
	
	return 0;
}

#define ShuffleDeepArray(%0) ShuffleDeepArray_Entry(_:%0, sizeof(%0), sizeof (%0[]))

stock ShuffleDeepArray_Entry(...) {
	assert(numargs() == 3);
	new
		i,
		base,
		size = getarg(1),
		target;
	#emit LOAD.S.alt 12
	#emit STOR.S.alt base
	#emit LOAD.S.pri size
	#emit SHL.C.pri  2
	#emit ADD
	#emit STOR.S.pri i
	while (i != base) {
		i -= 4;
		target = (random(size) << 2) + base;
		// Get the first slot.
		#emit LREF.S.pri i
		#emit LOAD.S.alt i
		#emit ADD
		#emit PUSH.pri
		// Get any other slot.
		#emit LREF.S.pri target
		#emit LOAD.S.alt target
		#emit ADD
		// Save one.
		#emit LOAD.S.alt i
		#emit SUB
		#emit SREF.S.pri i
		// Save the other
		#emit POP.pri
		#emit LOAD.S.alt target
		#emit SUB
		#emit SREF.S.pri target
	}
}

#define ResetDeepArray(%0) ResetDeepArray_Entry(_:%0, sizeof(%0), sizeof (%0[]))

stock ResetDeepArray_Entry(...) {
	// Put all the slots back how they should be originally.
	assert(numargs() == 3);
	new
		i,
		base,
		size = getarg(1),
		target;
	#emit LOAD.S.alt 12
	#emit STOR.S.alt i
	#emit LOAD.S.pri size
	#emit SHL.C.pri  2
	#emit ADD
	#emit STOR.S.pri base
	#emit STOR.S.pri target
	size = getarg(2) << 2;
	while (i != base) {
		#emit LOAD.S.alt i
		#emit LOAD.S.pri target
		#emit SUB
		#emit STOR.I
		i += 4;
		target += size;
	}
}

#define SortArrayUsingComparator(%1,%2) \
	SortArrayUsingComparator_Entry(sizeof(%1), %1, !"\0\0\0\0" #%2)

#define Comparator:%1(%2) \
	forward %1(%2); public %1(%2)

enum e_COMPARE_ORDER {
	ORDER_ASCENDING = -1,
	ORDER_EQUAL,
	ORDER_DESCENDING
};

static stock GetFunctionAddress(const funcname[]) {
	new idx, address;
	
	if (-1 != (idx = funcidx(funcname))) {
		#emit LCTRL		   1
		#emit NEG
		#emit MOVE.alt
		#emit ADD.C		   32
		#emit STOR.S.pri   address
		#emit LREF.S.pri   address
		#emit ADD
		#emit LOAD.S.alt   idx
		#emit SHL.C.alt	   3
		#emit ADD
		#emit STOR.S.pri   address
		#emit LREF.S.pri   address
		#emit STOR.S.pri   address
	}
	
	return address;
}

stock SortArrayUsingComparator_Entry(size, ...) {
	new array, func;
	
	#emit LOAD.S.pri  16
	#emit STOR.S.pri  array
	#emit LOAD.S.pri  20
	#emit LOAD.I
	#emit STOR.S.pri  func
	
	if (!func) {
		#emit LOAD.S.pri  20
		#emit ADD.C       4
		#emit PUSH.pri
		#emit PUSH.C      4
		#emit LCTRL       6
		#emit ADD.C       36
		#emit LCTRL       8
		#emit PUSH.pri
		#emit CONST.pri   GetFunctionAddress
		#emit SCTRL       6
		#emit LOAD.S.alt  20
		#emit STOR.I
		#emit STOR.S.pri  func
	}
	
	if (!func) {
		print(!"(SortArrayUsingComparator) Invalid comparator given.");
		
		return;
	}
	
	SortArrayUsingComparator_QS(array, func, 0, size - 1);
}

stock SortArrayUsingComparator_QS(array, func, left, right) {
	new
		sp;
_SortDeepArray_recurse:
	new
		left_hold = left,
		right_hold = right,
		pivot = left
	;
	
	while (left_hold <= right_hold) {
		new result;
		
		for (;;) {
			#emit LOAD.S.pri  array
			#emit LOAD.S.alt  pivot
			#emit SHL.C.alt   2
			#emit ADD
			#emit PUSH.pri
			#emit LOAD.I
			#emit POP.alt
			#emit ADD
			#emit PUSH.pri
			
			#emit LOAD.S.pri  array
			#emit LOAD.S.alt  left_hold
			#emit SHL.C.alt   2
			#emit ADD
			#emit PUSH.pri
			#emit LOAD.I
			#emit POP.alt
			#emit ADD
			#emit PUSH.pri
			
			#emit PUSH.C      8
			#emit LCTRL       6
			#emit ADD.C       36
			#emit LCTRL       8
			#emit PUSH.pri
			#emit LOAD.S.pri  func
			#emit SCTRL       6
			#emit STOR.S.pri  result
			
			if (result < 0) {
				left_hold++;
			} else {
				break;
			}
		}
		
		for (;;) {
			#emit LOAD.S.pri  array
			#emit LOAD.S.alt  pivot
			#emit SHL.C.alt   2
			#emit ADD
			#emit PUSH.pri
			#emit LOAD.I
			#emit POP.alt
			#emit ADD
			#emit PUSH.pri
			
			#emit LOAD.S.pri  array
			#emit LOAD.S.alt  right_hold
			#emit SHL.C.alt   2
			#emit ADD
			#emit PUSH.pri
			#emit LOAD.I
			#emit POP.alt
			#emit ADD
			#emit PUSH.pri
			
			#emit PUSH.C      8
			#emit LCTRL       6
			#emit ADD.C       36
			#emit LCTRL       8
			#emit PUSH.pri
			#emit LOAD.S.pri  func
			#emit SCTRL       6
			#emit STOR.S.pri  result
			
			if (result > 0) {
				right_hold--;
			} else {
				break;
			}
		}
		
		if (left_hold <= right_hold) {
			#emit PUSH.S      right_hold
			#emit PUSH.S      left_hold
			#emit PUSH.S      array
			#emit PUSH.C      12
			#emit LCTRL       6
			#emit ADD.C       36
			#emit LCTRL       8
			#emit PUSH.pri
			#emit CONST.pri   ExchangeArraySlots
			#emit SCTRL       6

			left_hold++, right_hold--;
		}
	}
	
	if (left_hold < right) {
		g_sort_stack[sp++] = left_hold;
		g_sort_stack[sp++] = right;
	}
	if (left < right_hold){
		right = right_hold;
		goto _SortDeepArray_recurse;
	}
	if (sp) {
		right = g_sort_stack[--sp];
		left = g_sort_stack[--sp];
		goto _SortDeepArray_recurse;
	}
}

#define SortArrayUsingComparator_Entry(%1)%2=>%3; \
	SortArrayUsingCompInto_Entry(%3, %1);

enum (<<= 1) {
	SORT_IS_PLAYERS = 1
};

stock SortArrayUsingCompInto_Entry(results[], size, ...) {
	new array, func, flags;
	
	#emit LOAD.S.pri  20
	#emit STOR.S.pri  array
	#emit LOAD.S.pri  24
	#emit LOAD.I
	#emit STOR.S.pri  func
	
	if (numargs() > 4)
		flags = getarg(4);
	
	if (!func) {
		#emit LOAD.S.pri  24
		#emit ADD.C       4
		#emit PUSH.pri
		#emit PUSH.C      4
		#emit LCTRL       6
		#emit ADD.C       36
		#emit LCTRL       8
		#emit PUSH.pri
		#emit CONST.pri   GetFunctionAddress
		#emit SCTRL       6
		#emit LOAD.S.alt  24
		#emit STOR.I
		#emit STOR.S.pri  func
	}
	
	if (!func) {
		print(!"(SortArrayUsingComparator) Invalid comparator given.");
		
		return;
	}
	
	if (flags & SORT_IS_PLAYERS) {
		new connected = 0;
		
		// Start filling the result array with connected players
		for (new i = 0; i < size; i++) {
			if (IsPlayerConnected(i))
				results[connected++] = i;
		}
		
		// Fill the remaining slots with INVALID_PLAYER_ID
		for (new i = connected; i < size; i++)
			results[i] = -1;
		
		// Store the original size in the flags
		flags |= size << 16;
		
		// Set the size so only the connected players will be sorted
		size = connected;
	} else {
		for (new i = 0; i < size; i++)
			results[i] = i;
	}
	
	SortArrayUsingCompInto_QS(array, results, func, 0, size - 1);
	
	if (flags & SORT_IS_PLAYERS) {
		if (size < flags >>> 16 && results[size] == -1)
			results[size] = INVALID_PLAYER_ID;
	}
}

stock SortArrayUsingCompInto_QS(array, results[], func, left, right) {
	new
		sp;
_SortDeepArray_recurse:
	new
		left_hold = left,
		right_hold = right,
		pivot = left
	;
	
	while (left_hold <= right_hold) {
		new result;
		
		for (;;) {
			if (results[pivot] == -1 && results[left_hold] == -1) {
				result = 0;
			} else if (results[pivot] == -1) {
				result = -1;
			} else if (results[left_hold] == -1) {
				result = 1;
			} else {
				// Load results[pivot]
				#emit LOAD.S.pri  pivot
				#emit SHL.C.pri   2  
				#emit LOAD.S.alt  results
				#emit ADD
				#emit LOAD.I
				#emit MOVE.alt
				
				// Push array[results[pivot]]
				#emit LOAD.S.pri  array
				#emit SHL.C.alt   2
				#emit ADD
				#emit PUSH.pri
				#emit LOAD.I
				#emit POP.alt
				#emit ADD
				#emit PUSH.pri
				
				// Load results[left_hold]
				#emit LOAD.S.pri  left_hold
				#emit SHL.C.pri   2  
				#emit LOAD.S.alt  results
				#emit ADD
				#emit LOAD.I
				#emit MOVE.alt
				
				// Push array[results[left_hold]]
				#emit LOAD.S.pri  array
				#emit SHL.C.alt   2
				#emit ADD
				#emit PUSH.pri
				#emit LOAD.I
				#emit POP.alt
				#emit ADD
				#emit PUSH.pri
				
				// Push arg. count
				#emit PUSH.C      8
				// Push return address
				#emit LCTRL       6
				#emit ADD.C       36
				#emit LCTRL       8
				#emit PUSH.pri
				// Call the comparator
				#emit LOAD.S.pri  func
				#emit SCTRL       6
				// Store the return
				#emit STOR.S.pri  result
			}
			
			if (result < 0) {
				left_hold++;
			} else {
				break;
			}
		}
		
		for (;;) {
			if (results[pivot] == -1 && results[right_hold] == -1) {
				result = 0;
			} else if (results[pivot] == -1) {
				result = -1;
			} else if (results[right_hold] == -1) {
				result = 1;
			} else {
				// Load results[pivot]
				#emit LOAD.S.pri  pivot
				#emit SHL.C.pri   2  
				#emit LOAD.S.alt  results
				#emit ADD
				#emit LOAD.I
				#emit MOVE.alt
				
				// Push array[results[pivot]]
				#emit LOAD.S.pri  array
				#emit SHL.C.alt   2
				#emit ADD
				#emit PUSH.pri
				#emit LOAD.I
				#emit POP.alt
				#emit ADD
				#emit PUSH.pri
			
				// Load results[right_hold]
				#emit LOAD.S.pri  right_hold
				#emit SHL.C.pri   2  
				#emit LOAD.S.alt  results
				#emit ADD
				#emit LOAD.I
				#emit MOVE.alt
			
				// Push array[results[right_hold]]
				#emit LOAD.S.pri  array
				#emit SHL.C.alt   2
				#emit ADD
				#emit PUSH.pri
				#emit LOAD.I
				#emit POP.alt
				#emit ADD
				#emit PUSH.pri
			
				// Push arg. count
				#emit PUSH.C      8
				// Push return address
				#emit LCTRL       6
				#emit ADD.C       36
				#emit LCTRL       8
				#emit PUSH.pri
				// Call the comparator
				#emit LOAD.S.pri  func
				#emit SCTRL       6
				// Store the return
				#emit STOR.S.pri  result
			}
			
			if (result > 0) {
				right_hold--;
			} else {
				break;
			}
		}
		
		if (left_hold <= right_hold) {
			// used instead of creating another variable
			result = results[right_hold];
			
			results[right_hold] = results[left_hold];
			results[left_hold] = result;
			
			left_hold++, right_hold--;
		}
	}
	
	if (left_hold < right) {
		g_sort_stack[sp++] = left_hold;
		g_sort_stack[sp++] = right;
	}
	if (left < right_hold){
		right = right_hold;
		goto _SortDeepArray_recurse;
	}
	if (sp) {
		right = g_sort_stack[--sp];
		left = g_sort_stack[--sp];
		goto _SortDeepArray_recurse;
	}
}

