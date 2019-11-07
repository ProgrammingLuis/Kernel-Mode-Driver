#include <ntddk.h>
#include "Structs.h"

DRIVER_INITIALIZE DriverEntry;
#pragma alloc_text(INIT, DriverEntry)
ULONG processId, baseAddress;

NTSTATUS KeReadVirtualMemory(PEPROCESS* Process, PVOID SourceAddress, PVOID TargetAddress, SIZE_T Size);
NTSTATUS KeWriteVirtualMemory(PEPROCESS* Process, PVOID SourceAddress, PVOID TargetAddress, SIZE_T Size);
VOID GetUserModule(IN PEPROCESS* pProcess);
VOID GetProcessId();

BOOLEAN foundProcess = FALSE;
LARGE_INTEGER time = { 1000 * 100 };

// Driver Entry

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING pRegistryPath) {

	UNREFERENCED_PARAMETER(pRegistryPath);

	NTSTATUS status = STATUS_SUCCESS;

	DbgPrintEx(0, 0, "Driver Loaded\n");

	pDriverObject->DriverUnload = NULL; // should implement an unload routine

	while (!foundProcess) {
		GetProcessId();
		KeDelayExecutionThread(KernelMode, FALSE, &time);
	}

	PEPROCESS process;
	PsLookupProcessByProcessId(processId, &process);

	// from here you should be able to read and write memory to your desired addresses

	return status;
}

/* REQUIRES: Process is a pointer to a valid PEPROCESS, SourceAddress is a valid pointer to a 
			 address in the desired program's virtual memory, TargetAddress is a valid pointer to where 
			 you want the data to be stored, Size is the size of data that is being read.
   MODIFIES: Modifies the TargetAddress by sending it the data at the SourceAddress.
   EFFECTS: Return NTSTATUS code STATUS_SUCCESS if if the SourceAddress was accessed sucessfully,
            otherwise it will return STATUS_ACCESS_DENIED if the memory could not be read. 
*/

NTSTATUS KeReadVirtualMemory(IN PEPROCESS* Process, IN PVOID SourceAddress, IN PVOID TargetAddress, IN SIZE_T Size)
{
	PSIZE_T Bytes;
	if (NT_SUCCESS(MmCopyVirtualMemory(*Process, SourceAddress, PsGetCurrentProcess(),
		TargetAddress, Size, KernelMode, &Bytes)))
		return STATUS_SUCCESS;
	else
		return STATUS_ACCESS_DENIED;
}

/* REQUIRES: Process is a valid pointer to your desired process, SourceAddress is a valid pointer to an address in
			 the desired program's virtual memory, TargetAddress is a valid pointer to an
			 address in your desired process's virtual memory where you want the data written to, 
			 Size is the size of data that is being written.
   MODIFIES: Modifies the SourceAddress by sending it the data at the TargetAddress.
   EFFECTS: Return NTSTATUS code STATUS_SUCCESS if if the SourceAddress was accessed sucessfully,
			otherwise it will return STATUS_ACCESS_DENIED if the address could not be written to.
*/

NTSTATUS KeWriteVirtualMemory(IN PEPROCESS* Process, IN PVOID SourceAddress, OUT PVOID TargetAddress, OUT SIZE_T Size)
{
	PSIZE_T Bytes;
	if (NT_SUCCESS(MmCopyVirtualMemory(PsGetCurrentProcess(), SourceAddress, *Process,
		TargetAddress, Size, KernelMode, &Bytes)))
		return STATUS_SUCCESS;
	else
		return STATUS_ACCESS_DENIED;
}

/* REQUIRES: Initialize WantedImageName to the filename of your desired process.
   MODIFIES: The processId variable declared at the start of this file
*/

VOID GetProcessId() {

	NTSTATUS status = STATUS_SUCCESS;
	PVOID buffer;

	UNICODE_STRING WantedImageName;

	RtlInitUnicodeString(&WantedImageName, L"desiredProcess.exe");

	buffer = ExAllocatePoolWithTag(NonPagedPool, 1024 * 1024, 'enoN');

	if (!buffer) {
		DbgPrintEx(0, 0, "couldn't allocate memory \n");
		return;
	}

	DbgPrintEx(0, 0, "Process list allocated at address %#p\n", buffer);

	PSYSTEM_PROCESS_INFORMATION pInfo = (PSYSTEM_PROCESS_INFORMATION)buffer;


	status = ZwQuerySystemInformation(0x5, pInfo, 1024 * 1024, NULL);
	if (!NT_SUCCESS(status)) {
		DbgPrintEx(0, 0, "ZwQuerySystemInformation Failed : STATUS CODE : %x\n", status);
		ExFreePoolWithTag(buffer, 'Enon');
		return;
	}

	if (NT_SUCCESS(status)) {
		for (;;) {
			if (RtlEqualUnicodeString(&pInfo->ImageName, &WantedImageName, TRUE)) {
				DbgPrintEx(0, 0, "Found the desired process.\n");
				foundProcess = TRUE;
				processId = (ULONG)pInfo->UniqueProcessId;
				break;
			}
			else if (pInfo->NextEntryOffset)
				pInfo = (PSYSTEM_PROCESS_INFORMATION)((PUCHAR)pInfo + pInfo->NextEntryOffset);
			else
				break;
		}
	}

	ExFreePoolWithTag(buffer, 'enoN');
}

/* REQUIRES: pProcess is a valid pointer to your desired process, 
             initialize ModuleName to your desired module's filename. 
   MODIFIES: baseAddress variable declared at the start of this file
*/

VOID GetUserModule(IN PEPROCESS* pProcess)
{
	if (*pProcess == NULL)
		return;

	PPEB pPeb = PsGetProcessPeb(*pProcess);
	UNICODE_STRING ModuleName;
	RtlInitUnicodeString(&ModuleName, L"desiredModule.dll");

	if (!pPeb || !pPeb->Ldr)
	{
		return;
	}

	DbgPrintEx(0, 0, "Crashed at GetUserModule\n");

	for (PLIST_ENTRY pListEntry = pPeb->Ldr->InLoadOrderModuleList.Flink;
		pListEntry != &pPeb->Ldr->InLoadOrderModuleList;
		pListEntry = pListEntry->Flink)
	{
		PLDR_DATA_TABLE_ENTRY pEntry = CONTAINING_RECORD(pListEntry, LDR_DATA_TABLE_ENTRY, InLoadOrderLinks);
		if (RtlCompareUnicodeString(&pEntry->BaseDllName, &ModuleName, TRUE) == 0) {
			DbgPrintEx(0, 0, "Succesfully retrieved user module.\n");
			baseAddress = (ULONG)(pEntry->DllBase);
			return;
		}
			
	}

	return;
}

