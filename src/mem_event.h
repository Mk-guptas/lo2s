/*
 * This file is part of the lo2s software.
 * Linux OTF2 sampling
 *
 * Copyright (c) 2016,
 *    Technische Universitaet Dresden, Germany
 *
 * lo2s is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * lo2s is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with lo2s.  If not, see <http://www.gnu.org/licenses/>.
 */
/*
 * mem_event.h
 *
 *  Created on: 20.02.2015
 *      Author: rschoene
 */

#ifndef MEM_EVENT_H_
#define MEM_EVENT_H_

/* gracefully copied from https://github.com/deater/perf_event_tests/blob/master/ */

#ifdef __powerpc__
#define rmb() asm volatile("sync" : : : "memory")
#elif defined(__s390__)
#define rmb() asm volatile("bcr 15,0" ::: "memory")
#elif defined(__sh__)
#if defined(__SH4A__) || defined(__SH5__)
#define rmb() asm volatile("synco" ::: "memory")
#else
#define rmb() asm volatile("" ::: "memory")
#endif
#elif defined(__hppa__)
#define rmb() asm volatile("" ::: "memory")
#elif defined(__sparc__)
#define rmb() asm volatile("" ::: "memory")
#elif defined(__alpha__)
#define rmb() asm volatile("mb" ::: "memory")
#elif defined(__ia64__)
#define rmb() asm volatile("mf" ::: "memory")
#elif defined(__arm__)
/*
 * Use the __kuser_memory_barrier helper in the CPU helper page. See
 * arch/arm/kernel/entry-armv.S in the kernel source for details.
 */
#define rmb() ((void (*)(void))0xffff0fa0)()
#elif defined(__aarch64__)
#define rmb() asm volatile("dmb ld" ::: "memory")
#elif defined(__mips__)
#define rmb()                                                                                      \
    asm volatile(".set mips2\n\t"                                                                  \
                 "sync\n\t"                                                                        \
                 ".set mips0"                                                                      \
                 : /* no output */                                                                 \
                 : /* no input */                                                                  \
                 : "memory")
#elif defined(__i386__)
#define rmb() asm volatile("lock; addl $0,0(%%esp)" ::: "memory")
#elif defined(__x86_64)
#if defined(__KNC__)
#define rmb() __sync_synchronize()
#else
#define rmb() asm volatile("lfence" ::: "memory")
#endif
#else
#error Need to define rmb for this architecture!
#error See the kernel source directory: tools/perf/perf.h file
#endif

int get_latency_load_event(unsigned long long* config, unsigned long long* config1,
                           int* precise_ip);
int get_latency_store_event(unsigned long long* config, unsigned long long* config1,
                            int* precise_ip);

uint64_t get_mem_event(int mem_level);

#define VENDOR_UNKNOWN -1
#define VENDOR_INTEL 1
#define VENDOR_AMD 2
#define VENDOR_IBM 3
#define VENDOR_ARM 4
#define PROCESSOR_UNKNOWN -1
#define PROCESSOR_PENTIUM_PRO 1
#define PROCESSOR_PENTIUM_II 2
#define PROCESSOR_PENTIUM_III 3
#define PROCESSOR_PENTIUM_4 4
#define PROCESSOR_PENTIUM_M 5
#define PROCESSOR_COREDUO 6
#define PROCESSOR_CORE2 7
#define PROCESSOR_NEHALEM 8
#define PROCESSOR_NEHALEM_EX 9
#define PROCESSOR_WESTMERE 10
#define PROCESSOR_WESTMERE_EX 11
#define PROCESSOR_SANDYBRIDGE 12
#define PROCESSOR_ATOM 13
#define PROCESSOR_K7 14
#define PROCESSOR_K8 15
#define PROCESSOR_AMD_FAM10H 16
#define PROCESSOR_AMD_FAM11H 17
#define PROCESSOR_AMD_FAM14H 18
#define PROCESSOR_AMD_FAM15H 19
#define PROCESSOR_IVYBRIDGE 20
#define PROCESSOR_KNIGHTSCORNER 21
#define PROCESSOR_SANDYBRIDGE_EP 22
#define PROCESSOR_AMD_FAM16H 23
#define PROCESSOR_IVYBRIDGE_EP 24
#define PROCESSOR_HASWELL 25
#define PROCESSOR_ATOM_CEDARVIEW 26
#define PROCESSOR_ATOM_SILVERMONT 27
#define PROCESSOR_BROADWELL 28
#define PROCESSOR_HASWELL_EP 29
#define PROCESSOR_POWER3 103
#define PROCESSOR_POWER4 104
#define PROCESSOR_POWER5 105
#define PROCESSOR_POWER6 106
#define PROCESSOR_POWER7 107
#define PROCESSOR_CORTEX_A8 200
#define PROCESSOR_CORTEX_A9 201
#define PROCESSOR_CORTEX_A5 202
#define PROCESSOR_CORTEX_A15 203
#define PROCESSOR_ARM1176 204

#endif /* MEM_EVENT_H_ */
