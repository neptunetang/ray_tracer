//
// Created by neptune on 09-04-20.
//

#include "hitable_list.h"

bool hitable_list::is_hit(const ray &r, float tmin, float tmax, hit_record &rec) const {
    hit_record tmp_rec;
    bool is_hit_something = false;
    float closest_so_far = tmax;
    for(int i=0; i<list_size; i++){
        if(list[i]->is_hit(r,tmin, closest_so_far, tmp_rec)){
            is_hit_something = true;
            closest_so_far = tmp_rec.t;
            rec = tmp_rec;
        }
    }
    return is_hit_something;
}