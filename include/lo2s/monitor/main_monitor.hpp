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

#pragma once

#include <lo2s/metric/plugin/metrics.hpp>
#ifdef HAVE_X86_ADAPT
#include <lo2s/metric/x86_adapt/metrics.hpp>
#endif
#ifdef HAVE_X86_ENERGY
#include <lo2s/metric/x86_energy/metrics.hpp>
#endif
#include <lo2s/process_info.hpp>
#include <lo2s/trace/trace.hpp>

namespace lo2s
{
namespace perf
{
namespace tracepoint
{
class MetricMonitor;
}
} // namespace perf

namespace monitor
{
struct MmapCache
{
    MmapCache(uint32_t pid, uint64_t addr, uint64_t len, uint64_t pgoff, std::string filename)
    : pid(pid), addr(addr), len(len), pgoff(pgoff), filename(filename)
    {
    }

    uint32_t pid;
    uint64_t addr;
    uint64_t len;
    uint64_t pgoff;
    std::string filename;
};

class MainMonitor
{
public:
    MainMonitor();

    virtual ~MainMonitor();

    trace::Trace& trace()
    {
        return trace_;
    }

    void insert_cached_mmap_events(std::deque<struct MmapCache> cached_events);

    std::map<pid_t, ProcessInfo>& get_process_infos()
    {
        return process_infos_;
    }

protected:
    trace::Trace trace_;

    std::map<pid_t, ProcessInfo> process_infos_;
    metric::plugin::Metrics metrics_;
    std::unique_ptr<perf::tracepoint::MetricMonitor> tracepoint_metrics_;
#ifdef HAVE_X86_ADAPT
    std::unique_ptr<metric::x86_adapt::Metrics> x86_adapt_metrics_;
#endif
#ifdef HAVE_X86_ENERGY
    std::unique_ptr<metric::x86_energy::Metrics> x86_energy_metrics_;
#endif
};
} // namespace monitor
} // namespace lo2s
