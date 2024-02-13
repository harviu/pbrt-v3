
#include "globals.h"
#include <atomic>

namespace pbrt {
    std::atomic<int> lab2_total_rays = 0;
    std::atomic<int> lab2_bbox_rays = 0;
    std::atomic<int> lab2_object_rays = 0;
    std::atomic<int> lab2_object1_rays = 0;
    std::atomic<int> lab2_object2_rays = 0;
    std::vector<int> tile_counter(0);
    int nTiles_x=0;
    int nTiles_y = 0;
}
