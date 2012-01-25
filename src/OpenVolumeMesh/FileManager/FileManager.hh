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
 *   $Revision$                                                          *
 *   $Date$                   *
 *   $LastChangedBy$                                                *
 *                                                                           *
\*===========================================================================*/

#ifndef FILEMANAGER_HH_
#define FILEMANAGER_HH_

#include <string>
#include <fstream>

namespace OpenVolumeMesh {

namespace IO {

/**
 * \class FileManager
 * \brief Read/Write mesh data from/to files
 *
 * \todo Implement binary file support
 */

class FileManager {
public:

  /// Default constructor
  FileManager();

  /// Default destructor
  ~FileManager();

  /**
   * \brief Read a mesh from a file
   *
   *  Returns true if the file was successfully read. The mesh
   *  is stored in parameter _mesh. If something goes wrong,
   *  this function returns false.
   *
   * @param _filename       The file that is to be read
   * @param _mesh           A reference to an OpenVolumeMesh instance
   * @param _topologyCheck  Pass true if you want to perform a topology check
   *                        each time an entity is added (slower performance)
   * @param _computeBottomUpAdjacencies Pass true if you want the file manager
   *                                    to directly compute the bottom-up adjacencies
   *                                    for the mesh. (Note: These are needed for
   *                                    some iterators to work, see documentation)
   * @param _computeFaceNormals Pass true if you want the file manager
   *                            to directly compute the face normals.
   */
  template <class MeshT>
  bool readFile(const std::string& _filename, MeshT& _mesh,
      bool _topologyCheck = true,
      bool _computeBottomUpAdjacencies = true,
      bool _computeFaceNormals = true) const;

  /**
   * \brief Write a mesh to a file
   *
   *  Returns true if the file was successfully written. The mesh
   *  is passed as parameter _mesh. If something goes wrong,
   *  this function returns false.
   *
   * @param _filename The file that is to be stored
   * @param _mesh     A const reference to an OpenVolumeMesh instance
   */
  template <class MeshT>
  bool writeFile(const std::string& _filename, const MeshT& _mesh) const;

  /**
   * \brief Test whether given file contains a hexahedral mesh
   */
  bool isHexahedralMesh(const std::string& _filename) const;

private:

  // Remove leading and trailing whitespaces
  void trimString(std::string& _string) const;

  // Get quoted text out of a string
  void extractQuotedText(std::string& _string) const;

  // Get a whole line from file
  bool getCleanLine(std::istream& ifs, std::string& _string, bool _skipEmptyLines = true) const;

  // Parse properties
  template<class MeshT, typename IterT>
  void parseVertexProperties(std::ifstream& _iff, std::stringstream& _sstr, const std::string& _identifier, MeshT& _mesh,
                                  const IterT& _begin, const IterT& _end) const;

  template<class MeshT, typename IterT>
  void parseEdgeProperties(std::ifstream& _iff, std::stringstream& _sstr, const std::string& _identifier, MeshT& _mesh,
                                  const IterT& _begin, const IterT& _end) const;

  template<class MeshT, typename IterT>
  void parseHalfEdgeProperties(std::ifstream& _iff, std::stringstream& _sstr, const std::string& _identifier, MeshT& _mesh,
                                  const IterT& _begin, const IterT& _end) const;

  template<class MeshT, typename IterT>
  void parseFaceProperties(std::ifstream& _iff, std::stringstream& _sstr, const std::string& _identifier, MeshT& _mesh,
                                  const IterT& _begin, const IterT& _end) const;

  template<class MeshT, typename IterT>
  void parseHalfFaceProperties(std::ifstream& _iff, std::stringstream& _sstr, const std::string& _identifier, MeshT& _mesh,
                                  const IterT& _begin, const IterT& _end) const;

  template<class MeshT, typename IterT>
  void parseCellProperties(std::ifstream& _iff, std::stringstream& _sstr, const std::string& _identifier, MeshT& _mesh,
                                  const IterT& _begin, const IterT& _end) const;

  // Add and initialize property
  template<class MeshT, typename PropHandleT, typename PropT, typename IterT>
  void initializeProperty(std::ifstream& _iff, MeshT& _mesh, const std::string& _s_tmp,
                          const IterT& _begin, const IterT& _end) const;

  template<typename PropIterT>
  void writePropertySection(std::ofstream& _ofs, const std::string& _identifier,
                            const PropIterT& _begin, const PropIterT& _end) const;
};

} // Namespace IO

} // Namespace FileManager

#if defined(INCLUDE_TEMPLATES) && !defined(FILEMANAGERT_CC)
#include "FileManagerT.cc"
#endif

#endif /* FILEMANAGER_HH_ */
