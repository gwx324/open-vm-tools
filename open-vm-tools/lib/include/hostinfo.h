/*********************************************************
 * Copyright (C) 1998-2016 VMware, Inc. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation version 2.1 and no later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the Lesser GNU General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA.
 *
 *********************************************************/

/*
 * hostinfo.h --
 *
 *      Interface to host-specific information functions
 *
 */

#if !defined(_HOSTINFO_H_)
#define _HOSTINFO_H_

#define INCLUDE_ALLOW_USERLEVEL
#define INCLUDE_ALLOW_VMCORE
#include "includeCheck.h"

#include "vm_basic_types.h"
#include "vm_basic_defs.h"
#include "x86cpuid.h"
#include "unicodeTypes.h"

typedef enum {
   HOSTINFO_PROCESS_QUERY_DEAD,    // Procss is dead (does not exist)
   HOSTINFO_PROCESS_QUERY_ALIVE,   // Process is alive (does exist)
   HOSTINFO_PROCESS_QUERY_UNKNOWN  // Process existence cannot be determined
} HostinfoProcessQuery;

HostinfoProcessQuery Hostinfo_QueryProcessExistence(int pid);

char *Hostinfo_NameGet(void);	/* don't free result */
char *Hostinfo_HostName(void);	/* free result */

void Hostinfo_MachineID(uint32 *hostNameHash,
                        uint64 *hostHardwareID);

Bool Hostinfo_GetMemoryInfoInPages(unsigned int *minSize,
                                   unsigned int *maxSize,
       unsigned int *currentSize);
#ifdef __linux__
Bool Hostinfo_GetSwapInfoInPages(unsigned int *totalSwap,
                                 unsigned int *freeSwap);
#endif
Bool Hostinfo_GetRatedCpuMhz(int32 cpuNumber,
                             uint32 *mHz);
char *Hostinfo_GetCpuDescription(uint32 cpuNumber);
void Hostinfo_GetTimeOfDay(VmTimeType *time);
VmTimeType Hostinfo_SystemUpTime(void);
VmTimeType Hostinfo_SystemTimerNS(void);

static INLINE VmTimeType
Hostinfo_SystemTimerUS(void)
{
   return Hostinfo_SystemTimerNS() / 1000ULL;
}

static INLINE VmTimeType
Hostinfo_SystemTimerMS(void)
{
   return Hostinfo_SystemTimerNS() / 1000000ULL;
}

int Hostinfo_OSVersion(unsigned int i);
int Hostinfo_GetSystemBitness(void);
const char *Hostinfo_OSVersionString(void);

char *Hostinfo_GetOSName(void);
char *Hostinfo_GetOSGuestString(void);

Bool Hostinfo_OSIsSMP(void);

#if defined(_WIN32)
Bool Hostinfo_OSIsWinNT(void);
Bool Hostinfo_OSIsWow64(void);
Bool Hostinfo_TSCInvariant(void);
DWORD Hostinfo_OpenProcessBits(void);
DWORD Hostinfo_OpenThreadBits(void);
#else
void Hostinfo_ResetProcessState(const int *keepFds,
                                size_t numKeepFds);

int Hostinfo_Execute(const char *path,
                     char * const *args,
                     Bool wait,
                     const int *keepFds,
                     size_t numKeepFds);

typedef enum HostinfoDaemonizeFlags {
   HOSTINFO_DAEMONIZE_DEFAULT = 0,
   HOSTINFO_DAEMONIZE_NOCHDIR = (1 << 0),
   HOSTINFO_DAEMONIZE_NOCLOSE = (1 << 1),
   HOSTINFO_DAEMONIZE_EXIT    = (1 << 2),
   HOSTINFO_DAEMONIZE_LOCKPID = (1 << 3),
} HostinfoDaemonizeFlags;

Bool Hostinfo_Daemonize(const char *path,
                        char * const *args,
                        HostinfoDaemonizeFlags flags,
                        const char *pidPath,
                        const int *keepFds,
                        size_t numKeepFds);
#endif

Bool Hostinfo_NestingSupported(void);
Bool Hostinfo_VCPUInfoBackdoor(unsigned bit);
Bool Hostinfo_SLC64Supported(void);
Bool Hostinfo_SynchronizedVTSCs(void);
Bool Hostinfo_NestedHVReplaySupported(void);
Bool Hostinfo_TouchBackDoor(void);
Bool Hostinfo_TouchVirtualPC(void);
Bool Hostinfo_TouchXen(void);
char *Hostinfo_HypervisorCPUIDSig(void);

#define HGMP_PRIVILEGE    0
#define HGMP_NO_PRIVILEGE 1
char *Hostinfo_GetModulePath(uint32 priv);
char *Hostinfo_GetLibraryPath(void *addr);

char *Hostinfo_GetUser(void);
void Hostinfo_LogMemUsage(void);


/*
 * HostInfoCpuIdInfo --
 *
 *      Contains cpuid information for a CPU.
 */

typedef struct {
   CpuidVendor vendor;

   uint32 version;
   uint8 family;
   uint8 model;
   uint8 stepping;
   uint8 type;

   uint32 features;
   uint32 extfeatures;
} HostinfoCpuIdInfo;


uint32 Hostinfo_NumCPUs(void);
char *Hostinfo_GetCpuidStr(void);
Bool Hostinfo_GetCpuid(HostinfoCpuIdInfo *info);

#if !defined(VMX86_SERVER)
Bool Hostinfo_CPUCounts(uint32 *logical,
                        uint32 *cores,
                        uint32 *pkgs);
#endif

#if defined(_WIN32)
typedef enum {
   OS_WIN95                  = 1,
   OS_WIN98                  = 2,
   OS_WINME                  = 3,
   OS_WINNT                  = 4,
   OS_WIN2K                  = 5,
   OS_WINXP                  = 6,
   OS_WIN2K3                 = 7,
   OS_VISTA                  = 8,
   OS_WINSEVEN               = 9,
   OS_WIN8                   = 10,
   OS_WIN10                  = 11,
   OS_UNKNOWN                = 99999 // last, highest value
} OS_TYPE;

typedef enum {
   OS_DETAIL_WIN95           = 1,
   OS_DETAIL_WIN98           = 2,
   OS_DETAIL_WINME           = 3,
   OS_DETAIL_WINNT           = 4,
   OS_DETAIL_WIN2K           = 5,
   OS_DETAIL_WIN2K_PRO       = 6,
   OS_DETAIL_WIN2K_SERV      = 7,
   OS_DETAIL_WIN2K_ADV_SERV  = 8,
   OS_DETAIL_WINXP           = 9,
   OS_DETAIL_WINXP_HOME      = 10,
   OS_DETAIL_WINXP_PRO       = 11,
   OS_DETAIL_WINXP_X64_PRO   = 12,
   OS_DETAIL_WIN2K3          = 13,
   OS_DETAIL_WIN2K3_WEB      = 14,
   OS_DETAIL_WIN2K3_ST       = 15,
   OS_DETAIL_WIN2K3_EN       = 16,
   OS_DETAIL_WIN2K3_BUS      = 17,
   OS_DETAIL_VISTA           = 18,
   OS_DETAIL_WIN2K8          = 19,
   OS_DETAIL_WINSEVEN        = 20,
   OS_DETAIL_WIN2K8R2        = 21,
   OS_DETAIL_WIN8            = 22,
   OS_DETAIL_WIN8SERVER      = 23,
   OS_DETAIL_WIN10           = 24,
   OS_DETAIL_WIN10SERVER     = 25,
   OS_DETAIL_UNKNOWN         = 99999  // last, highest value
} OS_DETAIL_TYPE;

/* generic names (to protect the future) but Windows specific for now */
OS_TYPE Hostinfo_GetOSType(void);
OS_DETAIL_TYPE Hostinfo_GetOSDetailType(void);

Bool Hostinfo_GetPCFrequency(uint64 *pcHz);
Bool Hostinfo_GetMhzOfProcessor(int32 processorNumber,
				uint32 *currentMhz,
                                uint32 *maxMhz);
uint64 Hostinfo_SystemIdleTime(void);
Bool Hostinfo_GetAllCpuid(CPUIDQuery *query);

static INLINE Bool
Hostinfo_AtLeastVista(void)
{
   return (Hostinfo_GetOSType() >= OS_VISTA);
}
#endif
void Hostinfo_LogLoadAverage(void);
Bool Hostinfo_GetLoadAverage(uint32 *l);

#ifdef __APPLE__
size_t Hostinfo_GetKernelZoneElemSize(char const *name);
char *Hostinfo_GetHardwareModel(void);
#endif

#endif /* ifndef _HOSTINFO_H_ */
