// Copyright (C) 2012 Zeex
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#if defined AMX_HEADER_INC
	#endinput
#endif
#define AMX_HEADER_INC

#if !defined _samp_included
	#tryinclude <console>
#endif

#include "amx_memory"

#define AMX_HDR_BYTES (56)
#define AMX_HDR_CELLS (AMX_HDR_BYTES / 4)

#define AMX_TAG_MASK (0x80000000)
#define AMX_TAG_STRONG (0x40000000)

enum AMX_HDR {
	AMX_HDR_SIZE,
	AMX_HDR_MAGIC,
	AMX_HDR_FILE_VERSION,
	AMX_HDR_AMX_VERSION,
	AMX_HDR_FLAGS,
	AMX_HDR_DEFSIZE,
	AMX_HDR_COD,
	AMX_HDR_DAT,
	AMX_HDR_HEA,
	AMX_HDR_STP,
	AMX_HDR_CIP,
	AMX_HDR_PUBLICS,
	AMX_HDR_NATIVES,
	AMX_HDR_LIBRARIES,
	AMX_HDR_PUBVARS,
	AMX_HDR_TAGS,
	AMX_HDR_NAMETABLE
}

const AMX_HDR_OFFSET_SIZE = 0;
const AMX_HDR_OFFSET_MAGIC = 4;
const AMX_HDR_OFFSET_FILE_VERSION = 6;
const AMX_HDR_OFFSET_AMX_VERSION = 7;
const AMX_HDR_OFFSET_FLAGS = 8;
const AMX_HDR_OFFSET_DEFSIZE = 10;
const AMX_HDR_OFFSET_COD = 12;
const AMX_HDR_OFFSET_DAT = 16;
const AMX_HDR_OFFSET_HEA = 20;
const AMX_HDR_OFFSET_STP = 24;
const AMX_HDR_OFFSET_CIP = 28;
const AMX_HDR_OFFSET_PUBLICS = 32;
const AMX_HDR_OFFSET_NATIVES = 36;
const AMX_HDR_OFFSET_LIBRARIES = 40;
const AMX_HDR_OFFSET_PUBVARS = 44;
const AMX_HDR_OFFSET_TAGS = 48;
const AMX_HDR_OFFSET_NAMETABLE = 52;

enum AMX_FUNCSTUBNT {
	AMX_FUNCSTUBNT_ADDRESS,
	AMX_FUNCSTUBNT_NAMEOFS
}
#define AMX_FUNCSTUBNT_ID AMX_FUNCSTUBNT_ADDRESS

// Publics
forward bool:GetPublicInfo(index, info[AMX_FUNCSTUBNT]);
forward GetPublicIndexFromAddress(address);
forward GetPublicIndexFromName(const name[]);
forward GetPublicAddressFromName(const name[]);
forward GetPublicAddressFromIndex(index);
forward bool:GetPublicNameFromIndex(index, name[], size = sizeof(name));
forward bool:GetPublicNameFromAddress(address, name[], size = sizeof(name));
forward HookPublic(index, address);

// Tags
forward bool:GetTagInfo(index, info[AMX_FUNCSTUBNT]);
forward GetTagIndexFromID(id);
forward GetTagIndexFromName(const name[]);
forward GetTagIDFromName(const name[]);
forward GetTagIDFromIndex(index);
forward bool:GetTagNameFromIndex(index, name[], size = sizeof(name));
forward bool:GetTagNameFromID(id, name[], size = sizeof(name));

// Natives
forward bool:GetNativeInfo(index, info[AMX_FUNCSTUBNT]);
forward GetNativeIndexFromAddress(address);
forward GetNativeIndexFromName(const name[]);
forward GetNativeAddressFromName(const name[]);
forward GetNativeAddressFromIndex(index);
forward bool:GetNativeNameFromIndex(index, name[], size = sizeof(name));
forward bool:GetNativeNameFromAddress(address, name[], size = sizeof(name));
forward HookNative(index, address);

// Public Variables
forward bool:GetPubVarInfo(index, info[AMX_FUNCSTUBNT]);
forward GetPubVarIndexFromName(const name[]);
forward GetPubVarIndexFromAddress(address);
forward GetPubVarAddressFromName(const name[]);
forward GetPubVarAddressFromIndex(index);
forward bool:GetPubVarNameFromIndex(index, name[], size = sizeof(name));
forward bool:GetPubVarNameFromAddress(address, name[], size = sizeof(name));

// General
forward GetRawAmxHeader(plain_amxhdr[AMX_HDR_CELLS]);
forward GetAmxHeaderNow(amxhdr[AMX_HDR]);
forward GetAmxHeader(amxhdr[AMX_HDR]);
forward GetAmxHeaderComponent(AMX_HDR:comp);
forward PrintAmxHeader();

stock GetRawAmxHeader(plain_amxhdr[AMX_HDR_CELLS]) {
	new address = 0;
	#emit lctrl 1  // DAT
	#emit neg      // -DAT
	#emit stor.s.pri address

	for (new i = 0; i < AMX_HDR_CELLS; i++) {
		plain_amxhdr[i] = ReadAmxMemory(address);
		address += 4;
	}
}

static stock copy_1(&dest, const source[], start) {
	#emit load.s.pri source
	#emit load.s.alt start
	#emit add
	#emit load.s.alt dest
	#emit movs 1
}

static stock copy_2(&dest, const source[], start) {
	#emit load.s.pri source
	#emit load.s.alt start
	#emit add
	#emit load.s.alt dest
	#emit movs 2
}

static stock copy_4(&dest, const source[], start) {
	#emit load.s.pri source
	#emit load.s.alt start
	#emit add
	#emit load.s.alt dest
	#emit movs 4
}

stock GetAmxHeaderNow(amxhdr[AMX_HDR]) {
	new plain_amxhdr[AMX_HDR_CELLS];
	GetRawAmxHeader(plain_amxhdr);

	copy_4(amxhdr[AMX_HDR_SIZE], plain_amxhdr, AMX_HDR_OFFSET_SIZE);
	copy_2(amxhdr[AMX_HDR_MAGIC], plain_amxhdr, AMX_HDR_OFFSET_MAGIC);
	copy_1(amxhdr[AMX_HDR_FILE_VERSION], plain_amxhdr, AMX_HDR_OFFSET_FILE_VERSION);
	copy_1(amxhdr[AMX_HDR_AMX_VERSION], plain_amxhdr, AMX_HDR_OFFSET_AMX_VERSION);
	copy_2(amxhdr[AMX_HDR_FLAGS], plain_amxhdr, AMX_HDR_OFFSET_FLAGS);
	copy_2(amxhdr[AMX_HDR_DEFSIZE], plain_amxhdr, AMX_HDR_OFFSET_DEFSIZE);
	copy_4(amxhdr[AMX_HDR_COD], plain_amxhdr, AMX_HDR_OFFSET_COD);
	copy_4(amxhdr[AMX_HDR_DAT], plain_amxhdr, AMX_HDR_OFFSET_DAT);
	copy_4(amxhdr[AMX_HDR_HEA], plain_amxhdr, AMX_HDR_OFFSET_HEA);
	copy_4(amxhdr[AMX_HDR_STP], plain_amxhdr, AMX_HDR_OFFSET_STP);
	copy_4(amxhdr[AMX_HDR_CIP], plain_amxhdr, AMX_HDR_OFFSET_CIP);
	copy_4(amxhdr[AMX_HDR_PUBLICS], plain_amxhdr, AMX_HDR_OFFSET_PUBLICS);
	copy_4(amxhdr[AMX_HDR_NATIVES], plain_amxhdr, AMX_HDR_OFFSET_NATIVES);
	copy_4(amxhdr[AMX_HDR_LIBRARIES], plain_amxhdr, AMX_HDR_OFFSET_LIBRARIES);
	copy_4(amxhdr[AMX_HDR_PUBVARS], plain_amxhdr, AMX_HDR_OFFSET_PUBVARS);
	copy_4(amxhdr[AMX_HDR_TAGS], plain_amxhdr, AMX_HDR_OFFSET_TAGS);
	copy_4(amxhdr[AMX_HDR_NAMETABLE], plain_amxhdr, AMX_HDR_OFFSET_NAMETABLE);
}

static gHdr[AMX_HDR];
static bool:gInitialized = false;

stock ResetStaticAmxHeader() {
	GetAmxHeaderNow(gHdr);
	gInitialized = true;
}

#define InitStaticAmxHeader() \
	if (!gInitialized) \
		ResetStaticAmxHeader()

stock GetAmxHeader(amxhdr[AMX_HDR]) {
	InitStaticAmxHeader();
	amxhdr = gHdr;
}

stock GetAmxHeaderComponent(AMX_HDR:comp) {
	InitStaticAmxHeader();
	return gHdr[comp];
}

stock PrintAmxHeader() {
	InitStaticAmxHeader();
	print("------------------------");
	print("AMX Header:");
	print("------------------------");
	printf("size         %d", gHdr[AMX_HDR_SIZE]);
	printf("magic        %x", gHdr[AMX_HDR_MAGIC]);
	printf("file_version %d", gHdr[AMX_HDR_FILE_VERSION]);
	printf("amx_version  %d", gHdr[AMX_HDR_AMX_VERSION]);
	printf("flags        %d", gHdr[AMX_HDR_FLAGS]);
	printf("defsize      %d", gHdr[AMX_HDR_DEFSIZE]);
	printf("cod          0x%08x", gHdr[AMX_HDR_COD]);
	printf("dat          0x%08x", gHdr[AMX_HDR_DAT]);
	printf("hea          0x%08x", gHdr[AMX_HDR_HEA]);
	printf("stp          0x%08x", gHdr[AMX_HDR_STP]);
	printf("cip          0x%08x", gHdr[AMX_HDR_CIP]);
	printf("publics      0x%08x", gHdr[AMX_HDR_PUBLICS]);
	printf("natives      0x%08x", gHdr[AMX_HDR_NATIVES]);
	printf("libraries    0x%08x", gHdr[AMX_HDR_LIBRARIES]);
	printf("pubvars      0x%08x", gHdr[AMX_HDR_PUBVARS]);
	printf("tags         0x%08x", gHdr[AMX_HDR_TAGS]);
	printf("nametable    0x%08x", gHdr[AMX_HDR_NAMETABLE]);
	print("------------------------");
}

// Compares a string stored in the name table starting at "s1" (packed)
// with another string "s2" (unpacked).
static stock NtCompare(s1, const s2[]) {
	new index = 0;
	new c1 = 0, c2 = 0;
	new diff = 0;

	do {
		c1 = ReadAmxMemory(s1) & 0xFF;
		++s1;
		c2 = s2[index++];
		diff = c1 - c2;
		if (diff != 0) {
			break;
		}
	} while (!(c1 & c2 == 0));

	return diff;
}

// Copies a name from the name table to a string. Returns the number
// of characters copied.
static stock NtCopy(src, dest[], size = sizeof(dest)) {
	new i = 0;
	new c = 0;

	do {
		c = ReadAmxMemory(src) & 0xFF;
		++src;
		dest[i++] = c;
	} while (c != '\0' && i <= size);

	dest[i] = '\0'; // terminator

	return i;
}

stock GetNumPublics(const amxhdr[AMX_HDR]) {
	new num_publics = (amxhdr[AMX_HDR_NATIVES] - amxhdr[AMX_HDR_PUBLICS]) / amxhdr[AMX_HDR_DEFSIZE];
	return num_publics;
}

stock GetPublicIndexFromAddress(address) {
	InitStaticAmxHeader();

	new num_publics = GetNumPublics(gHdr);
	new off = gHdr[AMX_HDR_PUBLICS] - gHdr[AMX_HDR_DAT];

	// Linear search
	for (new i = 0; i < num_publics; i++) {
		if (ReadAmxMemory(off) == address) {
			return i;
		}
		off += gHdr[AMX_HDR_DEFSIZE];
	}

	return -1;
}

stock bool:GetPublicInfo(index, info[AMX_FUNCSTUBNT]) {
	InitStaticAmxHeader();

	new num_publics = GetNumPublics(gHdr);

	if (index < 0 || index >= num_publics) {
		return false;
	}

	new off = gHdr[AMX_HDR_PUBLICS] - gHdr[AMX_HDR_DAT] + index * gHdr[AMX_HDR_DEFSIZE];
	info[AMX_FUNCSTUBNT_ADDRESS] = ReadAmxMemory(off);
	info[AMX_FUNCSTUBNT_NAMEOFS] = ReadAmxMemory(off + 4);

	return true;
}

stock GetPublicIndexFromName(const name[]) {
	InitStaticAmxHeader();

	new num_publics = GetNumPublics(gHdr);

	// Binary search
	new first = 0;
	new last = num_publics - 1;
	new mid = 0;

	while (first <= last) {
		mid = (first + last) / 2;

		new off = gHdr[AMX_HDR_PUBLICS] - gHdr[AMX_HDR_DAT] + mid * gHdr[AMX_HDR_DEFSIZE];
		new nameofs = ReadAmxMemory(off + 4) - gHdr[AMX_HDR_DAT];

		new diff = NtCompare(nameofs, name);
		if (diff < 0) {
			first = mid + 1;
		} else if (diff > 0) {
			last = mid - 1;
		} else {
			return mid;
		}
	}

	return -1;
}

stock GetPublicAddressFromIndex(index) {
	new info[AMX_FUNCSTUBNT];
	GetPublicInfo(index, info);
	return info[AMX_FUNCSTUBNT_ADDRESS];
}

stock GetPublicAddressFromName(const name[]) {
	return GetPublicAddressFromIndex(GetPublicIndexFromName(name));
}

stock bool:GetPublicNameFromIndex(index, name[], size = sizeof(name)) {
	new info[AMX_FUNCSTUBNT];
	if (!GetPublicInfo(index, info)) {
		return false;
	}
	return (NtCopy(info[AMX_FUNCSTUBNT_NAMEOFS]
	        - GetAmxHeaderComponent(AMX_HDR_DAT), name, size) > 0);
}

stock bool:GetPublicNameFromAddress(address, name[], size = sizeof(name)) {
	return GetPublicNameFromIndex(GetPublicIndexFromAddress(address), name, size);
}

stock HookPublic(index, address) {
	InitStaticAmxHeader();

	new num_publics = GetNumPublics(gHdr);

	if (index < 0 || index >= num_publics) {
		return 0;
	}

	new off = gHdr[AMX_HDR_PUBLICS] - gHdr[AMX_HDR_DAT] + index * gHdr[AMX_HDR_DEFSIZE];
	new old_address = ReadAmxMemory(off);
	WriteAmxMemory(off, address);

	return old_address;
}

stock GetNumNatives(const amxhdr[AMX_HDR]) {
	return (amxhdr[AMX_HDR_LIBRARIES] - amxhdr[AMX_HDR_NATIVES]) / amxhdr[AMX_HDR_DEFSIZE];
}

stock GetNativeIndexFromAddress(address) {
	InitStaticAmxHeader();

	new num_natives = GetNumNatives(gHdr);
	new off = gHdr[AMX_HDR_NATIVES] - gHdr[AMX_HDR_DAT];

	// Linear search
	for (new i = 0; i < num_natives; i++) {
		if (ReadAmxMemory(off) == address) {
			return i;
		}
		off += gHdr[AMX_HDR_DEFSIZE];
	}

	return -1;
}

stock bool:GetNativeInfo(index, info[AMX_FUNCSTUBNT]) {
	InitStaticAmxHeader();

	// For when "index" is not valid
	info[AMX_FUNCSTUBNT_ADDRESS] = -1;

	new num_natives = GetNumNatives(gHdr);

	if (index < 0 || index >= num_natives) {
		return false;
	}

	new off = gHdr[AMX_HDR_NATIVES] - gHdr[AMX_HDR_DAT] + index * gHdr[AMX_HDR_DEFSIZE];
	info[AMX_FUNCSTUBNT_ADDRESS] = ReadAmxMemory(off);
	info[AMX_FUNCSTUBNT_NAMEOFS] = ReadAmxMemory(off + 4);

	return true;
}

stock GetNativeIndexFromName(const name[]) {
	InitStaticAmxHeader();

	new num_natives = GetNumNatives(gHdr);
	new off = gHdr[AMX_HDR_NATIVES] - gHdr[AMX_HDR_DAT];

	// Linear search
	for (new i = 0; i < num_natives; i++) {
		new nameofs = ReadAmxMemory(off + 4) - gHdr[AMX_HDR_DAT];

		new diff = NtCompare(nameofs, name);
		if (diff == 0) {
			return i;
		}

		off += gHdr[AMX_HDR_DEFSIZE];
	}

	return -1;
}

stock GetNativeAddressFromIndex(index) {
	new info[AMX_FUNCSTUBNT];
	GetNativeInfo(index, info);
	return info[AMX_FUNCSTUBNT_ADDRESS];
}

stock GetNativeAddressFromName(const name[]) {
	return GetNativeAddressFromIndex(GetNativeIndexFromName(name));
}

stock bool:GetNativeNameFromIndex(index, name[], size = sizeof(name)) {
	new info[AMX_FUNCSTUBNT];
	if (!GetNativeInfo(index, info)) {
		return false;
	}
	return (NtCopy(info[AMX_FUNCSTUBNT_NAMEOFS]
	        - GetAmxHeaderComponent(AMX_HDR_DAT), name, size) > 0);
}

stock bool:GetNativeNameFromAddress(address, name[], size = sizeof(name)) {
	return GetNativeNameFromIndex(GetNativeIndexFromAddress(address), name, size);
}

stock HookNative(index, address) {
	InitStaticAmxHeader();

	new num_natives = GetNumNatives(gHdr);

	if (index < 0 || index >= num_natives) {
		return 0;
	}

	new off = gHdr[AMX_HDR_NATIVES] - gHdr[AMX_HDR_DAT] + index * gHdr[AMX_HDR_DEFSIZE];
	new old_address = ReadAmxMemory(off);
	WriteAmxMemory(off, address);

	return old_address;
}

stock GetNumPubVars(const amxhdr[AMX_HDR]) {
	return (amxhdr[AMX_HDR_TAGS] - amxhdr[AMX_HDR_PUBVARS]) / amxhdr[AMX_HDR_DEFSIZE];
}

stock bool:GetPubVarInfo(index, info[AMX_FUNCSTUBNT]) {
	InitStaticAmxHeader();

	new num_pubvars = GetNumPubVars(gHdr);

	if (index < 0 || index >= num_pubvars) {
		return false;
	}

	new off = gHdr[AMX_HDR_PUBVARS] - gHdr[AMX_HDR_DAT] + index * gHdr[AMX_HDR_DEFSIZE];
	info[AMX_FUNCSTUBNT_ADDRESS] = ReadAmxMemory(off);
	info[AMX_FUNCSTUBNT_NAMEOFS] = ReadAmxMemory(off + 4);

	return true;
}

stock GetPubVarIndexFromName(const name[]) {
	InitStaticAmxHeader();

	new num_pubvars = GetNumPubVars(gHdr);
	new off = gHdr[AMX_HDR_PUBVARS] - gHdr[AMX_HDR_DAT];

	// Linear search
	for (new i = 0; i < num_pubvars; i++) {
		new nameofs = ReadAmxMemory(off + 4) - gHdr[AMX_HDR_DAT];

		new diff = NtCompare(nameofs, name);
		if (diff == 0) {
			return i;
		}

		off += gHdr[AMX_HDR_DEFSIZE];
	}

	return -1;
}

stock GetPubVarIndexFromAddress(address) {
	InitStaticAmxHeader();

	new num_pubvars = GetNumPubVars(gHdr);
	new off = gHdr[AMX_HDR_PUBVARS] - gHdr[AMX_HDR_DAT];

	// Linear search
	for (new i = 0; i < num_pubvars; i++) {
		if (ReadAmxMemory(off) == address) {
			return i;
		}
		off += gHdr[AMX_HDR_DEFSIZE];
	}

	return -1;
}

stock GetPubVarAddressFromIndex(index) {
	new info[AMX_FUNCSTUBNT];
	GetPubVarInfo(index, info);
	return info[AMX_FUNCSTUBNT_ADDRESS];
}

stock GetPubVarAddressFromName(const name[]) {
	return GetPubVarAddressFromIndex(GetPubVarIndexFromName(name));
}

stock bool:GetPubVarNameFromIndex(index, name[], size = sizeof(name)) {
	new info[AMX_FUNCSTUBNT];
	if (!GetPubVarInfo(index, info)) {
		return false;
	}
	return (NtCopy(info[AMX_FUNCSTUBNT_NAMEOFS]
	        - GetAmxHeaderComponent(AMX_HDR_DAT), name, size) > 0);
}

stock bool:GetPubVarNameFromAddress(address, name[], size = sizeof(name)) {
	return GetPubVarNameFromIndex(GetPubVarIndexFromAddress(address), name, size);
}

stock GetNumTags(const amxhdr[AMX_HDR]) {
	return (amxhdr[AMX_HDR_NAMETABLE] - amxhdr[AMX_HDR_TAGS]) / amxhdr[AMX_HDR_DEFSIZE];
}

stock bool:GetTagInfo(index, info[AMX_FUNCSTUBNT]) {
	if (index == 0) {
		info[AMX_FUNCSTUBNT_ID] = AMX_TAG_MASK;
		info[AMX_FUNCSTUBNT_NAMEOFS] = 0;
		return true;
	}
	InitStaticAmxHeader();

	new num_tags = GetNumTags(gHdr);

	if (index < 0 || index >= num_tags) {
		return false;
	}

	new off = gHdr[AMX_HDR_TAGS] - gHdr[AMX_HDR_DAT] + index * gHdr[AMX_HDR_DEFSIZE];
	info[AMX_FUNCSTUBNT_ID] = ReadAmxMemory(off) | AMX_TAG_MASK;
	info[AMX_FUNCSTUBNT_NAMEOFS] = ReadAmxMemory(off + 4);

	return true;
}

stock GetTagIndexFromName(const name[]) {
	InitStaticAmxHeader();

	new num_tags = GetNumTags(gHdr);
	new off = gHdr[AMX_HDR_TAGS] - gHdr[AMX_HDR_DAT];

	// Linear search
	for (new i = 0; i < num_tags; i++) {
		new nameofs = ReadAmxMemory(off + 4) - gHdr[AMX_HDR_DAT];

		new diff = NtCompare(nameofs, name);
		if (diff == 0) {
			return i;
		}

		off += gHdr[AMX_HDR_DEFSIZE];
	}

	return -1;
}

stock GetTagIndexFromID(id) {
	id &= ~AMX_TAG_MASK;
	if (id == 0)
		return 0;
	InitStaticAmxHeader();

	new num_tags = GetNumTags(gHdr);
	new off = gHdr[AMX_HDR_TAGS] - gHdr[AMX_HDR_DAT];

	// Linear search
	for (new i = 0; i <= num_tags; i++) {
		if (ReadAmxMemory(off) == id) {
			return i;
		}
		off += gHdr[AMX_HDR_DEFSIZE];
	}

	return -1;
}

stock GetTagIDFromIndex(index) {
	if (index == 0)
		return AMX_TAG_MASK;
	new info[AMX_FUNCSTUBNT];
	GetTagInfo(index, info);
	return info[AMX_FUNCSTUBNT_ID];
}

stock GetTagIDFromName(const name[]) {
	if (name[0] == '_' && name[1] == '\0')
		return AMX_TAG_MASK;
	return GetTagIDFromIndex(GetTagIndexFromName(name));
}

stock bool:GetTagNameFromIndex(index, name[], size = sizeof(name)) {
	if (index == 0)
	{
		name[0] = '_';
		name[1] = '\0';
		return true;
	}
	new info[AMX_FUNCSTUBNT];
	if (!GetTagInfo(index, info)) {
		return false;
	}
	return (NtCopy(info[AMX_FUNCSTUBNT_NAMEOFS]
	        - GetAmxHeaderComponent(AMX_HDR_DAT), name, size) > 0);
}

stock bool:GetTagNameFromID(id, name[], size = sizeof(name)) {
	if (id == 0)
	{
		name[0] = '_';
		name[1] = '\0';
		return true;
	}
	return GetTagNameFromIndex(GetTagIndexFromID(id), name, size);
}

#define AMX_ASSEMBLY_NO_BUGGED_TAGS 2

stock bool:IsTagIDStrong(tag) {
	return !!(tag & AMX_TAG_STRONG);
}

stock bool:IsTagIDWeak(tag) {
	return !(tag & AMX_TAG_STRONG);
}

stock bool:IsTagIDEmpty(tag) {
	return !(tag & ~AMX_TAG_MASK);
}

stock bool:IsTagNameStrong(const tag[]) {
	return ('A' <= tag[0] <= 'Z');
}

stock bool:IsTagNameWeak(const tag[]) {
	return !('A' <= tag[0] <= 'Z');
}

stock bool:IsTagNameEmpty(const tag[]) {
	return (tag[0] == '_' && tag[1] == '\0');
}

stock bool:IsTagIndexStrong(tag) {
	new info[AMX_FUNCSTUBNT];
	return (GetTagInfo(tag, info) && IsTagIDStrong(info[AMX_FUNCSTUBNT_ID]));
}

stock bool:IsTagIndexWeak(tag) {
	new info[AMX_FUNCSTUBNT];
	return (GetTagInfo(tag, info) && IsTagIDWeak(info[AMX_FUNCSTUBNT_ID]));
}

stock bool:IsTagIndexEmpty(tag) {
	return (tag == 0);
}

#undef InitStaticAmxHeader

