/** @file

  Copyright (c) 2016, Intel Corporation. All rights reserved.

  Redistribution and use in source and binary forms, with or without modification,
  are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright notice, this
  list of conditions and the following disclaimer in the documentation and/or other
  materials provided with the distribution.

  3. Neither the name of the copyright holder nor the names of its contributors may
  be used to endorse or promote products derived from this software without specific
  prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
  SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
  DAMAGE.

**/

#ifndef __BOOT_H__
#define __BOOT_H__


#define LINUX_IMAGE_LOAD_ADDR           0x80000
#define LINUX_UIMAGE_SIGNATURE           0x56190527
#define LINUX_DTB_ORIGINAL_OFFSET        0x08000000
#define LINUX_DTB_RELOCATED_OFFSET       0x3FFF7000
// Additional size that could be used for FDT entries added by the UEFI OS Loader
// Estimation based on: EDID (300bytes) + bootargs (200bytes) + initrd region (20bytes)
//                      + system memory region (20bytes) + mp_core entries (200 bytes)
#define FDT_ADDITIONAL_ENTRIES_SIZE      0x300

typedef enum {
	BOOT_SOURCE_RSVD = 0,
    BOOT_SOURCE_FPGA,
    BOOT_SOURCE_NAND,
    BOOT_SOURCE_SDMMC,
	BOOT_SOURCE_QSPI,
} BOOT_SOURCE_TYPE;

typedef
VOID
(EFIAPI *BOOTIMAGE_ENTRY_POINT)(
  IN UINTN    R0,
  IN UINTN    R1,
  IN UINTN    R2
  );

typedef struct {
  UINTN   Base;
  UINTN   Size;
} FdtMemoryRegionType;

// ==================================================================
// Functions Definition
// ==================================================================
BOOT_SOURCE_TYPE
EFIAPI
GetBootSourceType (
  VOID
  );

VOID
EFIAPI
PreparePlatformHardwareToBoot (
  VOID
  );

VOID
EFIAPI
JumpToEntry (
  IN UINTN    EntryMemoryAddr,
  IN UINTN    R0,
  IN UINTN    R1,
  IN UINTN    R2
  );

VOID
EFIAPI
LoadDxeImageToRam (
  IN  UINTN            DestinationMemoryBase,
  OUT UINT32*          pFileSize
  );

VOID
EFIAPI
LoadBootImageAndTransferControl (
  IN  BOOT_SOURCE_TYPE  BootSourceType,
  IN  UINT32            IsLinuxBoot,
  IN  CHAR8*            LinuxDtbFilename
  );

EFI_STATUS
EFIAPI
UpdateBootImageDtbWithMemoryInfoAndBootArgs (
  IN  BOOT_SOURCE_TYPE      BootSourceType,
  IN  EFI_PHYSICAL_ADDRESS  FdtBlobBase
  );

EFI_STATUS
EFIAPI
RelocateFdt (
  EFI_PHYSICAL_ADDRESS   OriginalFdtOffset,
  UINTN                  OriginalFdtSize,
  EFI_PHYSICAL_ADDRESS   RelocatedFdtOffset,
  UINTN                  *RelocatedFdtSize
  );

VOID
BootLinuxFromRam (
  VOID
  );
#endif

