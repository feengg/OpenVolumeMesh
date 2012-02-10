/*===========================================================================*\
 *                                                                           *
 *                            OpenVolumeMesh                                 *
 *        Copyright (C) 2011 by Computer Graphics Group, RWTH Aachen         *
 *                        www.openvolumemesh.org                             *
 *                                                                           *
 *---------------------------------------------------------------------------*
 *  This file is part of OpenVolumeMesh.                                     *
 *                                                                           *
 *  OpenVolumeMesh is free software: you can redistribute it and/or modify   *
 *  it under the terms of the GNU Lesser General Public License as           *
 *  published by the Free Software Foundation, either version 3 of           *
 *  the License, or (at your option) any later version with the              *
 *  following exceptions:                                                    *
 *                                                                           *
 *  If other files instantiate templates or use macros                       *
 *  or inline functions from this file, or you compile this file and         *
 *  link it with other files to produce an executable, this file does        *
 *  not by itself cause the resulting executable to be covered by the        *
 *  GNU Lesser General Public License. This exception does not however       *
 *  invalidate any other reasons why the executable file might be            *
 *  covered by the GNU Lesser General Public License.                        *
 *                                                                           *
 *  OpenVolumeMesh is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
 *  GNU Lesser General Public License for more details.                      *
 *                                                                           *
 *  You should have received a copy of the GNU LesserGeneral Public          *
 *  License along with OpenVolumeMesh.  If not,                              *
 *  see <http://www.gnu.org/licenses/>.                                      *
 *                                                                           *
\*===========================================================================*/

/*===========================================================================*\
 *                                                                           *
 *   $Revision$                                                         *
 *   $Date$                    *
 *   $LastChangedBy$                                                *
 *                                                                           *
\*===========================================================================*/

#ifndef NORMALATTRIB_HH_
#define NORMALATTRIB_HH_

#include <cassert>

#include "../Core/OpenVolumeMeshHandle.hh"
#include "OpenVolumeMeshStatus.hh"
#include "../Core/PropertyDefines.hh"

namespace OpenVolumeMesh {

// Forward declaration
template<class VecT>
class GeometryKernel;

template <class VecT>
class NormalAttrib {
public:

    NormalAttrib(GeometryKernel<VecT>& _kernel);
    virtual ~NormalAttrib();

    /** \brief A simple heuristic to estimate the vertex normals
     *
     * This function takes the vertices' surrounding outside
     * face normals into account and computes an average
     * out of it.
     */
    void update_vertex_normals();

    /** \brief Compute face normals
     *
     * This is accomplished by taking two adjacent half-edges
     * that are incident to the faces and compute their
     * cross product. Note that this method looses accuracy
     * in case the faces in question is not planar.
     */
    void update_face_normals();

    const VecT& operator[](const VertexHandle& _h) const {
        assert((unsigned int)_h.idx < v_normals_.size());
        return v_normals_[_h.idx()];
    }

    const VecT& operator[](const FaceHandle& _h) const {
        assert((unsigned int)_h.idx < f_normals_.size());
        return f_normals_[_h.idx()];
    }

    VecT& operator[](const VertexHandle& _h) {
        assert((unsigned int)_h.idx < kernel_.n_vertices());
        return v_normals_[_h.idx()];
    }

    VecT& operator[](const FaceHandle& _h) {
        assert((unsigned int)_h.idx() < kernel_.n_faces());
        return f_normals_[_h.idx()];
    }

private:

    void compute_vertex_normal(const VertexHandle& _vh);

    void compute_face_normal(const FaceHandle& _fh);

    GeometryKernel<VecT>& kernel_;

    VertexPropertyT<VecT> v_normals_;
    FacePropertyT<VecT> f_normals_;
};

} // Namespace OpenVolumeMesh

#if defined(INCLUDE_TEMPLATES) && !defined(NORMALATTRIBT_CC)
#include "NormalAttribT.cc"
#endif

#endif /* NORMALATTRIB_HH_ */
