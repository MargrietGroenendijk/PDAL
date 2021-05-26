/******************************************************************************
 * Copyright (c) 2014, Hobu Inc. (howard@hobu.co)
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following
 * conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of the Howard Butler or Hobu, Inc.
 *       the names of its contributors may be
 *       used to endorse or promote products derived from this software
 *       without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 ****************************************************************************/

#pragma once

#include <unordered_map>
#include <set>

#include <pdal/pdal_export.hpp>
#include <pdal/private/SimpleHexGrid.hpp>

#include "Hexer.hpp"

#include "exception.hpp"
#include "Hexagon.hpp"
#include "Path.hpp"
#include "Segment.hpp"

namespace pdal
{
namespace hexer
{

class HexIter;

class HexGrid : public SimpleHexGrid
{
    friend class HexIter;

public:
    PDAL_DLL HexGrid(int dense_limit);
    HexGrid(double height, int dense_limit);
    ~HexGrid()
    {
        for (std::vector<Path*>::size_type i = 0; i < m_paths.size(); i++)
            delete m_paths[i];
    }

    PDAL_DLL void findShapes();
    PDAL_DLL void findParentPaths();
    PDAL_DLL void toWKT(std::ostream&) const;

    bool dense(Hexagon *h);
    void addPoint(double x, double y)
        { addPoint(Point(x, y)); }
    void addPoint(Point p);
    void processSample();

    void extractShapes();
    void dumpInfo();
    void drawHexagons();
    Hexagon *getHexagon(HexKey key);
    PDAL_DLL void addDenseHexagon(HexKey key);
    HexIter hexBegin();
    HexIter hexEnd();
    int denseLimit() const
        { return m_dense_limit; }
    std::vector<Path *> const& rootPaths() const
        { return m_paths; }
    void setSampleSize(unsigned sampleSize)
        { m_maxSample = sampleSize; }
    size_t densePointCount() const;

private:
    Hexagon *findHexagon(Point p);
    void findShape(Hexagon *hex);
    void findHole(Hexagon *hex);
    void cleanPossibleRoot(Segment s, Path *p);
    void findParentPath(Path *p);
    void markNeighborBelow(Hexagon *hex);

    /// Map of hexagons based on keys.
    typedef std::unordered_map<HexKey, Hexagon> HexMap;
    HexMap m_hexes;
    /// Set of dense hexagons with non-dense neighbors above.
    typedef std::set<Hexagon *, HexCompare> HexSet;
    HexSet m_pos_roots;
    /// Map of roots and their associated paths.
    typedef std::unordered_map<Hexagon *, Path *> HexPathMap;
    HexPathMap m_hex_paths;
    /// List of paths
    std::vector<Path *> m_paths;
    /// Number of points that must lie in a hexagon for it to be interesting.
    int m_dense_limit;
    /// Minimum y - 1.
    int m_miny;
    /// Vector of points to use to determine hex height.
    std::vector<Point> m_sample;
    /// Maximum sample size.
    unsigned m_maxSample;
};

} // namespace hexer
} // namespace pdal

