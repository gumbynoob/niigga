#include "../stdafx.h"
#include "HvxCalls.h"
#pragma warning(push)
#pragma warning(disable:4826) // Get rid of the sign-extended warning

#define HvxCall QWORD _declspec(naked)
namespace xbox {
	namespace Hvx
	{
		// lets hide stuff the rest of the project doesn't need to see
		namespace
		{
			const BYTE HvPeekPokeExp[] = {
				0x48, 0x58, 0x50, 0x52, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x34, 0x1F, 0xD6, 0xDA,
				0x2F, 0xCA, 0xA8, 0x17, 0xF0, 0x30, 0xCC, 0x44, 0x0A, 0x41, 0xFA, 0x7C, 0xA0, 0xC1, 0xFD, 0x33,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x7A, 0x02, 0x59, 0x43, 0x9E, 0xE6, 0x93, 0xD5, 0x01, 0xC9, 0x48, 0x4D, 0xB2, 0xBF, 0x9D, 0x18,
				0xA9, 0x16, 0x5E, 0xFF, 0x1E, 0xD5, 0xB6, 0xA8, 0x79, 0x60, 0xA8, 0x2F, 0xC1, 0x8D, 0x20, 0x8A,
				0xEB, 0x46, 0xC3, 0x01, 0xEC, 0xC4, 0xDB, 0xDF, 0xA1, 0x04, 0xD1, 0xDF, 0x23, 0x69, 0x5E, 0xCC,
				0x50, 0xC3, 0xF4, 0xDD, 0xA4, 0x80, 0x7D, 0x05, 0x2D, 0x57, 0xFF, 0x60, 0xA5, 0x58, 0x69, 0x27,
				0x9A, 0x33, 0x70, 0xE8, 0xC2, 0x82, 0xDC, 0xDA, 0xE2, 0x4D, 0xE1, 0xF8, 0xA1, 0xD2, 0xCC, 0x8D,
				0x98, 0x05, 0xD1, 0xA3, 0x2E, 0x37, 0x06, 0x0F, 0xF7, 0xEF, 0x70, 0xEF, 0x28, 0xD7, 0xAE, 0xD5,
				0x5B, 0x19, 0x1B, 0x13, 0x50, 0x0D, 0x15, 0x00, 0x92, 0x01, 0xEE, 0x38, 0xA7, 0x61, 0xB1, 0xA1,
				0x27, 0xBF, 0xB0, 0x42, 0x0F, 0x07, 0xC3, 0x8F, 0x78, 0xAD, 0xAF, 0x87, 0x8F, 0x34, 0x8A, 0xA6,
				0x69, 0x7D, 0x40, 0xB6, 0x5C, 0x9E, 0x01, 0xEC, 0x9F, 0x5E, 0x78, 0x30, 0x09, 0x5A, 0x21, 0xFF,
				0x35, 0x8C, 0x13, 0xBE, 0xBC, 0x92, 0x67, 0xE3, 0x17, 0x0B, 0x09, 0x1C, 0xE2, 0x9D, 0xEC, 0xFD,
				0xFB, 0x6C, 0x49, 0x3A, 0xCC, 0xE7, 0x99, 0xB6, 0xB3, 0x8A, 0x8F, 0xEF, 0xF7, 0xA0, 0x28, 0x4F,
				0x72, 0xC7, 0x3D, 0xD7, 0xCC, 0xEB, 0xB2, 0x1B, 0x74, 0x93, 0xD7, 0x02, 0x05, 0xD5, 0xE1, 0x25,
				0x35, 0xD7, 0xE0, 0x50, 0xEA, 0xCF, 0x82, 0x69, 0xE3, 0x3B, 0x6F, 0xFA, 0x13, 0xF0, 0x5B, 0xD9,
				0x1A, 0xB0, 0xD3, 0x0B, 0x85, 0x4D, 0x6A, 0xFC, 0x31, 0x45, 0xC3, 0xA3, 0xFA, 0x7E, 0xDA, 0x93,
				0x84, 0xD4, 0xE7, 0xFA, 0xAB, 0x7C, 0x22, 0x96, 0x54, 0x69, 0x7F, 0xC9, 0xF8, 0xC4, 0x5A, 0xC2,
				0x82, 0x99, 0x34, 0x46, 0x81, 0x6F, 0x06, 0x33, 0x19, 0x94, 0x74, 0xA4, 0x76, 0x02, 0x4F, 0xB9,
				0x48, 0x56, 0x50, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x60, 0x00, 0x00, 0x01, 0x90,
				0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00,
				0x7D, 0x88, 0x02, 0xA6, 0xFB, 0xE1, 0xFF, 0xF0, 0xF9, 0x81, 0xFF, 0xF8, 0x94, 0x21, 0xFF, 0x00,
				0x7C, 0x9F, 0x23, 0x78, 0x2C, 0x1F, 0x00, 0x00, 0x41, 0x82, 0x00, 0xC0, 0x2C, 0x1F, 0x00, 0x01,
				0x41, 0x82, 0x00, 0xC0, 0x2C, 0x1F, 0x00, 0x02, 0x41, 0x82, 0x00, 0xC0, 0x2C, 0x1F, 0x00, 0x03,
				0x41, 0x82, 0x00, 0xC0, 0x2C, 0x1F, 0x00, 0x0A, 0x41, 0x82, 0x00, 0x64, 0x2C, 0x1F, 0x00, 0x05,
				0x41, 0x82, 0x00, 0xD4, 0x2C, 0x1F, 0x00, 0x06, 0x41, 0x82, 0x00, 0xD4, 0x2C, 0x1F, 0x00, 0x07,
				0x41, 0x82, 0x00, 0xD4, 0x2C, 0x1F, 0x00, 0x08, 0x41, 0x82, 0x00, 0xD4, 0x2C, 0x1F, 0x00, 0x0B,
				0x40, 0x80, 0x00, 0x00, 0x80, 0x60, 0x00, 0x4C, 0x7C, 0x62, 0x1A, 0x14, 0x80, 0x63, 0x00, 0x08,
				0x7C, 0x69, 0x03, 0xA6, 0x7C, 0xC3, 0x33, 0x78, 0x38, 0x80, 0x00, 0x01, 0x4E, 0x80, 0x04, 0x21,
				0x7C, 0x66, 0x1B, 0x78, 0x7C, 0xE9, 0x03, 0xA6, 0x2C, 0x1F, 0x00, 0x04, 0x41, 0x82, 0x00, 0x6C,
				0x2C, 0x1F, 0x00, 0x09, 0x41, 0x82, 0x00, 0xA0, 0x48, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x05,
				0x7C, 0xA6, 0x2B, 0x78, 0x3C, 0x80, 0x7C, 0x60, 0x50, 0xA6, 0x54, 0x6A, 0x60, 0x84, 0x02, 0xA6,
				0x50, 0xC4, 0x32, 0xE8, 0x7C, 0x68, 0x02, 0xA6, 0x38, 0x63, 0x00, 0x30, 0x90, 0x83, 0x00, 0x00,
				0x7C, 0x00, 0x18, 0x6C, 0x7C, 0x00, 0x1F, 0xAC, 0x7C, 0x00, 0x04, 0xAC, 0x4C, 0x00, 0x01, 0x2C,
				0x7C, 0x79, 0x4A, 0xA6, 0x48, 0x00, 0x00, 0x98, 0x88, 0x65, 0x00, 0x00, 0x48, 0x00, 0x00, 0x90,
				0xA0, 0x65, 0x00, 0x00, 0x48, 0x00, 0x00, 0x88, 0x80, 0x65, 0x00, 0x00, 0x48, 0x00, 0x00, 0x80,
				0xE8, 0x65, 0x00, 0x00, 0x48, 0x00, 0x00, 0x78, 0x8B, 0xE5, 0x00, 0x00, 0x9B, 0xE6, 0x00, 0x00,
				0x38, 0xA5, 0x00, 0x01, 0x38, 0xC6, 0x00, 0x01, 0x42, 0x00, 0xFF, 0xF0, 0x38, 0x60, 0x00, 0x00,
				0x48, 0x00, 0x00, 0x5C, 0x98, 0xC5, 0x00, 0x00, 0x48, 0x00, 0x00, 0x40, 0xB0, 0xC5, 0x00, 0x00,
				0x48, 0x00, 0x00, 0x38, 0x90, 0xC5, 0x00, 0x00, 0x48, 0x00, 0x00, 0x30, 0xF8, 0xC5, 0x00, 0x00,
				0x48, 0x00, 0x00, 0x28, 0x8B, 0xE6, 0x00, 0x00, 0x9B, 0xE5, 0x00, 0x00, 0x7C, 0x00, 0x28, 0x6C,
				0x7C, 0x00, 0x2F, 0xAC, 0x7C, 0x00, 0x04, 0xAC, 0x4C, 0x00, 0x01, 0x2C, 0x38, 0xA5, 0x00, 0x01,
				0x38, 0xC6, 0x00, 0x01, 0x42, 0x00, 0xFF, 0xE0, 0x38, 0x60, 0x00, 0x00, 0x7C, 0x00, 0x28, 0x6C,
				0x7C, 0x00, 0x2F, 0xAC, 0x7C, 0x00, 0x04, 0xAC, 0x4C, 0x00, 0x01, 0x2C, 0x38, 0x21, 0x01, 0x00,
				0xEB, 0xE1, 0xFF, 0xF0, 0xE9, 0x81, 0xFF, 0xF8, 0x7D, 0x88, 0x03, 0xA6, 0x4E, 0x80, 0x00, 0x20
			};
		}

		namespace SysCalls
		{
			static HvxCall HvxKeysExecute(PVOID pvPayload, DWORD cbPayload, QWORD Arg1, QWORD Arg2, QWORD Arg3, QWORD Arg4)
			{
				if (global::isDevkit) {
					__asm
					{
						li	r0, 0x40
						sc
						blr
					}
				} else {
					__asm
					{
						li	r0, 0x42
						sc
						blr
					}
				}
			}

			static HvxCall HvxExpansionInstall(DWORD PhysicalAddress, DWORD CodeSize) {
				
				if(global::isDevkit) {
					__asm
					{
						li	r0, 0x70
						sc
						blr
					}
				} 
				else 
				{
					__asm
					{
						li	r0, 0x72
						sc
						blr
					}
				}
			}

			static HvxCall HvxExpansionCall(DWORD ExpansionId, QWORD Param1 = 0, QWORD Param2 = 0, QWORD Param3 = 0, QWORD Param4 = 0) {
				
				if (global::isDevkit) {
					__asm
					{
						li	r0, 0x71
						sc
						blr
					}
				} 
				else 
				{
					__asm
					{
						li	r0, 0x73
						sc
						blr
					}
				}
			}
		}

		QWORD HvKeysExecute(PVOID pvPayload, DWORD cbPayload, QWORD arg1 = NULL, QWORD arg2 = NULL, QWORD arg3 = NULL, QWORD arg4 = NULL)
		{
			return SysCalls::HvxKeysExecute(pvPayload, cbPayload, arg1, arg2, arg3, arg4);
		}

		QWORD HvExpansionInstall(DWORD PhysicalAddress, DWORD CodeSize)
		{
			return SysCalls::HvxExpansionInstall(PhysicalAddress, CodeSize);
		}

		QWORD HvExpansionCall(DWORD ExpansionId, QWORD Param1 = NULL, QWORD Param2 = NULL, QWORD Param3 = NULL, QWORD Param4 = NULL)
		{
			return SysCalls::HvxExpansionCall(ExpansionId, Param1, Param2, Param3, Param4);
		}

		DWORD HvPeekPokeExpID = 0x48565050;
		HRESULT InitializeHvPeekPoke() {
			// Allocate physcial memory for this expansion
			VOID* pPhysExp = XPhysicalAlloc(0x1000, MAXULONG_PTR, 0, PAGE_READWRITE);
			DWORD physExpAdd = (DWORD)MmGetPhysicalAddress(pPhysExp);

			// Copy over our expansion data
			ZeroMemory(pPhysExp, 0x1000);
			memcpy(pPhysExp, HvPeekPokeExp, sizeof(HvPeekPokeExp));

			// Now we can install our expansion
			////xbox::utilities::DbgOut("ExpAdd: 0x%016llX\n", physExpAdd);
			HRESULT result = (HRESULT)HvExpansionInstall(physExpAdd, 0x1000);

			// Free our allocated data
			XPhysicalFree(pPhysExp);

			// Return our install result
			return result;
		}

		BYTE    HvPeekBYTE(QWORD Address) {
			return (BYTE)HvExpansionCall(HvPeekPokeExpID, PEEK_BYTE, Address);
		}
		WORD    HvPeekWORD(QWORD Address) {
			return (WORD)HvExpansionCall(HvPeekPokeExpID, PEEK_WORD, Address);
		}
		DWORD   HvPeekDWORD(QWORD Address) {
			return (DWORD)HvExpansionCall(HvPeekPokeExpID, PEEK_DWORD, Address);
		}
		QWORD   HvPeekQWORD(QWORD Address) {
			return HvExpansionCall(HvPeekPokeExpID, PEEK_QWORD, Address);
		}

		HRESULT HvPeekBytes(QWORD Address, PVOID Buffer, DWORD Size) {

			// Create a physical buffer to peek into
			VOID* data = XPhysicalAlloc(Size, MAXULONG_PTR, 0, PAGE_READWRITE);
			ZeroMemory(data, Size);

			HRESULT result = (HRESULT)HvExpansionCall(HvPeekPokeExpID, PEEK_BYTES, Address, (QWORD)MmGetPhysicalAddress(data), Size);

			// If its successful copy it back
			if (result == S_OK) memcpy(Buffer, data, Size);

			// Free our physical data and return our result
			XPhysicalFree(data);
			return result;
		}

		HRESULT HvPokeBYTE(QWORD Address, BYTE Value) {
			return (HRESULT)HvExpansionCall(HvPeekPokeExpID, POKE_BYTE, Address, Value);
		}
		HRESULT HvPokeWORD(QWORD Address, WORD Value) {
			return (HRESULT)HvExpansionCall(HvPeekPokeExpID, POKE_WORD, Address, Value);
		}
		HRESULT HvPokeDWORD(QWORD Address, DWORD Value) {
			return (HRESULT)HvExpansionCall(HvPeekPokeExpID, POKE_DWORD, Address, Value);
		}
		HRESULT HvPokeQWORD(QWORD Address, QWORD Value) {
			return (HRESULT)HvExpansionCall(HvPeekPokeExpID, POKE_QWORD, Address, Value);
		}
		HRESULT HvPokeBytes(QWORD Address, PVOID Buffer, DWORD Size) {

			// Create a physical buffer to poke from
			VOID* data = XPhysicalAlloc(Size, MAXULONG_PTR, 0, PAGE_READWRITE);
			memcpy(data, Buffer, Size);

			HRESULT result = (HRESULT)HvExpansionCall(HvPeekPokeExpID, POKE_BYTES, Address, (QWORD)MmGetPhysicalAddress(data), Size);

			// Free our physical data and return our result
			XPhysicalFree(data);
			return result;
		}
	}
}
#pragma warning(pop)