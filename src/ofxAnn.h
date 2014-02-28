#pragma once

#include "ofMain.h"
#include <nanoflann.hpp>

template < typename container_t, typename size_t = int, typename coord_t = float >
class ofxAnn {
public:
    struct result_knn {
        result_knn(int count) :
        indices(vector< size_t >(count)),
        distances(vector< coord_t >(count))
        { }
        
        typename vector< size_t >::iterator indices_it;
        vector< size_t > indices;
        typename vector< coord_t>::iterator distances_it;
        vector< coord_t > distances;
        
        size_t size() const { return indices.size(); }
    };
    
    struct result_radius {
        result_radius() {};
        
        typedef std::vector< std::pair< size_t, coord_t > > container;
        container data;
        typename container::iterator it;
        
        size_t size() const { return data.size(); }
        typename container::iterator begin() { return data.begin(); }
        typename container::iterator end() { return data.end(); }
    };
    
    ofxAnn(container_t & _container) :
    container(_container),
    adapter(Adapter(_container)),
    index(Index(15 /* dims */,
                adapter,
                nanoflann::KDTreeSingleIndexAdaptorParams(10 /* max leaf */)))
    { }
    
    void buildIndex() { if ( container.size() > 0 ) index.buildIndex(); }
    result_knn findNearest(ofPoint & pt) { return findNeighbors(pt, 1); }
    result_knn findNearest(vector<float> & parameters) { return findNeighbors(parameters, 1); }
    
    result_knn findNeighbors(ofPoint & pt, const size_t numResults = 1)
    {
        result_knn r(numResults);
        
        float query[3] = { pt.x, pt.y, pt.z };
        
        index.knnSearch(&query[0], numResults, &r.indices[0], &r.distances[0]);
                
        return r;        
    }
    
    result_knn findNeighbors(vector<float> & parameters, const size_t numResults = 1)
    {
        result_knn r(numResults);
        
        float query[parameters.size()];
        for (int i=0; i < parameters.size(); i++) {
            query[i] = parameters[i];
        }
        
        index.knnSearch(&query[0], numResults, &r.indices[0], &r.distances[0]);
        
        return r;
    }
    
    result_radius findWithin(ofPoint & pt, const coord_t radius)
    {
        result_radius r;
        nanoflann::SearchParams params;
        float query[3] = { pt.x, pt.y, pt.z };
        
        index.radiusSearch(&query[0], radius, r.data, params);
        
        return r;
    }
    
    result_radius findWithin(vector<float> & parameters, const coord_t radius)
    {
        result_radius r;
        nanoflann::SearchParams params;
        
        float query[parameters.size()];
        for (int i=0; i < parameters.size(); i++) {
            query[i] = parameters[i];
        }
        
        index.radiusSearch(&query[0], radius, r.data, params);
        
        return r;
    }
    
private:
    container_t & container;
    
    struct Adapter {
        const container_t &container;
        
        Adapter(const container_t &_container) :
        container(_container)
        { }
        
        inline const container_t & getContainer() const { return container; }

//        inline const ofPoint getPoint(size_t idx) const {
//            return getContainer().at(idx).getPoint();
//        }
        inline const vector<float> getValues(size_t idx) const {
            return getContainer().at(idx).getValues();
        }
        
        // KD callbacks
        
        inline size_t kdtree_get_point_count() const { return container.size(); }
        
        // Returns the distance between the vector "p1[0:size-1]" and the data
        // point with index "idx_p2" stored in the class:
        inline coord_t kdtree_distance
        (const coord_t * p1, const size_t idx_p2, size_t size) const
        {
//            ofPoint pt = getPoint(idx_p2);
            vector<float> pt = getValues(idx_p2);
            const coord_t d0 = p1[0] - pt[0];
            const coord_t d1 = p1[1] - pt[1];
            const coord_t d2 = p1[2] - pt[2];
            const coord_t d3 = p1[3] - pt[3];
            const coord_t d4 = p1[4] - pt[4];
            const coord_t d5 = p1[5] - pt[5];
            const coord_t d6 = p1[6] - pt[6];
            const coord_t d7 = p1[7] - pt[7];
            const coord_t d8 = p1[8] - pt[8];
            const coord_t d9 = p1[9] - pt[9];
            const coord_t d10 = p1[10] - pt[10];
            const coord_t d11 = p1[11] - pt[11];
            const coord_t d12 = p1[12] - pt[12];
            const coord_t d13 = p1[13] - pt[13];
            const coord_t d14 = p1[14] - pt[14];
            const coord_t d15 = p1[15] - pt[15];
            return d0 * d0 + d1 * d1 + d2 * d2 + d3 * d3 + d4 * d4 + d5 * d5
            + d6 * d6 + d7 * d7 + d8 * d8 + d9 * d9 + d10 * d10
            + d11 * d11 + d12 * d12 + d13 * d13 + d14 * d14 + d15 * d15;
        }
        
        // Returns the dim'th component of the idx'th point in the class:
        // Since this is inlined and the "dim" argument is typically an
        // immediate value, the "if/else's" are actually solved at compile time.
        inline float kdtree_get_pt
        (const size_t idx, int dim) const
        {
//            ofPoint pt = getPoint(idx);
            vector<float> pt = getValues(idx);
            if (dim == 0) return pt[0];
            else if (dim == 1) return pt[1];
            else if (dim == 2) return pt[2];
            else if (dim == 3) return pt[3];
            else if (dim == 4) return pt[4];
            else if (dim == 5) return pt[5];
            else if (dim == 6) return pt[6];
            else if (dim == 7) return pt[7];
            else if (dim == 8) return pt[8];
            else if (dim == 9) return pt[9];
            else if (dim == 10) return pt[10];
            else if (dim == 11) return pt[11];
            else if (dim == 12) return pt[12];
            else if (dim == 13) return pt[13];
            else if (dim == 14) return pt[14];
            else return pt[15];
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
        15 /* dims */,
        size_t
    > Index;
    
    const Adapter adapter;
    Index index;
};