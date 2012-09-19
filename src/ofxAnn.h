#pragma once

#include "ofMain.h"
#include <nanoflann.hpp>

template < typename container_t, typename size_t = int, typename coord_t = float >
class ofxAnn {
public:
    struct result {
        result(int count) :
        indices(vector< size_t >(count)),
        distances(vector< coord_t >(count))
        { }
        
        typename vector< size_t >::iterator indices_it;
        vector< size_t > indices;
        typename vector< coord_t>::iterator distances_it;
        vector< coord_t > distances;
    };
    
    ofxAnn(container_t & _container) :
    adapter(Adapter(_container)),
    index(Index(3 /* dims */,
                adapter,
                nanoflann::KDTreeSingleIndexAdaptorParams(10 /* max leaf */)))
    { }
    
    void buildIndex() { index.buildIndex(); }
    result findNearest(ofPoint & pt) { return findNeighbors(pt, 1); }
    
    result findNeighbors(ofPoint & pt, const size_t numResults = 1)
    {
        result r(numResults);
        
        float query[3] = { pt.x, pt.y, pt.z };
        
        index.knnSearch(&query[0], numResults, &r.indices[0], &r.distances[0]);
                
        return r;        
    }
private:
    
    struct Adapter {
        const container_t &container;
        
        Adapter(const container_t &_container) :
        container(_container)
        { }
        
        inline const container_t & getContainer() const { return container; }
        inline const ofPoint getPoint(size_t idx) const {
            return getContainer()[idx].getPoint();
        }
        
        // KD callbacks
        
        inline size_t kdtree_get_point_count() const { return container.size(); }
        
        // Returns the distance between the vector "p1[0:size-1]" and the data
        // point with index "idx_p2" stored in the class:
        inline coord_t kdtree_distance
        (const coord_t * p1, const size_t idx_p2, size_t size) const
        {
            ofPoint pt = getPoint(idx_p2);
            const coord_t d0 = p1[0] - pt.x;
            const coord_t d1 = p1[1] - pt.y;
            const coord_t d2 = p1[2] - pt.z;
            return d0 * d0 + d1 * d1 + d2 * d2;
        }
        
        // Returns the dim'th component of the idx'th point in the class:
        // Since this is inlined and the "dim" argument is typically an
        // immediate value, the "if/else's" are actually solved at compile time.
        inline float kdtree_get_pt
        (const size_t idx, int dim) const
        {
            ofPoint pt = getPoint(idx);
            if (dim == 0) return pt.x;
            else if (dim == 1) return pt.y;
            else return pt.z;
        }
        
        // Optional bounding-box computation: return false to default to a
        // standard bbox computation loop. Return true if the BBOX was already
        // computed by the class and returned in "bb" so it can be avoided to
        // redo it again. Look at bb.size() to find out the expected
        // dimensionality (e.g. 2 or 3 for point clouds)
        template <class BBOX>
        bool kdtree_get_bbox(BBOX &bb) const { return false; } 
    };
    
    typedef nanoflann::KDTreeSingleIndexAdaptor<
        nanoflann::L2_Simple_Adaptor< coord_t, Adapter >,
        Adapter,
        3 /* dims */,
        size_t
    > Index;
    
    const Adapter adapter;
    Index index;
};