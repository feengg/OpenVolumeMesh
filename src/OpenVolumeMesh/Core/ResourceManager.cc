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

#include "ResourceManager.hh"
#include "BaseProperty.hh"

namespace OpenVolumeMesh {

ResourceManager::ResourceManager() {
}

ResourceManager::~ResourceManager() {

    // Delete all persistent properties
    for(std::vector<BaseProperty*>::iterator it = vertex_props_.begin();
            it != vertex_props_.end(); ++it) {

        (*it)->set_non_persistent();
        (*it)->set_ref_count(1u);
        delete *it;
    }
    vertex_props_.clear();
    for(std::vector<BaseProperty*>::iterator it = edge_props_.begin();
            it != edge_props_.end(); ++it) {

        (*it)->set_non_persistent();
        (*it)->set_ref_count(1u);
        delete *it;
    }
    edge_props_.clear();
    for(std::vector<BaseProperty*>::iterator it = halfedge_props_.begin();
            it != halfedge_props_.end(); ++it) {

        (*it)->set_non_persistent();
        (*it)->set_ref_count(1u);
        delete *it;
    }
    halfedge_props_.clear();
    for(std::vector<BaseProperty*>::iterator it = face_props_.begin();
            it != face_props_.end(); ++it) {

        (*it)->set_non_persistent();
        (*it)->set_ref_count(1u);
        delete *it;
    }
    face_props_.clear();
    for(std::vector<BaseProperty*>::iterator it = halfface_props_.begin();
            it != halfface_props_.end(); ++it) {

        (*it)->set_non_persistent();
        (*it)->set_ref_count(1u);
        delete *it;
    }
    halfface_props_.clear();
    for(std::vector<BaseProperty*>::iterator it = cell_props_.begin();
            it != cell_props_.end(); ++it) {

        (*it)->set_non_persistent();
        (*it)->set_ref_count(1u);
        delete *it;
    }
    cell_props_.clear();
    for(std::vector<BaseProperty*>::iterator it = mesh_props_.begin();
            it != mesh_props_.end(); ++it) {

        (*it)->set_non_persistent();
        (*it)->set_ref_count(1u);
        delete *it;
    }
    mesh_props_.clear();

}

void ResourceManager::resize_vprops(unsigned int _nv) {

    for(std::vector<BaseProperty*>::iterator it = vertex_props_.begin();
            it != vertex_props_.end(); ++it) {
        (*it)->resize(_nv);
    }
}

void ResourceManager::resize_eprops(unsigned int _ne) {

    for(std::vector<BaseProperty*>::iterator it = edge_props_.begin();
            it != edge_props_.end(); ++it) {
        (*it)->resize(_ne);
    }
    for(std::vector<BaseProperty*>::iterator it = halfedge_props_.begin();
            it != halfedge_props_.end(); ++it) {
        (*it)->resize(2u*_ne);
    }
}

void ResourceManager::resize_fprops(unsigned int _nf) {

    for(std::vector<BaseProperty*>::iterator it = face_props_.begin();
            it != face_props_.end(); ++it) {
        (*it)->resize(_nf);
    }
    for(std::vector<BaseProperty*>::iterator it = halfface_props_.begin();
            it != halfface_props_.end(); ++it) {
        (*it)->resize(2u*_nf);
    }
}

void ResourceManager::resize_cprops(unsigned int _nc) {

    for(std::vector<BaseProperty*>::iterator it = mesh_props_.begin();
            it != mesh_props_.end(); ++it) {
        (*it)->resize(_nc);
    }
}

void ResourceManager::vertex_deleted(const VertexHandle& _h) {

    for(std::vector<BaseProperty*>::iterator it = vertex_props_.begin();
            it != vertex_props_.end(); ++it) {
        (*it)->delete_element(_h.idx());
    }
}

void ResourceManager::edge_deleted(const EdgeHandle& _h) {

    for(std::vector<BaseProperty*>::iterator it = edge_props_.begin();
            it != edge_props_.end(); ++it) {
        (*it)->delete_element(_h.idx());
    }
    for(std::vector<BaseProperty*>::iterator it = halfedge_props_.begin();
            it != halfedge_props_.end(); ++it) {
        (*it)->delete_element(_h.idx()*2 + 1);
        (*it)->delete_element(_h.idx()*2);
    }
}

void ResourceManager::face_deleted(const FaceHandle& _h) {

    for(std::vector<BaseProperty*>::iterator it = face_props_.begin();
            it != face_props_.end(); ++it) {
        (*it)->delete_element(_h.idx());
    }
    for(std::vector<BaseProperty*>::iterator it = halfface_props_.begin();
            it != halfface_props_.end(); ++it) {
        (*it)->delete_element(_h.idx()*2 + 1);
        (*it)->delete_element(_h.idx()*2);
    }
}

void ResourceManager::cell_deleted(const CellHandle& _h) {

    for(std::vector<BaseProperty*>::iterator it = cell_props_.begin();
            it != cell_props_.end(); ++it) {
        (*it)->delete_element(_h.idx());
    }
}

void ResourceManager::released_property(VertexPropHandle _handle) {

    delete (*(vertex_props_.begin() + _handle.idx()));
    std::vector<BaseProperty*>::iterator it = vertex_props_.erase(vertex_props_.begin() + _handle.idx());
    VertexPropHandle decrHandle(_handle.idx() - 1);
    for(; it < vertex_props_.end(); ++it) {
        (*it)->set_handle(decrHandle);
    }
}

void ResourceManager::released_property(EdgePropHandle _handle) {

    delete (*(edge_props_.begin() + _handle.idx()));
    std::vector<BaseProperty*>::iterator it = edge_props_.erase(edge_props_.begin() + _handle.idx());
    EdgePropHandle decrHandle(_handle.idx() - 1);
    for(; it < edge_props_.end(); ++it) {
        (*it)->set_handle(decrHandle);
    }
}

void ResourceManager::released_property(HalfEdgePropHandle _handle) {

    delete (*(halfedge_props_.begin() + _handle.idx()));
    std::vector<BaseProperty*>::iterator it = halfedge_props_.erase(halfedge_props_.begin() + _handle.idx());
    HalfEdgePropHandle decrHandle(_handle.idx() - 1);
    for(; it < halfedge_props_.end(); ++it) {
        (*it)->set_handle(decrHandle);
    }
}

void ResourceManager::released_property(FacePropHandle _handle) {

    delete (*(face_props_.begin() + _handle.idx()));
    std::vector<BaseProperty*>::iterator it = face_props_.erase(face_props_.begin() + _handle.idx());
    FacePropHandle decrHandle(_handle.idx() - 1);
    for(; it < face_props_.end(); ++it) {
        (*it)->set_handle(decrHandle);
    }
}

void ResourceManager::released_property(HalfFacePropHandle _handle) {

    delete (*(halfface_props_.begin() + _handle.idx()));
    std::vector<BaseProperty*>::iterator it = halfface_props_.erase(halfface_props_.begin() + _handle.idx());
    HalfFacePropHandle decrHandle(_handle.idx() - 1);
    for(; it < halfface_props_.end(); ++it) {
        (*it)->set_handle(decrHandle);
    }
}

void ResourceManager::released_property(CellPropHandle _handle) {

    delete (*(cell_props_.begin() + _handle.idx()));
    std::vector<BaseProperty*>::iterator it = cell_props_.erase(cell_props_.begin() + _handle.idx());
    CellPropHandle decrHandle(_handle.idx() - 1);
    for(; it < cell_props_.end(); ++it) {
        (*it)->set_handle(decrHandle);
    }
}

void ResourceManager::released_property(MeshPropHandle _handle) {

    delete (*(mesh_props_.begin() + _handle.idx()));
    std::vector<BaseProperty*>::iterator it = mesh_props_.erase(mesh_props_.begin() + _handle.idx());
    MeshPropHandle decrHandle(_handle.idx() - 1);
    for(; it < mesh_props_.end(); ++it) {
        (*it)->set_handle(decrHandle);
    }
}

void ResourceManager::set_persistent_copy(VertexPropHandle _handle) {
    (*(vertex_props_.begin() + _handle.idx()))->set_master_copy(true);
}

void ResourceManager::set_persistent_copy(EdgePropHandle _handle) {
    (*(edge_props_.begin() + _handle.idx()))->set_master_copy(true);
}

void ResourceManager::set_persistent_copy(HalfEdgePropHandle _handle) {
    (*(halfedge_props_.begin() + _handle.idx()))->set_master_copy(true);
}

void ResourceManager::set_persistent_copy(FacePropHandle _handle) {
    (*(face_props_.begin() + _handle.idx()))->set_master_copy(true);
}

void ResourceManager::set_persistent_copy(HalfFacePropHandle _handle) {
    (*(halfface_props_.begin() + _handle.idx()))->set_master_copy(true);
}

void ResourceManager::set_persistent_copy(CellPropHandle _handle) {
    (*(cell_props_.begin() + _handle.idx()))->set_master_copy(true);
}

void ResourceManager::set_persistent_copy(MeshPropHandle _handle) {
    (*(mesh_props_.begin() + _handle.idx()))->set_master_copy(true);
}

} // Namespace OpenVolumeMesh