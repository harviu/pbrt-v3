
#if defined(_MSC_VER)
#define NOMINMAX
#pragma once
#endif

#ifndef PBRT_LAB_2_GLOBAL_H
#define PBRT_LAB_2_GLOBAL_H

#include <atomic>
#include <vector>

namespace pbrt {
    extern std::atomic<int> lab2_total_rays ;
    extern std::atomic<int> lab2_bbox_rays ;
    extern std::atomic<int> lab2_object_rays ;
    extern std::atomic<int> lab2_object1_rays ;
    extern std::atomic<int> lab2_object2_rays ;
    extern std::vector<int> tile_counter;
    extern int nTiles_x, nTiles_y;
}

#endif  // PBRT_LAB_2_GLOBAL_H